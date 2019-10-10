#include "LED-128-4.h"


namespace LW_BlockCiphers
{

unsigned char LED_128_4::keySize = 128;
unsigned char LED_128_4::keySizeConst0 = static_cast<unsigned char>(keySize >> 4);
unsigned char LED_128_4::keySizeConst1 = static_cast<unsigned char>(0x01 ^ (keySize >> 4));
unsigned char LED_128_4::keySizeConst2 = static_cast<unsigned char>(0x02 ^ (keySize & 0x0F));
unsigned char LED_128_4::keySizeConst3 = static_cast<unsigned char>(0x03 ^ (keySize & 0x0F));
unsigned char LED_128_4::sBox[] = {0x0C, 0x05, 0x06, 0x0B, 0x09, 0x00, 0x0A, 0x0D, 0x03, 0x0E, 0x0F, 0x08, 0x04, 0x07, 0x01, 0x02};

unsigned char LED_128_4::RC02[] = {0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00};
unsigned char LED_128_4::RC13[] = {0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00, 0x01, 0x02, 0x04};

unsigned char LED_128_4::mul2[] = {0x0B, 0x0A, 0x0C, 0x05, 0x01, 0x00, 0x07, 0x09, 0x06, 0x0F, 0x0D, 0x03, 0x08, 0x0E, 0x02, 0x04};
unsigned char LED_128_4::mul4[] = {0x05, 0x07, 0x0B, 0x0A, 0x02, 0x00, 0x0E, 0x01, 0x0C, 0x0D, 0x09, 0x06, 0x03, 0x0F, 0x04, 0x08};
unsigned char LED_128_4::mul5[] = {0x09, 0x02, 0x0D, 0x01, 0x0B, 0x00, 0x04, 0x0C, 0x0F, 0x03, 0x06, 0x0E, 0x07, 0x08, 0x05, 0x0A};
unsigned char LED_128_4::mul6[] = {0x0E, 0x0D, 0x07, 0x0F, 0x03, 0x00, 0x09, 0x08, 0x0A, 0x02, 0x04, 0x05, 0x0B, 0x01, 0x06, 0x0C};
unsigned char LED_128_4::mul8[] = {0x0A, 0x0E, 0x05, 0x07, 0x04, 0x00, 0x0F, 0x02, 0x0B, 0x09, 0x01, 0x0C, 0x06, 0x0D, 0x08, 0x03};
unsigned char LED_128_4::mul9[] = {0x06, 0x0B, 0x03, 0x0C, 0x0D, 0x00, 0x05, 0x0F, 0x08, 0x07, 0x0E, 0x04, 0x02, 0x0A, 0x09, 0x01};
unsigned char LED_128_4::mula[] = {0x01, 0x04, 0x09, 0x02, 0x05, 0x00, 0x08, 0x0B, 0x0D, 0x06, 0x0C, 0x0F, 0x0E, 0x03, 0x0A, 0x07};
unsigned char LED_128_4::mulb[] = {0x0D, 0x01, 0x0F, 0x09, 0x0C, 0x00, 0x02, 0x06, 0x0E, 0x08, 0x03, 0x07, 0x0A, 0x04, 0x0B, 0x05};
unsigned char LED_128_4::mule[] = {0x04, 0x03, 0x02, 0x08, 0x07, 0x00, 0x06, 0x0A, 0x01, 0x0B, 0x05, 0x09, 0x0D, 0x0C, 0x0E, 0x0F};
unsigned char LED_128_4::mulf[] = {0x08, 0x06, 0x04, 0x03, 0x0E, 0x00, 0x0C, 0x07, 0x02, 0x05, 0x0A, 0x01, 0x09, 0x0B, 0x0F, 0x0D};

	unsigned char* LED_128_4::byte2nibble(unsigned char bytes[], int offSet)
	{
		unsigned char *b = new unsigned char[16];
		for (int i = 0; i < 8; i++)
		{
			b[i * 2 + 0] = static_cast<unsigned char>(bytes[offSet + i] & 0x0F);
			b[i * 2 + 1] = static_cast<unsigned char>(bytes[offSet + i] >> 4 & 0xF);
		}
		return b;
	}

	unsigned char* LED_128_4::nibbles2byte(unsigned char nibbles[])
	{
		unsigned char *c = new unsigned char[8];
		for (int i = 0; i < 8; i++)
		{
			c[i] = static_cast<unsigned char>(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
		}
		return c;
	}

	void LED_128_4::nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet)
	{
		for (int i = 0; i < 8; i++)
		{
			bytes[offSet + i] = static_cast<unsigned char>(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
		}
	}

	void LED_128_4::AddKey(unsigned char state[], unsigned char roundKey[])
	{
		for (int i = 0; i < 16; i++)
		{
			state[i] ^= roundKey[i];
		}
	}

	void LED_128_4::AddConstants(unsigned char state[], int round)
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

	void LED_128_4::SubCellShiftRowAndMixColumns(unsigned char state[])
	{
		unsigned char *temp = new unsigned char[16];

        temp[0] = (mul4[state[0]] ^ sBox[state[5]] ^ mul2[state[10]] ^ mul2[state[15]]);
        temp[4] = (mul8[state[0]] ^ mul6[state[5]] ^ mul5[state[10]] ^ mul6[state[15]]);
        temp[8] = (mulb[state[0]] ^ mule[state[5]] ^ mula[state[10]] ^ mul9[state[15]]);
        temp[12] = (mul2[state[0]] ^ mul2[state[5]] ^ mulf[state[10]] ^ mulb[state[15]]);

        temp[1] = (mul4[state[1]] ^ sBox[state[6]] ^ mul2[state[11]] ^ mul2[state[12]]);
        temp[5] = (mul8[state[1]] ^ mul6[state[6]] ^ mul5[state[11]] ^ mul6[state[12]]);
        temp[9] = (mulb[state[1]] ^ mule[state[6]] ^ mula[state[11]] ^ mul9[state[12]]);
        temp[13] = (mul2[state[1]] ^ mul2[state[6]] ^ mulf[state[11]] ^ mulb[state[12]]);

        temp[2] = (mul4[state[2]] ^ sBox[state[7]] ^ mul2[state[8]] ^ mul2[state[13]]);
        temp[6] = (mul8[state[2]] ^ mul6[state[7]] ^ mul5[state[8]] ^ mul6[state[13]]);
        temp[10] = (mulb[state[2]] ^ mule[state[7]] ^ mula[state[8]] ^ mul9[state[13]]);
        temp[14] = (mul2[state[2]] ^ mul2[state[7]] ^ mulf[state[8]] ^ mulb[state[13]]);

        temp[3] = (mul4[state[3]] ^ sBox[state[4]] ^ mul2[state[9]] ^ mul2[state[14]]);
        temp[7] = (mul8[state[3]] ^ mul6[state[4]] ^ mul5[state[9]] ^ mul6[state[14]]);
        temp[11] = (mulb[state[3]] ^ mule[state[4]] ^ mula[state[9]] ^ mul9[state[14]]);
        temp[15] = (mul2[state[3]] ^ mul2[state[4]] ^ mulf[state[9]] ^ mulb[state[14]]);

		for(int i=0;i<16;i++)
            state[i] = temp[i];
	}

	void LED_128_4::Step(unsigned char state[], int step)
	{
		for (int i = 0; i < 4; i++)
		{
			AddConstants(state, (step * 4 + i));
			SubCellShiftRowAndMixColumns(state);
		}
	}

	void LED_128_4::EncryptOneBlock(unsigned char state[], unsigned char sk0[], unsigned char sk1[])
	{
		for (int i = 0; i < 12; i+=2)
		{
			AddKey(state, sk0);
			Step(state, i);
			AddKey(state, sk1);
			Step(state, i+1);
		}
		AddKey(state, sk0);
	}

	unsigned char* LED_128_4::Encrypt(unsigned char input[], unsigned char key[], int len)
	{
		unsigned char *cipherText = new unsigned char[len];

		unsigned char *sk0 = byte2nibble(key, 0);
		unsigned char *sk1 = byte2nibble(key, 8);

		for (int i = 0; i < len; i += 8)
		{
			unsigned char *state = byte2nibble(input, i);

			EncryptOneBlock(state, sk0, sk1);

			nibbles2byte(state, cipherText, i);
		}

		return cipherText;
	}
}
