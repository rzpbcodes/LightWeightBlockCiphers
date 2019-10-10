import random
import time
from builtins import print

from LED_64.LED_64_4s import *
from LED_64.LED_64_4 import *
from LED_64.LED_64_8 import *
from LED_64.LED_64_16 import *
from LED_64.LED_64_32 import *
from LED_64.LED_64_64 import *

from LED_128.LED_128_4s import *
from LED_128.LED_128_4 import *
from LED_128.LED_128_8 import *
from LED_128.LED_128_16 import *
from LED_128.LED_128_32 import *
from LED_128.LED_128_64 import *

from LED_80.LED_80_4s import *
from LED_80.LED_80_4 import *
from LED_80.LED_80_8 import *
from LED_80.LED_80_16 import *
from LED_80.LED_80_32 import *
from LED_80.LED_80_64 import *

from LED_64_D.LED_64_4_D1 import *
from LED_64_D.LED_64_4_D2 import *

from PRESENT_80.PRESENT_80_4 import *

def getRandomArray(len):
    data = [None]*len;
    for i in range(0,len,1):
        data[i] = random.randint(0,255)
    return data

def printArray(data, len):
    for i in range(0, len):
        print(format(data[i], '0X'), " ", end='')
    print("")
    return

def byte2nibble(byteArr, offSet):
    b = [None] * (len(byteArr) * 2)
    for i in range(0, len(byteArr), 1):
        b[i * 2 + 0] = byteArr[offSet + i] & 0x0F;
        b[i * 2 + 1] = (byteArr[offSet + i] >> 4) & 0x0F;
    return b

def TestVectors64(Encrypt, name):
    plain = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]
    key = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]

    ciphertext = Encrypt(plain, key)
    ciphertext = byte2nibble(ciphertext, 0)

    print(name + " TestVector: ", end="")
    printArray(ciphertext, len(ciphertext))
    return

def TestVectors128(Encrypt, name):
    plain = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]
    key = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]

    ciphertext = Encrypt(plain, key)
    ciphertext = byte2nibble(ciphertext, 0)

    print(name + " TestVector: ", end="")
    printArray(ciphertext, len(ciphertext))
    return

def TestVectors80(Encrypt, name):
    plain = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]
    key = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 0x10, 0x32]

    ciphertext = Encrypt(plain, key)
    ciphertext = byte2nibble(ciphertext, 0)

    print(name + " TestVector: ", end="")
    printArray(ciphertext, len(ciphertext))
    return

def presentTestVectors80(Encrypt, name):
    plain = [0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ]
    key = [0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF]

    ciphertext = Encrypt(plain, key)
    ciphertext = byte2nibble(ciphertext, 0)

    print(name + " TestVector: ", end="")
    printArray(ciphertext, len(ciphertext))
    return

def TestVectors64Decryption(Decrypt, name):
    plain = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]
    key = [0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]

    ciphertext = LED_64_4.Encrypt(plain, key)
    _PT = Decrypt(ciphertext,key)

    plain = byte2nibble(plain,0)
    ciphertext = byte2nibble(ciphertext, 0)
    _PT = byte2nibble(_PT, 0)

    print(name + " TestVector: ", end="\n")
    printArray(plain, len(plain))
    printArray(ciphertext, len(ciphertext))
    printArray(_PT, len(_PT))
    return

def PerformTest(Encrypt, name, blockCounts, keySize, iterCount):
    dataSize = blockCount * 8
    input = getRandomArray(dataSize)
    key = getRandomArray(keySize)

    totalBytes = dataSize * iterCount

    start = time.time()
    for i in range(0,iterCount,1):
        input = Encrypt(input,key)
    end = time.time()

    diff = end - start
    throughPut = totalBytes / diff
    throughPut /= 1024
    print(name + " Throughput: " + format(throughPut,"0.2f") + " kb/s")
    return


while(True):
    print("\n1. LED_64\n2. LED 80\n3. LED 128\n4. PRESENT-80\n5. LED_64_Decryption\n6. Exit")
    ch = input("Enter your Choice = ")
    print()
    if ch == '1' or ch =='2' or ch =='3' or ch == '4' or ch=='5':
        limit = 10000
        blockCount = (int)(input("Number of Blocks per Encryption(1-" + str(limit) + ") = "))
        if blockCount > limit:
            blockCount = limit
        iterCount = (int)(input("Number of iteration(100-10000) = "))
        if ch=='1':
            keySize = 8
            Encrypt = LED_64_4s.Encrypt
            TestVectors64(Encrypt, "LED_64_4s")
            PerformTest(Encrypt, "LED_64_4s", blockCount, keySize, iterCount)

            Encrypt = LED_64_4.Encrypt
            TestVectors64(Encrypt, "LED_64_4")
            PerformTest(Encrypt, "LED_64_4", blockCount, keySize, iterCount*4)

            Encrypt = LED_64_8.Encrypt
            TestVectors64(Encrypt, "LED_64_8")
            PerformTest(Encrypt, "LED_64_8", blockCount, keySize, iterCount*8)

            Encrypt = LED_64_16.Encrypt
            TestVectors64(Encrypt, "LED_64_16")
            PerformTest(Encrypt, "LED_64_16", blockCount, keySize, iterCount*16)

            Encrypt = LED_64_32.Encrypt
            TestVectors64(Encrypt, "LED_64_32")
            PerformTest(Encrypt, "LED_64_32", blockCount, keySize, iterCount*32)

            Encrypt = LED_64_64.Encrypt
            TestVectors64(Encrypt, "LED_64_64")
            PerformTest(Encrypt, "LED_64_64", blockCount, keySize, iterCount*64)
        elif ch == '2':
            keySize = 10
            Encrypt = LED_80_4s.Encrypt
            TestVectors80(Encrypt, "LED_80_4s")
            PerformTest(Encrypt, "LED_80_4s", blockCount, keySize, iterCount)

            Encrypt = LED_80_4.Encrypt
            TestVectors80(Encrypt, "LED_80_4")
            PerformTest(Encrypt, "LED_80_4", blockCount, keySize, iterCount*4)

            Encrypt = LED_80_8.Encrypt
            TestVectors80(Encrypt, "LED_80_8")
            PerformTest(Encrypt, "LED_80_8", blockCount, keySize, iterCount*8)

            Encrypt = LED_80_16.Encrypt
            TestVectors80(Encrypt, "LED_80_16")
            PerformTest(Encrypt, "LED_80_16", blockCount, keySize, iterCount*16)

            Encrypt = LED_80_32.Encrypt
            TestVectors80(Encrypt, "LED_80_32")
            PerformTest(Encrypt, "LED_80_32", blockCount, keySize, iterCount*32)

            Encrypt = LED_80_64.Encrypt
            TestVectors80(Encrypt, "LED_80_64")
            PerformTest(Encrypt, "LED_80_64", blockCount, keySize, iterCount*64)
        elif ch == '3':
            keySize = 16
            Encrypt = LED_128_4s.Encrypt
            TestVectors128(Encrypt, "LED_128_4s")
            PerformTest(Encrypt, "LED_128_4s", blockCount, keySize, iterCount)

            Encrypt = LED_128_4.Encrypt
            TestVectors128(Encrypt, "LED_128_4")
            PerformTest(Encrypt, "LED_128_4", blockCount, keySize, iterCount*4)

            Encrypt = LED_128_8.Encrypt
            TestVectors128(Encrypt, "LED_128_8")
            PerformTest(Encrypt, "LED_128_8", blockCount, keySize, iterCount*8)

            Encrypt = LED_128_16.Encrypt
            TestVectors128(Encrypt, "LED_128_16")
            PerformTest(Encrypt, "LED_128_16", blockCount, keySize, iterCount*16)

            Encrypt = LED_128_32.Encrypt
            TestVectors128(Encrypt, "LED_128_32")
            PerformTest(Encrypt, "LED_128_32", blockCount, keySize, iterCount*32)

            Encrypt = LED_128_64.Encrypt
            TestVectors128(Encrypt, "LED_128_64")
            PerformTest(Encrypt, "LED_128_64", blockCount, keySize, iterCount*64)
        elif ch == '4':
            keySize = 10
            Encrypt = PRESENT_80_4.Encrypt
            presentTestVectors80(Encrypt, "PRESENT_80_4")
            PerformTest(Encrypt, "PRESENT_80_4", blockCount, keySize, iterCount)
        elif ch=='5':
            keySize = 8
            Encrypt = LED_64_4_D1.Decrypt
            TestVectors64Decryption(Encrypt, "LED_64_4_D1")
            PerformTest(Encrypt, "LED_64_4_D1", blockCount, keySize, iterCount * 4)

            Encrypt = LED_64_4_D2.Decrypt
            TestVectors64Decryption(Encrypt, "LED_64_4_D2")
            PerformTest(Encrypt, "LED_64_4_D2", blockCount, keySize, iterCount * 4)
    elif ch=='6':
        break
    else:
        print("\nWrong Input\n")
