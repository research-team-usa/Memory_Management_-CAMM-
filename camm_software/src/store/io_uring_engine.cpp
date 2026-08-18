#include "camm/store.hpp"
#include <stdexcept>
namespace camm{
AsyncExecutor::AsyncExecutor(std::size_t n){if(n==0)n=1;for(std::size_t i=0;i<n;++i)workers_.emplace_back([this]{loop();});}
AsyncExecutor::~AsyncExecutor(){{std::lock_guard<std::mutex>g(mutex_);stop_=true;}cv_.notify_all();for(auto&t:workers_)if(t.joinable())t.join();}
std::future<bool>AsyncExecutor::submit(std::function<bool()>job){auto t=std::make_shared<std::packaged_task<bool()>>(std::move(job));auto f=t->get_future();{std::lock_guard<std::mutex>g(mutex_);if(stop_)throw std::runtime_error("executor stopped");jobs_.push([t]{(*t)();});}cv_.notify_one();return f;}
void AsyncExecutor::loop(){for(;;){std::function<void()>j;{std::unique_lock<std::mutex>l(mutex_);cv_.wait(l,[this]{return stop_||!jobs_.empty();});if(stop_&&jobs_.empty())return;j=std::move(jobs_.front());jobs_.pop();}j();}}
}
