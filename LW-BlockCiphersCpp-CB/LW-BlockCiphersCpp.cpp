#include <iostream>
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <thread>
#include <string>
#include <cstring>

#include "LED_64/LED-64-4s.h"
#include "LED_64/LED-64-4.h"
#include "LED_64/LED-64-8.h"
#include "LED_64/LED-64-16.h"
#include "LED_64/LED-64-32.h"
#include "LED_64/LED-64-64.h"

#include "LED_128/LED-128-4s.h"
#include "LED_128/LED-128-4.h"
#include "LED_128/LED-128-8.h"
#include "LED_128/LED-128-16.h"
#include "LED_128/LED-128-32.h"
#include "LED_128/LED-128-64.h"

#include "LED_80/LED-80-4s.h"
#include "LED_80/LED-80-4.h"
#include "LED_80/LED-80-8.h"
#include "LED_80/LED-80-16.h"
#include "LED_80/LED-80-32.h"
#include "LED_80/LED-80-64.h"

#include "PRESENT_80/PRESENT_80_4.h"
#include "LED_64_D/LED-64-4-D1.h"
#include "LED_64_D/LED-64-4-D2.h"

using namespace std;

unsigned char* getRandomArray(int len)
{
    unsigned char *data = new unsigned char[len];
    for(int i=0;i<len;i++)
	{
		unsigned char c = rand()%256;
        data[i] = c;
	}
    return data;
}

void printArray(unsigned char *data, int len)
{
	for(int i=0;i<len;i++)
    {
        cout <<hex<< (static_cast<int>(data[i]) & 0xFF);
        cout<<" ";
    }
    cout<<endl;
    std::cout<<std::dec;
}

unsigned char* byte2nibble(unsigned char bytes[], int offSet)
{
	unsigned char *b = new unsigned char[16];
	for (int i = 0; i < 8; i++)
	{
		b[i * 2 + 0] = static_cast<unsigned char>(bytes[offSet + i] & 0x0F);
		b[i * 2 + 1] = static_cast<unsigned char>(bytes[offSet + i] >> 4 & 0xF);
	}
	return b;
}

typedef unsigned char* (*encFn)(unsigned char input[], unsigned char key[], int len);

void TestVectors64(encFn Encrypt, string name)
{
    unsigned char input[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};
    unsigned char key[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};
    unsigned char *cipher;

    cipher = Encrypt(input,key,8);
    cipher = byte2nibble(cipher,0);

    cout<<name<<" TestVector: ";
    printArray(cipher,16);
}

void TestVectors128(encFn Encrypt, string name)
{
    unsigned char input[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};
    unsigned char key[16] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};
    unsigned char *cipher;

    cipher = Encrypt(input,key,8);
    cipher = byte2nibble(cipher,0);

    cout<<name<<" TestVector: ";
    printArray(cipher,16);
}

void TestVectors80(encFn Encrypt, string name)
{
    unsigned char input[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};
    unsigned char key[10] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 0x10, 0x32};
    unsigned char *cipher;

    cipher = Encrypt(input,key,8);
    cipher = byte2nibble(cipher,0);

    cout<<name<<" TestVector: ";
    printArray(cipher,16);
}

void presentTestVectors80(encFn Encrypt, string name)
{
    unsigned char input[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    unsigned char key[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    unsigned char *cipher;

    cipher = Encrypt(input,key,8);
    cipher = byte2nibble(cipher,0);

    cout<<name<<" TestVector: ";
    printArray(cipher,16);
}

void TestVectors64Decryption(encFn Decrypt, string name)
{
    unsigned char input[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};
    unsigned char key[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};
    unsigned char *cipher;

    cipher = LW_BlockCiphers::LED_64_4::Encrypt(input,key,8);
    unsigned char *_PT = Decrypt(cipher,key,8);

    unsigned char* _input = byte2nibble(input,0);
    cipher = byte2nibble(cipher,0);
    _PT = byte2nibble(_PT,0);

    cout<<name<<" TestVector: \n";
    printArray(_input,16);
    printArray(cipher,16);
    printArray(_PT,16);
}

void PerformTest(encFn Encrypt, string name, int blockCounts, int keySize, int iterCount)
{
    int dataSize = blockCounts * 8;
    unsigned char *input;
    unsigned char *key;

    input = getRandomArray(dataSize);
    key = getRandomArray(keySize);

    double totalBytes = dataSize * iterCount;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<iterCount; i++)
        {
            input = Encrypt(input, key, dataSize);
        }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    double throughPut = totalBytes / elapsed.count();
    throughPut /= 1024;

    cout<<name<<" Throughput: "<<throughPut<<" kb/s"<<endl;
}

int main()
{
    srand(time(0));

    encFn Encrypt;

    while(true)
    {
        try
        {
        cout<<"\n1. LED_64\n2. LED 80\n3. LED 128\n4. PRESENT-80\n5. LED_64_Decryption\n6. Exit\n";
        cout<<"Enter your choice = ";
        string ch;
        cin>>ch;
        cout<<endl;
        if(ch[0]=='1'||ch[0]=='2'||ch[0]=='3'||ch[0]=='4'||ch[0]=='5')
        {
            int limit = 10000;
            int blockCount = 0;
            cout<<"Number of Blocks per Encryption(0-"<<limit<<") = ";
            cin>>blockCount;
            if (blockCount > limit)
                blockCount = limit;
            cout<<"Number of iteration(1000-100000) = ";
            int iterCount = 0;
            cin>>iterCount;
            if(ch[0]=='1')
            {
                int keySize = 8;

                Encrypt = LW_BlockCiphers::LED_64_4s::Encrypt;
                TestVectors64(Encrypt, "LED_64_4s");
                PerformTest(Encrypt, "LED_64_4s", blockCount, keySize, iterCount);

                Encrypt = LW_BlockCiphers::LED_64_4::Encrypt;
                TestVectors64(Encrypt, "LED_64_4");
                PerformTest(Encrypt, "LED_64_4", blockCount, keySize, iterCount*4);

                Encrypt = LW_BlockCiphers::LED_64_8::Encrypt;
                TestVectors64(Encrypt, "LED_64_8");
                PerformTest(Encrypt, "LED_64_8", blockCount, keySize, iterCount*8);

                Encrypt = LW_BlockCiphers::LED_64_16::Encrypt;
                TestVectors64(Encrypt, "LED_64_16");
                PerformTest(Encrypt, "LED_64_16", blockCount, keySize, iterCount*16);

                Encrypt = LW_BlockCiphers::LED_64_32::Encrypt;
                TestVectors64(Encrypt, "LED_64_32");
                PerformTest(Encrypt, "LED_64_32", blockCount, keySize, iterCount*32);

                Encrypt = LW_BlockCiphers::LED_64_64::Encrypt;
                TestVectors64(Encrypt, "LED_64_64");
                PerformTest(Encrypt, "LED_64_64", blockCount, keySize, iterCount*64);
            }
            else if(ch[0]=='2')
            {
                int keySize = 10;

                Encrypt = LW_BlockCiphers::LED_80_4s::Encrypt;
                TestVectors80(Encrypt, "LED_80_4s");
                PerformTest(Encrypt, "LED_80_4s", blockCount, keySize, iterCount);

                Encrypt = LW_BlockCiphers::LED_80_4::Encrypt;
                TestVectors80(Encrypt, "LED_80_4");
                PerformTest(Encrypt, "LED_80_4", blockCount, keySize, iterCount*4);

                Encrypt = LW_BlockCiphers::LED_80_8::Encrypt;
                TestVectors80(Encrypt, "LED_80_8");
                PerformTest(Encrypt, "LED_80_8", blockCount, keySize, iterCount*8);

                Encrypt = LW_BlockCiphers::LED_80_16::Encrypt;
                TestVectors80(Encrypt, "LED_80_16");
                PerformTest(Encrypt, "LED_80_16", blockCount, keySize, iterCount*16);

                Encrypt = LW_BlockCiphers::LED_80_32::Encrypt;
                TestVectors80(Encrypt, "LED_80_32");
                PerformTest(Encrypt, "LED_80_32", blockCount, keySize, iterCount*32);

                Encrypt = LW_BlockCiphers::LED_80_64::Encrypt;
                TestVectors80(Encrypt, "LED_80_64");
                PerformTest(Encrypt, "LED_80_64", blockCount, keySize, iterCount*64);
            }
            else if(ch[0]=='3')
            {
                int keySize = 16;

                Encrypt = LW_BlockCiphers::LED_128_4s::Encrypt;
                TestVectors128(Encrypt, "LED_128_4s");
                PerformTest(Encrypt, "LED_128_4s", blockCount, keySize, iterCount);

                Encrypt = LW_BlockCiphers::LED_128_4::Encrypt;
                TestVectors128(Encrypt, "LED_128_4");
                PerformTest(Encrypt, "LED_128_4", blockCount, keySize, iterCount*4);

                Encrypt = LW_BlockCiphers::LED_128_8::Encrypt;
                TestVectors128(Encrypt, "LED_128_8");
                PerformTest(Encrypt, "LED_128_8", blockCount, keySize, iterCount*8);

                Encrypt = LW_BlockCiphers::LED_128_16::Encrypt;
                TestVectors128(Encrypt, "LED_128_16");
                PerformTest(Encrypt, "LED_128_16", blockCount, keySize, iterCount*16);

                Encrypt = LW_BlockCiphers::LED_128_32::Encrypt;
                TestVectors128(Encrypt, "LED_128_32");
                PerformTest(Encrypt, "LED_128_32", blockCount, keySize, iterCount*32);

                Encrypt = LW_BlockCiphers::LED_128_64::Encrypt;
                TestVectors128(Encrypt, "LED_128_64");
                PerformTest(Encrypt, "LED_128_64", blockCount, keySize, iterCount*64);
            }
            else if(ch[0]=='4')
            {
                int keySize = 10;

                Encrypt = LW_BlockCiphers::PRESENT_80_4::Encrypt;
                presentTestVectors80(Encrypt, "PRESENT_80_4");
                PerformTest(Encrypt, "PRESENT_80_4", blockCount, keySize, iterCount);
            }
            else if(ch[0]=='5')
            {
                int keySize = 8;

                Encrypt = LW_BlockCiphers::LED_64_4_D1::Decrypt;
                TestVectors64Decryption(Encrypt, "LED_64_4_D1");
                PerformTest(Encrypt, "LED_64_4_D1", blockCount, keySize, iterCount*4);

                cout<<"\n";
                Encrypt = LW_BlockCiphers::LED_64_4_D2::Decrypt;
                TestVectors64Decryption(Encrypt, "LED_64_4_D2");
                PerformTest(Encrypt, "LED_64_4_D2", blockCount, keySize, iterCount*4);
            }
        }
        else if(ch[0]=='6')
        {
            break;
        }
        else
        {
            cout<<"\nWrong Input\n";
        }
        }
        catch(exception ex)
        {
            cout<<"\nWrong Input\n";
        }
    }

    return 0;
}
