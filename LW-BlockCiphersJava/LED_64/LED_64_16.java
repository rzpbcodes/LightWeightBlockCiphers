package lw.blockciphersjava.LED_64;

public class LED_64_16 {
    static byte keySize = 64;
    static int keySizeConst = 0x3254;
    static int[] RC = new int[] { 
        0x1010, 0x3030, 0x7070, 0x7171, 0x7373, 0x6767, 0x5757, 0x3737, 0x7676, 0x7575,
        0x6363, 0x4747, 0x1717, 0x3636, 0x7474, 0x6161, 0x5353, 0x2727, 0x5656, 0x3535,
        0x6262, 0x4545, 0x0303, 0x0606, 0x1414, 0x2020, 0x5050, 0x3131, 0x7272, 0x6565, 
        0x4343, 0x0707 };

    static int mask = 0x000F;

    static int[] T0 = new int[] { 0xBDA5, 0xA1E7, 0xCF5B, 0x597A, 0x1C42, 0x00, 0x72FE, 0x9621, 0x6EBC, 0xF89D, 0xD319, 0x37C6, 0x8A63, 0xE4DF, 0x2B84, 0x4538 };
    static int[] T1 = new int[] { 0xB4EC, 0xA3D5, 0xC276, 0x58FB, 0x1739, 0x00, 0x769A, 0x9A8D, 0x61A3, 0xFB2E, 0xD54F, 0x3958, 0x8DB4, 0xEC17, 0x2E61, 0x4FC2 };
    static int[] T2 = new int[] { 0x819B, 0x642A, 0x49DC, 0x3215, 0xE5B1, 0x00, 0xC847, 0x7BC9, 0x2DF6, 0x563F, 0xAC6D, 0x1FE3, 0x9E78, 0xB38E, 0xFA52, 0xD7A4 };
    static int[] T3 = new int[] { 0xD6EB, 0x1BDA, 0xF37C, 0x9CF5, 0xCD31, 0x00, 0x2597, 0x6F89, 0xE8A6, 0x872F, 0x3E4D, 0x7453, 0xA2B8, 0x4A1E, 0xB962, 0x51C4 };

    static int[] byte2uint16(short[] b, int offSet)
    {
        int[] x = new int[4];
        x[0] ^= (int)((b[offSet + 0] & 0x0F) << 0);
        x[0] ^= (int)((b[offSet + 2] & 0x0F) << 4);
        x[0] ^= (int)((b[offSet + 4] & 0x0F) << 8);
        x[0] ^= (int)((b[offSet + 6] & 0x0F) << 12);

        x[1] ^= (int)((b[offSet + 0] & 0xF0) >> 4);
        x[1] ^= (int)((b[offSet + 2] & 0xF0) << 0);
        x[1] ^= (int)((b[offSet + 4] & 0xF0) << 4);
        x[1] ^= (int)((b[offSet + 6] & 0xF0) << 8);

        x[2] ^= (int)((b[offSet + 1] & 0x0F) << 0);
        x[2] ^= (int)((b[offSet + 3] & 0x0F) << 4);
        x[2] ^= (int)((b[offSet + 5] & 0x0F) << 8);
        x[2] ^= (int)((b[offSet + 7] & 0x0F) << 12);

        x[3] ^= (int)((b[offSet + 1] & 0xF0) >> 4);
        x[3] ^= (int)((b[offSet + 3] & 0xF0) << 0);
        x[3] ^= (int)((b[offSet + 5] & 0xF0) << 4);
        x[3] ^= (int)((b[offSet + 7] & 0xF0) << 8);

        return x;
    }

    static short[] uint162byte(int[] x)
    {
        short[] b = new short[8];
        b[0] ^= (x[0] & 0xF);
        b[0] ^= ((x[1] & 0xF) << 4);

        b[1] ^= (x[2] & 0xF);
        b[1] ^= ((x[3] & 0xF) << 4);

        b[2] ^= (x[0] >> 4 & 0xF);
        b[2] ^= ((x[1] >> 4 & 0xF) << 4);

        b[3] ^= (x[2] >> 4 & 0xF);
        b[3] ^= ((x[3] >> 4 & 0xF) << 4);

        b[4] ^= (x[0] >> 8 & 0xF);
        b[4] ^= ((x[1] >> 8 & 0xF) << 4);

        b[5] ^= (x[2] >> 8 & 0xF);
        b[5] ^= ((x[3] >> 8 & 0xF) << 4);

        b[6] ^= (x[0] >> 12 & 0xF);
        b[6] ^= ((x[1] >> 12 & 0xF) << 4);

        b[7] ^= (x[2] >> 12 & 0xF);
        b[7] ^= ((x[3] >> 12 & 0xF) << 4);

        return b;
    }

    static void uint162byte(int[] x, short[] b, int offSet)
    {
        b[offSet + 0] ^= (x[0] & 0xF);
        b[offSet + 0] ^= ((x[1] & 0xF) << 4);

        b[offSet + 1] ^= (x[2] & 0xF);
        b[offSet + 1] ^= ((x[3] & 0xF) << 4);

        b[offSet + 2] ^= (x[0] >> 4 & 0xF);
        b[offSet + 2] ^= ((x[1] >> 4 & 0xF) << 4);

        b[offSet + 3] ^= (x[2] >> 4 & 0xF);
        b[offSet + 3] ^= ((x[3] >> 4 & 0xF) << 4);

        b[offSet + 4] ^= (x[0] >> 8 & 0xF);
        b[offSet + 4] ^= ((x[1] >> 8 & 0xF) << 4);

        b[offSet + 5] ^= (x[2] >> 8 & 0xF);
        b[offSet + 5] ^= ((x[3] >> 8 & 0xF) << 4);

        b[offSet + 6] ^= (x[0] >> 12 & 0xF);
        b[offSet + 6] ^= ((x[1] >> 12 & 0xF) << 4);

        b[offSet + 7] ^= (x[2] >> 12 & 0xF);
        b[offSet + 7] ^= ((x[3] >> 12 & 0xF) << 4);
    }

    static void AddKey(int[] state, int[] roundKey)
    {
        state[0] ^= roundKey[0];
        state[1] ^= roundKey[1];
        state[2] ^= roundKey[2];
        state[3] ^= roundKey[3];
    }

    static void AddConstants(int[] state, int round)
    {
        state[0] ^= keySizeConst;
        state[1] ^= RC[round];
    }

    static void SubCellShiftRowAndMixColumns(int[] state)
    {
        int[] temp = new int[4];

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
        
        for(int i=0;i<4;i++)
        state[i] = temp[i];
    }

    static void Step(int[] state, int step)
    {
        for (int i = 0; i < 4; i++)
        {
            AddConstants(state, (step * 4 + i));
            SubCellShiftRowAndMixColumns(state);
        }
    }

    static void EncryptOneBlock(int[] state, int[] sk0)
    {
        for (int i = 0; i < 8; i++)
        {
            AddKey(state, sk0);
            Step(state, i);
        }
        AddKey(state, sk0);
    }
    
    public static short[] Encrypt(short[] input, short[] key)
    {
        short[] cipherText = new short[input.length];

        int[] sk0 = byte2uint16(key, 0);

        for (int i = 0; i < input.length; i += 8)
        {
            int[] state = byte2uint16(input, i);

            EncryptOneBlock(state, sk0);

            uint162byte(state, cipherText, i);
        }

        return cipherText;
    }
}
