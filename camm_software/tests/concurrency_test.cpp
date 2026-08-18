#include "camm/ram_cache.hpp"
#include "camm/store.hpp"
#include <cassert>
#include <memory>
#include <thread>
int main(){camm::RamCache c(1024*1024);camm::Buffer d(4096,9);camm::Key k;k=camm::finalize_key(k,d);c.put(k,std::make_shared<camm::Buffer>(d));std::thread a([&]{std::shared_ptr<const camm::Buffer>o;assert(c.get(k,o));}),b([&]{std::shared_ptr<const camm::Buffer>o;assert(c.get(k,o));});a.join();b.join();camm::AsyncExecutor e;assert(e.submit([]{return true;}).get());}
