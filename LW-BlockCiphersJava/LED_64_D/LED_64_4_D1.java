package lw.blockciphersjava.LED_64_D;

public class LED_64_4_D1
{
	//4 1 2 2 8 6 5 6 B E A 9 2 2 F B 
	//C C D 4 3 8 4 5 7 6 2 E D 9 9 D 

	private static byte keySize = 64;
	private static byte keySizeConst0 = (byte)(keySize >>> 4);
	private static byte keySizeConst1 = (byte)(0x01 ^ (keySize >>> 4));
	private static byte keySizeConst2 = (byte)(0x02 ^ (keySize & 0x0F));
	private static byte keySizeConst3 = (byte)(0x03 ^ (keySize & 0x0F));

	private static byte[] sBoxInv = new byte[] {0x05, 0x0E, 0x0F, 0x08, 0x0C, 0x01, 0x02, 0x0D, 0x0B, 0x04, 0x06, 0x03, 0x00, 0x07, 0x09, 0x0A};

	private static byte[] RC02 = new byte[] {0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00};

	private static byte[] RC13 = new byte[] {0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00, 0x01, 0x02, 0x04};

	private static byte[] mul2Inv = new byte[] {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x03, 0x01, 0x07, 0x05, 0x0B, 0x09, 0x0F, 0x0D};
	private static byte[] mul3Inv = new byte[] {0x00, 0x03, 0x06, 0x05, 0x0C, 0x0F, 0x0A, 0x09, 0x0B, 0x08, 0x0D, 0x0E, 0x07, 0x04, 0x01, 0x02};
	private static byte[] mul4Inv = new byte[] {0x00, 0x04, 0x08, 0x0C, 0x03, 0x07, 0x0B, 0x0F, 0x06, 0x02, 0x0E, 0x0A, 0x05, 0x01, 0x0D, 0x09};
	private static byte[] mul5Inv = new byte[] {0x00, 0x05, 0x0A, 0x0F, 0x07, 0x02, 0x0D, 0x08, 0x0E, 0x0B, 0x04, 0x01, 0x09, 0x0C, 0x03, 0x06};
	private static byte[] mul6Inv = new byte[] {0x00, 0x06, 0x0C, 0x0A, 0x0B, 0x0D, 0x07, 0x01, 0x05, 0x03, 0x09, 0x0F, 0x0E, 0x08, 0x02, 0x04};
	private static byte[] mul7Inv = new byte[] {0x00, 0x07, 0x0E, 0x09, 0x0F, 0x08, 0x01, 0x06, 0x0D, 0x0A, 0x03, 0x04, 0x02, 0x05, 0x0C, 0x0B};
	private static byte[] mul8Inv = new byte[] {0x00, 0x08, 0x03, 0x0B, 0x06, 0x0E, 0x05, 0x0D, 0x0C, 0x04, 0x0F, 0x07, 0x0A, 0x02, 0x09, 0x01};
	private static byte[] mul9Inv = new byte[] {0x00, 0x09, 0x01, 0x08, 0x02, 0x0B, 0x03, 0x0A, 0x04, 0x0D, 0x05, 0x0C, 0x06, 0x0F, 0x07, 0x0E};
	private static byte[] mulcInv = new byte[] {0x00, 0x0C, 0x0B, 0x07, 0x05, 0x09, 0x0E, 0x02, 0x0A, 0x06, 0x01, 0x0D, 0x0F, 0x03, 0x04, 0x08};
	private static byte[] muldInv = new byte[] {0x00, 0x0D, 0x09, 0x04, 0x01, 0x0C, 0x08, 0x05, 0x02, 0x0F, 0x0B, 0x06, 0x03, 0x0E, 0x0A, 0x07};
	private static byte[] muleInv = new byte[] {0x00, 0x0E, 0x0F, 0x01, 0x0D, 0x03, 0x02, 0x0C, 0x09, 0x07, 0x06, 0x08, 0x04, 0x0A, 0x0B, 0x05};
        
    static byte[] byte2nibble(short[] bytes, int offSet)
    {
        byte[] b = new byte[16];
        for (int i = 0; i < 8; i++)
        {
            b[i * 2 + 0] = (byte)(bytes[offSet + i] & 0x0F);
            b[i * 2 + 1] = (byte)(bytes[offSet + i] >> 4 & 0xF);
        }
        return b;
    }

    static short[] nibbles2byte(byte[] nibbles)
    {
        short[] c = new short[8];
        for (int i = 0; i < 8; i++)
        {
            c[i] = (short)(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
        }
        return c;
    }

    static void nibbles2byte(byte[] nibbles, short[] bytes, int offSet)
    {
        for (int i = 0; i < 8; i++)
            bytes[offSet + i] = (short)(nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4));
    }

    static void AddKey(byte[] state, byte[] roundKey)
    {
        for (int i = 0; i < 16; i++)
            state[i] ^= roundKey[i];
    }

	private static void AddConstants(byte[] state, int round)
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

	private static void SubCellShiftRowAndMixColumns(byte[] state)
	{
		byte[] temp = new byte[16];


		temp[0] = (byte)(mulcInv[state[0]] ^ mulcInv[state[4]] ^ muldInv[state[8]] ^ mul4Inv[state[12]]);
		temp[5] = (byte)(mul3Inv[state[0]] ^ mul8Inv[state[4]] ^ mul4Inv[state[8]] ^ mul5Inv[state[12]]);
		temp[10] = (byte)(mul7Inv[state[0]] ^ mul6Inv[state[4]] ^ mul2Inv[state[8]] ^ muleInv[state[12]]);
		temp[15] = (byte)(muldInv[state[0]] ^ mul9Inv[state[4]] ^ mul9Inv[state[8]] ^ muldInv[state[12]]);

		temp[1] = (byte)(mulcInv[state[1]] ^ mulcInv[state[5]] ^ muldInv[state[9]] ^ mul4Inv[state[13]]);
		temp[6] = (byte)(mul3Inv[state[1]] ^ mul8Inv[state[5]] ^ mul4Inv[state[9]] ^ mul5Inv[state[13]]);
		temp[11] = (byte)(mul7Inv[state[1]] ^ mul6Inv[state[5]] ^ mul2Inv[state[9]] ^ muleInv[state[13]]);
		temp[12] = (byte)(muldInv[state[1]] ^ mul9Inv[state[5]] ^ mul9Inv[state[9]] ^ muldInv[state[13]]);

		temp[2] = (byte)(mulcInv[state[2]] ^ mulcInv[state[6]] ^ muldInv[state[10]] ^ mul4Inv[state[14]]);
		temp[7] = (byte)(mul3Inv[state[2]] ^ mul8Inv[state[6]] ^ mul4Inv[state[10]] ^ mul5Inv[state[14]]);
		temp[8] = (byte)(mul7Inv[state[2]] ^ mul6Inv[state[6]] ^ mul2Inv[state[10]] ^ muleInv[state[14]]);
		temp[13] = (byte)(muldInv[state[2]] ^ mul9Inv[state[6]] ^ mul9Inv[state[10]] ^ muldInv[state[14]]);

		temp[3] = (byte)(mulcInv[state[3]] ^ mulcInv[state[7]] ^ muldInv[state[11]] ^ mul4Inv[state[15]]);
		temp[4] = (byte)(mul3Inv[state[3]] ^ mul8Inv[state[7]] ^ mul4Inv[state[11]] ^ mul5Inv[state[15]]);
		temp[9] = (byte)(mul7Inv[state[3]] ^ mul6Inv[state[7]] ^ mul2Inv[state[11]] ^ muleInv[state[15]]);
		temp[14] = (byte)(muldInv[state[3]] ^ mul9Inv[state[7]] ^ mul9Inv[state[11]] ^ muldInv[state[15]]);

		for (int i = 0; i < state.length; i++)
                    state[i] = sBoxInv[temp[i]];
	}

	private static void Step(byte[]state, int step)
	{
		for (int i = 0; i < 4; i++)
		{
			SubCellShiftRowAndMixColumns(state);
			AddConstants(state, (step * 4 + i));
		}
	}

	private static void EncryptOneBlock(byte[] state, byte[] sk0)
	{
		AddKey(state, sk0);
		for (int i = 0; i < 8; i++)
		{
			Step(state, i);
			AddKey(state, sk0);
		}
	}

	public static short[] Decrypt(short[] input, short[] key)
	{
		short[] cipherText = new short[input.length];

		byte[] sk0 = byte2nibble(key, 0);

		for (int i = 0; i < input.length; i += 8)
		{
			byte[] state = byte2nibble(input, i);
			EncryptOneBlock(state, sk0);

			nibbles2byte(state, cipherText, i);
		}

		return cipherText;
	}
}