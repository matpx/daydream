#pragma once

#define FMT_HEADER_ONLY
#include <fmt/core.h>

#ifndef NDEBUG
#define DD_LOG_DEBUG(MSG) fmt::print(MSG); fmt::print("\n");
#else
#define DD_LOG_DEBUG(MSG)
#endif
#define DD_LOG_INFO(MSG) fmt::print(MSG); fmt::print("\n");
