#include "camm/store.hpp"
#include <sys/stat.h>
namespace camm{bool cache_file_exists(const std::string&p){struct stat s{};return ::stat(p.c_str(),&s)==0;}}
