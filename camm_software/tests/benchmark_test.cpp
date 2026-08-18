#include "camm/store.hpp"
#include <chrono>
#include <cstdio>
#include <iostream>
int main(){std::remove("benchmark.bin");camm::Buffer d(16*1024*1024,17);camm::Key r;auto k=camm::finalize_key(r,d);auto a=std::chrono::steady_clock::now();camm::DiskStore s("benchmark.bin",64*1024*1024);s.put(r,d);s.flush();auto b=std::chrono::steady_clock::now();camm::Buffer o;s.get(k,o);auto c=std::chrono::steady_clock::now();std::cout<<"Unvalidierter lokaler Test: write_ms="<<std::chrono::duration_cast<std::chrono::milliseconds>(b-a).count()<<" read_ms="<<std::chrono::duration_cast<std::chrono::milliseconds>(c-b).count()<<"\n";std::remove("benchmark.bin");return o==d?0:1;}
