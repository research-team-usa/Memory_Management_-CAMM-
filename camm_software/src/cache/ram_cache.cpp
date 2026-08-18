#include "camm/ram_cache.hpp"
namespace camm{
RamCache::RamCache(std::uint64_t l):limit_(l){stats_.limit=l;}
bool RamCache::get(const Key&k,std::shared_ptr<const Buffer>&o){std::lock_guard<std::mutex>g(mutex_);auto i=entries_.find(k);if(i==entries_.end()){++stats_.misses;return false;}lru_.erase(i->second.pos);lru_.push_front(k);i->second.pos=lru_.begin();o=i->second.data;++stats_.hits;return true;}
void RamCache::put(const Key&k,std::shared_ptr<Buffer>d){if(!d)return;std::lock_guard<std::mutex>g(mutex_);auto i=entries_.find(k);if(i!=entries_.end()){used_-=i->second.data->size();lru_.erase(i->second.pos);entries_.erase(i);}lru_.push_front(k);used_+=d->size();entries_.emplace(k,Entry{std::move(d),lru_.begin()});trim_locked();stats_.used=used_;}
void RamCache::trim_locked(){while(used_>limit_&&!lru_.empty()){Key k=lru_.back();auto i=entries_.find(k);if(i!=entries_.end()){used_-=i->second.data->size();entries_.erase(i);++stats_.evictions;}lru_.pop_back();}}
void RamCache::erase(const Key&k){std::lock_guard<std::mutex>g(mutex_);auto i=entries_.find(k);if(i==entries_.end())return;used_-=i->second.data->size();lru_.erase(i->second.pos);entries_.erase(i);stats_.used=used_;}void RamCache::set_limit(std::uint64_t n){std::lock_guard<std::mutex>g(mutex_);limit_=n;trim_locked();stats_.used=used_;stats_.limit=limit_;}CacheStats RamCache::stats()const{std::lock_guard<std::mutex>g(mutex_);auto s=stats_;s.used=used_;s.limit=limit_;return s;}
}
