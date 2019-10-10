namespace LW_BlockCiphers
{
	class LED_64_4
	{
	private:
		static unsigned char keySize;
		static unsigned char keySizeConst0;
		static unsigned char keySizeConst1;
		static unsigned char keySizeConst2;
		static unsigned char keySizeConst3;

		static unsigned char sBox[];
		static unsigned char RC02[];
		static unsigned char RC13[];

		static unsigned char mul2[];
		static unsigned char mul4[];
		static unsigned char mul5[];
		static unsigned char mul6[];
		static unsigned char mul8[];
		static unsigned char mul9[];
		static unsigned char mula[];
		static unsigned char mulb[];
		static unsigned char mule[];
		static unsigned char mulf[];

		static unsigned char* byte2nibble(unsigned char bytes[], int offSet);

		static unsigned char* nibbles2byte(unsigned char nibbles[]);

		static void nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet);

		static void AddKey(unsigned char state[], unsigned char roundKey[]);

		static void AddConstants(unsigned char state[], int round);

		static void SubCellShiftRowAndMixColumns(unsigned char state[]);

		static void Step(unsigned char state[], int step);

		static void EncryptOneBlock(unsigned char state[], unsigned char subKeys[]);

	public:
		static unsigned char* Encrypt(unsigned char input[], unsigned char key[], int len);

	};
}
