class PRESENT_80_4:
    sBox4 = [0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2]
    position = 0
    element_source = 0
    bit_source = 0
    element_destination = 0
    bit_destination = 0
    # Key scheduling variables
    save1  = 0
    save2 = 0

    @classmethod
    def runPresent(cls, state, key):
        for round in range(0, 31, 1):
            for i in range(0, 8, 1):
                state[i] ^= key[i + 2]

            for i in range(0, 8, 1):
                state[i] = ((cls.sBox4[(state[i] >> 4) & 0x0F ] << 4 | cls.sBox4[state[i] & 0xF]) & 0xFF)

            temp_pLayer = [0] * 8

            for i in range(0, 64, 1):
                position = ((16 * i) % 63)
                if i == 63:
                    position = 63

                element_source = (i // 8);
                bit_source = (i % 8);
                element_destination = (position // 8);
                bit_destination = (position % 8);
                temp_pLayer[element_destination] |= ((((state[element_source] >> bit_source) & 0x1) << bit_destination)&0xFF);

            for i in range(0, 8, 1):
                state[i] = temp_pLayer[i]

            save1 = key[0]
            save2 = key[1]

            for i in range(0, 8, 1):
                key[i] = key[i + 2]

            key[8] = save1
            key[9] = save2

            save1 = (key[0] & 7)

            for i in range(0, 9, 1):
                key[i] = ((key[i] >> 3 | key[i + 1] << 5)&0xFF);

            key[9] = ((key[9] >> 3 | save1 << 5)&0xFF);

            key[9] = (cls.sBox4[(key[9] >> 4) & 0x0F ] << 4 | (key[9] & 0xF)) # S-Box application

            if ((round + 1) % 2 == 1): # round counter addition
                key[1] ^= 128

            key[2] = (((((round + 1) >> 1) ^ (key[2] & 15)) | (key[2] & 240))&0xFF);

        for i in range(0, 8, 1):
            state[i] ^= key[i + 2]

        return

    @classmethod
    def Encrypt(cls, plainText, key):
        cipherText = [None] * len(plainText)

        for i in range(0, len(plainText), 8):
            state = [0] * 8
            for j in range(0, 8, 1):
                state[j] = plainText[i+j]

            cls.runPresent(state,key)

            for j in range(0, 8, 1):
                cipherText[i+j] = state[j]

        return cipherText