#include "LED-128-4s.h"

namespace LW_BlockCiphers
{

unsigned char LED_128_4s::keySize = 128;
unsigned char LED_128_4s::sBox[] = {0x0C, 0x05, 0x06, 0x0B, 0x09, 0x00, 0x0A, 0x0D, 0x03, 0x0E, 0x0F, 0x08, 0x04, 0x07, 0x01, 0x02};
unsigned char LED_128_4s::RC[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3E, 0x3D, 0x3B, 0x37, 0x2F, 0x1E, 0x3C, 0x39, 0x33, 0x27, 0x0E, 0x1D, 0x3A, 0x35, 0x2B, 0x16, 0x2C, 0x18, 0x30, 0x21, 0x02, 0x05, 0x0B, 0x17, 0x2E, 0x1C, 0x38, 0x31, 0x23, 0x06, 0x0D, 0x1B, 0x36, 0x2D, 0x1A, 0x34, 0x29, 0x12, 0x24, 0x08, 0x11, 0x22, 0x04};
unsigned char LED_128_4s::nibbleFilter = 0x0F;
unsigned char LED_128_4s::ReductionPoly = 0x3;

	unsigned char* LED_128_4s::byte2nibble(unsigned char bytes[], int offSet)
	{
		unsigned char *b = new unsigned char[16];
		for (int i = 0; i < 8; i++)
		{
			b[i * 2 + 0] = static_cast<unsigned char>(bytes[offSet + i] & 0x0F);
			b[i * 2 + 1] = static_cast<unsigned char>(bytes[offSet + i] >> 4 & 0xF);
		}
		return b;
	}

	unsigned char* LED_128_4s::nibbles2byte(unsigned char nibbles[])
	{
		unsigned char *c = new unsigned char[8];
		for (int i = 0; i < 8; i++)
		{
			c[i] = static_cast<unsigned char>(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
		}
		return c;
	}

	void LED_128_4s::nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet)
	{
		for (int i = 0; i < 8; i++)
		{
			bytes[offSet + i] = static_cast<unsigned char>(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
		}
	}

    unsigned char LED_128_4s::xTimes(unsigned char a)
    {
        a <<= 1;
        if ((a & 0x10) == 0x10)
            a ^= ReductionPoly;
        return static_cast<unsigned char>(a & nibbleFilter);
    }

    unsigned char LED_128_4s::x2Times(unsigned char a)
    {
        a <<= 1;
        if ((a & 0x10) == 0x10)
            a ^= ReductionPoly;
        a <<= 1;
        if ((a & 0x10) == 0x10)
            a ^= ReductionPoly;
        return static_cast<unsigned char>(a & nibbleFilter);
    }

	void LED_128_4s::AddKey(unsigned char state[], unsigned char roundKey[])
	{
		for (int i = 0; i < 16; i++)
		{
			state[i] ^= roundKey[i];
		}
	}

	void LED_128_4s::AddConstants(unsigned char state[], int round)
	{
		state[0] ^= static_cast<unsigned char>(keySize >> 4);
		state[4] ^= static_cast<unsigned char>(0x01 ^ (keySize >> 4));
		state[8] ^= static_cast<unsigned char>(0x02 ^ (keySize & 0x0F));
		state[12] ^= static_cast<unsigned char>(0x03 ^ (keySize & 0x0F));

		unsigned char temp = static_cast<unsigned char>(RC[round] >> 3 & 0x07);
		state[1] ^= temp;
		state[9] ^= temp;

		temp = static_cast<unsigned char>(RC[round] & 0x07);
		state[5] ^= temp;
		state[13] ^= temp;
	}

	void LED_128_4s::SboxShiftRows(unsigned char state[])
	{
		unsigned char *temp = new unsigned char[16];

		temp[0] = sBox[state[0]]; temp[1] = sBox[state[1]]; temp[2] = sBox[state[2]]; temp[3] = sBox[state[3]];
        temp[4] = sBox[state[5]];temp[5] = sBox[state[6]];temp[6] = sBox[state[7]];temp[7] = sBox[state[4]];
        temp[8] = sBox[state[10]];temp[9] = sBox[state[11]];temp[10] = sBox[state[8]];temp[11] = sBox[state[9]];
        temp[12] = sBox[state[15]];temp[13] = sBox[state[12]];temp[14] = sBox[state[13]];temp[15] = sBox[state[14]];

		for(int i=0;i<16;i++)
            state[i] = temp[i];
	}

	void LED_128_4s::MultiplyColumn(unsigned char temp[])
    {
        temp[0] = (x2Times(temp[0]) ^ temp[1] ^ xTimes(temp[2]) ^ xTimes(temp[3]));
        temp[1] = (x2Times(temp[1]) ^ temp[2] ^ xTimes(temp[3]) ^ xTimes(temp[0]));
        temp[2] = (x2Times(temp[2]) ^ temp[3] ^ xTimes(temp[0]) ^ xTimes(temp[1]));
        temp[3] = (x2Times(temp[3]) ^ temp[0] ^ xTimes(temp[1]) ^ xTimes(temp[2]));
    }

	void LED_128_4s::MixColumns(unsigned char state[])
	{
		for (int r = 0; r < 4; r++)
        {
            unsigned char *temp = new unsigned char[4];
            for (int c = 0; c < 4; c++)
                temp[c] = state[4 * c + r];

            MultiplyColumn(temp);

            for (int c = 0; c < 4; c++)
                state[c * 4 + r] = temp[c];
        }
	}

	void LED_128_4s::Step(unsigned char state[], int step)
	{
		for (int i = 0; i < 4; i++)
		{
			AddConstants(state, (step * 4 + i));
			SboxShiftRows(state);
			MixColumns(state);
		}
	}

	void LED_128_4s::EncryptOneBlock(unsigned char state[], unsigned char sk0[], unsigned char sk1[])
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

	unsigned char* LED_128_4s::Encrypt(unsigned char input[], unsigned char key[], int len)
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
