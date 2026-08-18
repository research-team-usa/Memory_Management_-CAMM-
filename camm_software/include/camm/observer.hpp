#pragma once
#include <atomic>
#include <cstdint>
#include <string>
#include <thread>
namespace camm{
enum class ObserverMode{Disabled,Summary,Sampling,Diagnostic};
struct SystemSample{std::uint64_t resident_bytes=0,virtual_bytes=0;};
class SystemObserver{public:explicit SystemObserver(std::uint64_t interval_ms=1000);~SystemObserver();void start();void stop();SystemSample latest()const;private:void loop();SystemSample read()const;std::uint64_t interval_;std::atomic<bool>running_{false};std::atomic<std::uint64_t>resident_{0},virtual_{0};std::thread worker_;};
class CuptiObserver{public:explicit CuptiObserver(ObserverMode);bool start();void stop();bool active()const noexcept;std::string status()const;private:ObserverMode mode_;bool active_=false;};
}
