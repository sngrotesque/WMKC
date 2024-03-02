#include <network/wmkc_net.hpp>

ADDRINFO *wmkc::net::getAddrInfo(wmkc_s32 family, wmkc_s32 type, wmkc_s32 proto, std::string addr, std::string serviceName)
{
    ADDRINFO hints = {0};
    hints.ai_family = family;
    hints.ai_socktype = type;
    hints.ai_protocol = proto;

    ADDRINFO *sockAddrRes = nullptr;
    wmkc_s32 err = getaddrinfo(addr.c_str(), serviceName.c_str(), &hints, &sockAddrRes);
    if(err) {
        wmkc::net::exception("wmkc::net::getAddrInfo");
    }
    return sockAddrRes;
}

std::string wmkc::net::networkAddr2stringAddr(wmkc_s32 family, const wmkcVoid *pAddr)
{
    char tmp_addr[INET6_ADDRSTRLEN];
    if(!inet_ntop(family, pAddr, tmp_addr, INET6_ADDRSTRLEN)) {
        wmkc::net::exception("wmkc::net::networkAddr2stringAddr");
    }
    return std::string(tmp_addr);
}

wmkc_u16 wmkc::net::networkPort2numberPort(const wmkc_u16 port)
{
    return ntohs(port);
}

wmkc::net::IPEndPoint wmkc::net::getNetworkInfo(wmkcNetSockT sockfd, wmkc_s32 family)
{
    SOCKADDR_IN *ipv4 = nullptr;
    SOCKADDR_IN6 *ipv6 = nullptr;
    SOCKADDR basicSockAddr = {0};
    socklen_t basicSockAddr_len = sizeof(basicSockAddr);
    wmkc::net::IPEndPoint addr_info;

    if(getsockname(sockfd, &basicSockAddr, &basicSockAddr_len) == WMKC_NET_ERROR) {
        wmkc::net::exception("wmkc::net::getNetworkInfo");
    }

    switch(family) {
        case AF_INET:
            ipv4 = (SOCKADDR_IN *)&basicSockAddr;
            addr_info.addr = wmkc::net::networkAddr2stringAddr(family, &ipv4->sin_addr);
            addr_info.port = wmkc::net::networkPort2numberPort(ipv4->sin_port);
            break;
        case AF_INET6:
            ipv6 = (SOCKADDR_IN6 *)&basicSockAddr;
            addr_info.addr = wmkc::net::networkAddr2stringAddr(family, &ipv6->sin6_addr);
            addr_info.port = wmkc::net::networkPort2numberPort(ipv6->sin6_port);
            break;
    }

    return addr_info;
}

wmkc::net::IPEndPoint wmkc::net::getNetworkInfo(wmkc_s32 family, SOCKADDR *pAddr)
{
    SOCKADDR_IN *ipv4 = nullptr;
    SOCKADDR_IN6 *ipv6 = nullptr;
    wmkc::net::IPEndPoint addr_info;
    
    switch(family) {
        case AF_INET:
            ipv4 = (SOCKADDR_IN *)pAddr;
            addr_info.addr = wmkc::net::networkAddr2stringAddr(family, &ipv4->sin_addr);
            addr_info.port = wmkc::net::networkPort2numberPort(ipv4->sin_port);
            break;
        case AF_INET6:
            ipv6 = (SOCKADDR_IN6 *)pAddr;
            addr_info.addr = wmkc::net::networkAddr2stringAddr(family, &ipv6->sin6_addr);
            addr_info.port = wmkc::net::networkPort2numberPort(ipv6->sin6_port);
            break;
    }

    return addr_info;
}

//****************************************************************************************************//
wmkc::net::Socket::Socket(wmkc_s32 _family, wmkc_s32 _type, wmkc_s32 _proto, wmkcNetSockT _fd)
: timeout(), fd(), family(_family), type(_type), proto(_proto), transmissionLength(), lAddr(), rAddr()
{
    if(_fd == WMKC_NET_ERROR) {
        this->fd = socket(this->family, this->type, this->proto);
        if(this->fd == WMKC_NET_ERROR) {
            wmkc::net::exception("wmkc::net::Socket::Socket");
        }
    } else {
        this->fd = _fd;
    }
}

wmkc::net::Socket::~Socket()
{

}

void wmkc::net::Socket::settimeout(double _val)
{
    this->timeout = _val;
#   if defined(WMKC_PLATFORM_WINOS)
    DWORD _timeout = (DWORD)(this->timeout * 1e3);
    wmkcChar *optval = (wmkcChar *)&_timeout;
#   elif defined(WMKC_PLATFORM_LINUX)
    double intpart = 0;
    double fracpart = modf(this->timeout, &intpart);
    struct timeval _timeout = {.tv_sec=(long)intpart, .tv_usec=(long)(fracpart * 1e6)};
    wmkcVoid *optval = (wmkcVoid *)&_timeout;
#   endif

    if(setsockopt(this->fd, SOL_SOCKET, SO_SNDTIMEO, optval, sizeof(_timeout)) ||
        setsockopt(this->fd, SOL_SOCKET, SO_RCVTIMEO, optval, sizeof(_timeout))) {
        wmkc::net::exception("wmkc::net::Socket::settimeout");
    }
}

void wmkc::net::Socket::connect(const std::string addr, const wmkc_u16 port)
{
    ADDRINFO *sockAddrResult = wmkc::net::getAddrInfo(this->family, this->type, this->proto,
        addr, std::to_string(port));

    if(::connect(this->fd, sockAddrResult->ai_addr, sockAddrResult->ai_addrlen) == WMKC_NET_ERROR) {
        freeaddrinfo(sockAddrResult);
        wmkc::net::exception("wmkc::net::Socket::connect");
    }

    this->rAddr = wmkc::net::getNetworkInfo(this->family, sockAddrResult->ai_addr);
    this->lAddr = wmkc::net::getNetworkInfo(this->fd, this->family);
    freeaddrinfo(sockAddrResult);
}

void wmkc::net::Socket::bind(const std::string addr, const wmkc_u16 port)
{
    ADDRINFO *sockAddrResult = wmkc::net::getAddrInfo(this->family, this->type, this->proto,
        addr, std::to_string(port));

    if(::bind(this->fd, sockAddrResult->ai_addr, sockAddrResult->ai_addrlen) == WMKC_NET_ERROR) {
        freeaddrinfo(sockAddrResult);
        wmkc::net::exception("wmkc::net::Socket::bind");
    }
    this->lAddr = wmkc::net::getNetworkInfo(this->family, sockAddrResult->ai_addr);

    freeaddrinfo(sockAddrResult);
}

void wmkc::net::Socket::listen(const wmkc_s32 backlog)
{
    if(::listen(this->fd, backlog) == WMKC_NET_ERROR) {
        wmkc::net::exception("wmkc::net::Socket::listen");
    }
}

wmkc::net::Socket wmkc::net::Socket::accept()
{
    SOCKADDR client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    wmkcNetSockT client_sockfd;

    if((client_sockfd = ::accept(this->fd, &client_addr, &client_addr_len)) == WMKC_NET_ERROR) {
        wmkc::net::exception("wmkc::net::Socket::accept");
    }

    return wmkc::net::Socket(this->family, this->type, this->proto, client_sockfd);
}

void wmkc::net::Socket::send(const std::string content, const wmkc_s32 flag)
{
    this->transmissionLength = ::send(this->fd, (wmkcNetBufT *)content.c_str(), content.size(), flag);

    if(this->transmissionLength == WMKC_NET_ERROR) {
        wmkc::net::exception("wmkc::net::Socket::send");
    }
}

void wmkc::net::Socket::sendall(const std::string content, const wmkc_s32 flag)
{
    wmkcNetBufT *offset_ptr = (wmkcNetBufT *)content.c_str();
    uint32_t size = (socklen_t)content.size();
    uint32_t retry_count = 5;

    while(size) {
        this->transmissionLength = ::send(this->fd, offset_ptr, size, flag);

        if((this->transmissionLength == WMKC_NET_ERROR) && (retry_count--)) {
            // 将retry_count放入此块中，并判断是否为0，如果是，那么就返回一个false
            // 同时记得改变这些函数的返回类型为布尔型
            continue;
        }

        offset_ptr += this->transmissionLength;
        size -= this->transmissionLength;
    }
}

std::string wmkc::net::Socket::recv(const wmkc_s32 len, const wmkc_s32 flag)
{
    wmkcNetBufT *buffer = new wmkcNetBufT[len];
    if(!buffer) {
        wmkc::exception(wmkcErr_ErrMemory, "wmkc::net::Socket::recv",
            "Failed to allocate memory for buffer.");
    }

    if((this->transmissionLength = ::recv(this->fd, buffer, len, flag)) == WMKC_NET_ERROR) {
        delete[] buffer;
        wmkc::net::exception("wmkc::net::Socket::recv");
    }

    std::string content((wmkcChar *)buffer, this->transmissionLength);

    delete[] buffer;
    return content;
}

void wmkc::net::Socket::sendto(const std::string content, wmkc::net::IPEndPoint target, const wmkc_s32 flag)
{
    ADDRINFO *sockAddrResult = wmkc::net::getAddrInfo(this->family, this->type, this->proto,
        target.addr, std::to_string(target.port));

    this->transmissionLength = ::sendto(this->fd, content.c_str(), content.size(), flag,
        sockAddrResult->ai_addr, sockAddrResult->ai_addrlen);
    if(this->transmissionLength == WMKC_NET_ERROR) {
        freeaddrinfo(sockAddrResult);
        wmkc::net::exception("wmkc::net::Socket::send");
    }

    freeaddrinfo(sockAddrResult);
}

std::string wmkc::net::Socket::recvfrom(const wmkc_s32 len, SOCKADDR *from, socklen_t *fromlen, const wmkc_s32 flag)
{
    wmkcNetBufT *buffer = new wmkcNetBufT[len];
    if(!buffer) {
        wmkc::exception(wmkcErr_ErrMemory, "wmkc::net::Socket::recvfrom",
            "Failed to allocate memory for buffer.");
    }

    if((this->transmissionLength = ::recvfrom(this->fd, buffer, len, flag, from, fromlen)) == WMKC_NET_ERROR) {
        delete[] buffer;
        exception("wmkc::net::Socket::recvfrom");
    }

    std::string content((wmkcChar *)buffer, this->transmissionLength);

    delete[] buffer;
    return content;
}

void wmkc::net::Socket::shutdown(const wmkc_s32 how)
{
    if(::shutdown(this->fd, how) == WMKC_NET_ERROR) {
        wmkc::net::exception("wmkc::net::Socket::shutdown");
    }
}

void wmkc::net::Socket::close()
{
#   if defined(WMKC_PLATFORM_WINOS)
    if(::closesocket(this->fd) == WMKC_NET_ERROR)
#   elif defined(WMKC_PLATFORM_LINUX)
    if(::close(this->fd) == WMKC_NET_ERROR)
#   endif
    {
        wmkc::net::exception("wmkc::net::Socket::close");
    }
}
