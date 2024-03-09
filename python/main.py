import wtools

import random

a = '!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~'

print(''.join(random.sample(a, 32)))
print(''.join(random.sample(a, 16)))



