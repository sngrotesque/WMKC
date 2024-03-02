#include <iostream>

#include <crypto/fea.hpp>

#include <wmkc_misc.hpp>
#include <wmkc_time.hpp>

void fea_speed_test(wmkcSize length = 16777216)
{
    wmkcByte *data = new wmkcByte[length];
    wmkc::crypto::fea fea((wmkcByte *)"aHSF8y3197ty(DSGF8913gr9g8asfF8)", (uint8_t *)"1395u08eurf8y137");
    wmkc::Time timer;
    double start_time, stop_time;

    printf("Start encryption...\n");

    start_time = timer.time();
    fea.encrypt(data, length, wmkc::crypto::xcryptMode::CBC);
    stop_time = timer.time();

    printf("time used: %.4lf\n", stop_time-start_time);

    delete[] data;
}

void fea_test()
{
    wmkc::crypto::fea fea((wmkcByte *)"aHSF8y3097ty(DSGF8913gr9g8asfF8)", (uint8_t *)"0395u08eurf8y137");
    char buffer[2048] = {"hello,world....................................................."};
    uint8_t *content = (uint8_t *)buffer;
    size_t length = strlen(buffer);

    fea.cbc_encrypt(content, length);
    wmkc::misc::PRINT(content, length, 32, 1, 0);

    fea.cbc_decrypt(content, length);
    wmkc::misc::PRINT(content, length, 32, 1, 0);
}

int main(int argc, char **argv)
{
    // fea_speed_test();
    fea_test();

    return 0;
}
