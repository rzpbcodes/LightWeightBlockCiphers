class LED_64_4_D1:
    keySize = 64
    keySizeConst0 = (keySize >> 4)
    keySizeConst1 = (0x01 ^ (keySize >> 4))
    keySizeConst2 = (0x02 ^ (keySize & 0x0F))
    keySizeConst3 = (0x03 ^ (keySize & 0x0F))

    sBoxInv = [0x05, 0x0E, 0x0F, 0x08, 0x0C, 0x01, 0x02, 0x0D, 0x0B, 0x04, 0x06, 0x03, 0x00, 0x07, 0x09, 0x0A]

    RC02 = [0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07,
    0x06, 0x05, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03,
    0x06, 0x05, 0x03, 0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00]

    RC13 = [0x01, 0x03, 0x07, 0x07, 0x07, 0x06, 0x05, 0x03, 0x07, 0x07, 0x06, 0x04, 0x01, 0x03, 0x07, 0x06, 0x05, 0x02,
    0x05, 0x03, 0x06, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x03, 0x07, 0x06, 0x04, 0x00, 0x01, 0x03, 0x06, 0x05, 0x03,
    0x06, 0x05, 0x02, 0x04, 0x01, 0x02, 0x04, 0x00, 0x01, 0x02, 0x04]

    mul2Inv = [0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x03, 0x01, 0x07, 0x05, 0x0B, 0x09, 0x0F, 0x0D]
    mul3Inv = [0x00, 0x03, 0x06, 0x05, 0x0C, 0x0F, 0x0A, 0x09, 0x0B, 0x08, 0x0D, 0x0E, 0x07, 0x04, 0x01, 0x02]
    mul4Inv = [0x00, 0x04, 0x08, 0x0C, 0x03, 0x07, 0x0B, 0x0F, 0x06, 0x02, 0x0E, 0x0A, 0x05, 0x01, 0x0D, 0x09]
    mul5Inv = [0x00, 0x05, 0x0A, 0x0F, 0x07, 0x02, 0x0D, 0x08, 0x0E, 0x0B, 0x04, 0x01, 0x09, 0x0C, 0x03, 0x06]
    mul6Inv = [0x00, 0x06, 0x0C, 0x0A, 0x0B, 0x0D, 0x07, 0x01, 0x05, 0x03, 0x09, 0x0F, 0x0E, 0x08, 0x02, 0x04]
    mul7Inv = [0x00, 0x07, 0x0E, 0x09, 0x0F, 0x08, 0x01, 0x06, 0x0D, 0x0A, 0x03, 0x04, 0x02, 0x05, 0x0C, 0x0B]
    mul8Inv = [0x00, 0x08, 0x03, 0x0B, 0x06, 0x0E, 0x05, 0x0D, 0x0C, 0x04, 0x0F, 0x07, 0x0A, 0x02, 0x09, 0x01]
    mul9Inv = [0x00, 0x09, 0x01, 0x08, 0x02, 0x0B, 0x03, 0x0A, 0x04, 0x0D, 0x05, 0x0C, 0x06, 0x0F, 0x07, 0x0E]
    mulcInv = [0x00, 0x0C, 0x0B, 0x07, 0x05, 0x09, 0x0E, 0x02, 0x0A, 0x06, 0x01, 0x0D, 0x0F, 0x03, 0x04, 0x08]
    muldInv = [0x00, 0x0D, 0x09, 0x04, 0x01, 0x0C, 0x08, 0x05, 0x02, 0x0F, 0x0B, 0x06, 0x03, 0x0E, 0x0A, 0x07]
    muleInv = [0x00, 0x0E, 0x0F, 0x01, 0x0D, 0x03, 0x02, 0x0C, 0x09, 0x07, 0x06, 0x08, 0x04, 0x0A, 0x0B, 0x05]

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

        state[1] ^= cls.RC02[31 - round]
        state[9] ^= cls.RC02[31 - round]

        state[5] ^= cls.RC13[31 - round]
        state[13] ^= cls.RC13[31 - round]
        return

    @classmethod
    def SubCellShiftRowAndMixColumns(cls, state):
        temp = [None] * 16

        temp[0] = (cls.mulcInv[state[0]] ^ cls.mulcInv[state[4]] ^ cls.muldInv[state[8]] ^ cls.mul4Inv[state[12]])
        temp[5] = (cls.mul3Inv[state[0]] ^ cls.mul8Inv[state[4]] ^ cls.mul4Inv[state[8]] ^ cls.mul5Inv[state[12]])
        temp[10] = (cls.mul7Inv[state[0]] ^ cls.mul6Inv[state[4]] ^ cls.mul2Inv[state[8]] ^ cls.muleInv[state[12]])
        temp[15] = (cls.muldInv[state[0]] ^ cls.mul9Inv[state[4]] ^ cls.mul9Inv[state[8]] ^ cls.muldInv[state[12]])

        temp[1] = (cls.mulcInv[state[1]] ^ cls.mulcInv[state[5]] ^ cls.muldInv[state[9]] ^ cls.mul4Inv[state[13]])
        temp[6] = (cls.mul3Inv[state[1]] ^ cls.mul8Inv[state[5]] ^ cls.mul4Inv[state[9]] ^ cls.mul5Inv[state[13]])
        temp[11] = (cls.mul7Inv[state[1]] ^ cls.mul6Inv[state[5]] ^ cls.mul2Inv[state[9]] ^ cls.muleInv[state[13]])
        temp[12] = (cls.muldInv[state[1]] ^ cls.mul9Inv[state[5]] ^ cls.mul9Inv[state[9]] ^ cls.muldInv[state[13]])

        temp[2] = (cls.mulcInv[state[2]] ^ cls.mulcInv[state[6]] ^ cls.muldInv[state[10]] ^ cls.mul4Inv[state[14]])
        temp[7] = (cls.mul3Inv[state[2]] ^ cls.mul8Inv[state[6]] ^ cls.mul4Inv[state[10]] ^ cls.mul5Inv[state[14]])
        temp[8] = (cls.mul7Inv[state[2]] ^ cls.mul6Inv[state[6]] ^ cls.mul2Inv[state[10]] ^ cls.muleInv[state[14]])
        temp[13] = (cls.muldInv[state[2]] ^ cls.mul9Inv[state[6]] ^ cls.mul9Inv[state[10]] ^ cls.muldInv[state[14]])

        temp[3] = (cls.mulcInv[state[3]] ^ cls.mulcInv[state[7]] ^ cls.muldInv[state[11]] ^ cls.mul4Inv[state[15]])
        temp[4] = (cls.mul3Inv[state[3]] ^ cls.mul8Inv[state[7]] ^ cls.mul4Inv[state[11]] ^ cls.mul5Inv[state[15]])
        temp[9] = (cls.mul7Inv[state[3]] ^ cls.mul6Inv[state[7]] ^ cls.mul2Inv[state[11]] ^ cls.muleInv[state[15]])
        temp[14] = (cls.muldInv[state[3]] ^ cls.mul9Inv[state[7]] ^ cls.mul9Inv[state[11]] ^ cls.muldInv[state[15]])

        for i in range(0, 16, 1):
            state[i] = cls.sBoxInv[temp[i]];
        return

    @classmethod
    def Step(cls, state, step):
        for i in range(0, 4, 1):
            cls.SubCellShiftRowAndMixColumns(state)
            cls.AddConstants(state, (step * 4 + i))
        return

    @classmethod
    def EncryptOneBlock(cls, state, sk0):
        cls.AddKey(state, sk0)
        for i in range(0, 8, 1):
            cls.Step(state, i)
            cls.AddKey(state, sk0)
        return

    @classmethod
    def Decrypt(cls, plainText, key):
        cipherText = [None] * len(plainText)
        sk0 = cls.byte2nibble(key, 0)
        for i in range(0, len(plainText), 8):
            state = cls.byte2nibble(plainText, i)
            cls.EncryptOneBlock(state, sk0)
            cls.nibbles2byteCopy(state, cipherText, i)
        return cipherText
