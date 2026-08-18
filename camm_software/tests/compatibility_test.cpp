#include "camm/llama_adapter.hpp"
#include <cassert>
int main(){camm::RuntimeFingerprint a{"x","cpu","m","t","c",4096,1},b=a;camm::LlamaAdapter x(a);assert(x.compatible(b));b.model="other";assert(!x.compatible(b));}
