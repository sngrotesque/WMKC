#include <iostream>
#include <fstream>

#include <crypto/fea.hpp>
#include <wmkc_misc.hpp>
#include <wmkc_pad.hpp>

#include <crypto/fea_cbc.cpp>
#include <crypto/fea_ecb.cpp>
#include <crypto/fea_ctr.cpp>
#include <crypto/fea_cfb.cpp>
#include <crypto/fea.cpp>
#include <wmkc_random.cpp>
#include <wmkc_time.cpp>
#include <wmkc_pad.cpp>

using namespace std;

const wByte *key = (wByte *)"[CeN&qmUNso53Q4|E$H<RW7;Y%?f.*~J";
const wByte *iv  = (wByte *)"_wnMsGmwfV=Q13]l";

wByte *xcrypt(wByte *buffer, wSize *length, wmkc::crypto::xcryptMode xcrypt_mode, wBool encryption)
{
    wmkc::crypto::fea fea(key, iv);
    wByte *result = nullptr;

    if(encryption) {
        result = wmkc::pkcs7_pad(buffer, length, WMKC_FEA_BL);
        fea.encrypt(result, *length, xcrypt_mode);
    } else {
        fea.decrypt(buffer, *length, xcrypt_mode);
        result = wmkc::pkcs7_unpad(buffer, length);
    }

    return result;
}

wVoid file_xcrypt(LPCWCHAR srcPath, LPCWCHAR dstPath, wmkc::crypto::xcryptMode xcrypt_mode, wBool encryption)
{
    fstream src_fp(srcPath, ios::in  | ios::binary | ios::ate);
    fstream dst_fp(dstPath, ios::out | ios::binary);

    if(!src_fp.is_open() || !dst_fp.is_open()) {
        cout << "Failed to file open." << endl;
        return;
    }

    wByte *buffer_in  = nullptr;
    wByte *buffer_out = nullptr;
    wSize length;

    length    = src_fp.tellg();
    buffer_in = new wByte[length];

    src_fp.seekg(ios::beg);
    src_fp.read((wChar *)buffer_in, length);
    buffer_out = xcrypt(buffer_in, &length, xcrypt_mode, encryption);
    dst_fp.write((wChar *)buffer_out, length);

    delete[] buffer_out;
    delete[] buffer_in;
    src_fp.close();
    dst_fp.close();
}

wS32 main(wS32 argc, wChar **argv)
{
    LPCWCHAR path1 = L"F:/Pitchers/Pixiv/18781732/2022_08_13_01_17_52_100440451_p0.jpg";
    LPCWCHAR path2 = L"C:/Users/sn/Desktop/收纳/100440451_encrypted.jpg";
    LPCWCHAR path3 = L"C:/Users/sn/Desktop/收纳/100440451_decrypted.jpg";

    file_xcrypt(path1, path2, wmkc::crypto::xcryptMode::CBC, 1);
    file_xcrypt(path2, path3, wmkc::crypto::xcryptMode::CBC, 0);

    return 0;
}
