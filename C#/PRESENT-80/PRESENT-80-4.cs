using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LW_BlockCiphersCSharp
{
    class PRESENT_80_4
    {
        static byte[] sBox4 = { 0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2 };
        //	pLayer variables
        static byte position = 0;
        static byte element_source = 0;
        static byte bit_source = 0;
        static byte element_destination = 0;
        static byte bit_destination = 0;
        //	Key scheduling variables
        static byte save1;
        static byte save2;

        static byte[] runPresent(byte[] state, byte[] key)
        {
            for (int round = 0; round < 31; round++)
            {
                //	addRoundkey
                for (int i = 0; i < 8; i++)
                    state[i] ^= key[i + 2];

                //	sBox 
                for (int i = 0; i < 8; i++)
                    state[i] = (byte)(sBox4[state[i] >> 4] << 4 | sBox4[state[i] & 0xF]);

                //	pLayer 
                byte[] temp_pLayer = new byte[8];

                for (int i = 0; i < 64; i++)
                {
                    position = (byte)((16 * i) % 63); 
                    if (i == 63) 
                        position = 63;

                    element_source = (byte)(i / 8);
                    bit_source = (byte)(i % 8);
                    element_destination = (byte)(position / 8);
                    bit_destination = (byte)(position % 8);
                    temp_pLayer[element_destination] |= (byte)(((state[element_source] >> bit_source) & 0x1) << bit_destination);
                }
                for (int i = 0; i < 8; i++)
                    state[i] = temp_pLayer[i];
                //	End pLayer 

                //	Key Scheduling 
                save1 = key[0];
                save2 = key[1];
                
                for (int i = 0; i < 8; i++)
                    key[i] = key[i + 2];
                
                key[8] = save1;
                key[9] = save2;

                save1 = (byte)(key[0] & 7); 

                for (int i = 0; i < 9; i++)
                    key[i] = (byte)(key[i] >> 3 | key[i + 1] << 5);

                key[9] = (byte)(key[9] >> 3 | save1 << 5);

                key[9] = (byte)(sBox4[key[9] >> 4] << 4 | (key[9] & 0xF)); //S-Box application

                if ((round + 1) % 2 == 1) 
                    key[1] ^= 128;

                key[2] = (byte)((((round + 1) >> 1) ^ (key[2] & 15)) | (key[2] & 240));
            }

            //	addRoundkey 
            for (int i = 0; i < 8; i++)
                state[i] ^= key[i + 2];

            return state;
        }

        public static byte[] Encrypt(byte[] input, byte[] key)
        {
            byte[] cipherText = new byte[input.Length];

            for (int i = 0; i < input.Length; i += 8)
            {
                byte[] state = new byte[8];
                for (int j = 0; j < 8; j++)
                    state[j] = input[i + j];

                state = runPresent(state, key);

                for (int j = 0; j < 8; j++)
                    cipherText[i + j] = state[j];
            }

            return cipherText;
        }
    }
}
