#include "camm/observer.hpp"
#include <chrono>
#include <fstream>
#include <unistd.h>
namespace camm{SystemObserver::SystemObserver(std::uint64_t i):interval_(i){}SystemObserver::~SystemObserver(){stop();}void SystemObserver::start(){bool e=false;if(!running_.compare_exchange_strong(e,true))return;worker_=std::thread([this]{loop();});}void SystemObserver::stop(){running_=false;if(worker_.joinable())worker_.join();}SystemSample SystemObserver::read()const{std::ifstream f("/proc/self/statm");std::uint64_t v=0,r=0;f>>v>>r;long p=::sysconf(_SC_PAGESIZE);return p>0?SystemSample{r*static_cast<std::uint64_t>(p),v*static_cast<std::uint64_t>(p)}:SystemSample{};}void SystemObserver::loop(){while(running_){auto s=read();resident_=s.resident_bytes;virtual_=s.virtual_bytes;std::this_thread::sleep_for(std::chrono::milliseconds(interval_));}}SystemSample SystemObserver::latest()const{return{resident_.load(),virtual_.load()};}}
