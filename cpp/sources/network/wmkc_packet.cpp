#include <network/wmkc_packet.hpp>

wmkc::net::packet::packet(wmkc::net::Socket current_fd)
: fd(current_fd), seq(), length(), crc(), data(), digest()
{
    memcpy(this->end, WMKC_PACKET_END, WMKC_PACKET_END_LEN);
}

wVoid wmkc::net::packet::send(std::string content)
{
    std::string packet;
    wmkc::structure _struct;
    wByte *p = nullptr;
    // begin
    // 1. get seq, and seq -> BBBB, (2333 -> 00 00 09 1d)
    packet.append(_struct.pack("!I", {this->seq}));

    // 2. get length, and Length -> BBBB, (72542384 -> 04 52 e8 b0)
    this->length = content.size();
    packet.append(_struct.pack("!I", {this->length}));

    // 3. get crc32, (00 00 09 1d 04 52 e8 b0 -> CRC32 -> 1740733043 -> 67 c1 7a 73)
    p = (wByte *)packet.c_str();
    this->crc = crc32(0, p, packet.size());
    packet.append(_struct.pack("!I", {this->crc}));

    // 4. add data...
    packet.append(content);

    // 5. get data hash digest, and merge...
    // ...

    // 6. merge end...
    packet.append(WMKC_PACKET_END, WMKC_PACKET_END_LEN);

    // 7. send.
    this->fd.send(packet);

    // end
    
    // over
    this->seq++;
}

std::string wmkc::net::packet::recv()
{
    
}
