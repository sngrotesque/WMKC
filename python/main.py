import binascii
import random
import struct
import time
import os

import wtools

def create_random_key_iv(key_len, iv_len):
    a = '!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~'
    return ''.join(random.sample(a, key_len)), ''.join(random.sample(a, iv_len))

def hexToBytesAndPrint(data :str):
    return binascii.a2b_hex(''.join(data.strip().split()))

ctx = wtools.imgToTextImage(r'F:/Pitchers/QQ/QQ_Images/QQ图片20240310213931.jpg', 'C:/Users/sn/Desktop/py/result_8_level.jpg')
ctx.draw(show = True, blackAndWhite = True)
