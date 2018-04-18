#ifndef GREGJM_Z80_UTILITIES_HPP
#define GREGJM_Z80_UTILITIES_HPP

#include <iostream>

namespace gregjm {
namespace z80 {

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& nl(std::basic_ostream<CharT, Traits> &os) {
    return os.put(os.widen('\n'));
}

} // namespace z80
} // namespace gregjm

#endif
