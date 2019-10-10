package lw.blockciphersjava;

import lw.blockciphersjava.LED_64.*;
import lw.blockciphersjava.LED_128.*;
import lw.blockciphersjava.LED_80.*;
import lw.blockciphersjava.PRESENT_80.*;
import lw.blockciphersjava.LED_64_D.*;

import java.util.Random;
import java.util.Scanner; 
import java.io.FileWriter;


public class LWBlockCiphersJava {

    static Random rnd = new Random();
    
    static short[] getRandomArray(int len)
    {
        short[] data = new short[len];
        for(int i=0;i<len;i++)
            data[i] = (short)rnd.nextInt(256);
        return data;
    }
    
    static void printArray(short []data, int len)
    {
        for(int i=0;i<len;i++)
        {
            System.out.print(String.format("%X", (data[i])));
            System.out.print(" ");
        }
        System.out.print("\n");
    }
    
    private static short[] byte2nibble(short[] bytes, int offSet)
    {
        short[] b = new short[bytes.length * 2];
        for (int i = 0; i < bytes.length; i++)
        {
            b[i * 2 + 0] = (byte)(bytes[offSet + i] & 0x0F);
            b[i * 2 + 1] = (byte)(bytes[offSet + i] >>> 4 & 0xF);
        }
        return b;
    }
    
    interface encFn
    {
        public short[] Encrypt(short[] input, short[] key);
    }
    
    private static void TestVectors64(encFn Encrypt, String name)
    {
        short[] plaintext = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe};
        short[] key = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe};
        
        short[] ciphertext;
        
        ciphertext = Encrypt.Encrypt(plaintext, key);
        ciphertext = byte2nibble(ciphertext,0);
        
        System.out.println(name + " TestVector: ");
        printArray(ciphertext, ciphertext.length);
    }
    
    private static void TestVectors80(encFn Encrypt, String name)
    {
        short[] plaintext = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe};
        short[] key = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe,0x10, 0x32};
        
        short[] ciphertext;
        
        ciphertext = Encrypt.Encrypt(plaintext, key);
        ciphertext = byte2nibble(ciphertext,0);
        
        System.out.println(name + " TestVector: ");
        printArray(ciphertext, ciphertext.length);
    }
    
    private static void TestVectors128(encFn Encrypt, String name)
    {
        short[] plaintext = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe};
        short[] key = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe, 0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe};
        
        short[] ciphertext;
        
        ciphertext = Encrypt.Encrypt(plaintext, key);
        ciphertext = byte2nibble(ciphertext,0);
        
        System.out.println(name + " TestVector: ");
        printArray(ciphertext, ciphertext.length);
    }
    
     private static void presentTestVectors80(encFn Encrypt, String name)
    {
        short[] plaintext = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe};
        short[] key = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe,0x10, 0x32};
        
        plaintext = new short[]{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        key = new short[]{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        
        short[] ciphertext;
        
        ciphertext = Encrypt.Encrypt(plaintext, key);
        ciphertext = byte2nibble(ciphertext,0);
        
        System.out.println(name + " TestVector: ");
        printArray(ciphertext, ciphertext.length);
    }
     
    private static void TestVectors64Decryption(encFn Decrypt, String name)
    {
        short[] plaintext = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe};
        short[] key = new short[] {0x10, 0x32, 0x54, 0x76,0x98,0xba,0xdc,0xfe,0x10, 0x32};
        short[] ciphertext;
        
        ciphertext = LED_64_4.Encrypt(plaintext, key);
        
        short[] _PT = Decrypt.Encrypt(ciphertext, key);

        plaintext = byte2nibble(plaintext, 0);
        ciphertext = byte2nibble(ciphertext, 0);
        _PT = byte2nibble(_PT, 0);

        System.out.println(name + " TestVector: ");
        printArray(plaintext, plaintext.length);
        printArray(ciphertext, ciphertext.length);
        printArray(_PT, _PT.length);
    }
    
    private static void PerformTest(encFn Encrypt, String name, int blockCounts, int keySize, int iterCount)
    {
        int dataSize = blockCounts * 8;
        short[] input;
        short[] key;

        input = getRandomArray(dataSize);
        key = getRandomArray(keySize);

        double totalBytes = dataSize * iterCount;
        
        long startTime = System.nanoTime();
        for (int i = 0; i < iterCount; i++)
            input = Encrypt.Encrypt(input, key);
        long endTime = System.nanoTime();
        
        double Elapsed = endTime - startTime;
        Elapsed = (Elapsed * 1.0)/1000/1000/1000;

        double throughPut = (totalBytes * 1.0) / Elapsed;
        throughPut /= 1024;
        
        System.out.println(name + " Throughput: " + String.format("%.2f", throughPut) + " kb/s");
    }
    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        
        encFn Encrypt;
        
        while(true)
        {
            try
            {
            System.out.println("\n1. LED_64\n2. LED 80\n3. LED 128\n4. PRESENT-80\n5. LED_64_Decryption\n6. Exit");
            System.out.print("Enter Your Choice = ");
            String ch = scan.next();
            System.out.println("");
            if (ch.equals("1") || ch.equals("2") || ch.equals("3") || ch.equals("4") || ch.equals("5"))
            {
                int limit = 10000;
                System.out.print("Number of Blocks per Encryption(0-" + limit + ") = ");
                int blockCount = Integer.parseInt(scan.next());
                if(blockCount > limit)
                    blockCount = limit;                    
                System.out.print("Number of iteration(1000-100000) = ");
                int iterCount = Integer.parseInt(scan.next());
                
                if (ch.equals("1"))
                {
                    int keySize = 8;

                    Encrypt = LED_64_4s::Encrypt;
                    TestVectors64(Encrypt, "LED_64_4s");
                    PerformTest(Encrypt, "LED_64_4s", blockCount, keySize, iterCount);
                    System.out.println("");

                    Encrypt = LED_64_4::Encrypt;
                    TestVectors64(Encrypt, "LED_64_4");
                    PerformTest(Encrypt, "LED_64_4", blockCount, keySize, iterCount * 4);
                    System.out.println("");

                    Encrypt = LED_64_8::Encrypt;
                    TestVectors64(Encrypt, "LED_64_8");
                    PerformTest(Encrypt, "LED_64_8", blockCount, keySize, iterCount * 8);
                    System.out.println("");

                    Encrypt = LED_64_16::Encrypt;
                    TestVectors64(Encrypt, "LED_64_16");
                    PerformTest(Encrypt, "LED_64_16", blockCount, keySize, iterCount * 16);
                    System.out.println("");

                    Encrypt = LED_64_32::Encrypt;
                    TestVectors64(Encrypt, "LED_64_32");
                    PerformTest(Encrypt, "LED_64_32", blockCount, keySize, iterCount * 32);
                    System.out.println("");

                    Encrypt = LED_64_64::Encrypt;
                    TestVectors64(Encrypt, "LED_64_64");
                    PerformTest(Encrypt, "LED_64_64", blockCount, keySize, iterCount * 64);
                    System.out.println("");
                }
                else if (ch.equals("2"))
                {
                    int keySize = 10;
                    Encrypt = LED_80_4s::Encrypt;
                    TestVectors80(Encrypt, "LED_80_4s");
                    PerformTest(Encrypt, "LED_80_4s", blockCount, keySize, iterCount);
                    System.out.println("");
                    
                    Encrypt = LED_80_4::Encrypt;
                    TestVectors80(Encrypt, "LED_80_4");
                    PerformTest(Encrypt, "LED_80_4", blockCount, keySize, iterCount*4);
                    System.out.println("");
                    
                    Encrypt = LED_80_8::Encrypt;
                    TestVectors80(Encrypt, "LED_80_8");
                    PerformTest(Encrypt, "LED_80_8", blockCount, keySize, iterCount*8);
                    System.out.println("");
                    
                    Encrypt = LED_80_16::Encrypt;
                    TestVectors80(Encrypt, "LED_80_16");
                    PerformTest(Encrypt, "LED_80_16", blockCount, keySize, iterCount*16);
                    System.out.println("");
                    
                    Encrypt = LED_80_32::Encrypt;
                    TestVectors80(Encrypt, "LED_80_32");
                    PerformTest(Encrypt, "LED_80_32", blockCount, keySize, iterCount*32);
                    System.out.println("");
                    
                    Encrypt = LED_80_64::Encrypt;
                    TestVectors80(Encrypt, "LED_80_64");
                    PerformTest(Encrypt, "LED_80_64", blockCount, keySize, iterCount*64);
                    System.out.println("");
                }
                else if (ch.equals("3"))
                {
                    int keySize = 16;
                    Encrypt = LED_128_4s::Encrypt;
                    TestVectors128(Encrypt, "LED_128_4s");
                    PerformTest(Encrypt, "LED_128_4s", blockCount, keySize, iterCount);
                    System.out.println("");
                    
                    Encrypt = LED_128_4::Encrypt;
                    TestVectors128(Encrypt, "LED_128_4");
                    PerformTest(Encrypt, "LED_128_4", blockCount, keySize, iterCount*4);
                    System.out.println("");
                    
                    Encrypt = LED_128_8::Encrypt;
                    TestVectors128(Encrypt, "LED_128_8");
                    PerformTest(Encrypt, "LED_128_8", blockCount, keySize, iterCount*8);
                    System.out.println("");
                    
                    Encrypt = LED_128_16::Encrypt;
                    TestVectors128(Encrypt, "LED_128_16");
                    PerformTest(Encrypt, "LED_128_16", blockCount, keySize, iterCount*16);
                    System.out.println("");
                    
                    Encrypt = LED_128_32::Encrypt;
                    TestVectors128(Encrypt, "LED_128_32");
                    PerformTest(Encrypt, "LED_128_32", blockCount, keySize, iterCount*32);
                    System.out.println("");

                    Encrypt = LED_128_64::Encrypt;
                    TestVectors128(Encrypt, "LED_128_64");
                    PerformTest(Encrypt, "LED_128_64", blockCount, keySize, iterCount*64);
                    System.out.println("");
                }
                else if (ch.equals("4"))
                {
                    int keySize = 10;
                    
                    Encrypt = PRESENT_80_4::Encrypt;
                    presentTestVectors80(Encrypt, "PRESENT_80_4");
                    PerformTest(Encrypt, "PRESENT_80_4", blockCount, keySize, iterCount*4);
                    System.out.println("");
                }
                else if(ch.equals("5"))
                {
                    int keySize = 8;
                    
                    Encrypt = LED_64_4_D1::Decrypt;
                    TestVectors64Decryption(Encrypt, "LED_64_4_D1");
                    PerformTest(Encrypt, "LED_64_4_D1", blockCount, keySize, iterCount * 4);
                    System.out.println("");
                    
                    Encrypt = LED_64_4_D2::Decrypt;
                    TestVectors64Decryption(Encrypt, "LED_64_4_D2");
                    PerformTest(Encrypt, "LED_64_4_D2", blockCount, keySize, iterCount * 4);
                    System.out.println("");
                }
            }
            else if(ch.equals("6"))
            {
                break;
            }
            else
            {
                System.out.println("\nWrong Input\n");
            }
            }
            catch(Exception ex)
            {
                System.out.println("Issue: "+ex.toString());
            }
            }
    }
}