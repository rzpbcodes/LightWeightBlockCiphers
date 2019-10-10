#include "LED-64-4-D2.h"

namespace LW_BlockCiphers
{

unsigned char LED_64_4_D2::keySize = 64;
unsigned char LED_64_4_D2::keySizeConst0 = static_cast<unsigned char>(keySize >> 4);
unsigned char LED_64_4_D2::keySizeConst1 = static_cast<unsigned char>(0x01 ^ (keySize >> 4));
unsigned char LED_64_4_D2::keySizeConst2 = static_cast<unsigned char>(0x02 ^ (keySize & 0x0F));
unsigned char LED_64_4_D2::keySizeConst3 = static_cast<unsigned char>(0x03 ^ (keySize & 0x0F));

unsigned char LED_64_4_D2::keySizeConst0inv = 0x09;
unsigned char LED_64_4_D2::keySizeConst1inv = 0x05;
unsigned char LED_64_4_D2::keySizeConst2inv = 0x07;
unsigned char LED_64_4_D2::keySizeConst3inv = 0x0F;

unsigned char LED_64_4_D2::sBoxInv[] = {0x05, 0x0E, 0x0F, 0x08, 0x0C, 0x01, 0x02, 0x0D, 0x0B, 0x04, 0x06, 0x03, 0x00, 0x07, 0x09, 0x0A};

unsigned char LED_64_4_D2::mul2Inv[] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x03, 0x01, 0x07, 0x05, 0x0B, 0x09, 0x0F, 0x0D};
unsigned char LED_64_4_D2::mul3Inv[] = {0x00, 0x03, 0x06, 0x05, 0x0C, 0x0F, 0x0A, 0x09, 0x0B, 0x08, 0x0D, 0x0E, 0x07, 0x04, 0x01, 0x02};
unsigned char LED_64_4_D2::mul4Inv[] = {0x00, 0x04, 0x08, 0x0C, 0x03, 0x07, 0x0B, 0x0F, 0x06, 0x02, 0x0E, 0x0A, 0x05, 0x01, 0x0D, 0x09};
unsigned char LED_64_4_D2::mul5Inv[] = {0x00, 0x05, 0x0A, 0x0F, 0x07, 0x02, 0x0D, 0x08, 0x0E, 0x0B, 0x04, 0x01, 0x09, 0x0C, 0x03, 0x06};
unsigned char LED_64_4_D2::mul6Inv[] = {0x00, 0x06, 0x0C, 0x0A, 0x0B, 0x0D, 0x07, 0x01, 0x05, 0x03, 0x09, 0x0F, 0x0E, 0x08, 0x02, 0x04};
unsigned char LED_64_4_D2::mul7Inv[] = {0x00, 0x07, 0x0E, 0x09, 0x0F, 0x08, 0x01, 0x06, 0x0D, 0x0A, 0x03, 0x04, 0x02, 0x05, 0x0C, 0x0B};
unsigned char LED_64_4_D2::mul8Inv[] = {0x00, 0x08, 0x03, 0x0B, 0x06, 0x0E, 0x05, 0x0D, 0x0C, 0x04, 0x0F, 0x07, 0x0A, 0x02, 0x09, 0x01};
unsigned char LED_64_4_D2::mul9Inv[] = {0x00, 0x09, 0x01, 0x08, 0x02, 0x0B, 0x03, 0x0A, 0x04, 0x0D, 0x05, 0x0C, 0x06, 0x0F, 0x07, 0x0E};
unsigned char LED_64_4_D2::mulcInv[] = {0x00, 0x0C, 0x0B, 0x07, 0x05, 0x09, 0x0E, 0x02, 0x0A, 0x06, 0x01, 0x0D, 0x0F, 0x03, 0x04, 0x08};
unsigned char LED_64_4_D2::muldInv[] = {0x00, 0x0D, 0x09, 0x04, 0x01, 0x0C, 0x08, 0x05, 0x02, 0x0F, 0x0B, 0x06, 0x03, 0x0E, 0x0A, 0x07};
unsigned char LED_64_4_D2::muleInv[] = {0x00, 0x0E, 0x0F, 0x01, 0x0D, 0x03, 0x02, 0x0C, 0x09, 0x07, 0x06, 0x08, 0x04, 0x0A, 0x0B, 0x05};

unsigned char LED_64_4_D2::mul2[] = {0x0A, 0x0F, 0x0D, 0x03, 0x0B, 0x02, 0x04, 0x09, 0x05, 0x08, 0x0C, 0x06, 0x00, 0x0E, 0x01, 0x07};
unsigned char LED_64_4_D2::mul3[] = {0x0F, 0x01, 0x02, 0x0B, 0x07, 0x03, 0x06, 0x04, 0x0E, 0x0C, 0x0A, 0x05, 0x00, 0x09, 0x08, 0x0D};
unsigned char LED_64_4_D2::mul4[] = {0x07, 0x0D, 0x09, 0x06, 0x05, 0x04, 0x08, 0x01, 0x0A, 0x03, 0x0B, 0x0C, 0x00, 0x0F, 0x02, 0x0E};
unsigned char LED_64_4_D2::mul5[] = {0x02, 0x03, 0x06, 0x0E, 0x09, 0x05, 0x0A, 0x0C, 0x01, 0x07, 0x0D, 0x0F, 0x00, 0x08, 0x0B, 0x04};
unsigned char LED_64_4_D2::mul6[] = {0x0D, 0x02, 0x04, 0x05, 0x0E, 0x06, 0x0C, 0x08, 0x0F, 0x0B, 0x07, 0x0A, 0x00, 0x01, 0x03, 0x09};
unsigned char LED_64_4_D2::mul7[] = {0x08, 0x0C, 0x0B, 0x0D, 0x02, 0x07, 0x0E, 0x05, 0x04, 0x0F, 0x01, 0x09, 0x00, 0x06, 0x0A, 0x03};
unsigned char LED_64_4_D2::mul8[] = {0x0E, 0x09, 0x01, 0x0C, 0x0A, 0x08, 0x03, 0x02, 0x07, 0x06, 0x05, 0x0B, 0x00, 0x0D, 0x04, 0x0F};
unsigned char LED_64_4_D2::mul9[] = {0x0B, 0x07, 0x0E, 0x04, 0x06, 0x09, 0x01, 0x0F, 0x0C, 0x02, 0x03, 0x08, 0x00, 0x0A, 0x0D, 0x05};
unsigned char LED_64_4_D2::mulc[] = {0x09, 0x04, 0x08, 0x0A, 0x0F, 0x0C, 0x0B, 0x03, 0x0D, 0x05, 0x0E, 0x07, 0x00, 0x02, 0x06, 0x01};
unsigned char LED_64_4_D2::muld[] = {0x0C, 0x0A, 0x07, 0x02, 0x03, 0x0D, 0x09, 0x0E, 0x06, 0x01, 0x08, 0x04, 0x00, 0x05, 0x0F, 0x0B};
unsigned char LED_64_4_D2::mule[] = {0x03, 0x0B, 0x05, 0x09, 0x04, 0x0E, 0x0F, 0x0A, 0x08, 0x0D, 0x02, 0x01, 0x00, 0x0C, 0x07, 0x06};

unsigned char LED_64_4_D2::RCconstants[][4] =
{{0x00, 0x01, 0x00, 0x01},{0x0B, 0x04, 0x0B, 0x0C},{0x0D, 0x05, 0x0D, 0x0F},{0x0C, 0x02, 0x08, 0x0B},{0x0E, 0x0C, 0x02, 0x03},{0x02, 0x0E, 0x0D, 0x04},{0x09, 0x0A, 0x06, 0x08},{0x0C, 0x02, 0x03, 0x03},{0x0B, 0x04, 0x00, 0x04},{0x08, 0x0D, 0x0F, 0x08},{0x06, 0x01, 0x0A, 0x07},{0x01, 0x07, 0x0E, 0x0C},{0x0F, 0x0B, 0x00, 0x0B},{0x0D, 0x05, 0x06, 0x07},{0x09, 0x0A, 0x0A, 0x0C},	{0x04, 0x0F, 0x00, 0x0F},{0x0D, 0x05, 0x01, 0x0B},{0x04, 0x0F, 0x0B, 0x07},{0x08, 0x0D, 0x03, 0x0C},{0x0E, 0x0C, 0x09, 0x0B},{0x07, 0x06, 0x0F, 0x03},{0x03, 0x09, 0x04, 0x04},{0x03, 0x09, 0x0F, 0x0C},{0x06, 0x01, 0x0D, 0x0B},{0x0C, 0x02, 0x0F, 0x07},{0x03, 0x09, 0x03, 0x08},{0x0E, 0x0C, 0x0E, 0x07},{0x0A, 0x03, 0x0E, 0x08},{0x0F, 0x0B, 0x07, 0x07},{0x00, 0x00, 0x07, 0x0C},{0x05, 0x08, 0x09, 0x0F},{0x07, 0x06, 0x08, 0x0F},{0x0E, 0x0C, 0x05, 0x0F},{0x0F, 0x0B, 0x0C, 0x0F},{0x05, 0x08, 0x05, 0x0B},{0x0F, 0x0B, 0x0B, 0x03},{0x08, 0x0D, 0x04, 0x00},{0x03, 0x09, 0x08, 0x00},{0x0B, 0x04, 0x0C, 0x00},{0x00, 0x00, 0x0C, 0x04},{0x00, 0x00, 0x0B, 0x08},{0x0D, 0x05, 0x0A, 0x03},{0x01, 0x07, 0x09, 0x00},{0x02, 0x0E, 0x01, 0x00},{0x01, 0x07, 0x05, 0x04},{0x0A, 0x03, 0x02, 0x0C},{0x07, 0x06, 0x04, 0x0B},{0x06, 0x01, 0x06, 0x03}};

	unsigned char* LED_64_4_D2::byte2nibble(unsigned char bytes[], int offSet)
	{
		unsigned char *b = new unsigned char[16];
		for (int i = 0; i < 8; i++)
		{
			b[i * 2 + 0] = static_cast<unsigned char>(bytes[offSet + i] & 0x0F);
			b[i * 2 + 1] = static_cast<unsigned char>(bytes[offSet + i] >> 4 & 0xF);
		}
		return b;
	}

	void LED_64_4_D2::nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet)
	{
		for (int i = 0; i < 8; i++)
		{
			bytes[offSet + i] = static_cast<unsigned char>(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
		}
	}

    void LED_64_4_D2::AddKey(unsigned char state[], unsigned char roundKey[])
    {
        for (int i = 0; i < 16; i++)
            state[i] ^= roundKey[i];
    }

    void LED_64_4_D2::AddConstants(unsigned char state[], int round)
    {
        state[0] ^= keySizeConst0inv;
        state[5] ^= keySizeConst1inv;
        state[10] ^= keySizeConst2inv;
        state[15] ^= keySizeConst3inv;

        state[1] ^= RCconstants[round][0];
        state[11] ^= RCconstants[round][2];

        state[6] ^= RCconstants[round][1];
        state[12] ^= RCconstants[round][3];
    }

    void LED_64_4_D2::SubCellShiftRowAndMixColumns(unsigned char state[])
    {
        unsigned char *temp = new unsigned char[16];

        //inverse MixColumn
        /*
        C C D 4
        3 8 4 5
        7 6 2 E
        D 9 9 D
        */

        temp[0] = static_cast<unsigned char>(mulc[state[0]] ^ mulc[state[4]] ^ muld[state[8]] ^ mul4[state[12]]);
        temp[5] = static_cast<unsigned char>(mul3[state[0]] ^ mul8[state[4]] ^ mul4[state[8]] ^ mul5[state[12]]);
        temp[10] = static_cast<unsigned char>(mul7[state[0]] ^ mul6[state[4]] ^ mul2[state[8]] ^ mule[state[12]]);
        temp[15] = static_cast<unsigned char>(muld[state[0]] ^ mul9[state[4]] ^ mul9[state[8]] ^ muld[state[12]]);

        temp[1] = static_cast<unsigned char>(mulc[state[1]] ^ mulc[state[5]] ^ muld[state[9]] ^ mul4[state[13]]);
        temp[6] = static_cast<unsigned char>(mul3[state[1]] ^ mul8[state[5]] ^ mul4[state[9]] ^ mul5[state[13]]);
        temp[11] = static_cast<unsigned char>(mul7[state[1]] ^ mul6[state[5]] ^ mul2[state[9]] ^ mule[state[13]]);
        temp[12] = static_cast<unsigned char>(muld[state[1]] ^ mul9[state[5]] ^ mul9[state[9]] ^ muld[state[13]]);

        temp[2] = static_cast<unsigned char>(mulc[state[2]] ^ mulc[state[6]] ^ muld[state[10]] ^ mul4[state[14]]);
        temp[7] = static_cast<unsigned char>(mul3[state[2]] ^ mul8[state[6]] ^ mul4[state[10]] ^ mul5[state[14]]);
        temp[8] = static_cast<unsigned char>(mul7[state[2]] ^ mul6[state[6]] ^ mul2[state[10]] ^ mule[state[14]]);
        temp[13] = static_cast<unsigned char>(muld[state[2]] ^ mul9[state[6]] ^ mul9[state[10]] ^ muld[state[14]]);

        temp[3] = static_cast<unsigned char>(mulc[state[3]] ^ mulc[state[7]] ^ muld[state[11]] ^ mul4[state[15]]);
        temp[4] = static_cast<unsigned char>(mul3[state[3]] ^ mul8[state[7]] ^ mul4[state[11]] ^ mul5[state[15]]);
        temp[9] = static_cast<unsigned char>(mul7[state[3]] ^ mul6[state[7]] ^ mul2[state[11]] ^ mule[state[15]]);
        temp[14] = static_cast<unsigned char>(muld[state[3]] ^ mul9[state[7]] ^ mul9[state[11]] ^ muld[state[15]]);

        for(int i=0;i<16;i++)
            state[i] = temp[i];
    }

    void LED_64_4_D2::invMixColumnShiftRow(unsigned char state[])
    {
        unsigned char *temp = new unsigned char[16];

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

        for(int i=0;i<16;i++)
            state[i] = temp[i];
    }

    void LED_64_4_D2::invSbox(unsigned char state[])
    {
        for (int i = 0; i < 16; i++)
            state[i] = sBoxInv[state[i]];
    }


    void LED_64_4_D2::EncryptOneBlock(unsigned char state[], unsigned char sk0[])
    {
        unsigned char* skMix = new unsigned char[16];
        for(int i=0;i<16;i++)
            skMix[i] = sk0[i];

        invMixColumnShiftRow(skMix);

        AddKey(state, sk0);
        invMixColumnShiftRow(state);
        for (int i = 31; i > 0; i--)
        {
            SubCellShiftRowAndMixColumns(state);
            AddConstants(state, i);
            if (i % 4 == 0)
            {
                AddKey(state, skMix);
            }
        }
        invSbox(state);

        state[0] ^= keySizeConst0;
        state[4] ^= keySizeConst1;
        state[8] ^= keySizeConst2;
        state[12] ^= keySizeConst3;

        state[1] ^= RCconstants[0][0];
        state[9] ^= RCconstants[0][2];

        state[5] ^= RCconstants[0][1];
        state[13] ^= RCconstants[0][3];

        AddKey(state, sk0);
    }

    unsigned char* LED_64_4_D2::Decrypt(unsigned char input[], unsigned char key[], int len)
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
