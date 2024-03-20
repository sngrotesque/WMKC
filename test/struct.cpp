#include <config/wmkc.hpp>

#include <wmkc_struct.hpp>
#include <wmkc_misc.hpp>

#include <iostream>

using namespace std;

wVoid struct_test()
{
    wmkc::structure Struct;
    string buffer = Struct.pack("!ffdf", 3.14, 5.0, 0.1, 3.14);
    wByte *res = (wByte *)buffer.c_str();
    wmkc::misc::PRINT(res, buffer.size(), 32, 1, 0);
}

int main(int argc, char **argv)
{
    struct_test();

    return 0;
}
