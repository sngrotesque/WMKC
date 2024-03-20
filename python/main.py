import binascii
import random
import struct

import wtools

def create_random_key_iv(key_len, iv_len):
    a = '!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~'
    return ''.join(random.sample(a, key_len)), ''.join(random.sample(a, iv_len))

def hexToBytesAndPrint(data :str):
    return binascii.a2b_hex(''.join(data.strip().split()))


content = '''
00 00 00 00 00 00 00 01 00 00 00 02 00 00 00 03 00 00 00 04 40 14 00 00 00 00 00 00 43 e1 a7 8d
'''
res = struct.unpack("!QIIIdf", hexToBytesAndPrint(content))
print(res)
