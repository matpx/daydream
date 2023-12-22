#include "fatal.hpp"
#include <spdlog/spdlog.h>

namespace dd {

[[noreturn]] void fatal(std::string_view fail_message) {
    spdlog::error(fail_message);
    std::abort();
}

} // namespace dd
