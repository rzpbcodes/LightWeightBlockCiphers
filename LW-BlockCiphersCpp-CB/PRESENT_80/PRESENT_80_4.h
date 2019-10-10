namespace LW_BlockCiphers
{
	class PRESENT_80_4
	{
    private:
		static unsigned char sBox4[];
		//	pLayer variables
		static unsigned char position;
		static unsigned char element_source;
		static unsigned char bit_source;
		static unsigned char element_destination;
		static unsigned char bit_destination;
		//	Key scheduling variables
		static unsigned char save1;
		static unsigned char save2;

		static unsigned char* runPresent(unsigned char state[], unsigned char key[]);

	public:
		static unsigned char* Encrypt(unsigned char input[], unsigned char key[], int len);
	};
}
