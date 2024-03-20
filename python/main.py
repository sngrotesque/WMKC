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
00 00 00 00 00 00 00 00 00 00 01 eb 00 00 00 00 00 00 7f fb 00 00 00 00 40 48 f5 c3
'''
res = struct.unpack("!dddf", hexToBytesAndPrint(content))
print(res)
