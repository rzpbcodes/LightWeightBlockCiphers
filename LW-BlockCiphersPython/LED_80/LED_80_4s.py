class LED_80_4s:
    keySize = 80
    sBox = [0x0C, 0x05, 0x06, 0x0B, 0x09, 0x00, 0x0A, 0x0D, 0x03, 0x0E, 0x0F, 0x08, 0x04, 0x07, 0x01, 0x02]
    RC = [0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3E, 0x3D, 0x3B, 0x37, 0x2F,
          0x1E, 0x3C, 0x39, 0x33, 0x27, 0x0E, 0x1D, 0x3A, 0x35, 0x2B,
          0x16, 0x2C, 0x18, 0x30, 0x21, 0x02, 0x05, 0x0B, 0x17, 0x2E,
          0x1C, 0x38, 0x31, 0x23, 0x06, 0x0D, 0x1B, 0x36, 0x2D, 0x1A,
          0x34, 0x29, 0x12, 0x24, 0x08, 0x11, 0x22, 0x04]
    nibbleFilter = 0x0F
    ReductionPoly = 0x3

    @classmethod
    def byte2nibble(cls, byteArr, offSet):
        b = [None]*16
        for i in range(0,8,1):
            b[i * 2 + 0] = byteArr[offSet + i] & 0x0F
            b[i * 2 + 1] = (byteArr[offSet + i] >> 4) & 0x0F
        return b

    @classmethod
    def nibbles2byte(cls, nibbles):
        c = [None]*8
        for i in range(0,8,1):
            c[i] = (nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4))
        return c

    @classmethod
    def nibbles2byteCopy(cls, nibbles, byteArr, offSet):
        for i in range(0,8,1):
            byteArr[i] = (nibbles[i * 2 + 0] ^ (nibbles[i * 2 + 1] << 4))
        return

    @classmethod
    def xTimes(cls, a):
        a <<= 1
        if ((a & 0x10) == 0x10):
            a ^= cls.ReductionPoly
        return (a & cls.nibbleFilter)

    @classmethod
    def x2Times(cls, a):
        a <<= 1
        if ((a & 0x10) == 0x10):
            a ^= cls.ReductionPoly
        a <<= 1
        if ((a & 0x10) == 0x10):
            a ^= cls.ReductionPoly
        return (a & cls.nibbleFilter)

    @classmethod
    def AddKey(cl, state, roundKey):
        for i in range(0,16,1):
            state[i] ^= roundKey[i]
        return

    @classmethod
    def AddConstants(cls, state, round):
        state[0] ^= (cls.keySize >> 4)
        state[4] ^= (0x01 ^ (cls.keySize >> 4))
        state[8] ^= (0x02 ^ (cls.keySize & 0x0F))
        state[12] ^= (0x03 ^ (cls.keySize & 0x0F))

        temp = (cls.RC[round] >> 3 & 0x07)
        state[1] ^= temp
        state[9] ^= temp

        temp = (cls.RC[round] & 0x07)
        state[5] ^= temp
        state[13] ^= temp
        return

    @classmethod
    def SboxShiftRows(cls, state):
        temp = [None]*16
        temp[0] = cls.sBox[state[0]]; temp[1] = cls.sBox[state[1]]; temp[2] = cls.sBox[state[2]]; temp[3] = cls.sBox[state[3]]
        temp[4] = cls.sBox[state[5]]; temp[5] = cls.sBox[state[6]];temp[6] = cls.sBox[state[7]];temp[7] = cls.sBox[state[4]]
        temp[8] = cls.sBox[state[10]]; temp[9] = cls.sBox[state[11]];temp[10] = cls.sBox[state[8]];temp[11] = cls.sBox[state[9]]
        temp[12] = cls.sBox[state[15]]; temp[13] = cls.sBox[state[12]];temp[14] = cls.sBox[state[13]];temp[15] = cls.sBox[state[14]]

        for i in range(0,16,1):
            state[i] = temp[i]
        return

    @classmethod
    def MultiplyColumn(cls, temp):
        temp[0] = (cls.x2Times(temp[0]) ^ temp[1] ^ cls.xTimes(temp[2]) ^ cls.xTimes(temp[3]))
        temp[1] = (cls.x2Times(temp[1]) ^ temp[2] ^ cls.xTimes(temp[3]) ^ cls.xTimes(temp[0]))
        temp[2] = (cls.x2Times(temp[2]) ^ temp[3] ^ cls.xTimes(temp[0]) ^ cls.xTimes(temp[1]))
        temp[3] = (cls.x2Times(temp[3]) ^ temp[0] ^ cls.xTimes(temp[1]) ^ cls.xTimes(temp[2]))
        return

    @classmethod
    def MixColumns(cls, state):
        for r in range(0,4,1):
            temp = [None]*4
            for c in range(0,4,1):
                temp[c] = state[4*c+r]
            cls.MultiplyColumn(temp)
            for c in range(0,4,1):
                state[4*c+r] = temp[c]
        return

    @classmethod
    def Step(cls, state, step):
        for i in range(0,4,1):
            cls.AddConstants(state, (step * 4 + i))
            cls.SboxShiftRows(state)
            cls.MixColumns(state)
        return

    @classmethod
    def EncryptOneBlock(cls, state, sk0, sk1):
        for i in range(0,12,2):
            cls.AddKey(state, sk0)
            cls.Step(state, i)
            cls.AddKey(state, sk1)
            cls.Step(state, i+1)
        cls.AddKey(state, sk0)
        return

    @classmethod
    def Encrypt(cls, plainText, key):
        cipherText = [None]*len(plainText)
        sk0 = cls.byte2nibble(key, 0)
        sk2 = [None]*8
        for i in range(0,8,1):
            sk2[i] = key[(8 + i) % 10]
        sk1 = cls.byte2nibble(sk2, 0)
        for i in range(0,len(plainText),8):
            state = cls.byte2nibble(plainText,i)
            cls.EncryptOneBlock(state, sk0, sk1)
            cls.nibbles2byteCopy(state, cipherText, i)
        return cipherText
    
        
        









    



    
        
