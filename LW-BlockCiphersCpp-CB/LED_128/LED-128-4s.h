namespace LW_BlockCiphers
{
	class LED_128_4s
	{
	private:
		static unsigned char keySize;
		static unsigned char sBox[];
		static unsigned char RC[];

		static unsigned char nibbleFilter;
		static unsigned char ReductionPoly;

		static unsigned char* byte2nibble(unsigned char bytes[], int offSet);

		static unsigned char* nibbles2byte(unsigned char nibbles[]);

		static void nibbles2byte(unsigned char nibbles[], unsigned char bytes[], int offSet);

		static unsigned char xTimes(unsigned char a);

		static unsigned char x2Times(unsigned char a);

		static void MultiplyColumn(unsigned char temp[]);

		static void AddKey(unsigned char state[], unsigned char roundKey[]);

		static void AddConstants(unsigned char state[], int round);

		static void SboxShiftRows(unsigned char state[]);

		static void MixColumns(unsigned char state[]);

		static void Step(unsigned char state[], int step);

		static void EncryptOneBlock(unsigned char state[], unsigned char subKeys[], unsigned char sk1[]);

	public:
		static unsigned char* Encrypt(unsigned char input[], unsigned char key[], int len);

	};
}
