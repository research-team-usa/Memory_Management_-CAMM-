#include "camm/store.hpp"
#include "camm/ram_cache.hpp"
#include "camm/policy.hpp"
#include "camm/metrics.hpp"
#include <iostream>
#include <memory>
#include <string>
int main(){try{std::string s="CAMM complete project";camm::Buffer d(s.begin(),s.end());camm::Key raw;raw.model=1;auto key=camm::finalize_key(raw,d);camm::DiskStore store("camm-cache.bin",256*1024*1024);if(!store.put(raw,d))return 2;store.flush();camm::Buffer out;if(!store.get(key,out))return 3;camm::RamCache ram(64*1024*1024);ram.put(key,std::make_shared<camm::Buffer>(out));std::cout<<std::string(out.begin(),out.end())<<"\n";return out==d?0:4;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 1;}}
