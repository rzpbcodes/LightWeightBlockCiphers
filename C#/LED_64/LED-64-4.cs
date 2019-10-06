using System;
using System.Collections.Generic;

using System.Text;

namespace LW_BlockCiphersCSharp
{
    class LED_64_4
    {
        static byte keySize = 64;
        static byte keySizeConst0 = (byte)(keySize >> 4);
        static byte keySizeConst1 = (byte)(0x01 ^ (keySize >> 4));
        static byte keySizeConst2 = (byte)(0x02 ^ (keySize & 0x0F));
        static byte keySizeConst3 = (byte)(0x03 ^ (keySize & 0x0F));

        static byte[] sBox = new byte[] { 0x0C, 0x05, 0x06, 0x0B, 0x09, 0x00, 0x0A, 0x0D, 0x03, 0x0E, 0x0F, 0x08, 0x04, 0x07, 0x01, 0x02 };
        static byte[] RC02 = new byte[] {
            0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00};

        static byte[] RC13 = new byte[] {
            0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00, 0x01, 0x02, 0x04};

        static byte[] mul2 = new byte[] { 0x0B, 0x0A, 0x0C, 0x05, 0x01, 0x00, 0x07, 0x09, 0x06, 0x0F, 0x0D, 0x03, 0x08, 0x0E, 0x02, 0x04 };
        static byte[] mul4 = new byte[] { 0x05, 0x07, 0x0B, 0x0A, 0x02, 0x00, 0x0E, 0x01, 0x0C, 0x0D, 0x09, 0x06, 0x03, 0x0F, 0x04, 0x08 };
        static byte[] mul5 = new byte[] { 0x09, 0x02, 0x0D, 0x01, 0x0B, 0x00, 0x04, 0x0C, 0x0F, 0x03, 0x06, 0x0E, 0x07, 0x08, 0x05, 0x0A };
        static byte[] mul6 = new byte[] { 0x0E, 0x0D, 0x07, 0x0F, 0x03, 0x00, 0x09, 0x08, 0x0A, 0x02, 0x04, 0x05, 0x0B, 0x01, 0x06, 0x0C };
        static byte[] mul8 = new byte[] { 0x0A, 0x0E, 0x05, 0x07, 0x04, 0x00, 0x0F, 0x02, 0x0B, 0x09, 0x01, 0x0C, 0x06, 0x0D, 0x08, 0x03 };
        static byte[] mul9 = new byte[] { 0x06, 0x0B, 0x03, 0x0C, 0x0D, 0x00, 0x05, 0x0F, 0x08, 0x07, 0x0E, 0x04, 0x02, 0x0A, 0x09, 0x01 };
        static byte[] mula = new byte[] { 0x01, 0x04, 0x09, 0x02, 0x05, 0x00, 0x08, 0x0B, 0x0D, 0x06, 0x0C, 0x0F, 0x0E, 0x03, 0x0A, 0x07 };
        static byte[] mulb = new byte[] { 0x0D, 0x01, 0x0F, 0x09, 0x0C, 0x00, 0x02, 0x06, 0x0E, 0x08, 0x03, 0x07, 0x0A, 0x04, 0x0B, 0x05 };
        static byte[] mule = new byte[] { 0x04, 0x03, 0x02, 0x08, 0x07, 0x00, 0x06, 0x0A, 0x01, 0x0B, 0x05, 0x09, 0x0D, 0x0C, 0x0E, 0x0F };
        static byte[] mulf = new byte[] { 0x08, 0x06, 0x04, 0x03, 0x0E, 0x00, 0x0C, 0x07, 0x02, 0x05, 0x0A, 0x01, 0x09, 0x0B, 0x0F, 0x0D };

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

            state[1] ^= RC02[round];
            state[9] ^= RC02[round];

            state[5] ^= RC13[round];
            state[13] ^= RC13[round];
        }

        static void SubCellShiftRowAndMixColumns(ref byte[] state)
        {
            byte[] temp = new byte[16];
            /*for (int c = 0; c < 4; c++)
            {
                temp[c] = (byte)(mul4[state[c]] ^ sBox[state[4 + (c + 1) % 4]] ^ mul2[state[8 + (c + 2) % 4]] ^ mul2[state[12 + (c + 3) % 4]]);
                temp[4 + c] = (byte)(mul8[state[c]] ^ mul6[state[4 + (c + 1) % 4]] ^ mul5[state[8 + (c + 2) % 4]] ^ mul6[state[12 + (c + 3) % 4]]);
                temp[8 + c] = (byte)(mulb[state[c]] ^ mule[state[4 + (c + 1) % 4]] ^ mula[state[8 + (c + 2) % 4]] ^ mul9[state[12 + (c + 3) % 4]]);
                temp[12 + c] = (byte)(mul2[state[c]] ^ mul2[state[4 + (c + 1) % 4]] ^ mulf[state[8 + (c + 2) % 4]] ^ mulb[state[12 + (c + 3) % 4]]);
            }*/

            temp[0] = (byte)(mul4[state[0]] ^ sBox[state[5]] ^ mul2[state[10]] ^ mul2[state[15]]);
            temp[4] = (byte)(mul8[state[0]] ^ mul6[state[5]] ^ mul5[state[10]] ^ mul6[state[15]]);
            temp[8] = (byte)(mulb[state[0]] ^ mule[state[5]] ^ mula[state[10]] ^ mul9[state[15]]);
            temp[12] = (byte)(mul2[state[0]] ^ mul2[state[5]] ^ mulf[state[10]] ^ mulb[state[15]]);

            temp[1] = (byte)(mul4[state[1]] ^ sBox[state[6]] ^ mul2[state[11]] ^ mul2[state[12]]);
            temp[5] = (byte)(mul8[state[1]] ^ mul6[state[6]] ^ mul5[state[11]] ^ mul6[state[12]]);
            temp[9] = (byte)(mulb[state[1]] ^ mule[state[6]] ^ mula[state[11]] ^ mul9[state[12]]);
            temp[13] = (byte)(mul2[state[1]] ^ mul2[state[6]] ^ mulf[state[11]] ^ mulb[state[12]]);

            temp[2] = (byte)(mul4[state[2]] ^ sBox[state[7]] ^ mul2[state[8]] ^ mul2[state[13]]);
            temp[6] = (byte)(mul8[state[2]] ^ mul6[state[7]] ^ mul5[state[8]] ^ mul6[state[13]]);
            temp[10] = (byte)(mulb[state[2]] ^ mule[state[7]] ^ mula[state[8]] ^ mul9[state[13]]);
            temp[14] = (byte)(mul2[state[2]] ^ mul2[state[7]] ^ mulf[state[8]] ^ mulb[state[13]]);

            temp[3] = (byte)(mul4[state[3]] ^ sBox[state[4]] ^ mul2[state[9]] ^ mul2[state[14]]);
            temp[7] = (byte)(mul8[state[3]] ^ mul6[state[4]] ^ mul5[state[9]] ^ mul6[state[14]]);
            temp[11] = (byte)(mulb[state[3]] ^ mule[state[4]] ^ mula[state[9]] ^ mul9[state[14]]);
            temp[15] = (byte)(mul2[state[3]] ^ mul2[state[4]] ^ mulf[state[9]] ^ mulb[state[14]]);

            state = temp;
        }

        static void Step(ref byte[] state, int step)
        {
            for (int i = 0; i < 4; i++)
            {
                AddConstants(ref state, (step * 4 + i));
                SubCellShiftRowAndMixColumns(ref state);
            }
        }

        static void EncryptOneBlock(ref byte[] state, byte[] sk0)
        {
            for (int i = 0; i < 8; i++)
            {
                AddKey(ref state, sk0);
                Step(ref state, i);
            }
            AddKey(ref state, sk0);
        }

        public static byte[] Encrypt(byte[] input, byte[] key)
        {
            byte[] cipherText = new byte[input.Length];

            byte[] sk0 = byte2nibble(key, 0);

            for (int i = 0; i < input.Length; i += 8)
            {
                byte[] state = byte2nibble(input, i);

                EncryptOneBlock(ref state, sk0);

                nibbles2byte(state, cipherText, i);
            }

            return cipherText;
        }

    }
}