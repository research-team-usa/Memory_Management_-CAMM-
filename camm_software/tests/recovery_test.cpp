#include "camm/store.hpp"
#include <cassert>
#include <cstdio>
int main(){std::remove("recovery.bin");camm::Buffer d(4096,7);camm::Key r;r.model=2;auto k=camm::finalize_key(r,d);{camm::DiskStore s("recovery.bin");assert(s.put(r,d));s.flush();}{camm::DiskStore s("recovery.bin");camm::Buffer o;assert(s.get(k,o)&&o==d);}std::remove("recovery.bin");}
