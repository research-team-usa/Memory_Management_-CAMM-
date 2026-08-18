#pragma once
#include "key.hpp"
#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
namespace camm {
struct StoreStats{std::uint64_t objects=0,bytes=0,reads=0,writes=0,deduplicated=0,corrupt=0;};
class DiskStore{
public:
 DiskStore(std::string,std::uint64_t limit_bytes=0);~DiskStore();
 DiskStore(const DiskStore&)=delete;DiskStore&operator=(const DiskStore&)=delete;
 bool put(const Key&,const Buffer&);bool get(const Key&,Buffer&);bool contains(const Key&)const;bool erase(const Key&);void flush();StoreStats stats()const;
private:
 struct Location{std::uint64_t offset=0,size=0;bool deleted=false;};
 void rebuild();void read_all(void*,std::size_t,std::uint64_t)const;void write_all(const void*,std::size_t,std::uint64_t);
 std::string path_;int fd_=-1;std::uint64_t limit_=0,end_=0;mutable std::mutex mutex_;std::unordered_map<Key,Location,KeyHash> index_;StoreStats stats_;
};
class AsyncExecutor{
public:explicit AsyncExecutor(std::size_t workers=1);~AsyncExecutor();std::future<bool> submit(std::function<bool()>);
private:void loop();std::mutex mutex_;std::condition_variable cv_;std::queue<std::function<void()>> jobs_;bool stop_=false;std::vector<std::thread> workers_;
};
bool cache_file_exists(const std::string&);
}
