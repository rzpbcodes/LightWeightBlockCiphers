namespace LW_BlockCiphers
{
	class LED_80_16
	{
	private:
		static unsigned char keySize;
		static unsigned short keySizeConst;
		static unsigned short RC[];

		static unsigned short mask;

		static unsigned short T0[];
		static unsigned short T1[];
		static unsigned short T2[];
		static unsigned short T3[];

		static unsigned short* byte2uint16(unsigned char b[], int offSet);

		static unsigned char* uint162byte(unsigned short x[]);

		static void uint162byte(unsigned short x[], unsigned char b[], int offSet);

		static void AddKey(unsigned short state[], unsigned short roundKey[]);

		static void AddConstants(unsigned short state[], int round);

		static void SubCellShiftRowAndMixColumns(unsigned short state[]);

		static void Step(unsigned short state[], int step);

		static void EncryptOneBlock(unsigned short state[], unsigned short sk0[], unsigned short sk1[]);

    public:
		static unsigned char* Encrypt(unsigned char input[], unsigned char key[], int len);

	};
}
