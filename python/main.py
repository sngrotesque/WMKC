import wtools

import binascii


a = '''10 cc 41 29 06 ab cc be 33 96 81 6f 26 f8 e3 6f d4 ae ea 87 54 5c 26 ce 56 00 b1 43 e8 e2 24 d8
        cc 89 81 b5 74 c4 c9 0e a9 55 b9 88 27 26 a6 8f 54 8d c3 7d 7e b8 cb 3b 36 2b d6 3a 09 50 aa 97
        e7 2e 99 6c 1c 0e 58 77 60 b3 43 09 03 1e b6 61 41 5c 6b 59 d5 81 be 7b de 33 da b4 bf 94 b9 0a'''
a = ''.join(a.split())
res = binascii.a2b_hex(a)

print(res)

