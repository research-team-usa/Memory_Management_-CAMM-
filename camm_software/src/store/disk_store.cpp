#include "camm/store.hpp"
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
namespace camm{namespace{constexpr std::uint64_t magic=0x43414d4d52454331ULL;constexpr std::uint32_t active=1;
#pragma pack(push,1)
struct Record{std::uint64_t magic;std::uint32_t flags,reserved;Key key;std::uint64_t payload_size,checksum;};
#pragma pack(pop)
std::runtime_error err(const char*w){return std::runtime_error(std::string(w)+": "+std::strerror(errno));}
void mix(std::size_t&s,std::uint64_t v){s^=std::hash<std::uint64_t>{}(v)+0x9e3779b97f4a7c15ULL+(s<<6U)+(s>>2U);}}
bool Key::operator==(const Key&o)const noexcept{return format_version==o.format_version&&model==o.model&&tokenizer==o.tokenizer&&runtime==o.runtime&&context==o.context&&type==o.type&&layer==o.layer&&sequence==o.sequence&&data_type==o.data_type&&token_start==o.token_start&&token_count==o.token_count&&byte_count==o.byte_count&&hash1==o.hash1&&hash2==o.hash2;}
std::size_t KeyHash::operator()(const Key&k)const noexcept{std::size_t s=0;mix(s,k.format_version);mix(s,k.model);mix(s,k.tokenizer);mix(s,k.runtime);mix(s,k.context);mix(s,static_cast<std::uint64_t>(k.type));mix(s,k.layer);mix(s,k.sequence);mix(s,k.data_type);mix(s,k.token_start);mix(s,k.token_count);mix(s,k.byte_count);mix(s,k.hash1);mix(s,k.hash2);return s;}
std::uint64_t hash_primary(const void*d,std::size_t n)noexcept{auto*p=static_cast<const std::uint8_t*>(d);std::uint64_t h=14695981039346656037ULL;for(std::size_t i=0;i<n;++i){h^=p[i];h*=1099511628211ULL;}return h;}
std::uint64_t hash_secondary(const void*d,std::size_t n)noexcept{auto*p=static_cast<const std::uint8_t*>(d);std::uint64_t h=0x9e3779b97f4a7c15ULL;for(std::size_t i=0;i<n;++i)h^=static_cast<std::uint64_t>(p[i])+0x9e3779b97f4a7c15ULL+(h<<6U)+(h>>2U);return h;}
Key finalize_key(Key k,const Buffer&d){k.byte_count=d.size();k.hash1=hash_primary(d.data(),d.size());k.hash2=hash_secondary(d.data(),d.size());return k;}
DiskStore::DiskStore(std::string p,std::uint64_t l):path_(std::move(p)),limit_(l){fd_=::open(path_.c_str(),O_RDWR|O_CREAT|O_CLOEXEC,0600);if(fd_<0)throw err("open");try{rebuild();}catch(...){::close(fd_);throw;}}
DiskStore::~DiskStore(){if(fd_>=0){::fsync(fd_);::close(fd_);}}
void DiskStore::read_all(void*p,std::size_t n,std::uint64_t o)const{auto*b=static_cast<std::uint8_t*>(p);for(std::size_t x=0;x<n;){ssize_t r=::pread(fd_,b+x,n-x,static_cast<off_t>(o+x));if(r<0){if(errno==EINTR)continue;throw err("pread");}if(r==0)throw std::runtime_error("unexpected EOF");x+=static_cast<std::size_t>(r);}}
void DiskStore::write_all(const void*p,std::size_t n,std::uint64_t o){auto*b=static_cast<const std::uint8_t*>(p);for(std::size_t x=0;x<n;){ssize_t r=::pwrite(fd_,b+x,n-x,static_cast<off_t>(o+x));if(r<0){if(errno==EINTR)continue;throw err("pwrite");}if(r==0)throw std::runtime_error("zero write");x+=static_cast<std::size_t>(r);}}
void DiskStore::rebuild(){struct stat st{};if(::fstat(fd_,&st)<0)throw err("fstat");std::uint64_t size=st.st_size,off=0;while(off<size){if(size-off<sizeof(Record)){::ftruncate(fd_,off);break;}Record r{};read_all(&r,sizeof(r),off);if(r.magic!=magic||r.payload_size>size-off-sizeof(r)){++stats_.corrupt;::ftruncate(fd_,off);break;}auto poff=off+sizeof(r);if(r.flags&active){index_[r.key]={poff,r.payload_size,false};++stats_.objects;stats_.bytes+=r.payload_size;}off=poff+r.payload_size;}end_=off;}
bool DiskStore::put(const Key&raw,const Buffer&d){Key k=finalize_key(raw,d);std::lock_guard<std::mutex>g(mutex_);auto it=index_.find(k);if(it!=index_.end()&&!it->second.deleted){Buffer old(it->second.size);if(!old.empty())read_all(old.data(),old.size(),it->second.offset);if(old==d){++stats_.deduplicated;return true;}}auto need=sizeof(Record)+d.size();if(limit_&&end_+need>limit_)return false;Record r{magic,active,0,k,d.size(),k.hash2};auto poff=end_+sizeof(r);write_all(&r,sizeof(r),end_);if(!d.empty())write_all(d.data(),d.size(),poff);index_[k]={poff,d.size(),false};end_=poff+d.size();++stats_.objects;++stats_.writes;stats_.bytes+=d.size();return true;}
bool DiskStore::get(const Key&k,Buffer&out){std::lock_guard<std::mutex>g(mutex_);auto it=index_.find(k);if(it==index_.end()||it->second.deleted)return false;out.resize(it->second.size);if(!out.empty())read_all(out.data(),out.size(),it->second.offset);if(hash_primary(out.data(),out.size())!=k.hash1||hash_secondary(out.data(),out.size())!=k.hash2){out.clear();++stats_.corrupt;return false;}++stats_.reads;return true;}
bool DiskStore::contains(const Key&k)const{std::lock_guard<std::mutex>g(mutex_);auto i=index_.find(k);return i!=index_.end()&&!i->second.deleted;}bool DiskStore::erase(const Key&k){std::lock_guard<std::mutex>g(mutex_);auto i=index_.find(k);if(i==index_.end())return false;i->second.deleted=true;return true;}void DiskStore::flush(){std::lock_guard<std::mutex>g(mutex_);if(::fsync(fd_)<0)throw err("fsync");}StoreStats DiskStore::stats()const{std::lock_guard<std::mutex>g(mutex_);return stats_;}
}
