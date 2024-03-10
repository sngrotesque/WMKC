#include <iostream>
#include <fstream>

#include <crypto/fea.hpp>

#include <wmkc_misc.hpp>
#include <wmkc_time.hpp>
#include <wmkc_pad.hpp>

const wByte *fea_test_key = (wByte *)"[CeN&qmUNso53Q4|E$H<RW7;Y%?f.*~J";
const wByte *fea_test_iv  = (wByte *)"_wnMsGmwfV=Q13]l";

void fea_speed(wmkc::crypto::xcryptMode mode, wSize length = 16777216)
{
    wmkc::crypto::fea fea(fea_test_key, fea_test_iv);
    double start, stop;
    wmkc::Time timer;
    wByte *buffer = new wByte[length];

    start = timer.time();
    fea.encrypt(buffer, length, mode);
    stop = timer.time();

    printf("data length: %.4lf, time used: %.4lf\n",
        (double)(length / (1024 * 1024)), (stop-start));

    delete[] buffer;
}

void fea_encrypt_test(wByte *data, wSize size, wmkc::crypto::xcryptMode mode = wmkc::crypto::xcryptMode::CTR)
{
    wmkc::crypto::fea fea(fea_test_key, fea_test_iv);

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

    std::cout << "Plaintext:\n";
    wmkc::misc::PRINT(data, size, 32, (size % 32), true);
    std::cout << "Key: ";
    wmkc::misc::PRINT(fea_test_key, 32, 32, 1, true);
    std::cout << "Iv:  ";
    wmkc::misc::PRINT(fea_test_iv, 16, 16, 1, true);

    fea.encrypt(data, size, mode);

    std::cout << "Ciphertext:\n";
    wmkc::misc::PRINT(data, size, 32, (size % 32), true);
}

int main()
{
    wChar text[2048] = {"hello, world.\n"};

    fea_encrypt_test((wByte *)text, strlen(text));

    return 0;
}
