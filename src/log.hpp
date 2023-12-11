#pragma once

#define FMT_HEADER_ONLY
#include <fmt/core.h>

#ifndef NDEBUG
#define DD_LOG_DEBUG(...) fmt::print(__VA_ARGS__); fmt::print("\n");
#else
#define DD_LOG_DEBUG(...)
#endif
#define DD_LOG_INFO(...) fmt::print(__VA_ARGS__); fmt::print("\n");
