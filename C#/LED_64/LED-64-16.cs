using System;
using System.Collections.Generic;

using System.Text;

namespace LW_BlockCiphersCSharp
{
    class LED_64_16
    {
        static byte keySize = 64;
        static UInt16 keySizeConst = 0x3254;
        static UInt16[] RC = new UInt16[] { 
            0x1010, 0x3030, 0x7070, 0x7171, 0x7373, 0x6767, 0x5757, 0x3737, 0x7676, 0x7575,
            0x6363, 0x4747, 0x1717, 0x3636, 0x7474, 0x6161, 0x5353, 0x2727, 0x5656, 0x3535,
            0x6262, 0x4545, 0x0303, 0x0606, 0x1414, 0x2020, 0x5050, 0x3131, 0x7272, 0x6565, 
            0x4343, 0x0707 };

        static UInt16 mask = 0x000F;

        static UInt16[] T0 = new UInt16[] { 0xBDA5, 0xA1E7, 0xCF5B, 0x597A, 0x1C42, 0x00, 0x72FE, 0x9621, 0x6EBC, 0xF89D, 0xD319, 0x37C6, 0x8A63, 0xE4DF, 0x2B84, 0x4538 };
        static UInt16[] T1 = new UInt16[] { 0xB4EC, 0xA3D5, 0xC276, 0x58FB, 0x1739, 0x00, 0x769A, 0x9A8D, 0x61A3, 0xFB2E, 0xD54F, 0x3958, 0x8DB4, 0xEC17, 0x2E61, 0x4FC2 };
        static UInt16[] T2 = new UInt16[] { 0x819B, 0x642A, 0x49DC, 0x3215, 0xE5B1, 0x00, 0xC847, 0x7BC9, 0x2DF6, 0x563F, 0xAC6D, 0x1FE3, 0x9E78, 0xB38E, 0xFA52, 0xD7A4 };
        static UInt16[] T3 = new UInt16[] { 0xD6EB, 0x1BDA, 0xF37C, 0x9CF5, 0xCD31, 0x00, 0x2597, 0x6F89, 0xE8A6, 0x872F, 0x3E4D, 0x7453, 0xA2B8, 0x4A1E, 0xB962, 0x51C4 };

        static UInt16[] byte2uint16(byte[] b, int offSet)
        {
            UInt16[] x = new UInt16[4];
            x[0] ^= (UInt16)((b[offSet + 0] & 0x0F) << 0);
            x[0] ^= (UInt16)((b[offSet + 2] & 0x0F) << 4);
            x[0] ^= (UInt16)((b[offSet + 4] & 0x0F) << 8);
            x[0] ^= (UInt16)((b[offSet + 6] & 0x0F) << 12);

            x[1] ^= (UInt16)((b[offSet + 0] & 0xF0) >> 4);
            x[1] ^= (UInt16)((b[offSet + 2] & 0xF0) << 0);
            x[1] ^= (UInt16)((b[offSet + 4] & 0xF0) << 4);
            x[1] ^= (UInt16)((b[offSet + 6] & 0xF0) << 8);

            x[2] ^= (UInt16)((b[offSet + 1] & 0x0F) << 0);
            x[2] ^= (UInt16)((b[offSet + 3] & 0x0F) << 4);
            x[2] ^= (UInt16)((b[offSet + 5] & 0x0F) << 8);
            x[2] ^= (UInt16)((b[offSet + 7] & 0x0F) << 12);

            x[3] ^= (UInt16)((b[offSet + 1] & 0xF0) >> 4);
            x[3] ^= (UInt16)((b[offSet + 3] & 0xF0) << 0);
            x[3] ^= (UInt16)((b[offSet + 5] & 0xF0) << 4);
            x[3] ^= (UInt16)((b[offSet + 7] & 0xF0) << 8);
           
            return x;
        }

        static void uint162byte(UInt16[] x, byte[] b, int offSet)
        {
            b[offSet + 0] ^= (byte)(x[0] & 0xF);
            b[offSet + 0] ^= (byte)((x[1] & 0xF) << 4);

            b[offSet + 1] ^= (byte)(x[2] & 0xF);
            b[offSet + 1] ^= (byte)((x[3] & 0xF) << 4);

            b[offSet + 2] ^= (byte)(x[0] >> 4 & 0xF);
            b[offSet + 2] ^= (byte)((x[1] >> 4 & 0xF) << 4);

            b[offSet + 3] ^= (byte)(x[2] >> 4 & 0xF);
            b[offSet + 3] ^= (byte)((x[3] >> 4 & 0xF) << 4);

            b[offSet + 4] ^= (byte)(x[0] >> 8 & 0xF);
            b[offSet + 4] ^= (byte)((x[1] >> 8 & 0xF) << 4);

            b[offSet + 5] ^= (byte)(x[2] >> 8 & 0xF);
            b[offSet + 5] ^= (byte)((x[3] >> 8 & 0xF) << 4);

            b[offSet + 6] ^= (byte)(x[0] >> 12 & 0xF);
            b[offSet + 6] ^= (byte)((x[1] >> 12 & 0xF) << 4);

            b[offSet + 7] ^= (byte)(x[2] >> 12 & 0xF);
            b[offSet + 7] ^= (byte)((x[3] >> 12 & 0xF) << 4);
        }

        static void AddKey(ref UInt16[] state, UInt16[] roundKey)
        {
            state[0] ^= roundKey[0];
            state[1] ^= roundKey[1];
            state[2] ^= roundKey[2];
            state[3] ^= roundKey[3];
        }

        static void AddConstants(ref UInt16[] state, int round)
        {
            state[0] ^= keySizeConst;
            state[1] ^= RC[round];
        }

        static void SubCellShiftRowAndMixColumns(ref UInt16[] state)
        {
            UInt16[] temp = new UInt16[4];

            temp[0] = T0[(state[0] >> 0) & mask];
            temp[0] ^= T1[(state[1] >> 4) & mask];
            temp[0] ^= T2[(state[2] >> 8) & mask];
            temp[0] ^= T3[(state[3] >> 12) & mask];

            temp[1] = T0[(state[1] >> 0) & mask];
            temp[1] ^= T1[(state[2] >> 4) & mask];
            temp[1] ^= T2[(state[3] >> 8) & mask];
            temp[1] ^= T3[(state[0] >> 12) & mask];

            temp[2] = T0[(state[2] >> 0) & mask];
            temp[2] ^= T1[(state[3] >> 4) & mask];
            temp[2] ^= T2[(state[0] >> 8) & mask];
            temp[2] ^= T3[(state[1] >> 12) & mask];

            temp[3] = T0[(state[3] >> 0) & mask];
            temp[3] ^= T1[(state[0] >> 4) & mask];
            temp[3] ^= T2[(state[1] >> 8) & mask];
            temp[3] ^= T3[(state[2] >> 12) & mask];

            state = temp;
        }

        static void Step(ref UInt16[] state, int step)
        {
            for (int i = 0; i < 4; i++)
            {
                AddConstants(ref state, (step * 4 + i));
                SubCellShiftRowAndMixColumns(ref state);
            }
        }

        static void EncryptOneBlock(ref UInt16[] state, UInt16[] sk0)
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

            UInt16[] sk0 = byte2uint16(key, 0);

            for (int i = 0; i < input.Length; i += 8)
            {
                UInt16[] state = byte2uint16(input, i);

                EncryptOneBlock(ref state, sk0);

                uint162byte(state, cipherText, i);
            }

            return cipherText;
        }

    }
}