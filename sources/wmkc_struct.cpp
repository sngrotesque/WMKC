#include <wmkc_struct.hpp>

wBool check_LE()
{
    int n = 1;
    return (*((char*)&n)==1)?(true):(false);
}

wVoid swap_byte(wChar *array, wU32 l, wU32 r)
{
    wChar swap;
    swap = *(array + l);
    *(array + l) = *(array + r);
    *(array + r) = swap;
}

wVoid change_endian(wChar *array, wU32 size)
{
    switch(size) {
        case 2:
            swap_byte(array, 0, 1);
            break;
        case 4:
            swap_byte(array, 0, 3);
            swap_byte(array, 1, 2);
            break;
        case 8:
            swap_byte(array, 0, 7);
            swap_byte(array, 1, 6);
            swap_byte(array, 2, 5);
            swap_byte(array, 3, 4);
            break;
    }
}

template <typename T>
std::string get_bytes_result(T n, wU32 size, wBool change)
{
    wChar buffer[sizeof(T)] = {0};
    memcpy(buffer, &n, sizeof(T));
    if(change) {
        change_endian(buffer, sizeof(T));
    }
    return std::string(buffer, sizeof(T));
}

template <typename T>
std::string single_pack(wChar format, wmkc::endianness current_endian, wmkc::endianness specify_endian, T arg)
{
    wBool change = ((specify_endian!=wmkc::endianness::NO)&&(current_endian!=specify_endian))?(true):(false);
    std::string results;

    switch(format) {
        case 'B':
            results = get_bytes_result(arg, 1, change); break;
        case 'H':
            results = get_bytes_result(arg, 2, change); break;
        case 'I':
        case 'f':
            results = get_bytes_result(arg, 4, change); break;
        case 'Q':
        case 'N':
        case 'd':
            results = get_bytes_result(arg, 8, change); break;
    }
    return results;
}

std::string wmkc::structure::pack(std::string format, ...)
{
    wmkc::endianness current_endian = (check_LE())?(wmkc::endianness::LE):(wmkc::endianness::BE);
    wmkc::endianness specify_endian;
    std::string results;

    switch(format[0]) {
        case '>':
        case '!':
            specify_endian = wmkc::endianness::BE; break;
        case '<':
            specify_endian = wmkc::endianness::LE; break;
        default:
            specify_endian = wmkc::endianness::NO; break;
    }
    format.erase(0, 1);

    va_list va;
    va_start(va, format);

    for(const char &fm : format) {
        switch(fm) {
            case 'B':
                results.append(single_pack(fm, current_endian, specify_endian, (wByte)va_arg(va, int)));
                break;
            case 'H':
                results.append(single_pack(fm, current_endian, specify_endian, (wU16)va_arg(va, int)));
                break;
            case 'I':
                results.append(single_pack(fm, current_endian, specify_endian, (wU32)va_arg(va, int)));
                break;
            case 'Q':
            case 'N':
                results.append(single_pack(fm, current_endian, specify_endian, (wSize)va_arg(va, wSSize)));
                break;
            case 'f':
                results.append(single_pack(fm, current_endian, specify_endian, (float)va_arg(va, double)));
                break;
            case 'd':
                results.append(single_pack(fm, current_endian, specify_endian, (double)va_arg(va, double)));
                break;
            default:
                wmkc::exception(wmkcErr_Err, "wmkc::structure::pack", "bad char in struct format");
        }
    }

    va_end(va);

    return results;
}

std::vector<std::any> wmkc::structure::unpack(std::string format, std::string buffer)
{
    std::vector<std::any> results;


    return results;
}
