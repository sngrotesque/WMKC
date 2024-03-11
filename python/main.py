from Crypto.Cipher import AES
from hexdump import hexdump
import binascii
import random

def create_random_key_iv(key_len, iv_len):
    a = '!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~'
    return ''.join(random.sample(a, key_len)), ''.join(random.sample(a, iv_len))

def hexToBytesAndPrint(data :str):
    return binascii.a2b_hex(''.join(data.strip().split()))

def aes_encrypt(data :bytes):
    aes = AES.new(key = b'0123456789abcdef0123456789abcdef', IV = b'0123456789abcdef', mode = AES.MODE_CFB, segment_size = 64)
    return aes.encrypt(data)

res = hexToBytesAndPrint('''61 73 6b 64 31 30 33 75 35 30 38 44 47 29 68 31 39 33 35 68 39 67 61 28 47 30 39 31 67 35 31 2d
        33 35 31 33 34 39 30 39 38 64 2d 38 30 67 3d 31 33 29 73 64 27 66 6c 5b 34 31 36 34 2d 31 39 5d''')
print(res)


