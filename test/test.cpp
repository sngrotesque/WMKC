#include <iostream>

#include <crypto/fea.hpp>

#include <wmkc_time.hpp>

void fea_speed_test(wmkcSize length)
{
    wmkcByte *data = new wmkcByte[length];
    wmkc::crypto::fea fea((wmkcByte *)"aHSF8y3197ty(DSGF8913gr9g8asfF8)", (uint8_t *)"1395u08eurf8y137");
    wmkc::Time timer;
    double start_time, stop_time;

    printf("Start encryption...\n");

    start_time = timer.time();
    fea.cbc_encrypt(data, length);
    stop_time = timer.time();

    printf("time used: %.4lf\n", stop_time-start_time);

    delete[] data;
}

int main(int argc, char **argv)
{
    fea_speed_test(16777216);

    return 0;
}
