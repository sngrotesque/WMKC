import binascii
import random
import struct
import time
import os

import wtools

# def create_random_key_iv(key_len, iv_len):
#     a = '!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~'
#     return ''.join(random.sample(a, key_len)), ''.join(random.sample(a, iv_len))

# def hexToBytesAndPrint(data :str):
#     return binascii.a2b_hex(''.join(data.strip().split()))

def convert(srcPath :str, dstPath :str):
    wtools.imgToTextImage(srcPath, dstPath, resize_factor=0.5).draw(blackAndWhite = True, brightnessLevel = 16)

src_path = 'C:/Users/sn/Desktop/字符视频/original'
dst_path = 'C:/Users/sn/Desktop/字符视频/results'

src_path_list = [f'{src_path}/{x}' for x in os.listdir(src_path)]
image_total = len(src_path_list)
dst_path_list = [f'{dst_path}/result{x}.jpg' for x in range(image_total)]

for x in range(image_total):
    if os.path.exists(dst_path_list[x]):
        continue
    print(f'\rprocess: {x}/{image_total}, {(x/image_total)*100:.2f}%.', end='')
    convert(src_path_list[x], dst_path_list[x])

