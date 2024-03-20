#include <config/wmkc.hpp>

#include <wmkc_struct.hpp>
#include <wmkc_misc.hpp>

#include <iostream>

#include <cmath>

using namespace std;

wVoid struct_pack_test()
{
    wmkc::structure Struct;
    std::string buffer = Struct.pack("!QIIIdf", 1, 2, 3, 4, 5.0, 451.309);
    wByte *res = (wByte *)buffer.c_str();
    wmkc::misc::PRINT(res, buffer.size(), 32, 1, 0);
}

int main(int argc, char **argv)
{
    struct_pack_test();

    return 0;
}
