import re
import os
import ssl
import sys
import rsa
import gzip
import zlib
import time
import json
import qrcode
import socket
import struct
import random
import base64
import hashlib
import binascii
import requests
import threading
import numpy as np
from PIL import Image
from hexdump import hexdump
import matplotlib.pyplot as plt
from snpy import *

ctx = wmkcNet('127.0.0.1', 49281)
ctx.connect()
print(f'本机套接字：{ctx.sockfd.getsockname()}')
ctx.close()