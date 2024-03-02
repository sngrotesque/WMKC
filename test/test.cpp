#include <iostream>

#include <network/wmkc_net.hpp>

int main(int argc, char **argv)
{
#   ifdef WMKC_PLATFORM_WINOS
    WSADATA ws;
    WSAStartup(MAKEWORD(2,2), &ws);
#   endif

    wmkc::net::Socket fd(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    fd.connect("www.baidu.com", 80);
    fd.send("GET / HTTP/1.1\r\nHost: www.baidu.com\r\nUser-Agent: Android\r\n\r\n");
    std::cout << fd.recv(4096) << std::endl;

    fd.shutdown(2);
    fd.close();

#   ifdef WMKC_PLATFORM_WINOS
    WSACleanup();
#   endif
    return 0;
}
