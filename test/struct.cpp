#include <wmkc_struct.hpp>
#include <wmkc_misc.hpp>

#include <crypto/fea.hpp>

#include <crypto/fea.cpp>
#include <crypto/fea_ctr.cpp>
#include <crypto/fea_ecb.cpp>
#include <crypto/fea_cbc.cpp>
#include <crypto/fea_cfb.cpp>

#include <iostream>
#include <cmath>

#include <zlib.h>

std::string struct_pack_test(wU32 seq, std::string content)
{
    wmkc::structure Struct;
    std::string results;

    try {
        results.append(Struct.pack("!II", seq, content.size()));
        results.append(content);
        results.append(Struct.pack("!I", crc32(0, (wByte *)content.c_str(), content.size())));
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return results;
}

void fea_test()
{
    std::string res = struct_pack_test(0x00000001, "GET / HTTP/1.1\r\nHost: www.baidu.com\r\nAccept: */*\r\nConnection: keep-alive\r\nUser-Agent: Android\r\n\r\n");
    wmkc::crypto::fea fea((wByte *)"abcdef0123456789abcdef0123456789", (wByte *)"abcdef0123456789");
    wSize length = res.size();
    wByte *buffer = new wByte[length];

    memcpy(buffer, res.c_str(), length);

    fea.encrypt(buffer, length, wmkc::crypto::xcryptMode::CTR);
    wmkc::misc::PRINT(buffer, length, 32, 1, 0);

    delete[] buffer;
}

int main(int argc, char **argv)
{
    fea_test();

    return 0;
}
