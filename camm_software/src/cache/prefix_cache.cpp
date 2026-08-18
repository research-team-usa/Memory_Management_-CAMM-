#include "camm/ram_cache.hpp"
#include <algorithm>
namespace camm{std::size_t common_prefix_length(const std::vector<std::uint32_t>&a,const std::vector<std::uint32_t>&b){std::size_t n=std::min(a.size(),b.size()),i=0;while(i<n&&a[i]==b[i])++i;return i;}bool prefix_is_worth_caching(std::size_t n,std::uint64_t t,std::size_t mn,std::uint64_t mt){return n>=mn&&t>=mt;}}
