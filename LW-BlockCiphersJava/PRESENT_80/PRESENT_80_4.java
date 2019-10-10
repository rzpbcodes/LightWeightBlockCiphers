package lw.blockciphersjava.PRESENT_80;

public class PRESENT_80_4 {
    private static short[] sBox4 = {0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2};
    private static short position = 0;
    private static short element_source = 0;
    private static short bit_source = 0;
    private static short element_destination = 0;
    private static short bit_destination = 0;
    private static short save1;
    private static short save2;

    private static short[] runPresent(short[] state, short[] key)
    {
        for (int round = 0; round < 31; round++)
        {
            for (int i = 0; i < 8; i++)
                state[i] ^= key[i + 2];

            for (int i = 0; i < 8; i++)
                state[i] = (short) (sBox4[(state[i] >> 4)& 0xF] << 4 | sBox4[state[i] & 0xF]);

            short[] temp_pLayer = new short[8];
            
            for (int i = 0; i < 64; i++)
            {
                    position = (short)((16 * i) % 63);
                    if (i == 63)
                        position = 63;
                    
                    element_source = (short) ((i / 8));
                    bit_source = (short)((i % 8));
                    element_destination = (short)((position / 8));
                    bit_destination = (short)((position % 8));
                    temp_pLayer[element_destination] |= (short)((((state[element_source] >> bit_source) & 0x1) << bit_destination) & 0xFF);
            }
            for (int i = 0; i < 8; i++)
                state[i] = temp_pLayer[i];
            save1 = key[0];
            save2 = key[1];

            for (int i = 0; i < 8; i++)
                key[i] = key[i + 2];
            key[8] = save1;
            key[9] = save2;

            save1 = (short)(key[0] & 7); 
            
            for (int i = 0; i < 9; i++)
                key[i] = (short) ((key[i] >> 3 | key[i + 1] << 5)&0xFF);
            
            key[9] = (short)((key[9] >> 3 | save1 << 5)&0xFF);

            key[9] = (short)(sBox4[(key[9] >> 4)& 0xF] << 4 | (key[9] & 0xF));

            if ((round + 1) % 2 == 1) 
                key[1] ^= 128;
            key[2] = (short)(((((round + 1) >> 1) ^ (key[2] & 15)) | (key[2] & 240))&0xFF);
        }
        for (int i = 0; i < 8; i++)
            state[i] ^= key[i + 2];
        
        return state;
    }

    public static short[] Encrypt(short[] input, short[] key)
    {
        short[] cipherText = new short[input.length];

        for (int i = 0; i < input.length; i += 8)
        {
            short[] state = new short[8];
            for (int j = 0; j < 8; j++)
                state[j] = input[i + j];

            state = runPresent(state, key);

            for (int j = 0; j < 8; j++)
                cipherText[i + j] = state[j];
        }

        return cipherText;
    }

}
