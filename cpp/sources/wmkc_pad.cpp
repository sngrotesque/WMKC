#include <wmkc_pad.hpp>

wmkcVoid wmkc::pad(wmkcByte *src, wmkcSize *size, wmkc_u32 blockSize, wmkcBool randVal)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pad", "src or size is NULL.");
    }
    wmkc_u32 padLen;
    wmkcSize totalLen;
    wmkc::random random;

    padLen = (blockSize - *size % blockSize);
    totalLen = padLen + *size;

    if(randVal) {
        std::string tmp = random.urandom(padLen - 1);
        memcpy(src + *size, tmp.c_str(), padLen - 1);
    } else {
        memset(src + *size, 0xac, padLen - 1);
    }

    src[(*size = totalLen) - 1] = padLen & 0xff;
}

wmkcVoid wmkc::unpad(wmkcByte *src, wmkcSize *size)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pad", "src or size is NULL.");
    }

    wmkcSize padLen;
    wmkcSize index;

    padLen = src[*size - 1];

    for(index = *size - padLen; index < *size; ++index)
        src[index] = 0x00;

    *size = *size - padLen;
}

wmkcByte *wmkc::pkcs7_pad(const wmkcByte *src, wmkcSize *size, wmkc_u32 blockSize)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pkcs7_pad", "src or size is NULL.");
    }
    wmkcByte *srcData = (wmkcByte *)src;
    wmkcSize srcSize = *size;

    wmkc_u32 padLen;
    wmkcSize totalLen;

    padLen = blockSize - srcSize % blockSize;
    totalLen = srcSize + padLen;

    wmkcByte *padded = new wmkcByte[totalLen];
    memcpy(padded, srcData, srcSize);
    memset(padded + srcSize, padLen, padLen);

    *size = totalLen;

    return padded;
}

wmkcByte *wmkc::pkcs7_unpad(const wmkcByte *src, wmkcSize *size)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pkcs7_pad", "src or size is NULL.");
    }
    wmkc_u32 padLen = src[*size - 1];
    wmkcSize unpaddedLen = *size - padLen;

    wmkcByte *unpadded = new wmkcByte[unpaddedLen];
    memcpy(unpadded, src, unpaddedLen);

    *size = unpaddedLen;

    return unpadded;
}
