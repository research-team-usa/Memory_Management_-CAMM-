#pragma once
#include <cstdint>
namespace camm{
struct PolicyConfig{std::uint64_t min_size=64*1024,min_recompute_us=5000;std::uint32_t min_reuse=2;double advantage=0.20;};
struct Cost{std::uint64_t restore_us=0,recompute_us=0,size=0,reuse=0;bool compatible=false;};
class AdaptivePolicy{public:explicit AdaptivePolicy(PolicyConfig={});bool should_restore(const Cost&)const;bool keep_ram(const Cost&)const;bool persist(const Cost&)const;private:PolicyConfig config_;};
}
