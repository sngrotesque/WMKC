#include <iostream>
#include <fstream>

#include <crypto/fea.hpp>

#include <wmkc_misc.hpp>
#include <wmkc_time.hpp>

void fea_speed_test(wSize length = 16777216)
{
    wByte *data = new wByte[length];
    wmkc::crypto::fea fea((wByte *)"aHSF8y3197ty(DSGF8913gr9g8asfF8)", (uint8_t *)"1395u08eurf8y137");
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
    wmkc::crypto::fea fea((wByte *)"aHSF8y3097ty(DSGF8913gr9g8asfF8)", (uint8_t *)"0395u08eurf8y137");
    char buffer[2048] = {"hello,world....................................................."};
    uint8_t *content = (uint8_t *)buffer;
    size_t length = strlen(buffer);

    fea.cbc_encrypt(content, length);
    wmkc::misc::PRINT(content, length, 32, 1, 0);

    fea.cbc_decrypt(content, length);
    wmkc::misc::PRINT(content, length, 32, 1, 0);
}

void file_test()
{
    std::fstream f(L"F:/A-传送文件夹/图片/447.2.jpg", std::ios::in | std::ios::binary);
    if(!f.is_open()) {
        std::cout << "failed to file open." << std::endl;
        return;
    }

    uint8_t buffer[8] = {0};

    f.read((char *)buffer, 8);

    wmkc::misc::PRINT(buffer, sizeof(buffer), (sizeof(buffer) > 8)?16:sizeof(buffer), 0, 0);
}

int main(int argc, char **argv)
{
    fea_speed_test();

    return 0;
}
