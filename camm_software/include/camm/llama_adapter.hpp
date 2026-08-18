#pragma once
#include "key.hpp"
#include <functional>
#include <string>
namespace camm{
struct RuntimeFingerprint{std::string llama_commit,backend,model,tokenizer,template_name;std::uint32_t context_size=0,kv_type=0;bool operator==(const RuntimeFingerprint&)const noexcept;};
class LlamaAdapter{public:using Export=std::function<bool(Buffer&)>;using Restore=std::function<bool(const Buffer&)>;explicit LlamaAdapter(RuntimeFingerprint);void callbacks(Export,Restore);bool save(Buffer&)const;bool load(const Buffer&)const;bool compatible(const RuntimeFingerprint&)const;Key prefix_key(const std::vector<std::uint32_t>&,std::uint64_t)const;private:RuntimeFingerprint current_;Export export_;Restore restore_;};
}
