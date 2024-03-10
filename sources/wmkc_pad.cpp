#include <wmkc_pad.hpp>

wVoid wmkc::pad(wByte *src, wSize *size, wU32 blockSize, wBool randVal)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pad", "src or size is NULL.");
    }
    wU32 padLen;
    wSize totalLen;
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

wVoid wmkc::unpad(wByte *src, wSize *size)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pad", "src or size is NULL.");
    }

    wSize padLen;
    wSize index;

    padLen = src[*size - 1];

    for(index = *size - padLen; index < *size; ++index)
        src[index] = 0x00;

    *size = *size - padLen;
}

wByte *wmkc::pkcs7_pad(const wByte *src, wSize *size, wU32 blockSize)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pkcs7_pad", "src or size is NULL.");
    }
    wByte *srcData = (wByte *)src;
    wSize srcSize = *size;

    wU32 padLen;
    wSize totalLen;

    padLen = blockSize - srcSize % blockSize;
    totalLen = srcSize + padLen;

    wByte *padded = new wByte[totalLen];
    memcpy(padded, srcData, srcSize);
    memset(padded + srcSize, padLen, padLen);

    *size = totalLen;

    return padded;
}

wByte *wmkc::pkcs7_unpad(const wByte *src, wSize *size)
{
    if(!src || !size) {
        wmkc::exception(wmkcErr_ErrNULL, "wmkc::pkcs7_pad", "src or size is NULL.");
    }
    wU32 padLen = src[*size - 1];
    wSize unpaddedLen = *size - padLen;

    wByte *unpadded = new wByte[unpaddedLen];
    memcpy(unpadded, src, unpaddedLen);

    *size = unpaddedLen;

    return unpadded;
}
