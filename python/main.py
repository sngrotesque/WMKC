import wtools
import binascii
import random

def create_random_key_iv():
    a = '!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~'
    return ''.join(random.sample(a, 32)), ''.join(random.sample(a, 16))

def hexToBytesAndPrint(data :str):
    return binascii.a2b_hex(''.join(data.strip().split()))

a = '''
09 ed 24 dc c8 42 f9 de 1c c4 81 21 2a
'''
print(hexToBytesAndPrint(a))


