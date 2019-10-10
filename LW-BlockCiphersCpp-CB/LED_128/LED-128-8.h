namespace LW_BlockCiphers
{
	class LED_128_8
	{
	private:
		static unsigned char keySize;

		static unsigned char RC0[];
		static unsigned char RC2[];
		static unsigned char RC4[];
		static unsigned char RC6[];

		static unsigned char sBox[];
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


		static unsigned char* byte2byte(unsigned char b[], int offSet);

		static void byte2byte(unsigned char state[], unsigned char b[], int offSet);

		static void AddKey(unsigned char state[], unsigned char roundKey[]);

		static void AddConstants(unsigned char state[], int round);

		static void SubCellShiftRowAndMixColumns(unsigned char state[]);

		static void Step(unsigned char state[], int step);

		static void EncryptOneBlock(unsigned char state[], unsigned char sk0[], unsigned char sk1[]);

	public:
		static unsigned char* Encrypt(unsigned char input[], unsigned char key[], int len);

	};
}
