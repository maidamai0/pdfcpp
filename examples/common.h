#pragma once

#include <string>

#ifndef RESOURCE_PATH
#define RESOURCE_PATH "./"
#endif

[[maybe_unused]] inline static auto full_path(std::string &&file_name) {
  return std::string(RESOURCE_PATH) + file_name;
}
