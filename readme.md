# Flipper enclave manager

A simple tool to manage keys in "security enclave" on flipper zero.

**PLEASE DO NOT TRY THIS ON A ORIGINAL FLIPPER ZERO. THIS CAN REPLACE ALL KEYS IN YOUR SECURITY ENCLAVE AND BREAK YOUR U2F FUNCTION.**

## How to use

If you would like to clear the "Enclave broken" message on startup, you will need a special firmware with keys in it.

If you want to have your own key(for privacy, you should), you will need the tool in utils folder.

To use the U2F function, replace the U2F cert in whose assests folder with the cert&.u2f file in the cert folder.

Discover more on https://www.lapiw.icu/flipper_zero_cks_u2f

## Current keys

```
Master key:
190677ACC8C903AFD9181A536E3BF2CFA755AA0953FE8021934F9183EC9A2224

Encrypted keys (unencrypted):
['F8A748AE6FE6D49D94BA5B286926623474A7DD91C0AF199C09AFFE784F4F7718', 
'678B83A36441A73DD1116A290FBEB886F28D3E49CDDBD4BC27AE87969A52F577', 
'F25EF9C77FE563A5FADE961D033C3A8D3463D66BDF0950B28A809068822A1C93', 
'D89A2C79024D6CC1BC48ED89AA04CF9FE542466C053DC22FC7B1E7C8790A305C', 
'5D033315BD78B5B5131FE5CC34D1F4505F90D21B6BF832A535F4ABC52092B553', 
'A12BED81C65D78ADE1BEEF7ED7AB5A73CA719AD342C67D164EEE5EC5916AE072', 
'DA2E59AC3DA3B8FB385783D80E20211BED35A342EC49282FC39697B20DF39FC6', 
'85855BDBF4474CB54A4816B52480A24AB2263245B85AEF363D40FEE540B5A614', 
'F3C454BBD1D8CBCF75490DD90F51380C5454902D1D59B84880C6C28672F5D53D', 
'B24C7753B7CE72734E3669F5F34865A1F8467B47DA030232C11D90E8FCBC9ED4']

Encrypted keys:
['3F9AE3871D217F2F4068743BBD06B8F0C3B186FF69D2D8F1410A44F87D0680A2', 
'AC186171386CC774E443BC96F0C08782F5E956F54E67E6D86075C341B96C3D91', 
'915B18EBD81139F6AC084FFD70DB44A0DBDFAD0301719D4080638D0A6B9DAE7E', 
'1DBE7E41D0B233419CECB98CFB6DF1CCE3243EF09DA5D4388CEFD67ED76D2783', 
'42328E22FBDEAF675F5A917CE70FDE0345E74CDA13FBBD8F4F26ADD761E475C7', 
'4B94199B7816B73DB744520ECB1B26E6BB317B478F76524785D66F18813587D9', 
'4B1F732A9D76A61C2080452A1226792668C1134B22794D6C890A3515CE502E6E', 
'FFB0052D21F5279DC3FF384DB9870782153786639EA357559646BCBAEE597DA1', 
'15DE6DE8ABBA53778A43D7EB2D364CF621D7AC0BF1327526320EDF254B593D9D', 
'53363569B91FDB389B08A0D3E81D3A974FCD1EF099BEB4B204A5020CEB864FCF']

All keys in C format:
{0x19, 0x06, 0x77, 0xAC, 0xC8, 0xC9, 0x03, 0xAF, 0xD9, 0x18, 0x1A, 0x53, 0x6E, 0x3B, 0xF2, 0xCF, 0xA7, 0x55, 0xAA, 0x09, 0x53, 0xFE, 0x80, 0x21, 0x93, 0x4F, 0x91, 0x83, 0xEC, 0x9A, 0x22, 0x24},
{0x3F, 0x9A, 0xE3, 0x87, 0x1D, 0x21, 0x7F, 0x2F, 0x40, 0x68, 0x74, 0x3B, 0xBD, 0x06, 0xB8, 0xF0, 0xC3, 0xB1, 0x86, 0xFF, 0x69, 0xD2, 0xD8, 0xF1, 0x41, 0x0A, 0x44, 0xF8, 0x7D, 0x06, 0x80, 0xA2},
{0xAC, 0x18, 0x61, 0x71, 0x38, 0x6C, 0xC7, 0x74, 0xE4, 0x43, 0xBC, 0x96, 0xF0, 0xC0, 0x87, 0x82, 0xF5, 0xE9, 0x56, 0xF5, 0x4E, 0x67, 0xE6, 0xD8, 0x60, 0x75, 0xC3, 0x41, 0xB9, 0x6C, 0x3D, 0x91},
{0x91, 0x5B, 0x18, 0xEB, 0xD8, 0x11, 0x39, 0xF6, 0xAC, 0x08, 0x4F, 0xFD, 0x70, 0xDB, 0x44, 0xA0, 0xDB, 0xDF, 0xAD, 0x03, 0x01, 0x71, 0x9D, 0x40, 0x80, 0x63, 0x8D, 0x0A, 0x6B, 0x9D, 0xAE, 0x7E},
{0x1D, 0xBE, 0x7E, 0x41, 0xD0, 0xB2, 0x33, 0x41, 0x9C, 0xEC, 0xB9, 0x8C, 0xFB, 0x6D, 0xF1, 0xCC, 0xE3, 0x24, 0x3E, 0xF0, 0x9D, 0xA5, 0xD4, 0x38, 0x8C, 0xEF, 0xD6, 0x7E, 0xD7, 0x6D, 0x27, 0x83},
{0x42, 0x32, 0x8E, 0x22, 0xFB, 0xDE, 0xAF, 0x67, 0x5F, 0x5A, 0x91, 0x7C, 0xE7, 0x0F, 0xDE, 0x03, 0x45, 0xE7, 0x4C, 0xDA, 0x13, 0xFB, 0xBD, 0x8F, 0x4F, 0x26, 0xAD, 0xD7, 0x61, 0xE4, 0x75, 0xC7},
{0x4B, 0x94, 0x19, 0x9B, 0x78, 0x16, 0xB7, 0x3D, 0xB7, 0x44, 0x52, 0x0E, 0xCB, 0x1B, 0x26, 0xE6, 0xBB, 0x31, 0x7B, 0x47, 0x8F, 0x76, 0x52, 0x47, 0x85, 0xD6, 0x6F, 0x18, 0x81, 0x35, 0x87, 0xD9},
{0x4B, 0x1F, 0x73, 0x2A, 0x9D, 0x76, 0xA6, 0x1C, 0x20, 0x80, 0x45, 0x2A, 0x12, 0x26, 0x79, 0x26, 0x68, 0xC1, 0x13, 0x4B, 0x22, 0x79, 0x4D, 0x6C, 0x89, 0x0A, 0x35, 0x15, 0xCE, 0x50, 0x2E, 0x6E},
{0xFF, 0xB0, 0x05, 0x2D, 0x21, 0xF5, 0x27, 0x9D, 0xC3, 0xFF, 0x38, 0x4D, 0xB9, 0x87, 0x07, 0x82, 0x15, 0x37, 0x86, 0x63, 0x9E, 0xA3, 0x57, 0x55, 0x96, 0x46, 0xBC, 0xBA, 0xEE, 0x59, 0x7D, 0xA1},
{0x15, 0xDE, 0x6D, 0xE8, 0xAB, 0xBA, 0x53, 0x77, 0x8A, 0x43, 0xD7, 0xEB, 0x2D, 0x36, 0x4C, 0xF6, 0x21, 0xD7, 0xAC, 0x0B, 0xF1, 0x32, 0x75, 0x26, 0x32, 0x0E, 0xDF, 0x25, 0x4B, 0x59, 0x3D, 0x9D},
{0x53, 0x36, 0x35, 0x69, 0xB9, 0x1F, 0xDB, 0x38, 0x9B, 0x08, 0xA0, 0xD3, 0xE8, 0x1D, 0x3A, 0x97, 0x4F, 0xCD, 0x1E, 0xF0, 0x99, 0xBE, 0xB4, 0xB2, 0x04, 0xA5, 0x02, 0x0C, 0xEB, 0x86, 0x4F, 0xCF}

Encrypted signature in C format:
{0x42, 0xF6, 0x02, 0x26, 0x45, 0x13, 0x9E, 0x69, 0x96, 0x53, 0xB9, 0xC1, 0x93, 0x22, 0xDE, 0x64},
{0x4B, 0x16, 0xAB, 0xD8, 0xA8, 0x0B, 0xAD, 0x9F, 0x05, 0x01, 0x96, 0x27, 0xD8, 0xAE, 0xA4, 0xF6},
{0x5A, 0x07, 0x2B, 0x4B, 0x55, 0xC4, 0x98, 0x48, 0x09, 0x44, 0x3F, 0xF1, 0x1B, 0xE3, 0x37, 0x51},
{0xA0, 0xDB, 0xC4, 0x45, 0x88, 0x99, 0x98, 0x26, 0xC9, 0x3B, 0x7E, 0xB3, 0xBA, 0xD6, 0x81, 0x5A},
{0xEB, 0x86, 0x2B, 0xB2, 0xB2, 0x2E, 0xBE, 0x9F, 0x57, 0x72, 0x2E, 0x74, 0x4F, 0x57, 0x2E, 0x03},
{0xE8, 0x1C, 0x6B, 0xE2, 0x90, 0xAE, 0x79, 0x4F, 0xB7, 0x3A, 0xEB, 0xE0, 0x3C, 0x34, 0xD9, 0x90},
{0xBD, 0x1F, 0x2D, 0xA0, 0x48, 0x57, 0xE1, 0x0D, 0xA3, 0x64, 0xE2, 0x72, 0xCE, 0xE7, 0x13, 0x2F},
{0x55, 0x1A, 0x54, 0xCB, 0x2C, 0xE8, 0xCF, 0x6F, 0x27, 0x11, 0xF4, 0x27, 0xFE, 0xAE, 0xB1, 0xCA},
{0x89, 0x55, 0x3E, 0x9E, 0x06, 0x46, 0x1E, 0x65, 0x30, 0xE7, 0x1D, 0x7A, 0x77, 0xD8, 0xF2, 0x51},
{0xB2, 0x32, 0x56, 0xF8, 0xC2, 0xB1, 0xAE, 0x30, 0x00, 0xB2, 0xB2, 0x75, 0xE1, 0xA1, 0xA4, 0xF9}

Encrypted private key for cert:
39 7C 85 AD CF 6B F1 33 41 97 14 B3 F1 18 25 E8 73 9D E1 9D 93 99 F9 5B B2 F8 27 15 EE 01 C5 AE 7A C8 DB 10 C4 59 CE E9 0E 62 E7 1D 13 70 F8 D9 57 32 30 29 41 D6 FB 34 31 D5 CF D3 A5 31 48 91 68 6E 57 73 3F 49 AE 09 B8 15 80 6A D8 8B D4 B0 28 A2 99 70 E9 BF 57 28 77 9D EA 01 8F 39 1B 5A 30 2B 1F 7A 89 66 BD BB 9B 92 AF 45 51 C0 C6 1A F8 05 41 6D 45 5F 89 EE 65 BC 09 D0 DC F9 69 29
```
