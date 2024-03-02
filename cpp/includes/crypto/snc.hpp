#include <config/wmkc.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_SNC
#define WMKC_CPP_SNC
#include <wmkc_exception.hpp>
#include <wmkc_memory.hpp>

#define SNC_BLOCKLEN 32
#define SNC_NB 8
#define SNC_NK 4

static const wmkcByte SNC_NR[3] = {7, 8, 9};
static const wmkcByte SNC_KN[3] = {32, 64, 96};

namespace wmkc {
    namespace crypto {
        typedef wmkcByte state_t[SNC_NB][SNC_NK];
        enum class snc_keyMode {SNC_256, SNC_512, SNC_768};
        enum class snc_xcryptMode {ECB, CBC, CTR, CFB};

        class snc {
            private:
                wmkc_u16 numberRounds;
                wmkc_u16 subKey_length;
                snc_keyMode keyMode;
                wmkcByte iv[SNC_BLOCKLEN];
                wmkcByte rk[864];

                wmkcVoid subBytes(state_t *state);
                wmkcVoid rowsMix(state_t *state);
                wmkcVoid columnShift(state_t *state);

                wmkcVoid invSubBytes(state_t *state);
                wmkcVoid invRowsMix(state_t *state);
                wmkcVoid invColumnShift(state_t *state);

                wmkcVoid xorWithIv(state_t *buf, state_t *iv);

                wmkcVoid cipher(state_t *state, wmkcByte *roundKey);
                wmkcVoid invCipher(state_t *state, wmkcByte *roundKey);

                wmkcVoid keyExtension(wmkc_u16 keySize, wmkcByte *iv, wmkcByte *key);

                wmkcVoid ecb_encrypt(wmkcByte *content, wmkcSize size);
                wmkcVoid ecb_decrypt(wmkcByte *content, wmkcSize size);
                wmkcVoid cbc_encrypt(wmkcByte *content, wmkcSize size);
                wmkcVoid cbc_decrypt(wmkcByte *content, wmkcSize size);
                wmkcVoid ctr_xcrypt(wmkcByte *content, wmkcSize size);
                wmkcVoid cfb_encrypt(wmkcByte *content, wmkcSize size, wmkcSize segment_size);
                wmkcVoid cfb_decrypt(wmkcByte *content, wmkcSize size, wmkcSize segment_size);
            public:
                wmkc_u32 segmentSize;
                snc(const wmkcByte *keyBuf, const wmkcByte *ivBuf, snc_keyMode mode = snc_keyMode::SNC_256, wmkc_u32 segment_size = 256);
                ~snc();
                wmkcVoid encrypt(wmkcByte *content, wmkcSize size, snc_xcryptMode xcryptMode = snc_xcryptMode::CBC);
                wmkcVoid decrypt(wmkcByte *content, wmkcSize size, snc_xcryptMode xcryptMode = snc_xcryptMode::CBC);
                std::string encrypt(std::string content, snc_xcryptMode xcryptMode = snc_xcryptMode::CBC);
                std::string decrypt(std::string content, snc_xcryptMode xcryptMode = snc_xcryptMode::CBC);
        };
    }
}

#endif /* WMKC_CPP_SNC */
#endif /* WMKC_SUPPORT */
