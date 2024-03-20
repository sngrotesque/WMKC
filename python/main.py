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
40 48 f5 c3 40 a0 00 00 3f b9 99 99 99 99 99 9a 40 48 f5 c3
'''
res = struct.unpack("!ffdf", hexToBytesAndPrint(content))
print(res)
