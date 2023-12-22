#pragma once

#include <string_view>

namespace dd {

[[noreturn]] void fatal(std::string_view fail_message);

inline void ensure_or_fatal(bool condition, std::string_view fail_message) {
    if (!condition) {
        fatal(fail_message);
    }
}

} // namespace dd
