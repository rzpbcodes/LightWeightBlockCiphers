#include "PRESENT_80_4.h"


namespace LW_BlockCiphers
{
    unsigned char PRESENT_80_4::sBox4[] = {0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2};
    unsigned char PRESENT_80_4::position = 0;
    unsigned char PRESENT_80_4::element_source = 0;
    unsigned char PRESENT_80_4::bit_source = 0;
    unsigned char PRESENT_80_4::element_destination = 0;
    unsigned char PRESENT_80_4::bit_destination = 0;
    unsigned char PRESENT_80_4::save1 = 0;
    unsigned char PRESENT_80_4::save2 = 0;

    unsigned char* PRESENT_80_4::runPresent(unsigned char state[], unsigned char key[])
    {
        for (int round = 0; round < 31; round++)
        {
            for (int i = 0; i < 8; i++)
            {
                state[i] ^= key[i + 2];
            }

            for (int i = 0; i < 8; i++)
            {
                state[i] = static_cast<unsigned char>(sBox4[state[i] >> 4] << 4 | sBox4[state[i] & 0xF]);
            }

            unsigned char temp_pLayer[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

            for (int i = 0; i < 64; i++)
            {
                position = static_cast<unsigned char>((16 * i) % 63);
                if (i == 63)
                {
                    position = 63;
                }

                element_source = static_cast<unsigned char>(i / 8);
                bit_source = static_cast<unsigned char>(i % 8);
                element_destination = static_cast<unsigned char>(position / 8);
                bit_destination = static_cast<unsigned char>(position % 8);
                temp_pLayer[element_destination] |= static_cast<unsigned char>(((state[element_source] >> bit_source) & 0x1) << bit_destination);
            }
            for (int i = 0; i < 8; i++)
            {
                state[i] = temp_pLayer[i];
            }
            save1 = key[0];
            save2 = key[1];

            for (int i = 0; i < 8; i++)
            {
                key[i] = key[i + 2];
            }
            key[8] = save1;
            key[9] = save2;

            save1 = static_cast<unsigned char>(key[0] & 7);

            for (int i = 0; i < 9; i++)
            {
                key[i] = static_cast<unsigned char>(key[i] >> 3 | key[i + 1] << 5);
            }

            key[9] = static_cast<unsigned char>(key[9] >> 3 | save1 << 5);

            key[9] = static_cast<unsigned char>(sBox4[key[9] >> 4] << 4 | (key[9] & 0xF));

            if ((round + 1) % 2 == 1)
            {
                key[1] ^= 128;
            }

            key[2] = static_cast<unsigned char>((((round + 1) >> 1) ^ (key[2] & 15)) | (key[2] & 240));
        }
        for (int i = 0; i < 8; i++)
        {
            state[i] ^= key[i + 2];
        }

        return state;
    }

    unsigned char* PRESENT_80_4::Encrypt(unsigned char input[], unsigned char key[], int len)
    {
        unsigned char *cipherText = new unsigned char[len];

        for (int i = 0; i < len; i += 8)
		{
			unsigned char *state = new unsigned char[8];
			for(int j=0;j<8;j++)
                state[j] = input[i+j];

			runPresent(state,key);

            for(int j=0;j<8;j++)
                cipherText[i+j] = state[j];
		}

        return cipherText;
    }
}
