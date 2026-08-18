#pragma once
#include <atomic>
#include <cstdint>
#include <string>
namespace camm{
struct MetricsSnapshot{std::uint64_t requests=0,ram_hits=0,disk_hits=0,misses=0,read_bytes=0,written_bytes=0;};
class Metrics{public:void request();void ram_hit(std::uint64_t);void disk_hit(std::uint64_t);void miss();void written(std::uint64_t);MetricsSnapshot snapshot()const;std::string report()const;private:std::atomic<std::uint64_t>requests_{0},ram_hits_{0},disk_hits_{0},misses_{0},read_bytes_{0},written_bytes_{0};};
}
