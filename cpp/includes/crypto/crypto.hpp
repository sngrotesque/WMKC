#include <config/wmkc.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_CRYPTO
#include <vector>
#include <algorithm>
#include <random>

namespace wmkc {
    namespace crypto {
        wmkcVoid generateSbox(wmkcByte *sbox);
        wmkcVoid generateRSbox(wmkcByte *rsbox, wmkcByte *sbox);
    }
}

#endif
#endif
