namespace LW_BlockCiphers
{
	class LED_80_32
	{
	private:
		static unsigned char keySize;
		static unsigned long keySizeConst;
		static unsigned long RCandKeySizeConst[];

		static unsigned long mask;

		static unsigned long T0[];
		static unsigned long T1[];
		static unsigned long T2[];
		static unsigned long T3[];

		static unsigned long* byte2uintArr(unsigned char b[], int offSet);

		static unsigned char* uintArr2byte(unsigned long x[]);

		static void uintArr2byte(unsigned long x[], unsigned char b[], int offSet);

		static void AddKey(unsigned long state[], unsigned long roundKey[]);

		static void AddConstants(unsigned long state[], int round);

		static void SubCellShiftRowAndMixColumns(unsigned long state[]);

		static void Step(unsigned long state[], int step);

		static void EncryptOneBlock(unsigned long state[], unsigned long sk0[], unsigned long sk1[]);

	public:
		static unsigned char* Encrypt(unsigned char input[], unsigned char key[], int len);

	};
}
