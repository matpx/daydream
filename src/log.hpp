#pragma once

#define FMT_HEADER_ONLY
#include <fmt/core.h>

namespace dd {

enum class LogServerity { DEBUG, INFO };

template <typename... T>
constexpr void log(const LogServerity severity, fmt::format_string<T...> fmt,
                   T &&...args) {
  switch (severity) {
  case LogServerity::DEBUG:
#ifdef NDEBUG
    return;
#endif
    fmt::print("DEBUG: ");
    break;
  case LogServerity::INFO:
    fmt::print("INFO: ");
    break;
  }

  fmt::print(fmt, args...);
  fmt::print("\n");
}

} // namespace dd
