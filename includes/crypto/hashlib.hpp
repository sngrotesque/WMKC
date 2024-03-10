#include <config/wmkc.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_HASH
#define WMKC_CPP_HASH
#include <wmkc_exception.hpp>
#include <wmkc_binascii.hpp>
#include <wmkc_memory.hpp>
#include <openssl/evp.h>

namespace wmkc {
    class hashlib {
        private:
            EVP_MD_CTX *md_ctx;
            const EVP_MD *md;

        public:
            wByte digest[64 + 1]; // SHA-512
            wByte hexdigest[(64 << 1) + 1];
    };
}

#endif
#endif
