#include <config/wmkc.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_MEMORY
#define WMKC_CPP_MEMORY

#ifdef WMKC_PLATFORM_WINOS
#   include <Windows.h>
#endif

namespace wmkc {
    wmkcVoid memory_zero(wmkcVoid *p, wmkcSize n);
    wmkcVoid memory_secure(wmkcVoid *p, wmkcSize n);
}

#endif /* WMKC_CPP_MEMORY */
#endif /* WMKC_SUPPORT */
