#include <config/wmkc.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_NET
#define WMKC_CPP_NET
#include <network/wmkc_net_exception.hpp>
#include <cmath>

#if defined(WMKC_PLATFORM_LINUX)
#   include <netdb.h>
#   include <unistd.h>
#   include <sys/time.h>
#   include <arpa/inet.h>
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <netinet/ip.h>
#   include <netinet/tcp.h>
#   define WMKC_NET_ERROR EOF             // 定义错误代码
typedef struct sockaddr     SOCKADDR;     // 套接字地址结构
typedef struct addrinfo     ADDRINFO;     // 域名解析结构
typedef struct sockaddr_in  SOCKADDR_IN;  // IPv4网络结构
typedef struct sockaddr_in6 SOCKADDR_IN6; // IPv6网络结构
typedef wS32   wSocket;                   // wmkcNet的socket类型
#elif defined(WMKC_PLATFORM_WINOS)
#   include <WS2tcpip.h>
#   if defined(_MSC_VER)
#       pragma comment(lib, "WS2_32")
#   endif
#   define WMKC_NET_ERROR SOCKET_ERROR    // 定义错误代码
typedef SOCKET         wSocket;           // wmkcNet的socket类型
#endif /* WMKC_PLATFORM_LINUX */

#include <wmkc_memory.hpp>

namespace wmkc {
    namespace net {
        class IPEndPoint {
            public:
                std::string addr;
                wU16 port;
                IPEndPoint(std::string addr, wU16 port): addr(addr), port(port) {}
                IPEndPoint():addr(),port() {};
        };

        ADDRINFO    *getAddrInfo(wS32 family, wS32 type, wS32 proto, std::string addr, std::string serviceName);
        IPEndPoint  getNetworkInfo(wSocket sockfd, wS32 family);
        IPEndPoint  getNetworkInfo(wS32 family, SOCKADDR *pAddr);
        std::string networkAddr2stringAddr(wS32 family, const wVoid *pAddr);
        wU16        networkPort2numberPort(const wU16 port);

        class Socket {
            public:
                double timeout; // 超时时间
                wSocket fd; // 套接字文件描述符
                wS32 family; // 套接字网络家族
                wS32 type;   // 套接字类型
                wS32 proto;  // 套接字协议
                wS32 transmissionLength; // 单次传输长度

                IPEndPoint lAddr; // 套接字绑定的本地IP端点
                IPEndPoint rAddr; // 套接字绑定的远程IP端点

                Socket(wS32 _family, wS32 _type, wS32 _proto, wSocket _fd = EOF);
                ~Socket();

                void settimeout(double _time);
                void connect(const std::string addr, const wU16 port);
                void bind(const std::string addr, const wU16 port);
                void listen(const wS32 backlog);
                Socket accept();
                void send(const std::string content, const wS32 flag = 0);
                void sendall(const std::string content, const wS32 flag = 0);
                void sendto(const std::string content, IPEndPoint target, const wS32 flag = 0);
                std::string recv(const wS32 len, const wS32 flag = 0);
                std::string recvfrom(const wS32 len, SOCKADDR *from = nullptr, socklen_t *fromlen = nullptr, const wS32 flag = 0);
                void shutdown(const wS32 how);
                void close();
        };
    };
}

#endif /* WMKC_CPP_NET */
#endif /* WMKC_SUPPORT */
