#include "camm/store.hpp"
#include <cassert>
#include <cstdio>
int main(){std::remove("store.bin");camm::Buffer d{1,2,3};camm::Key r;r.model=1;auto k=camm::finalize_key(r,d);camm::DiskStore s("store.bin",1024*1024);assert(s.put(r,d));assert(s.put(r,d));camm::Buffer o;assert(s.get(k,o)&&o==d);std::remove("store.bin");}
