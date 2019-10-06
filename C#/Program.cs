using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Security.Cryptography;

namespace LW_BlockCiphersCSharp
{
    class Program
    {
        static RNGCryptoServiceProvider rng = new RNGCryptoServiceProvider();

        static byte[] getRandomArray(int len)
        {
            byte[] data = new byte[len];
            rng.GetBytes(data);
            return data;
        }

        public static void printArray(byte[] data, int len)
        {
            for (int i = 0; i < len; i++)
            {
                Console.Write(data[i].ToString("X"));
                Console.Write(" ");
            }
            Console.WriteLine("");
        }

        static void printArray(byte[] data, int len, string delim)
        {
            for (int i = 0; i < len; i++)
            {
                Console.Write(data[i].ToString(delim));
                Console.Write(" ");
            }
            Console.WriteLine("");
        }

        static byte[] byte2nibble(byte[] bytes, int offSet)
        {
            byte[] b = new byte[bytes.Length * 2];
            for (int i = 0; i < bytes.Length; i++)
            {
                b[i * 2 + 0] = (byte)(bytes[offSet + i] & 0x0F);
                b[i * 2 + 1] = (byte)(bytes[offSet + i] >> 4 & 0xF);
            }
            return b;
        }

        static Stopwatch sWatch = new Stopwatch();
        delegate byte[] encFn(byte[] input, byte[] key);

        static void TestVectors64(encFn Encrypt, string name)
        {
            byte[] plaintext = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] key = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] ciphertext;

            ciphertext = Encrypt(plaintext, key);
            ciphertext = byte2nibble(ciphertext, 0);

            Console.Write(name + " TestVector: ");
            printArray(ciphertext, ciphertext.Length);
        }

        static void TestVectors80(encFn Encrypt, string name)
        {
            byte[] plaintext = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] key = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 0x10, 0x32 };
            byte[] ciphertext;

            ciphertext = Encrypt(plaintext, key);
            ciphertext = byte2nibble(ciphertext, 0);

            Console.Write(name + " TestVector: ");
            printArray(ciphertext, ciphertext.Length);
        }

        static void TestVectors128(encFn Encrypt, string name)
        {
            byte[] plaintext = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] key = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] ciphertext;

            ciphertext = Encrypt(plaintext, key);
            ciphertext = byte2nibble(ciphertext, 0);

            Console.Write(name + " TestVector: ");
            printArray(ciphertext, ciphertext.Length);
        }

        static void presentTestVectors80(encFn Encrypt, string name)
        {
            byte[] plaintext = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] key = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 0x10, 0x32 };
            byte[] ciphertext;

            plaintext = new byte[8] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
            key = new byte[10] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

            ciphertext = Encrypt(plaintext, key);
            ciphertext = byte2nibble(ciphertext, 0);

            Console.Write(name + " TestVector: ");
            printArray(ciphertext, ciphertext.Length);
        }

        static void TestVectors64Decryption(encFn Decrypt, string name)
        {
            byte[] plaintext = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] key = new byte[] { 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
            byte[] ciphertext;

            ciphertext = LED_64_4.Encrypt(plaintext, key);

            byte[] _PT = Decrypt(ciphertext, key);

            plaintext = byte2nibble(plaintext, 0);
            ciphertext = byte2nibble(ciphertext, 0);
            _PT = byte2nibble(_PT, 0);

            Console.WriteLine(name + " TestVector: ");
            printArray(plaintext, plaintext.Length);
            printArray(ciphertext, ciphertext.Length);
            printArray(_PT, _PT.Length);
        }


        static void PerformTest(encFn Encrypt, string name, int blockCounts, int keySize, int iterCount)
        {
            int dataSize = blockCounts * 8;
            byte[] input;
            byte[] key;

            input = getRandomArray(dataSize);
            key = getRandomArray(keySize);

            double totalBytes = dataSize * iterCount;

            sWatch.Reset();
            sWatch.Start();
            for (int i = 0; i < iterCount; i++)
                input = Encrypt(input, key);
            sWatch.Stop();

            double throughPut = totalBytes / sWatch.Elapsed.TotalSeconds;
            throughPut /= 1024;

            Console.WriteLine(name + " Throughput: " + throughPut.ToString("f2") + " KB/s");
        }

        static void Main(string[] args)
        {
            encFn Encrypt;

            while (true)
            {
                try
                {
                    Console.WriteLine("\n1. LED_64\n2. LED 80\n3. LED 128\n4. PRESENT-80\n5. LED_64_Decryption\n6. Exit");
                    Console.Write("Enter Your Choice = ");
                    char ch = Console.ReadLine()[0];
                    Console.WriteLine("\n");
                    if (ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5')
                    {
                        int limit = 10000;
                        Console.Write("Number of Blocks per Encryption(0-" + limit + ") = ");
                        int blockCount = int.Parse(Console.ReadLine());
                        if (blockCount > limit)
                            blockCount = limit;
                        Console.Write("Number of iteration(1000-100000) = ");
                        int iterCount = int.Parse(Console.ReadLine());

                        if (ch == '1')
                        {
                            int keySize = 8;

                            Encrypt = LED_64_4s.Encrypt;
                            TestVectors64(Encrypt, "LED_64_4s");
                            PerformTest(Encrypt, "LED_64_4s", blockCount, keySize, iterCount);
                            Console.WriteLine("");

                            Encrypt = LED_64_4.Encrypt;
                            TestVectors64(Encrypt, "LED_64_4");
                            PerformTest(Encrypt, "LED_64_4", blockCount, keySize, iterCount * 4);
                            Console.WriteLine("");

                            Encrypt = LED_64_8.Encrypt;
                            TestVectors64(Encrypt, "LED_64_8");
                            PerformTest(Encrypt, "LED_64_8", blockCount, keySize, iterCount * 8);
                            Console.WriteLine("");

                            Encrypt = LED_64_16.Encrypt;
                            TestVectors64(Encrypt, "LED_64_16");
                            PerformTest(Encrypt, "LED_64_16", blockCount, keySize, iterCount * 16);
                            Console.WriteLine("");

                            Encrypt = LED_64_32.Encrypt;
                            TestVectors64(Encrypt, "LED_64_32");
                            PerformTest(Encrypt, "LED_64_32", blockCount, keySize, iterCount * 32);
                            Console.WriteLine("");

                            Encrypt = LED_64_64.Encrypt;
                            TestVectors64(Encrypt, "LED_64_64");
                            PerformTest(Encrypt, "LED_64_64", blockCount, keySize, iterCount * 64);
                            Console.WriteLine("");
                        }
                        else if (ch == '2')
                        {
                            int keySize = 10;

                            Encrypt = LED_80_4s.Encrypt;
                            TestVectors80(Encrypt, "LED_80_4s");
                            PerformTest(Encrypt, "LED_80_4s", blockCount, keySize, iterCount);
                            Console.WriteLine("");

                            Encrypt = LED_80_4.Encrypt;
                            TestVectors80(Encrypt, "LED_80_4");
                            PerformTest(Encrypt, "LED_80_4", blockCount, keySize, iterCount * 4);
                            Console.WriteLine("");

                            Encrypt = LED_80_8.Encrypt;
                            TestVectors80(Encrypt, "LED_80_8");
                            PerformTest(Encrypt, "LED_80_8", blockCount, keySize, iterCount * 8);
                            Console.WriteLine("");

                            Encrypt = LED_80_16.Encrypt;
                            TestVectors80(Encrypt, "LED_80_16");
                            PerformTest(Encrypt, "LED_80_16", blockCount, keySize, iterCount * 16);
                            Console.WriteLine("");

                            Encrypt = LED_80_32.Encrypt;
                            TestVectors80(Encrypt, "LED_80_32");
                            PerformTest(Encrypt, "LED_80_32", blockCount, keySize, iterCount * 32);
                            Console.WriteLine("");

                            Encrypt = LED_80_64.Encrypt;
                            TestVectors80(Encrypt, "LED_80_64");
                            PerformTest(Encrypt, "LED_80_64", blockCount, keySize, iterCount * 64);
                            Console.WriteLine("");
                        }
                        else if (ch == '3')
                        {
                            int keySize = 16;

                            Encrypt = LED_128_4s.Encrypt;
                            TestVectors128(Encrypt, "LED_128_4s");
                            PerformTest(Encrypt, "LED_128_4s", blockCount, keySize, iterCount);
                            Console.WriteLine("");

                            Encrypt = LED_128_4.Encrypt;
                            TestVectors128(Encrypt, "LED_128_4");
                            PerformTest(Encrypt, "LED_128_4", blockCount, keySize, iterCount * 4);
                            Console.WriteLine("");

                            Encrypt = LED_128_8.Encrypt;
                            TestVectors128(Encrypt, "LED_128_8");
                            PerformTest(Encrypt, "LED_128_8", blockCount, keySize, iterCount * 8);
                            Console.WriteLine("");

                            Encrypt = LED_128_16.Encrypt;
                            TestVectors128(Encrypt, "LED_128_16");
                            PerformTest(Encrypt, "LED_128_16", blockCount, keySize, iterCount * 16);
                            Console.WriteLine("");

                            Encrypt = LED_128_32.Encrypt;
                            TestVectors128(Encrypt, "LED_128_32");
                            PerformTest(Encrypt, "LED_128_32", blockCount, keySize, iterCount * 32);
                            Console.WriteLine("");

                            Encrypt = LED_128_64.Encrypt;
                            TestVectors128(Encrypt, "LED_128_64");
                            PerformTest(Encrypt, "LED_128_64", blockCount, keySize, iterCount * 64);
                            Console.WriteLine("");
                        }
                        else if (ch == '4')
                        {
                            int keySize = 10;

                            Encrypt = PRESENT_80_4.Encrypt;
                            presentTestVectors80(Encrypt, "PRESENT_80_4");
                            PerformTest(Encrypt, "PRESENT_80_4", blockCount, keySize, iterCount * 4);
                            Console.WriteLine("");
                        }
                        else if (ch == '5')
                        {
                            int keySize = 10;

                            Encrypt = LED_64_4_D1.Decrypt;
                            TestVectors64Decryption(Encrypt, "LED_64_4_D1");
                            PerformTest(Encrypt, "LED_64_4_D", blockCount, keySize, iterCount * 4);
                            Console.WriteLine("");

                            Encrypt = LED_64_4_D2.Decrypt;
                            TestVectors64Decryption(Encrypt, "LED_64_4_D2");
                            PerformTest(Encrypt, "LED_64_4_D", blockCount, keySize, iterCount * 4);
                            Console.WriteLine("");
                        }
                    }
                    else if (ch == '6')
                    {
                        break;
                    }
                    else
                    {
                        Console.WriteLine("Wrong Input");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }
    }
}
