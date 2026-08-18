#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>
namespace camm {
using Buffer=std::vector<std::uint8_t>;
enum class ObjectType:std::uint32_t{PromptPrefix=1,KvState=2,ContextCheckpoint=3,TensorBlock=4};
struct Key{
 std::uint64_t format_version=1,model=0,tokenizer=0,runtime=0,context=0;
 ObjectType type=ObjectType::PromptPrefix;
 std::uint32_t layer=0,sequence=0,data_type=0;
 std::uint64_t token_start=0,token_count=0,byte_count=0,hash1=0,hash2=0;
 bool operator==(const Key&)const noexcept;
};
struct KeyHash{std::size_t operator()(const Key&)const noexcept;};
std::uint64_t hash_primary(const void*,std::size_t)noexcept;
std::uint64_t hash_secondary(const void*,std::size_t)noexcept;
Key finalize_key(Key,const Buffer&);
}
