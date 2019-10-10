#include "LED-64-4-D1.h"

namespace LW_BlockCiphers
{

unsigned char LED_64_4_D1::keySize = 64;
unsigned char LED_64_4_D1::keySizeConst0 = static_cast<unsigned char>(keySize >> 4);
unsigned char LED_64_4_D1::keySizeConst1 = static_cast<unsigned char>(0x01 ^ (keySize >> 4));
unsigned char LED_64_4_D1::keySizeConst2 = static_cast<unsigned char>(0x02 ^ (keySize & 0x0F));
unsigned char LED_64_4_D1::keySizeConst3 = static_cast<unsigned char>(0x03 ^ (keySize & 0x0F));

unsigned char LED_64_4_D1::sBoxInv[] = {0x05, 0x0E, 0x0F, 0x08, 0x0C, 0x01, 0x02, 0x0D, 0x0B, 0x04, 0x06, 0x03, 0x00, 0x07, 0x09, 0x0A};
unsigned char LED_64_4_D1::RC02[] = {0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00};
unsigned char LED_64_4_D1::RC13[] = {0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00, 0x01, 0x02, 0x04};
unsigned char LED_64_4_D1::mul2Inv[] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x03, 0x01, 0x07, 0x05, 0x0B, 0x09, 0x0F, 0x0D};
unsigned char LED_64_4_D1::mul3Inv[] = {0x00, 0x03, 0x06, 0x05, 0x0C, 0x0F, 0x0A, 0x09, 0x0B, 0x08, 0x0D, 0x0E, 0x07, 0x04, 0x01, 0x02};
unsigned char LED_64_4_D1::mul4Inv[] = {0x00, 0x04, 0x08, 0x0C, 0x03, 0x07, 0x0B, 0x0F, 0x06, 0x02, 0x0E, 0x0A, 0x05, 0x01, 0x0D, 0x09};
unsigned char LED_64_4_D1::mul5Inv[] = {0x00, 0x05, 0x0A, 0x0F, 0x07, 0x02, 0x0D, 0x08, 0x0E, 0x0B, 0x04, 0x01, 0x09, 0x0C, 0x03, 0x06};
unsigned char LED_64_4_D1::mul6Inv[] = {0x00, 0x06, 0x0C, 0x0A, 0x0B, 0x0D, 0x07, 0x01, 0x05, 0x03, 0x09, 0x0F, 0x0E, 0x08, 0x02, 0x04};
unsigned char LED_64_4_D1::mul7Inv[] = {0x00, 0x07, 0x0E, 0x09, 0x0F, 0x08, 0x01, 0x06, 0x0D, 0x0A, 0x03, 0x04, 0x02, 0x05, 0x0C, 0x0B};
unsigned char LED_64_4_D1::mul8Inv[] = {0x00, 0x08, 0x03, 0x0B, 0x06, 0x0E, 0x05, 0x0D, 0x0C, 0x04, 0x0F, 0x07, 0x0A, 0x02, 0x09, 0x01};
unsigned char LED_64_4_D1::mul9Inv[] = {0x00, 0x09, 0x01, 0x08, 0x02, 0x0B, 0x03, 0x0A, 0x04, 0x0D, 0x05, 0x0C, 0x06, 0x0F, 0x07, 0x0E};
unsigned char LED_64_4_D1::mulcInv[] = {0x00, 0x0C, 0x0B, 0x07, 0x05, 0x09, 0x0E, 0x02, 0x0A, 0x06, 0x01, 0x0D, 0x0F, 0x03, 0x04, 0x08};
unsigned char LED_64_4_D1::muldInv[] = {0x00, 0x0D, 0x09, 0x04, 0x01, 0x0C, 0x08, 0x05, 0x02, 0x0F, 0x0B, 0x06, 0x03, 0x0E, 0x0A, 0x07};
unsigned char LED_64_4_D1::muleInv[] = {0x00, 0x0E, 0x0F, 0x01, 0x0D, 0x03, 0x02, 0x0C, 0x09, 0x07, 0x06, 0x08, 0x04, 0x0A, 0x0B, 0x05};

	unsigned char* LED_64_4_D1::byte2nibble(unsigned char bytes[], int offSet)
	{
		unsigned char *b = new unsigned char[16];
		for (int i = 0; i < 8; i++)
		{
			b[i * 2 + 0] = static_cast<unsigned char>(bytes[offSet + i] & 0x0F);
			b[i * 2 + 1] = static_cast<unsigned char>(bytes[offSet + i] >> 4 & 0xF);
		}
		return b;
	}

	void LED_64_4_D1::nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet)
	{
		for (int i = 0; i < 8; i++)
		{
			bytes[offSet + i] = static_cast<unsigned char>(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
		}
	}

    void LED_64_4_D1::AddKey(unsigned char state[], unsigned char roundKey[])
    {
        for (int i = 0; i < 16; i++)
            state[i] ^= roundKey[i];
    }

    void LED_64_4_D1::AddConstants(unsigned char state[], int round)
    {
        state[0] ^= keySizeConst0;
        state[4] ^= keySizeConst1;
        state[8] ^= keySizeConst2;
        state[12] ^= keySizeConst3;

        state[1] ^= RC02[31 - round];
        state[9] ^= RC02[31 - round];

        state[5] ^= RC13[31 - round];
        state[13] ^= RC13[31 - round];
    }

    void LED_64_4_D1::SubCellShiftRowAndMixColumns(unsigned char state[])
    {
        unsigned char *temp = new unsigned char[16];

        //inverse MixColumn
        /*
        C C D 4
        3 8 4 5
        7 6 2 E
        D 9 9 D
        */

        temp[0] = static_cast<unsigned char>(mulcInv[state[0]] ^ mulcInv[state[4]] ^ muldInv[state[8]] ^ mul4Inv[state[12]]);
        temp[5] = static_cast<unsigned char>(mul3Inv[state[0]] ^ mul8Inv[state[4]] ^ mul4Inv[state[8]] ^ mul5Inv[state[12]]);
        temp[10] = static_cast<unsigned char>(mul7Inv[state[0]] ^ mul6Inv[state[4]] ^ mul2Inv[state[8]] ^ muleInv[state[12]]);
        temp[15] = static_cast<unsigned char>(muldInv[state[0]] ^ mul9Inv[state[4]] ^ mul9Inv[state[8]] ^ muldInv[state[12]]);

        temp[1] = static_cast<unsigned char>(mulcInv[state[1]] ^ mulcInv[state[5]] ^ muldInv[state[9]] ^ mul4Inv[state[13]]);
        temp[6] = static_cast<unsigned char>(mul3Inv[state[1]] ^ mul8Inv[state[5]] ^ mul4Inv[state[9]] ^ mul5Inv[state[13]]);
        temp[11] = static_cast<unsigned char>(mul7Inv[state[1]] ^ mul6Inv[state[5]] ^ mul2Inv[state[9]] ^ muleInv[state[13]]);
        temp[12] = static_cast<unsigned char>(muldInv[state[1]] ^ mul9Inv[state[5]] ^ mul9Inv[state[9]] ^ muldInv[state[13]]);

        temp[2] = static_cast<unsigned char>(mulcInv[state[2]] ^ mulcInv[state[6]] ^ muldInv[state[10]] ^ mul4Inv[state[14]]);
        temp[7] = static_cast<unsigned char>(mul3Inv[state[2]] ^ mul8Inv[state[6]] ^ mul4Inv[state[10]] ^ mul5Inv[state[14]]);
        temp[8] = static_cast<unsigned char>(mul7Inv[state[2]] ^ mul6Inv[state[6]] ^ mul2Inv[state[10]] ^ muleInv[state[14]]);
        temp[13] = static_cast<unsigned char>(muldInv[state[2]] ^ mul9Inv[state[6]] ^ mul9Inv[state[10]] ^ muldInv[state[14]]);

        temp[3] = static_cast<unsigned char>(mulcInv[state[3]] ^ mulcInv[state[7]] ^ muldInv[state[11]] ^ mul4Inv[state[15]]);
        temp[4] = static_cast<unsigned char>(mul3Inv[state[3]] ^ mul8Inv[state[7]] ^ mul4Inv[state[11]] ^ mul5Inv[state[15]]);
        temp[9] = static_cast<unsigned char>(mul7Inv[state[3]] ^ mul6Inv[state[7]] ^ mul2Inv[state[11]] ^ muleInv[state[15]]);
        temp[14] = static_cast<unsigned char>(muldInv[state[3]] ^ mul9Inv[state[7]] ^ mul9Inv[state[11]] ^ muldInv[state[15]]);

        //inverse Sbox
        for (int i = 0; i < 16; i++)
            state[i] = sBoxInv[temp[i]];
    }

    void LED_64_4_D1::Step(unsigned char state[], int step)
    {
        for (int i = 0; i < 4; i++)
        {
            SubCellShiftRowAndMixColumns(state);
            AddConstants(state, (step * 4 + i));
        }
    }

    void LED_64_4_D1::EncryptOneBlock(unsigned char state[], unsigned char sk0[])
    {
        AddKey(state, sk0);
        for (int i = 0; i < 8; i++)
        {
            Step(state, i);
            AddKey(state, sk0);
        }
    }

    unsigned char* LED_64_4_D1::Decrypt(unsigned char input[], unsigned char key[], int len)
    {
        unsigned char *cipherText = new unsigned char[len];

		unsigned char *sk0 = byte2nibble(key, 0);

        for (int i = 0; i < len; i += 8)
        {
            unsigned char *state = byte2nibble(input, i);
            EncryptOneBlock(state, sk0);

            nibbles2byte(state, cipherText, i);
        }

        return cipherText;
    }
}
