#pragma once

namespace dd {

class NoCopy {
public:
  NoCopy() = default;
  NoCopy(const NoCopy &) = delete;
};

} // namespace dd
