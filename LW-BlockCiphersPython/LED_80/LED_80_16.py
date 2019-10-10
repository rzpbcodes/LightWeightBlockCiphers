class LED_80_16:
    keySize = 80
    keySizeConst = 0x3245
    RC = [0x1010, 0x3030, 0x7070, 0x7171, 0x7373, 0x6767, 0x5757, 0x3737, 0x7676, 0x7575,
          0x6363, 0x4747, 0x1717, 0x3636, 0x7474, 0x6161, 0x5353, 0x2727, 0x5656, 0x3535,
          0x6262, 0x4545, 0x0303, 0x0606, 0x1414, 0x2020, 0x5050, 0x3131, 0x7272, 0x6565,
          0x4343, 0x0707, 0x1616, 0x3434, 0x6060, 0x5151, 0x3333, 0x6666, 0x5555, 0x2323,
          0x4646, 0x1515, 0x2222, 0x4444, 0x0101, 0x1212, 0x2424, 0x4040]
    mask = 0x000F

    T0 = [0xBDA5, 0xA1E7, 0xCF5B, 0x597A, 0x1C42, 0x00, 0x72FE, 0x9621, 0x6EBC, 0xF89D, 0xD319, 0x37C6, 0x8A63, 0xE4DF, 0x2B84, 0x4538]
    T1 = [0xB4EC, 0xA3D5, 0xC276, 0x58FB, 0x1739, 0x00, 0x769A, 0x9A8D, 0x61A3, 0xFB2E, 0xD54F, 0x3958, 0x8DB4, 0xEC17, 0x2E61, 0x4FC2]
    T2 = [0x819B, 0x642A, 0x49DC, 0x3215, 0xE5B1, 0x00, 0xC847, 0x7BC9, 0x2DF6, 0x563F, 0xAC6D, 0x1FE3, 0x9E78, 0xB38E, 0xFA52, 0xD7A4]
    T3 = [0xD6EB, 0x1BDA, 0xF37C, 0x9CF5, 0xCD31, 0x00, 0x2597, 0x6F89, 0xE8A6, 0x872F, 0x3E4D, 0x7453, 0xA2B8, 0x4A1E, 0xB962, 0x51C4]

    @classmethod
    def byte2uint16(cls, b, offSet):
        x = [None]*4
        x[0] = ((b[offSet + 0] & 0x0F) << 0)
        x[0] ^= ((b[offSet + 2] & 0x0F) << 4)
        x[0] ^= ((b[offSet + 4] & 0x0F) << 8)
        x[0] ^= ((b[offSet + 6] & 0x0F) << 12)

        x[1] = ((b[offSet + 0] & 0xF0) >> 4)
        x[1] ^= ((b[offSet + 2] & 0xF0) << 0)
        x[1] ^= ((b[offSet + 4] & 0xF0) << 4)
        x[1] ^= ((b[offSet + 6] & 0xF0) << 8)

        x[2] = ((b[offSet + 1] & 0x0F) << 0)
        x[2] ^= ((b[offSet + 3] & 0x0F) << 4)
        x[2] ^= ((b[offSet + 5] & 0x0F) << 8)
        x[2] ^= ((b[offSet + 7] & 0x0F) << 12)

        x[3] = ((b[offSet + 1] & 0xF0) >> 4)
        x[3] ^= ((b[offSet + 3] & 0xF0) << 0)
        x[3] ^= ((b[offSet + 5] & 0xF0) << 4)
        x[3] ^= ((b[offSet + 7] & 0xF0) << 8)

        return x

    @classmethod
    def uint162byte(cls, x):
        b = [None]*8
        b[0] = (x[0] & 0xF)
        b[0] ^= ((x[1] & 0xF) << 4)

        b[1] = (x[2] & 0xF)
        b[1] ^= ((x[3] & 0xF) << 4)

        b[2] = (x[0] >> 4 & 0xF)
        b[2] ^= ((x[1] >> 4 & 0xF) << 4)

        b[3] = (x[2] >> 4 & 0xF)
        b[3] ^= ((x[3] >> 4 & 0xF) << 4)

        b[4] = (x[0] >> 8 & 0xF)
        b[4] ^= ((x[1] >> 8 & 0xF) << 4)

        b[5] = (x[2] >> 8 & 0xF)
        b[5] ^= ((x[3] >> 8 & 0xF) << 4)

        b[6] = (x[0] >> 12 & 0xF)
        b[6] ^= ((x[1] >> 12 & 0xF) << 4)

        b[7] = (x[2] >> 12 & 0xF)
        b[7] ^= ((x[3] >> 12 & 0xF) << 4)

        return b

    @classmethod
    def uint162byteCopy(cls, x, b, offSet):
        b[offSet + 0] = (x[0] & 0xF)
        b[offSet + 0] ^= ((x[1] & 0xF) << 4)

        b[offSet + 1] = (x[2] & 0xF)
        b[offSet + 1] ^= ((x[3] & 0xF) << 4)

        b[offSet + 2] = (x[0] >> 4 & 0xF)
        b[offSet + 2] ^= ((x[1] >> 4 & 0xF) << 4)

        b[offSet + 3] = (x[2] >> 4 & 0xF)
        b[offSet + 3] ^= ((x[3] >> 4 & 0xF) << 4)

        b[offSet + 4] = (x[0] >> 8 & 0xF)
        b[offSet + 4] ^= ((x[1] >> 8 & 0xF) << 4)

        b[offSet + 5] = (x[2] >> 8 & 0xF)
        b[offSet + 5] ^= ((x[3] >> 8 & 0xF) << 4)

        b[offSet + 6] = (x[0] >> 12 & 0xF)
        b[offSet + 6] ^= ((x[1] >> 12 & 0xF) << 4)

        b[offSet + 7] = (x[2] >> 12 & 0xF)
        b[offSet + 7] ^= ((x[3] >> 12 & 0xF) << 4)

        return b

    @classmethod
    def AddKey(cls, state, roundKey):
        state[0] ^= roundKey[0]
        state[1] ^= roundKey[1]
        state[2] ^= roundKey[2]
        state[3] ^= roundKey[3]
        return

    @classmethod
    def AddConstants(cls, state, round):
        state[0] ^= cls.keySizeConst
        state[1] ^= cls.RC[round]
        return

    @classmethod
    def SubCellShiftRowAndMixColumns(cls, state):
        temp = [None]*4
        temp[0] = cls.T0[(state[0] >> 0) & cls.mask]
        temp[0] ^= cls.T1[(state[1] >> 4) & cls.mask]
        temp[0] ^= cls.T2[(state[2] >> 8) & cls.mask]
        temp[0] ^= cls.T3[(state[3] >> 12) & cls.mask]

        temp[1] = cls.T0[(state[1] >> 0) & cls.mask]
        temp[1] ^= cls.T1[(state[2] >> 4) & cls.mask]
        temp[1] ^= cls.T2[(state[3] >> 8) & cls.mask]
        temp[1] ^= cls.T3[(state[0] >> 12) & cls.mask]

        temp[2] = cls.T0[(state[2] >> 0) & cls.mask]
        temp[2] ^= cls.T1[(state[3] >> 4) & cls.mask]
        temp[2] ^= cls.T2[(state[0] >> 8) & cls.mask]
        temp[2] ^= cls.T3[(state[1] >> 12) & cls.mask]

        temp[3] = cls.T0[(state[3] >> 0) & cls.mask]
        temp[3] ^= cls.T1[(state[0] >> 4) & cls.mask]
        temp[3] ^= cls.T2[(state[1] >> 8) & cls.mask]
        temp[3] ^= cls.T3[(state[2] >> 12) & cls.mask]

        for i in range(0,4,1):
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
            cls.Step(state, i + 1)
        cls.AddKey(state, sk0)
        return

    @classmethod
    def Encrypt(cls, plainText, key):
        cipherText = [None] * len(plainText)
        sk0 = cls.byte2uint16(key, 0)
        sk2 = [None] * 8
        for i in range(0, 8, 1):
            sk2[i] = key[(8 + i) % 10]
        sk1 = cls.byte2uint16(sk2, 0)
        for i in range(0, len(plainText), 8):
            state = cls.byte2uint16(plainText, i)
            cls.EncryptOneBlock(state, sk0, sk1)
            cls.uint162byteCopy(state, cipherText, i)
        return cipherText


















    

















    
