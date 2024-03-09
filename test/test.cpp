#include <iostream>
#include <fstream>

#include <crypto/fea.hpp>

#include <wmkc_misc.hpp>
#include <wmkc_time.hpp>
#include <wmkc_pad.hpp>

const wByte *fea_test_key = (wByte *)"[Ceb&qmUNso53Q4|E$H<RW7;Y%?f.*~J";
const wByte *fea_test_iv  = (wByte *)"_WnMsGmwfV=Q13]l";

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
    wmkc::crypto::fea fea(fea_test_key, fea_test_iv);
    char buffer[2048] = {"hello,world....................................................."};
    uint8_t *content = (uint8_t *)buffer;
    size_t length = strlen(buffer);

    fea.cbc_encrypt(content, length);
    wmkc::misc::PRINT(content, length, 32, 1, 0);

    fea.cbc_decrypt(content, length);
    wmkc::misc::PRINT(content, length, 32, 1, 0);
}

void file_cbc_xcrypt_test(const wChar *in_file_path, const wChar *out_file_path, wChar method)
{
    std::fstream inFile(in_file_path, std::ios::in | std::ios::binary | std::ios::ate);
    std::fstream outFile(out_file_path, std::ios::out | std::ios::binary);
    wmkc::crypto::fea fea(fea_test_key, fea_test_iv);

    if(!inFile.is_open() || !outFile.is_open()) {
        wmkc::exception(-1, "main", "failed to file open.");
    }
    wSize length = inFile.tellg();
    wByte *in_content = new wByte[length];
    wByte *out_content = nullptr;

    inFile.seekg(0, std::ios::beg);
    inFile.read((wChar *)in_content, length);

    if((method == 'e') || (method == 'E')) {
        out_content = wmkc::pkcs7_pad(in_content, &length, WMKC_FEA_BLOCKLEN);
        fea.encrypt(out_content, length, wmkc::crypto::xcryptMode::CBC);
    } else if((method == 'd') || (method == 'D')) {
        fea.decrypt(in_content, length, wmkc::crypto::xcryptMode::CBC);
        out_content = wmkc::pkcs7_unpad(in_content, &length);
    }

    outFile.write((wChar *)out_content, length);

    outFile.close();
    inFile.close();
    delete[] out_content;
    delete[] in_content;
}

int main(int argc, char **argv)
{
    const wChar *src_path = "C:/Users/sn/Desktop/fea_test/dee7180e2b780946355892b442b19ceb4d877e12.png";
    const wChar *dst_path = "C:/Users/sn/Desktop/fea_test/decrypt.png";

    file_cbc_xcrypt_test(src_path, dst_path, 'd');

    return 0;
}
