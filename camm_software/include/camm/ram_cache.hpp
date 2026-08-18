#pragma once
#include "key.hpp"
#include <list>
#include <future>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
namespace camm {
struct CacheStats{std::uint64_t hits=0,misses=0,evictions=0,used=0,limit=0;};
class RamCache{
public:explicit RamCache(std::uint64_t);bool get(const Key&,std::shared_ptr<const Buffer>&);void put(const Key&,std::shared_ptr<Buffer>);void erase(const Key&);void set_limit(std::uint64_t);CacheStats stats()const;
private:struct Entry{std::shared_ptr<Buffer>data;std::list<Key>::iterator pos;};void trim_locked();mutable std::mutex mutex_;std::uint64_t limit_=0,used_=0;std::list<Key>lru_;std::unordered_map<Key,Entry,KeyHash>entries_;CacheStats stats_;
};
std::size_t common_prefix_length(const std::vector<std::uint32_t>&,const std::vector<std::uint32_t>&);
bool prefix_is_worth_caching(std::size_t,std::uint64_t,std::size_t,std::uint64_t);
class SingleFlight{
public:using Result=Buffer;std::shared_future<Result>execute(const Key&,std::function<Result()>);
private:void remove(const Key&);std::mutex mutex_;std::unordered_map<Key,std::shared_future<Result>,KeyHash>operations_;
};
}
