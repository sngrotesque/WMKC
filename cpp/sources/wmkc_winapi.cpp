#include <wmkc_winapi.hpp>

struct wmkc::winapi::widthHeight wmkc::winapi::getScreenResolution()
{
    wmkc::winapi::widthHeight size;
    size.width = GetSystemMetrics(SM_CXSCREEN);
    size.height = GetSystemMetrics(SM_CYSCREEN);
    if(!size.width || !size.height) {
        wmkcErr_exception(wmkcErr_Err32, "wmkc::winapi::getScreenResolution",
            "GetSystemMetrics function returned an error code when called.");
    }
}

struct wmkc::winapi::widthHeight wmkc::winapi::getCursorPos()
{
    wmkc::winapi::widthHeight point;
    POINT _point_tmp = {0};
    if(!GetCursorPos(&_point_tmp)) {
        wmkcErr_exception(GetLastError(), "wmkc::winapi::getCursorPos",
            "GetCursorPos function returned an error code when called.");
    }
    point.width = _point_tmp.x;
    point.height = _point_tmp.y;
}

std::string wmkc::winapi::getUserName(wmkcChar format = 'A')
{
    if(format == 'A') {
        wmkcChar tmp_buffer[512] = {0};
        DWORD tmp_buffer_size = sizeof(tmp_buffer);
        GetUserNameA(tmp_buffer, &tmp_buffer_size);
        return std::string(tmp_buffer);
    } else if(format == 'W') {
        WCHAR tmp_buffer[512] = {0};
        DWORD tmp_buffer_size = sizeof(tmp_buffer) >> 1;
        GetUserNameW(tmp_buffer, &tmp_buffer_size);
        return std::string((wmkcChar *)tmp_buffer, tmp_buffer_size);
    }
}

wmkcVoid wmkc::winapi::setCursorPos(wmkc_u32 x, wmkc_u32 y)
{
    if(!SetCursorPos(x, y)) {
        wmkcErr_exception(wmkcErr_ErrSysFunc, "wmkc::winapi::setCursorPos",
            "SetCursorPos function returned an error code when called.");
    }
}

wmkcVoid wmkc::winapi::setDesktopWallpaper(std::string path)
{
    
}

wmkcVoid wmkc::winapi::opacityStartMenu(BYTE alpha)
{
    
}
