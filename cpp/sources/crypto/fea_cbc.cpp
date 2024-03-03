#include <crypto/fea.hpp>

wVoid wmkc::crypto::fea::cbc_encrypt(wByte *p, wSize n)
{
    wByte roundIv[WMKC_FEA_BLOCKLEN];

    memcpy(roundIv, this->iv, WMKC_FEA_BLOCKLEN);
    for(wU32 i = 0; i < n; i += WMKC_FEA_BLOCKLEN) {
        this->xorWithIV(p + i, roundIv);
        this->cipher(p + i, this->roundKey);
        memcpy(roundIv, p + i, WMKC_FEA_BLOCKLEN);
    }
}

wVoid wmkc::crypto::fea::cbc_decrypt(wByte *c, wSize n)
{
    wByte roundIv[WMKC_FEA_BLOCKLEN];
    wByte roundBuffer[WMKC_FEA_BLOCKLEN];

    memcpy(roundIv, this->iv, WMKC_FEA_BLOCKLEN);
    for(wU32 i = 0; i < n; i += WMKC_FEA_BLOCKLEN) {
        memcpy(roundBuffer, c + i, WMKC_FEA_BLOCKLEN);
        this->invCipher(c + i, this->roundKey);
        this->xorWithIV(c + i, roundIv);
        memcpy(roundIv, roundBuffer, WMKC_FEA_BLOCKLEN);
    }
}
