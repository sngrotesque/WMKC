#include <wmkc_exception.hpp>

void wmkc::exception(wmkc_s32 errCode, std::string funcName, std::string errMessage)
{
    throw std::runtime_error(std::string(funcName + "[" + std::to_string(errCode) + "]: " + errMessage));
}

#if defined(WMKC_PLATFORM_WINOS) && (_MSC_VER >= 1930)
template <typename T>
std::string std::to_string(T value) {
    std::ostringstream os;
    os << value;
    return os.c_str();
}
#endif
