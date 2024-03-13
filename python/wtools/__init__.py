from .compression import gzip_comp, gzip_decomp, zlib_comp, zlib_decomp, lzma2_comp, lzma2_decomp
from .crypto import aes_encrypt, aes_decrypt, hash_sum, zlib_crc32

from .packet import packet

from .socket import tcp_socket, udp_socket

def fread(path :str, open_mode :str = 'rb', encoding :str = None):
        with open(path, open_mode, encoding = encoding) as f_obj:
            return f_obj.read()

def fwrite(path :str, open_mode :str = 'wb', content :bytes = None, encoding :str = None):
    with open(path, open_mode, encoding = encoding) as f_obj:
        return f_obj.write(content)
