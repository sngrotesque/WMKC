#include <crypto/fea.hpp>

wmkcVoid wmkc::crypto::fea::ecb_encrypt(wmkcByte *p)
{
    this->cipher(p, this->roundKey);
}

wmkcVoid wmkc::crypto::fea::ecb_decrypt(wmkcByte *c)
{
    this->invCipher(c, this->roundKey);
}
