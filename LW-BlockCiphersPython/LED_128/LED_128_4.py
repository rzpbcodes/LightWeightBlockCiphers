class LED_128_4:
    keySize = 128
    keySizeConst0 = (keySize >> 4)
    keySizeConst1 = (0x01 ^ (keySize >> 4))
    keySizeConst2 = (0x02 ^ (keySize & 0x0F))
    keySizeConst3 = (0x03 ^ (keySize & 0x0F))

    sBox = [0x0C, 0x05, 0x06, 0x0B, 0x09, 0x00, 0x0A, 0x0D, 0x03, 0x0E, 0x0F, 0x08, 0x04, 0x07, 0x01, 0x02]
    RC02 = [0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07,
            0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01,
            0x03, 0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00]

    RC13 = [0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02,
            0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05,
            0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00, 0x01, 0x02, 0x04]

    mul2 = [0x0B, 0x0A, 0x0C, 0x05, 0x01, 0x00, 0x07, 0x09, 0x06, 0x0F, 0x0D, 0x03, 0x08, 0x0E, 0x02, 0x04]
    mul4 = [0x05, 0x07, 0x0B, 0x0A, 0x02, 0x00, 0x0E, 0x01, 0x0C, 0x0D, 0x09, 0x06, 0x03, 0x0F, 0x04, 0x08]
    mul5 = [0x09, 0x02, 0x0D, 0x01, 0x0B, 0x00, 0x04, 0x0C, 0x0F, 0x03, 0x06, 0x0E, 0x07, 0x08, 0x05, 0x0A]
    mul6 = [0x0E, 0x0D, 0x07, 0x0F, 0x03, 0x00, 0x09, 0x08, 0x0A, 0x02, 0x04, 0x05, 0x0B, 0x01, 0x06, 0x0C]
    mul8 = [0x0A, 0x0E, 0x05, 0x07, 0x04, 0x00, 0x0F, 0x02, 0x0B, 0x09, 0x01, 0x0C, 0x06, 0x0D, 0x08, 0x03]
    mul9 = [0x06, 0x0B, 0x03, 0x0C, 0x0D, 0x00, 0x05, 0x0F, 0x08, 0x07, 0x0E, 0x04, 0x02, 0x0A, 0x09, 0x01]
    mula = [0x01, 0x04, 0x09, 0x02, 0x05, 0x00, 0x08, 0x0B, 0x0D, 0x06, 0x0C, 0x0F, 0x0E, 0x03, 0x0A, 0x07]
    mulb = [0x0D, 0x01, 0x0F, 0x09, 0x0C, 0x00, 0x02, 0x06, 0x0E, 0x08, 0x03, 0x07, 0x0A, 0x04, 0x0B, 0x05]
    mule = [0x04, 0x03, 0x02, 0x08, 0x07, 0x00, 0x06, 0x0A, 0x01, 0x0B, 0x05, 0x09, 0x0D, 0x0C, 0x0E, 0x0F]
    mulf = [0x08, 0x06, 0x04, 0x03, 0x0E, 0x00, 0x0C, 0x07, 0x02, 0x05, 0x0A, 0x01, 0x09, 0x0B, 0x0F, 0x0D]

    @classmethod
    def byte2nibble(cls, byteArr, offSet):
        b = [None] * 16
        for i in range(0, 8, 1):
            b[i * 2 + 0] = byteArr[offSet + i] & 0x0F
            b[i * 2 + 1] = (byteArr[offSet + i] >> 4) & 0x0F
        return b

    @classmethod
    def nibbles2byte(cls, nibbles):
        c = [None] * 8
        for i in range(0, 8, 1):
            c[i] = (nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4))
        return c

    @classmethod
    def nibbles2byteCopy(cls, nibbles, byteArr, offSet):
        for i in range(0, 8, 1):
            byteArr[offSet + i] = (nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4))
        return

    @classmethod
    def AddKey(cl, state, roundKey):
        for i in range(0, 16, 1):
            state[i] ^= roundKey[i]
        return

    @classmethod
    def AddConstants(cls, state, round):
        state[0] ^= cls.keySizeConst0
        state[4] ^= cls.keySizeConst1
        state[8] ^= cls.keySizeConst2
        state[12] ^= cls.keySizeConst3

        state[1] ^= cls.RC02[round]
        state[9] ^= cls.RC02[round]

        state[5] ^= cls.RC13[round]
        state[13] ^= cls.RC13[round]
        return

    @classmethod
    def SubCellShiftRowAndMixColumns(cls, state):
        temp = [None] * 16

        temp[0] = (cls.mul4[state[0]] ^ cls.sBox[state[5]] ^ cls.mul2[state[10]] ^ cls.mul2[state[15]])
        temp[4] = (cls.mul8[state[0]] ^ cls.mul6[state[5]] ^ cls.mul5[state[10]] ^ cls.mul6[state[15]])
        temp[8] = (cls.mulb[state[0]] ^ cls.mule[state[5]] ^ cls.mula[state[10]] ^ cls.mul9[state[15]])
        temp[12] = (cls.mul2[state[0]] ^ cls.mul2[state[5]] ^ cls.mulf[state[10]] ^ cls.mulb[state[15]])

        temp[1] = (cls.mul4[state[1]] ^ cls.sBox[state[6]] ^ cls.mul2[state[11]] ^ cls.mul2[state[12]])
        temp[5] = (cls.mul8[state[1]] ^ cls.mul6[state[6]] ^ cls.mul5[state[11]] ^ cls.mul6[state[12]])
        temp[9] = (cls.mulb[state[1]] ^ cls.mule[state[6]] ^ cls.mula[state[11]] ^ cls.mul9[state[12]])
        temp[13] = (cls.mul2[state[1]] ^ cls.mul2[state[6]] ^ cls.mulf[state[11]] ^ cls.mulb[state[12]])

        temp[2] = (cls.mul4[state[2]] ^ cls.sBox[state[7]] ^ cls.mul2[state[8]] ^ cls.mul2[state[13]])
        temp[6] = (cls.mul8[state[2]] ^ cls.mul6[state[7]] ^ cls.mul5[state[8]] ^ cls.mul6[state[13]])
        temp[10] = (cls.mulb[state[2]] ^ cls.mule[state[7]] ^ cls.mula[state[8]] ^ cls.mul9[state[13]])
        temp[14] = (cls.mul2[state[2]] ^ cls.mul2[state[7]] ^ cls.mulf[state[8]] ^ cls.mulb[state[13]])

        temp[3] = (cls.mul4[state[3]] ^ cls.sBox[state[4]] ^ cls.mul2[state[9]] ^ cls.mul2[state[14]])
        temp[7] = (cls.mul8[state[3]] ^ cls.mul6[state[4]] ^ cls.mul5[state[9]] ^ cls.mul6[state[14]])
        temp[11] = (cls.mulb[state[3]] ^ cls.mule[state[4]] ^ cls.mula[state[9]] ^ cls.mul9[state[14]])
        temp[15] = (cls.mul2[state[3]] ^ cls.mul2[state[4]] ^ cls.mulf[state[9]] ^ cls.mulb[state[14]])

        for i in range(0, 16, 1):
            state[i] = temp[i]
        return

    @classmethod
    def Step(cls, state, step):
        for i in range(0, 4, 1):
            cls.AddConstants(state, (step * 4 + i))
            cls.SubCellShiftRowAndMixColumns(state)
        return

    @classmethod
    def EncryptOneBlock(cls, state, sk0, sk1):
        for i in range(0, 12, 2):
            cls.AddKey(state, sk0)
            cls.Step(state, i)
            cls.AddKey(state, sk1)
            cls.Step(state, i+1)
        cls.AddKey(state, sk0)
        return

    @classmethod
    def Encrypt(cls, plainText, key):
        cipherText = [None] * len(plainText)
        sk0 = cls.byte2nibble(key, 0)
        sk1 = cls.byte2nibble(key, 8)
        for i in range(0, len(plainText), 8):
            state = cls.byte2nibble(plainText, i)
            cls.EncryptOneBlock(state, sk0, sk1)
            cls.nibbles2byteCopy(state, cipherText, i)
        return cipherText
