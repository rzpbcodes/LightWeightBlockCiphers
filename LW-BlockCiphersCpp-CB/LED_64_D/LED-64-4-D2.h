namespace LW_BlockCiphers
{
    class LED_64_4_D2
	{
		//4 1 2 2 8 6 5 6 B E A 9 2 2 F B
		//C C D 4 3 8 4 5 7 6 2 E D 9 9 D

	private:
		static unsigned char keySize;
		static unsigned char keySizeConst0;
		static unsigned char keySizeConst1;
		static unsigned char keySizeConst2;
		static unsigned char keySizeConst3;

        static unsigned char keySizeConst0inv;
		static unsigned char keySizeConst1inv;
		static unsigned char keySizeConst2inv;
		static unsigned char keySizeConst3inv;

		static unsigned char sBoxInv[];

		static unsigned char mul2Inv[];
		static unsigned char mul3Inv[];
		static unsigned char mul4Inv[];
		static unsigned char mul5Inv[];
		static unsigned char mul6Inv[];
		static unsigned char mul7Inv[];
		static unsigned char mul8Inv[];
		static unsigned char mul9Inv[];
		static unsigned char mulcInv[];
		static unsigned char muldInv[];
		static unsigned char muleInv[];

        static unsigned char mul2[];
		static unsigned char mul3[];
		static unsigned char mul4[];
		static unsigned char mul5[];
		static unsigned char mul6[];
		static unsigned char mul7[];
		static unsigned char mul8[];
		static unsigned char mul9[];
		static unsigned char mulc[];
		static unsigned char muld[];
		static unsigned char mule[];

		static unsigned char RCconstants[][4];

		static unsigned char* byte2nibble(unsigned char bytes[], int offSet);

		static void nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet);

		static void AddKey(unsigned char state[], unsigned char roundKey[]);

		static void AddConstants(unsigned char state[], int round);

		static void SubCellShiftRowAndMixColumns(unsigned char state[]);

        static void invMixColumnShiftRow(unsigned char state[]);

		static void invSbox(unsigned char state[]);

		static void EncryptOneBlock(unsigned char state[], unsigned char sk0[]);

	public:
		static unsigned char* Decrypt(unsigned char input[], unsigned char key[], int len);

	};
}
