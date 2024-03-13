/*
* 此C++代码的一切请参考自己编写的Python代码中的packet.py进行编写
*/

#include <config/wmkc.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_PACKET
#define WMKC_CPP_PACKET

#include <network/wmkc_net.hpp>
#include <crypto/hashlib.hpp>
#include <wmkc_struct.hpp>

#include <zlib.h>
#include <lzma.h>

namespace wmkc {
    namespace net {
        class packet {
            private:
                net::Socket fd;

            public:
                packet(net::Socket current_fd);
                wVoid send(std::string content);
                std::string recv();
        };
    };
}

#endif
#endif
