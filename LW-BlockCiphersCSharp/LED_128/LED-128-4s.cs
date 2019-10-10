using System;
using System.Collections.Generic;

using System.Text;

namespace LW_BlockCiphersCSharp
{
    class LED_128_4s
    {
        static byte keySize = 128;
        static byte keySizeConst0 = (byte)(keySize >> 4);
        static byte keySizeConst1 = (byte)(0x01 ^ (keySize >> 4));
        static byte keySizeConst2 = (byte)(0x02 ^ (keySize & 0x0F));
        static byte keySizeConst3 = (byte)(0x03 ^ (keySize & 0x0F));
        static byte[] sBox = new byte[] { 0x0C, 0x05, 0x06, 0x0B, 0x09, 0x00, 0x0A, 0x0D, 0x03, 0x0E, 0x0F, 0x08, 0x04, 0x07, 0x01, 0x02 };
        static byte[] RC = new byte[] {
		0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3E, 0x3D, 0x3B, 0x37, 0x2F,
		0x1E, 0x3C, 0x39, 0x33, 0x27, 0x0E, 0x1D, 0x3A, 0x35, 0x2B,
		0x16, 0x2C, 0x18, 0x30, 0x21, 0x02, 0x05, 0x0B, 0x17, 0x2E,
        0x1C, 0x38, 0x31, 0x23, 0x06, 0x0D, 0x1B, 0x36, 0x2D, 0x1A,
		0x34, 0x29, 0x12, 0x24, 0x08, 0x11, 0x22, 0x04 };

        static byte nibbleFilter = 0x0F;
        static byte ReductionPoly = 0x3;

        static byte[] byte2nibble(byte[] bytes, int offSet)
        {
            byte[] b = new byte[16];
            for (int i = 0; i < 8; i++)
            {
                b[i * 2 + 0] = (byte)(bytes[offSet + i] & 0x0F);
                b[i * 2 + 1] = (byte)(bytes[offSet + i] >> 4 & 0xF);
            }
            return b;
        }

        static void nibbles2byte(byte[] nibbles, byte[] bytes, int offSet)
        {
            for (int i = 0; i < 8; i++)
                bytes[offSet + i] = (byte)(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
        }

        static byte xTimes(byte a)
        {
            a <<= 1;
            if ((a & 0x10) == 0x10)
                a ^= ReductionPoly;
            return (byte)(a & nibbleFilter);
        }

        static byte x2Times(byte a)
        {
            a <<= 1;
            if ((a & 0x10) == 0x10)
                a ^= ReductionPoly;
            a <<= 1;
            if ((a & 0x10) == 0x10)
                a ^= ReductionPoly;
            return (byte)(a & nibbleFilter);
        }

        static void AddKey(ref byte[] state, byte[] roundKey)
        {
            for (int i = 0; i < 16; i++)
                state[i] ^= roundKey[i];
        }

        static void AddConstants(ref byte[] state, int round)
        {
            state[0] ^= keySizeConst0;
            state[4] ^= keySizeConst1;
            state[8] ^= keySizeConst2;
            state[12] ^= keySizeConst3;

            byte temp = (byte)(RC[round] >> 3 & 0x07);
            state[1] ^= temp;
            state[9] ^= temp;

            temp = (byte)(RC[round] & 0x07);
            state[5] ^= temp;
            state[13] ^= temp;
        }

        static void SboxShiftRows(ref byte[] state)
        {
            byte[] temp = new byte[16];

            temp[0] = sBox[state[0]]; temp[1] = sBox[state[1]]; temp[2] = sBox[state[2]]; temp[3] = sBox[state[3]];
            temp[4] = sBox[state[5]]; temp[5] = sBox[state[6]]; temp[6] = sBox[state[7]]; temp[7] = sBox[state[4]];
            temp[8] = sBox[state[10]]; temp[9] = sBox[state[11]]; temp[10] = sBox[state[8]]; temp[11] = sBox[state[9]];
            temp[12] = sBox[state[15]]; temp[13] = sBox[state[12]]; temp[14] = sBox[state[13]]; temp[15] = sBox[state[14]];

            state = temp;
        }

        static void MultiplyColumn(byte[] temp)
        {
            temp[0] = (byte)(x2Times(temp[0]) ^ temp[1] ^ xTimes(temp[2]) ^ xTimes(temp[3]));
            temp[1] = (byte)(x2Times(temp[1]) ^ temp[2] ^ xTimes(temp[3]) ^ xTimes(temp[0]));
            temp[2] = (byte)(x2Times(temp[2]) ^ temp[3] ^ xTimes(temp[0]) ^ xTimes(temp[1]));
            temp[3] = (byte)(x2Times(temp[3]) ^ temp[0] ^ xTimes(temp[1]) ^ xTimes(temp[2]));
        }

        static void MixColumns(ref byte[] state)
        {
            for (int r = 0; r < 4; r++)
            {
                byte[] temp = new byte[4];
                for (int c = 0; c < 4; c++)
                    temp[c] = state[4 * c + r];

                MultiplyColumn(temp);

                for (int c = 0; c < 4; c++)
                    state[c * 4 + r] = temp[c];
            }
        }

        static void Step(ref byte[] state, int step)
        {
            for (int i = 0; i < 4; i++)
            {
                AddConstants(ref state, (step * 4 + i));
                SboxShiftRows(ref state);
                MixColumns(ref state);
            }
        }

        static void EncryptOneBlock(ref byte[] state, byte[] sk0, byte[] sk1)
        {
            for (int i = 0; i < 12; i += 2)
            {
                AddKey(ref state, sk0);
                Step(ref state, i);
                AddKey(ref state, sk1);
                Step(ref state, i + 1);
            }
            AddKey(ref state, sk0);
        }

        public static byte[] Encrypt(byte[] input, byte[] key)
        {
            byte[] cipherText = new byte[input.Length];

            byte[] sk0 = byte2nibble(key, 0);
            byte[] sk1 = byte2nibble(key, 8);

            for (int i = 0; i < input.Length; i += 8)
            {
                byte[] state = byte2nibble(input, i);

                EncryptOneBlock(ref state, sk0, sk1);

                nibbles2byte(state, cipherText, i);
            }

            return cipherText;
        }

    }
}