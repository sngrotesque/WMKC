#include <wmkc_random.hpp>

constexpr wmkcByte BIT_BYTE_SWAP(wmkcByte x)
{
    return ((x & 0xf) << 4) ^ (x >> 4);
}

wmkc::random::random()
{
    this->seed();
}

wmkcVoid wmkc::random::seed()
{
    wmkc::Time timer;
    srand((unsigned)(timer.time() * 1.e6));
}

wmkcSize wmkc::random::rand()
{
    wmkcSize n = 0, num[32];
    wmkc_u32 x, count;
    for(x = 0; x < 32; ++x) {
        num[x] = ::rand() ^ (::rand() ^ (::rand() & ::rand()));
        n = n + (n ^ num[x]);
    }
    n = n + BIT_BYTE_SWAP(::rand() & 0x0f);
    for(count = 0; count < 32; ++count) {
        for(x = 0; x < 32; ++x) {
            num[x] = ::rand() ^ (::rand() ^ (::rand() & ::rand()));
        }
        n = (n + (n ^ num[count])) ^ count;
        n = (n + ::rand()) ^ BIT_BYTE_SWAP((count + (::rand() ^ (n - num[count]))) & 0xff);
    }
    return n;
}

wmkcSize wmkc::random::randint(wmkcSize min, wmkcSize max)
{
    return this->rand() % (max - min + 1) + min;
}

wmkcVoid wmkc::random::urandom(wmkcByte *buf, wmkcSize size)
{
    if(!buf || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::random::urandom", "buf or size is NULL.");
    }

#   if defined(WMKC_PLATFORM_WINOS)
    HCRYPTPROV hProv;
    if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        wmkc::exception(wmkcErr_ErrSysFunc, "wmkc::random::urandom",
            "CryptAcquireContext function returned an error code when called.");
    }
    if(!CryptGenRandom(hProv, size, buf)) {
        wmkc::exception(wmkcErr_ErrSysFunc, "wmkc::random::urandom",
            "CryptGenRandom function returned an error code when called.");
    }
    if(!CryptReleaseContext(hProv, 0)) {
        wmkc::exception(wmkcErr_ErrSysFunc, "wmkc::random::urandom",
            "CryptReleaseContext function returned an error code when called.");
    }
#   elif defined(WMKC_PLATFORM_LINUX)
    if(getrandom(buf, size, GRND_RANDOM) == wmkcErr_Err32) {
        wmkc::exception(wmkcErr_ErrSysFunc, "wmkc::random::urandom",
            "getrandom function returned an error code when called.");
    }
#   endif
}

std::string wmkc::random::urandom(wmkc_u32 size)
{
    if(!size) {
        return std::string();
    }
    wmkcByte *buf = new wmkcByte[size];
    if(!buf) {
        wmkc::exception(wmkcErr_ErrMemory, "wmkc::random::urandom",
            "Failed to allocate memory for buf.");
    }

    try {
        this->urandom(buf, size);
    } catch(std::exception &e) {
        delete[] buf;
        std::rethrow_exception(std::current_exception());
    }

    std::string result((wmkcChar *)buf, size);
    delete[] buf;
    return result;
}
