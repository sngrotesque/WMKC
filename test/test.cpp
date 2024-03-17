#include <iostream>
#include <fstream>

#include <crypto/fea.hpp>

#include <wmkc_misc.hpp>
#include <wmkc_time.hpp>
#include <wmkc_pad.hpp>

const wByte *fea_test_key = (wByte *)"[CeN&qmUNso53Q4|E$H<RW7;Y%?f.*~J";
const wByte *fea_test_iv  = (wByte *)"_wnMsGmwfV=Q13]l";

class wBuffer {
    public:
        wByte *data;
        wSize size;
        wBuffer(wByte *_d, wSize _s)
        : data(_d), size(_s) {}
        wBuffer() {}
        ~wBuffer()
        {
            delete[] this->data;
            this->size = 0;
        }
};

void fea_speed(wmkc::crypto::xcryptMode mode, wSize length = 16777216)
{
    wmkc::crypto::fea fea(fea_test_key, fea_test_iv);
    double start, stop;
    wmkc::Time timer;
    wByte *buffer = new wByte[length];

    start = timer.time();
    fea.encrypt(buffer, length, mode);
    stop = timer.time();

    printf("data length: %.2lfMB, time used: %.4lf\n",
        (double)(length / (1024 * 1024)), (stop-start));

    delete[] buffer;
}

void fea_encrypt_test(wByte *data, wSize size, wmkc::crypto::xcryptMode mode, wBool encrypt, wBool showHexStream)
{
    wmkc::crypto::fea fea(fea_test_key, fea_test_iv, 64);

    switch(mode) {
        case wmkc::crypto::xcryptMode::ECB:
            std::cout << "Current encryption mode: ECB.\n"; break;
        case wmkc::crypto::xcryptMode::CBC:
            std::cout << "Current encryption mode: CBC.\n"; break;
        case wmkc::crypto::xcryptMode::CTR:
            std::cout << "Current encryption mode: CTR.\n"; break;
        case wmkc::crypto::xcryptMode::CFB:
            std::cout << "Current encryption mode: CFB.\n"; break;
    }

    if(encrypt) {
        std::cout << "Plaintext:\n";
    } else {
        std::cout << "Ciphertext:\n";
    }
    wmkc::misc::PRINT(data, size, 32, (size % 32), true);
    std::cout << "Key: ";
    wmkc::misc::PRINT(fea_test_key, 32, 32, 1, true);
    std::cout << "Iv:  ";
    wmkc::misc::PRINT(fea_test_iv, 16, 16, 1, true);

    if(encrypt) {
        fea.encrypt(data, size, mode);
        std::cout << "Ciphertext:\n";
    } else {
        fea.decrypt(data, size, mode);
        std::cout << "Plaintext:\n";
    }

    if(showHexStream) {
        wmkc::misc::PRINT(data, size, 32, (size % 32), true);
    }
}

wBuffer file_read(const wchar_t *path)
{
    std::fstream fp(path, std::ios::binary | std::ios::in | std::ios::ate);
    wBuffer buffer;

    buffer.size = fp.tellg();
    buffer.data = new wByte[buffer.size];

    fp.seekg(0);
    fp.read((wChar *)buffer.data, buffer.size);

    fp.close();
    return buffer;
}

void fea_test()
{
    wChar text[256] = {"askd103u508DG)h1935h9ga(G091g51-351349098d-80g=13)sd'fl[4164-19]"};
    fea_encrypt_test((wByte *)text, strlen(text), wmkc::crypto::xcryptMode::CFB, 1, 1);
}

int main()
{
    wBuffer buffer = file_read(L"f:/A-传送文件夹/91看片_8.18.3402c6616.apk");

    wmkc::misc::PRINT(buffer.data, 32, 32, 1, 0);

    fea_encrypt_test(buffer.data, buffer.size, wmkc::crypto::xcryptMode::CTR, 1, 0);

    wmkc::misc::PRINT(buffer.data, 32, 32, 1, 0);

    return 0;
}
