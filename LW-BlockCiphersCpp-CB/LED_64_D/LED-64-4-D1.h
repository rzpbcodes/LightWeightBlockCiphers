namespace LW_BlockCiphers
{
    class LED_64_4_D1
	{
		//4 1 2 2 8 6 5 6 B E A 9 2 2 F B
		//C C D 4 3 8 4 5 7 6 2 E D 9 9 D

	private:
		static unsigned char keySize;
		static unsigned char keySizeConst0;
		static unsigned char keySizeConst1;
		static unsigned char keySizeConst2;
		static unsigned char keySizeConst3;

		static unsigned char sBoxInv[];

		static unsigned char RC02[];

		static unsigned char RC13[];

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

		static unsigned char* byte2nibble(unsigned char bytes[], int offSet);

		static void nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet);

		static void AddKey(unsigned char state[], unsigned char roundKey[]);

		static void AddConstants(unsigned char state[], int round);

		static void SubCellShiftRowAndMixColumns(unsigned char state[]);

		static void Step(unsigned char state[], int step);

		static void EncryptOneBlock(unsigned char state[], unsigned char sk0[]);

	public:
		static unsigned char* Decrypt(unsigned char input[], unsigned char key[], int len);

	};
}
