﻿using System;
using System.Collections.Generic;

using System.Text;

namespace LW_BlockCiphersCSharp
{
    class LED_80_32
    {
        static byte keySize = 80;
        static uint keySizeConst = 0x03020405;
        static uint[] RCandKeySizeConst = new uint[] {
            0x13021405, 0x33023405, 0x73027405, 0x73127415, 0x73327435, 0x63726475, 0x53725475, 0x33723475, 0x73627465, 0x73527455,
            0x63326435, 0x43724475, 0x13721475, 0x33623465, 0x73427445, 0x63126415, 0x53325435, 0x23722475, 0x53625465, 0x33523455,
            0x63226425, 0x43524455, 0x03320435, 0x03620465, 0x13421445, 0x23022405, 0x53025405, 0x33123415, 0x73227425, 0x63526455, 
            0x43324435, 0x03720475, 0x13621465, 0x33423445, 0x63026405, 0x53125415, 0x33323435, 0x63626465, 0x53525455, 0x23322435,
            0x43624465, 0x13521455, 0x23222425, 0x43424445, 0x03120415, 0x13221425, 0x23422445, 0x43024405 };

        static uint mask = 0x000000FF;

        static uint[] T0 = new uint[] { 0xBBDDAA55, 0xBAD1AE57, 0xBCDFA55B, 0xB5D9A75A, 0xB1DCA452, 0xB0D0A050, 0xB7D2AF5E, 0xB9D6A251, 0xB6DEAB5C, 0xBFD8A95D, 0xBDD3A159, 0xB3D7AC56, 0xB8DAA653, 0xBED4AD5F, 0xB2DBA854, 0xB4D5A358, 0xAB1DEA75, 0xAA11EE77, 0xAC1FE57B, 0xA519E77A, 0xA11CE472, 0xA010E070, 0xA712EF7E, 0xA916E271, 0xA61EEB7C, 0xAF18E97D, 0xAD13E179, 0xA317EC76, 0xA81AE673, 0xAE14ED7F, 0xA21BE874, 0xA415E378, 0xCBFD5AB5, 0xCAF15EB7, 0xCCFF55BB, 0xC5F957BA, 0xC1FC54B2, 0xC0F050B0, 0xC7F25FBE, 0xC9F652B1, 0xC6FE5BBC, 0xCFF859BD, 0xCDF351B9, 0xC3F75CB6, 0xC8FA56B3, 0xCEF45DBF, 0xC2FB58B4, 0xC4F553B8, 0x5B9D7AA5, 0x5A917EA7, 0x5C9F75AB, 0x559977AA, 0x519C74A2, 0x509070A0, 0x57927FAE, 0x599672A1, 0x569E7BAC, 0x5F9879AD, 0x5D9371A9, 0x53977CA6, 0x589A76A3, 0x5E947DAF, 0x529B78A4, 0x549573A8, 0x1BCD4A25, 0x1AC14E27, 0x1CCF452B, 0x15C9472A, 0x11CC4422, 0x10C04020, 0x17C24F2E, 0x19C64221, 0x16CE4B2C, 0x1FC8492D, 0x1DC34129, 0x13C74C26, 0x18CA4623, 0x1EC44D2F, 0x12CB4824, 0x14C54328, 0x0B0D0A05, 0x0A010E07, 0x0C0F050B, 0x0509070A, 0x010C0402, 0x00000000, 0x07020F0E, 0x09060201, 0x060E0B0C, 0x0F08090D, 0x0D030109, 0x03070C06, 0x080A0603, 0x0E040D0F, 0x020B0804, 0x04050308, 0x7B2DFAE5, 0x7A21FEE7, 0x7C2FF5EB, 0x7529F7EA, 0x712CF4E2, 0x7020F0E0, 0x7722FFEE, 0x7926F2E1, 0x762EFBEC, 0x7F28F9ED, 0x7D23F1E9, 0x7327FCE6, 0x782AF6E3, 0x7E24FDEF, 0x722BF8E4, 0x7425F3E8, 0x9B6D2A15, 0x9A612E17, 0x9C6F251B, 0x9569271A, 0x916C2412, 0x90602010, 0x97622F1E, 0x99662211, 0x966E2B1C, 0x9F68291D, 0x9D632119, 0x93672C16, 0x986A2613, 0x9E642D1F, 0x926B2814, 0x94652318, 0x6BEDBAC5, 0x6AE1BEC7, 0x6CEFB5CB, 0x65E9B7CA, 0x61ECB4C2, 0x60E0B0C0, 0x67E2BFCE, 0x69E6B2C1, 0x66EEBBCC, 0x6FE8B9CD, 0x6DE3B1C9, 0x63E7BCC6, 0x68EAB6C3, 0x6EE4BDCF, 0x62EBB8C4, 0x64E5B3C8, 0xFB8D9AD5, 0xFA819ED7, 0xFC8F95DB, 0xF58997DA, 0xF18C94D2, 0xF08090D0, 0xF7829FDE, 0xF98692D1, 0xF68E9BDC, 0xFF8899DD, 0xFD8391D9, 0xF3879CD6, 0xF88A96D3, 0xFE849DDF, 0xF28B98D4, 0xF48593D8, 0xDB3D1A95, 0xDA311E97, 0xDC3F159B, 0xD539179A, 0xD13C1492, 0xD0301090, 0xD7321F9E, 0xD9361291, 0xD63E1B9C, 0xDF38199D, 0xDD331199, 0xD3371C96, 0xD83A1693, 0xDE341D9F, 0xD23B1894, 0xD4351398, 0x3B7DCA65, 0x3A71CE67, 0x3C7FC56B, 0x3579C76A, 0x317CC462, 0x3070C060, 0x3772CF6E, 0x3976C261, 0x367ECB6C, 0x3F78C96D, 0x3D73C169, 0x3377CC66, 0x387AC663, 0x3E74CD6F, 0x327BC864, 0x3475C368, 0x8BAD6A35, 0x8AA16E37, 0x8CAF653B, 0x85A9673A, 0x81AC6432, 0x80A06030, 0x87A26F3E, 0x89A66231, 0x86AE6B3C, 0x8FA8693D, 0x8DA36139, 0x83A76C36, 0x88AA6633, 0x8EA46D3F, 0x82AB6834, 0x84A56338, 0xEB4DDAF5, 0xEA41DEF7, 0xEC4FD5FB, 0xE549D7FA, 0xE14CD4F2, 0xE040D0F0, 0xE742DFFE, 0xE946D2F1, 0xE64EDBFC, 0xEF48D9FD, 0xED43D1F9, 0xE347DCF6, 0xE84AD6F3, 0xEE44DDFF, 0xE24BD8F4, 0xE445D3F8, 0x2BBD8A45, 0x2AB18E47, 0x2CBF854B, 0x25B9874A, 0x21BC8442, 0x20B08040, 0x27B28F4E, 0x29B68241, 0x26BE8B4C, 0x2FB8894D, 0x2DB38149, 0x23B78C46, 0x28BA8643, 0x2EB48D4F, 0x22BB8844, 0x24B58348, 0x4B5D3A85, 0x4A513E87, 0x4C5F358B, 0x4559378A, 0x415C3482, 0x40503080, 0x47523F8E, 0x49563281, 0x465E3B8C, 0x4F58398D, 0x4D533189, 0x43573C86, 0x485A3683, 0x4E543D8F, 0x425B3884, 0x44553388 };
        static uint[] T1 = new uint[] { 0xBB44EECC, 0xBA43EDC5, 0xBC42E7C6, 0xB548EFCB, 0xB147E3C9, 0xB040E0C0, 0xB746E9CA, 0xB94AE8CD, 0xB641EAC3, 0xBF4BE2CE, 0xBD45E4CF, 0xB349E5C8, 0xB84DEBC4, 0xBE4CE1C7, 0xB24EE6C1, 0xB44FECC2, 0xAB34DE5C, 0xAA33DD55, 0xAC32D756, 0xA538DF5B, 0xA137D359, 0xA030D050, 0xA736D95A, 0xA93AD85D, 0xA631DA53, 0xAF3BD25E, 0xAD35D45F, 0xA339D558, 0xA83DDB54, 0xAE3CD157, 0xA23ED651, 0xA43FDC52, 0xCB247E6C, 0xCA237D65, 0xCC227766, 0xC5287F6B, 0xC1277369, 0xC0207060, 0xC726796A, 0xC92A786D, 0xC6217A63, 0xCF2B726E, 0xCD25746F, 0xC3297568, 0xC82D7B64, 0xCE2C7167, 0xC22E7661, 0xC42F7C62, 0x5B84FEBC, 0x5A83FDB5, 0x5C82F7B6, 0x5588FFBB, 0x5187F3B9, 0x5080F0B0, 0x5786F9BA, 0x598AF8BD, 0x5681FAB3, 0x5F8BF2BE, 0x5D85F4BF, 0x5389F5B8, 0x588DFBB4, 0x5E8CF1B7, 0x528EF6B1, 0x548FFCB2, 0x1B743E9C, 0x1A733D95, 0x1C723796, 0x15783F9B, 0x11773399, 0x10703090, 0x1776399A, 0x197A389D, 0x16713A93, 0x1F7B329E, 0x1D75349F, 0x13793598, 0x187D3B94, 0x1E7C3197, 0x127E3691, 0x147F3C92, 0x0B040E0C, 0x0A030D05, 0x0C020706, 0x05080F0B, 0x01070309, 0x00000000, 0x0706090A, 0x090A080D, 0x06010A03, 0x0F0B020E, 0x0D05040F, 0x03090508, 0x080D0B04, 0x0E0C0107, 0x020E0601, 0x040F0C02, 0x7B649EAC, 0x7A639DA5, 0x7C6297A6, 0x75689FAB, 0x716793A9, 0x706090A0, 0x776699AA, 0x796A98AD, 0x76619AA3, 0x7F6B92AE, 0x7D6594AF, 0x736995A8, 0x786D9BA4, 0x7E6C91A7, 0x726E96A1, 0x746F9CA2, 0x9BA48EDC, 0x9AA38DD5, 0x9CA287D6, 0x95A88FDB, 0x91A783D9, 0x90A080D0, 0x97A689DA, 0x99AA88DD, 0x96A18AD3, 0x9FAB82DE, 0x9DA584DF, 0x93A985D8, 0x98AD8BD4, 0x9EAC81D7, 0x92AE86D1, 0x94AF8CD2, 0x6B14AE3C, 0x6A13AD35, 0x6C12A736, 0x6518AF3B, 0x6117A339, 0x6010A030, 0x6716A93A, 0x691AA83D, 0x6611AA33, 0x6F1BA23E, 0x6D15A43F, 0x6319A538, 0x681DAB34, 0x6E1CA137, 0x621EA631, 0x641FAC32, 0xFBB42EEC, 0xFAB32DE5, 0xFCB227E6, 0xF5B82FEB, 0xF1B723E9, 0xF0B020E0, 0xF7B629EA, 0xF9BA28ED, 0xF6B12AE3, 0xFFBB22EE, 0xFDB524EF, 0xF3B925E8, 0xF8BD2BE4, 0xFEBC21E7, 0xF2BE26E1, 0xF4BF2CE2, 0xDB544EFC, 0xDA534DF5, 0xDC5247F6, 0xD5584FFB, 0xD15743F9, 0xD05040F0, 0xD75649FA, 0xD95A48FD, 0xD6514AF3, 0xDF5B42FE, 0xDD5544FF, 0xD35945F8, 0xD85D4BF4, 0xDE5C41F7, 0xD25E46F1, 0xD45F4CF2, 0x3B945E8C, 0x3A935D85, 0x3C925786, 0x35985F8B, 0x31975389, 0x30905080, 0x3796598A, 0x399A588D, 0x36915A83, 0x3F9B528E, 0x3D95548F, 0x33995588, 0x389D5B84, 0x3E9C5187, 0x329E5681, 0x349F5C82, 0x8BD4BE4C, 0x8AD3BD45, 0x8CD2B746, 0x85D8BF4B, 0x81D7B349, 0x80D0B040, 0x87D6B94A, 0x89DAB84D, 0x86D1BA43, 0x8FDBB24E, 0x8DD5B44F, 0x83D9B548, 0x88DDBB44, 0x8EDCB147, 0x82DEB641, 0x84DFBC42, 0xEBC41E7C, 0xEAC31D75, 0xECC21776, 0xE5C81F7B, 0xE1C71379, 0xE0C01070, 0xE7C6197A, 0xE9CA187D, 0xE6C11A73, 0xEFCB127E, 0xEDC5147F, 0xE3C91578, 0xE8CD1B74, 0xEECC1177, 0xE2CE1671, 0xE4CF1C72, 0x2BE46E1C, 0x2AE36D15, 0x2CE26716, 0x25E86F1B, 0x21E76319, 0x20E06010, 0x27E6691A, 0x29EA681D, 0x26E16A13, 0x2FEB621E, 0x2DE5641F, 0x23E96518, 0x28ED6B14, 0x2EEC6117, 0x22EE6611, 0x24EF6C12, 0x4BF4CE2C, 0x4AF3CD25, 0x4CF2C726, 0x45F8CF2B, 0x41F7C329, 0x40F0C020, 0x47F6C92A, 0x49FAC82D, 0x46F1CA23, 0x4FFBC22E, 0x4DF5C42F, 0x43F9C528, 0x48FDCB24, 0x4EFCC127, 0x42FEC621, 0x44FFCC22 };
        static uint[] T2 = new uint[] { 0x881199BB, 0x861492BA, 0x84199DBC, 0x831291B5, 0x8E159BB1, 0x801090B0, 0x8C1894B7, 0x871B9CB9, 0x821D9FB6, 0x851693BF, 0x8A1C96BD, 0x811F9EB3, 0x891E97B8, 0x8B1398BE, 0x8F1A95B2, 0x8D179AB4, 0x684129AB, 0x664422AA, 0x64492DAC, 0x634221A5, 0x6E452BA1, 0x604020A0, 0x6C4824A7, 0x674B2CA9, 0x624D2FA6, 0x654623AF, 0x6A4C26AD, 0x614F2EA3, 0x694E27A8, 0x6B4328AE, 0x6F4A25A2, 0x6D472AA4, 0x4891D9CB, 0x4694D2CA, 0x4499DDCC, 0x4392D1C5, 0x4E95DBC1, 0x4090D0C0, 0x4C98D4C7, 0x479BDCC9, 0x429DDFC6, 0x4596D3CF, 0x4A9CD6CD, 0x419FDEC3, 0x499ED7C8, 0x4B93D8CE, 0x4F9AD5C2, 0x4D97DAC4, 0x3821195B, 0x3624125A, 0x34291D5C, 0x33221155, 0x3E251B51, 0x30201050, 0x3C281457, 0x372B1C59, 0x322D1F56, 0x3526135F, 0x3A2C165D, 0x312F1E53, 0x392E1758, 0x3B23185E, 0x3F2A1552, 0x3D271A54, 0xE851B91B, 0xE654B21A, 0xE459BD1C, 0xE352B115, 0xEE55BB11, 0xE050B010, 0xEC58B417, 0xE75BBC19, 0xE25DBF16, 0xE556B31F, 0xEA5CB61D, 0xE15FBE13, 0xE95EB718, 0xEB53B81E, 0xEF5AB512, 0xED57BA14, 0x0801090B, 0x0604020A, 0x04090D0C, 0x03020105, 0x0E050B01, 0x00000000, 0x0C080407, 0x070B0C09, 0x020D0F06, 0x0506030F, 0x0A0C060D, 0x010F0E03, 0x090E0708, 0x0B03080E, 0x0F0A0502, 0x0D070A04, 0xC881497B, 0xC684427A, 0xC4894D7C, 0xC3824175, 0xCE854B71, 0xC0804070, 0xCC884477, 0xC78B4C79, 0xC28D4F76, 0xC586437F, 0xCA8C467D, 0xC18F4E73, 0xC98E4778, 0xCB83487E, 0xCF8A4572, 0xCD874A74, 0x78B1C99B, 0x76B4C29A, 0x74B9CD9C, 0x73B2C195, 0x7EB5CB91, 0x70B0C090, 0x7CB8C497, 0x77BBCC99, 0x72BDCF96, 0x75B6C39F, 0x7ABCC69D, 0x71BFCE93, 0x79BEC798, 0x7BB3C89E, 0x7FBAC592, 0x7DB7CA94, 0x28D1F96B, 0x26D4F26A, 0x24D9FD6C, 0x23D2F165, 0x2ED5FB61, 0x20D0F060, 0x2CD8F467, 0x27DBFC69, 0x22DDFF66, 0x25D6F36F, 0x2ADCF66D, 0x21DFFE63, 0x29DEF768, 0x2BD3F86E, 0x2FDAF562, 0x2DD7FA64, 0x586139FB, 0x566432FA, 0x54693DFC, 0x536231F5, 0x5E653BF1, 0x506030F0, 0x5C6834F7, 0x576B3CF9, 0x526D3FF6, 0x556633FF, 0x5A6C36FD, 0x516F3EF3, 0x596E37F8, 0x5B6338FE, 0x5F6A35F2, 0x5D673AF4, 0xA8C169DB, 0xA6C462DA, 0xA4C96DDC, 0xA3C261D5, 0xAEC56BD1, 0xA0C060D0, 0xACC864D7, 0xA7CB6CD9, 0xA2CD6FD6, 0xA5C663DF, 0xAACC66DD, 0xA1CF6ED3, 0xA9CE67D8, 0xABC368DE, 0xAFCA65D2, 0xADC76AD4, 0x18F1E93B, 0x16F4E23A, 0x14F9ED3C, 0x13F2E135, 0x1EF5EB31, 0x10F0E030, 0x1CF8E437, 0x17FBEC39, 0x12FDEF36, 0x15F6E33F, 0x1AFCE63D, 0x11FFEE33, 0x19FEE738, 0x1BF3E83E, 0x1FFAE532, 0x1DF7EA34, 0x98E1798B, 0x96E4728A, 0x94E97D8C, 0x93E27185, 0x9EE57B81, 0x90E07080, 0x9CE87487, 0x97EB7C89, 0x92ED7F86, 0x95E6738F, 0x9AEC768D, 0x91EF7E83, 0x99EE7788, 0x9BE3788E, 0x9FEA7582, 0x9DE77A84, 0xB83189EB, 0xB63482EA, 0xB4398DEC, 0xB33281E5, 0xBE358BE1, 0xB03080E0, 0xBC3884E7, 0xB73B8CE9, 0xB23D8FE6, 0xB53683EF, 0xBA3C86ED, 0xB13F8EE3, 0xB93E87E8, 0xBB3388EE, 0xBF3A85E2, 0xBD378AE4, 0xF8A1592B, 0xF6A4522A, 0xF4A95D2C, 0xF3A25125, 0xFEA55B21, 0xF0A05020, 0xFCA85427, 0xF7AB5C29, 0xF2AD5F26, 0xF5A6532F, 0xFAAC562D, 0xF1AF5E23, 0xF9AE5728, 0xFBA3582E, 0xFFAA5522, 0xFDA75A24, 0xD871A94B, 0xD674A24A, 0xD479AD4C, 0xD372A145, 0xDE75AB41, 0xD070A040, 0xDC78A447, 0xD77BAC49, 0xD27DAF46, 0xD576A34F, 0xDA7CA64D, 0xD17FAE43, 0xD97EA748, 0xDB73A84E, 0xDF7AA542, 0xDD77AA44 };
        static uint[] T3 = new uint[] { 0xDD66EEBB, 0xD16BEDBA, 0xDF63E7BC, 0xD96CEFB5, 0xDC6DE3B1, 0xD060E0B0, 0xD265E9B7, 0xD66FE8B9, 0xDE68EAB6, 0xD867E2BF, 0xD36EE4BD, 0xD764E5B3, 0xDA62EBB8, 0xD46AE1BE, 0xDB69E6B2, 0xD561ECB4, 0x1DB6DEAB, 0x11BBDDAA, 0x1FB3D7AC, 0x19BCDFA5, 0x1CBDD3A1, 0x10B0D0A0, 0x12B5D9A7, 0x16BFD8A9, 0x1EB8DAA6, 0x18B7D2AF, 0x13BED4AD, 0x17B4D5A3, 0x1AB2DBA8, 0x14BAD1AE, 0x1BB9D6A2, 0x15B1DCA4, 0xFD367ECB, 0xF13B7DCA, 0xFF3377CC, 0xF93C7FC5, 0xFC3D73C1, 0xF03070C0, 0xF23579C7, 0xF63F78C9, 0xFE387AC6, 0xF83772CF, 0xF33E74CD, 0xF73475C3, 0xFA327BC8, 0xF43A71CE, 0xFB3976C2, 0xF5317CC4, 0x9DC6FE5B, 0x91CBFD5A, 0x9FC3F75C, 0x99CCFF55, 0x9CCDF351, 0x90C0F050, 0x92C5F957, 0x96CFF859, 0x9EC8FA56, 0x98C7F25F, 0x93CEF45D, 0x97C4F553, 0x9AC2FB58, 0x94CAF15E, 0x9BC9F652, 0x95C1FC54, 0xCDD63E1B, 0xC1DB3D1A, 0xCFD3371C, 0xC9DC3F15, 0xCCDD3311, 0xC0D03010, 0xC2D53917, 0xC6DF3819, 0xCED83A16, 0xC8D7321F, 0xC3DE341D, 0xC7D43513, 0xCAD23B18, 0xC4DA311E, 0xCBD93612, 0xC5D13C14, 0x0D060E0B, 0x010B0D0A, 0x0F03070C, 0x090C0F05, 0x0C0D0301, 0x00000000, 0x02050907, 0x060F0809, 0x0E080A06, 0x0807020F, 0x030E040D, 0x07040503, 0x0A020B08, 0x040A010E, 0x0B090602, 0x05010C04, 0x2D569E7B, 0x215B9D7A, 0x2F53977C, 0x295C9F75, 0x2C5D9371, 0x20509070, 0x22559977, 0x265F9879, 0x2E589A76, 0x2857927F, 0x235E947D, 0x27549573, 0x2A529B78, 0x245A917E, 0x2B599672, 0x25519C74, 0x6DF68E9B, 0x61FB8D9A, 0x6FF3879C, 0x69FC8F95, 0x6CFD8391, 0x60F08090, 0x62F58997, 0x66FF8899, 0x6EF88A96, 0x68F7829F, 0x63FE849D, 0x67F48593, 0x6AF28B98, 0x64FA819E, 0x6BF98692, 0x65F18C94, 0xED86AE6B, 0xE18BAD6A, 0xEF83A76C, 0xE98CAF65, 0xEC8DA361, 0xE080A060, 0xE285A967, 0xE68FA869, 0xEE88AA66, 0xE887A26F, 0xE38EA46D, 0xE784A563, 0xEA82AB68, 0xE48AA16E, 0xEB89A662, 0xE581AC64, 0x8D762EFB, 0x817B2DFA, 0x8F7327FC, 0x897C2FF5, 0x8C7D23F1, 0x807020F0, 0x827529F7, 0x867F28F9, 0x8E782AF6, 0x887722FF, 0x837E24FD, 0x877425F3, 0x8A722BF8, 0x847A21FE, 0x8B7926F2, 0x85712CF4, 0x3DE64EDB, 0x31EB4DDA, 0x3FE347DC, 0x39EC4FD5, 0x3CED43D1, 0x30E040D0, 0x32E549D7, 0x36EF48D9, 0x3EE84AD6, 0x38E742DF, 0x33EE44DD, 0x37E445D3, 0x3AE24BD8, 0x34EA41DE, 0x3BE946D2, 0x35E14CD4, 0x7D465E3B, 0x714B5D3A, 0x7F43573C, 0x794C5F35, 0x7C4D5331, 0x70405030, 0x72455937, 0x764F5839, 0x7E485A36, 0x7847523F, 0x734E543D, 0x77445533, 0x7A425B38, 0x744A513E, 0x7B495632, 0x75415C34, 0xAD26BE8B, 0xA12BBD8A, 0xAF23B78C, 0xA92CBF85, 0xAC2DB381, 0xA020B080, 0xA225B987, 0xA62FB889, 0xAE28BA86, 0xA827B28F, 0xA32EB48D, 0xA724B583, 0xAA22BB88, 0xA42AB18E, 0xAB29B682, 0xA521BC84, 0x4DA61EEB, 0x41AB1DEA, 0x4FA317EC, 0x49AC1FE5, 0x4CAD13E1, 0x40A010E0, 0x42A519E7, 0x46AF18E9, 0x4EA81AE6, 0x48A712EF, 0x43AE14ED, 0x47A415E3, 0x4AA21BE8, 0x44AA11EE, 0x4BA916E2, 0x45A11CE4, 0xBD966E2B, 0xB19B6D2A, 0xBF93672C, 0xB99C6F25, 0xBC9D6321, 0xB0906020, 0xB2956927, 0xB69F6829, 0xBE986A26, 0xB897622F, 0xB39E642D, 0xB7946523, 0xBA926B28, 0xB49A612E, 0xBB996622, 0xB5916C24, 0x5D16CE4B, 0x511BCD4A, 0x5F13C74C, 0x591CCF45, 0x5C1DC341, 0x5010C040, 0x5215C947, 0x561FC849, 0x5E18CA46, 0x5817C24F, 0x531EC44D, 0x5714C543, 0x5A12CB48, 0x541AC14E, 0x5B19C642, 0x5511CC44 };

        static uint[] byte2uintArr(byte[] b, int offSet)
        {
            uint[] x = new uint[2];

            x[0] ^= b[offSet + 6]; x[0] <<= 8;
            x[0] ^= b[offSet + 4]; x[0] <<= 8;
            x[0] ^= b[offSet + 2]; x[0] <<= 8;
            x[0] ^= b[offSet + 0];

            x[1] ^= b[offSet + 7]; x[1] <<= 8;
            x[1] ^= b[offSet + 5]; x[1] <<= 8;
            x[1] ^= b[offSet + 3]; x[1] <<= 8;
            x[1] ^= b[offSet + 1];

            return x;
        }

        static void uintArr2byte(uint[] x, byte[] b, int offSet)
        {
            b[offSet + 0] = (byte)(x[0] & 0xFF);
            b[offSet + 2] = (byte)(x[0] >> 8 & 0xFF);
            b[offSet + 4] = (byte)(x[0] >> 16 & 0xFF);
            b[offSet + 6] = (byte)(x[0] >> 24 & 0xFF);

            b[offSet + 1] = (byte)(x[1] & 0xFF);
            b[offSet + 3] = (byte)(x[1] >> 8 & 0xFF);
            b[offSet + 5] = (byte)(x[1] >> 16 & 0xFF);
            b[offSet + 7] = (byte)(x[1] >> 24 & 0xFF);
        }

        static void AddKey(ref uint[] state, uint[] roundKey)
        {
            state[0] ^= roundKey[0];
            state[1] ^= roundKey[1];
        }

        static void AddConstants(ref uint[] state, int round)
        {
            state[0] ^= RCandKeySizeConst[round];
        }

        static void SubCellShiftRowAndMixColumns(ref uint[] state)
        {
            uint[] temp = new uint[2];
            byte b2, b3, b6, b7;

            b2 = (byte)(((state[0] >> 12) & 0xF) ^ ((state[1] >> 4) & 0xF0));
            b6 = (byte)(((state[0] >> 20) & 0xF0) ^ ((state[1] >> 28) & 0xF));

            b3 = (byte)(((state[1] >> 12) & 0xF) ^ ((state[0] >> 4) & 0xF0));
            b7 = (byte)(((state[1] >> 20) & 0xF0) ^ ((state[0] >> 28) & 0xF));

            temp[0] = T0[state[0] & mask];
            temp[0] ^= T1[b2];
            temp[0] ^= T2[(state[1] >> 16) & mask];
            temp[0] ^= T3[b6];

            temp[1] = T0[state[1] & mask];
            temp[1] ^= T1[b3];
            temp[1] ^= T2[(state[0] >> 16) & mask];
            temp[1] ^= T3[b7];

            state = temp;
        }

        static void Step(ref uint[] state, int step)
        {
            for (int i = 0; i < 4; i++)
            {
                AddConstants(ref state, (step * 4 + i));
                SubCellShiftRowAndMixColumns(ref state);
            }
        }

        static void EncryptOneBlock(ref uint[] state, uint[] sk0, uint[] sk1)
        {
            for (int i = 0; i < 12; i += 2)
            {
                AddKey(ref state, sk0);
                Step(ref state, i);
                AddKey(ref state, sk1);
                Step(ref state, i + 1);
            }
            AddKey(ref state, sk0);
        }

        public static byte[] Encrypt(byte[] input, byte[] key)
        {
            byte[] cipherText = new byte[input.Length];

            uint[] sk0 = byte2uintArr(key, 0);

            byte[] sk2 = new byte[8];
            for (int i = 0; i < 8; i++)
                sk2[i] = key[(8 + i) % 10];

            uint[] sk1 = byte2uintArr(sk2, 0);

            for (int i = 0; i < input.Length; i += 8)
            {
                uint[] state = byte2uintArr(input, i);

                EncryptOneBlock(ref state, sk0, sk1);

                uintArr2byte(state, cipherText, i);
            }

            return cipherText;
        }
    }
}