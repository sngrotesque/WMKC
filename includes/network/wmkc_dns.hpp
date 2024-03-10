#include <config/wmkc.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_DNS
#define WMKC_CPP_DNS
#include <network/wmkc_net.hpp>
#include <vector>
#include <sstream>

namespace wmkc {
    namespace net {
        std::string dns(std::string hostname, std::string dnsServer);
    }
}

#endif
#endif
