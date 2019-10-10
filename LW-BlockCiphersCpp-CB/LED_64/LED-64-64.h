namespace LW_BlockCiphers
{
	class LED_64_64
	{
	private:
		static unsigned char keySize;

		static unsigned long long T0[];
		static unsigned long long T1[];
		static unsigned long long T2[];
		static unsigned long long T3[];
		static unsigned long long T4[];
		static unsigned long long T5[];
		static unsigned long long T6[];
		static unsigned long long T7[];

		static unsigned long long RCandKeySizeConstLong[];

		static unsigned long long byte2ulong(unsigned char b[], int offSet);

		static unsigned char* ulong2byte(unsigned long long x);

		static void ulong2byte(unsigned long long x, unsigned char b[], int offSet);

		static unsigned long long AddKey(unsigned long long state, unsigned long long roundKey);

		static unsigned long long AddConstants(unsigned long long state, int round);

		static unsigned long long SubCellShiftRowAndMixColumns(unsigned long long state);

		static unsigned long long Step(unsigned long long state, int step);

		static unsigned long long EncryptOneBlock(unsigned long long state, unsigned long long sk0);

	public:
		static unsigned char* Encrypt(unsigned char input[], unsigned char key[], int len);

	};
}
