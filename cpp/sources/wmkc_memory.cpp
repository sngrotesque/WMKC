#include <wmkc_memory.hpp>

wmkcVoid wmkc::memory_zero(wmkcVoid *p, wmkcSize n)
{
    memset(p, 0x00, n);
}

wmkcVoid wmkc::memory_secure(wmkcVoid *p, wmkcSize n)
{
#   if defined(WMKC_PLATFORM_WINOS)
    SecureZeroMemory(p, n);
#   elif defined(WMKC_PLATFORM_LINUX)
    explicit_bzero(p, n);
#   endif
}
