#include "LED-128-8.h"

namespace LW_BlockCiphers
{

unsigned char LED_128_8::keySize = 128;
unsigned char LED_128_8::RC0[] = { 0x08, 0x08, 0x08, 0x18, 0x38, 0x78, 0x78, 0x78, 0x68, 0x58, 0x38, 0x78, 0x78, 0x68, 0x48, 0x18, 0x38, 0x78, 0x68, 0x58, 0x28, 0x58, 0x38, 0x68, 0x48, 0x08, 0x08, 0x18, 0x28, 0x58, 0x38, 0x78, 0x68, 0x48, 0x08, 0x18, 0x38, 0x68, 0x58, 0x38, 0x68, 0x58, 0x28, 0x48, 0x18, 0x28, 0x48, 0x08 };
unsigned char LED_128_8::RC2[] = { 0x19, 0x39, 0x79, 0x79, 0x79, 0x69, 0x59, 0x39, 0x79, 0x79, 0x69, 0x49, 0x19, 0x39, 0x79, 0x69, 0x59, 0x29, 0x59, 0x39, 0x69, 0x49, 0x09, 0x09, 0x19, 0x29, 0x59, 0x39, 0x79, 0x69, 0x49, 0x09, 0x19, 0x39, 0x69, 0x59, 0x39, 0x69, 0x59, 0x29, 0x49, 0x19, 0x29, 0x49, 0x09, 0x19, 0x29, 0x49 };
unsigned char LED_128_8::RC4[] = { 0x02, 0x02, 0x02, 0x12, 0x32, 0x72, 0x72, 0x72, 0x62, 0x52, 0x32, 0x72, 0x72, 0x62, 0x42, 0x12, 0x32, 0x72, 0x62, 0x52, 0x22, 0x52, 0x32, 0x62, 0x42, 0x02, 0x02, 0x12, 0x22, 0x52, 0x32, 0x72, 0x62, 0x42, 0x02, 0x12, 0x32, 0x62, 0x52, 0x32, 0x62, 0x52, 0x22, 0x42, 0x12, 0x22, 0x42, 0x02 };
unsigned char LED_128_8::RC6[] = { 0x13, 0x33, 0x73, 0x73, 0x73, 0x63, 0x53, 0x33, 0x73, 0x73, 0x63, 0x43, 0x13, 0x33, 0x73, 0x63, 0x53, 0x23, 0x53, 0x33, 0x63, 0x43, 0x03, 0x03, 0x13, 0x23, 0x53, 0x33, 0x73, 0x63, 0x43, 0x03, 0x13, 0x33, 0x63, 0x53, 0x33, 0x63, 0x53, 0x23, 0x43, 0x13, 0x23, 0x43, 0x03, 0x13, 0x23, 0x43 };

unsigned char LED_128_8::sBox[] = {0xCC, 0xC5, 0xC6, 0xCB, 0xC9, 0xC0, 0xCA, 0xCD, 0xC3, 0xCE, 0xCF, 0xC8, 0xC4, 0xC7, 0xC1, 0xC2, 0x5C, 0x55, 0x56, 0x5B, 0x59, 0x50, 0x5A, 0x5D, 0x53, 0x5E, 0x5F, 0x58, 0x54, 0x57, 0x51, 0x52, 0x6C, 0x65, 0x66, 0x6B, 0x69, 0x60, 0x6A, 0x6D, 0x63, 0x6E, 0x6F, 0x68, 0x64, 0x67, 0x61, 0x62, 0xBC, 0xB5, 0xB6, 0xBB, 0xB9, 0xB0, 0xBA, 0xBD, 0xB3, 0xBE, 0xBF, 0xB8, 0xB4, 0xB7, 0xB1, 0xB2, 0x9C, 0x95, 0x96, 0x9B, 0x99, 0x90, 0x9A, 0x9D, 0x93, 0x9E, 0x9F, 0x98, 0x94, 0x97, 0x91, 0x92, 0x0C, 0x05, 0x06, 0x0B, 0x09, 0x00, 0x0A, 0x0D, 0x03, 0x0E, 0x0F, 0x08, 0x04, 0x07, 0x01, 0x02, 0xAC, 0xA5, 0xA6, 0xAB, 0xA9, 0xA0, 0xAA, 0xAD, 0xA3, 0xAE, 0xAF, 0xA8, 0xA4, 0xA7, 0xA1, 0xA2, 0xDC, 0xD5, 0xD6, 0xDB, 0xD9, 0xD0, 0xDA, 0xDD, 0xD3, 0xDE, 0xDF, 0xD8, 0xD4, 0xD7, 0xD1, 0xD2, 0x3C, 0x35, 0x36, 0x3B, 0x39, 0x30, 0x3A, 0x3D, 0x33, 0x3E, 0x3F, 0x38, 0x34, 0x37, 0x31, 0x32, 0xEC, 0xE5, 0xE6, 0xEB, 0xE9, 0xE0, 0xEA, 0xED, 0xE3, 0xEE, 0xEF, 0xE8, 0xE4, 0xE7, 0xE1, 0xE2, 0xFC, 0xF5, 0xF6, 0xFB, 0xF9, 0xF0, 0xFA, 0xFD, 0xF3, 0xFE, 0xFF, 0xF8, 0xF4, 0xF7, 0xF1, 0xF2, 0x8C, 0x85, 0x86, 0x8B, 0x89, 0x80, 0x8A, 0x8D, 0x83, 0x8E, 0x8F, 0x88, 0x84, 0x87, 0x81, 0x82, 0x4C, 0x45, 0x46, 0x4B, 0x49, 0x40, 0x4A, 0x4D, 0x43, 0x4E, 0x4F, 0x48, 0x44, 0x47, 0x41, 0x42, 0x7C, 0x75, 0x76, 0x7B, 0x79, 0x70, 0x7A, 0x7D, 0x73, 0x7E, 0x7F, 0x78, 0x74, 0x77, 0x71, 0x72, 0x1C, 0x15, 0x16, 0x1B, 0x19, 0x10, 0x1A, 0x1D, 0x13, 0x1E, 0x1F, 0x18, 0x14, 0x17, 0x11, 0x12, 0x2C, 0x25, 0x26, 0x2B, 0x29, 0x20, 0x2A, 0x2D, 0x23, 0x2E, 0x2F, 0x28, 0x24, 0x27, 0x21, 0x22};
unsigned char LED_128_8::mul2[] = {0xBB, 0xBA, 0xBC, 0xB5, 0xB1, 0xB0, 0xB7, 0xB9, 0xB6, 0xBF, 0xBD, 0xB3, 0xB8, 0xBE, 0xB2, 0xB4, 0xAB, 0xAA, 0xAC, 0xA5, 0xA1, 0xA0, 0xA7, 0xA9, 0xA6, 0xAF, 0xAD, 0xA3, 0xA8, 0xAE, 0xA2, 0xA4, 0xCB, 0xCA, 0xCC, 0xC5, 0xC1, 0xC0, 0xC7, 0xC9, 0xC6, 0xCF, 0xCD, 0xC3, 0xC8, 0xCE, 0xC2, 0xC4, 0x5B, 0x5A, 0x5C, 0x55, 0x51, 0x50, 0x57, 0x59, 0x56, 0x5F, 0x5D, 0x53, 0x58, 0x5E, 0x52, 0x54, 0x1B, 0x1A, 0x1C, 0x15, 0x11, 0x10, 0x17, 0x19, 0x16, 0x1F, 0x1D, 0x13, 0x18, 0x1E, 0x12, 0x14, 0x0B, 0x0A, 0x0C, 0x05, 0x01, 0x00, 0x07, 0x09, 0x06, 0x0F, 0x0D, 0x03, 0x08, 0x0E, 0x02, 0x04, 0x7B, 0x7A, 0x7C, 0x75, 0x71, 0x70, 0x77, 0x79, 0x76, 0x7F, 0x7D, 0x73, 0x78, 0x7E, 0x72, 0x74, 0x9B, 0x9A, 0x9C, 0x95, 0x91, 0x90, 0x97, 0x99, 0x96, 0x9F, 0x9D, 0x93, 0x98, 0x9E, 0x92, 0x94, 0x6B, 0x6A, 0x6C, 0x65, 0x61, 0x60, 0x67, 0x69, 0x66, 0x6F, 0x6D, 0x63, 0x68, 0x6E, 0x62, 0x64, 0xFB, 0xFA, 0xFC, 0xF5, 0xF1, 0xF0, 0xF7, 0xF9, 0xF6, 0xFF, 0xFD, 0xF3, 0xF8, 0xFE, 0xF2, 0xF4, 0xDB, 0xDA, 0xDC, 0xD5, 0xD1, 0xD0, 0xD7, 0xD9, 0xD6, 0xDF, 0xDD, 0xD3, 0xD8, 0xDE, 0xD2, 0xD4, 0x3B, 0x3A, 0x3C, 0x35, 0x31, 0x30, 0x37, 0x39, 0x36, 0x3F, 0x3D, 0x33, 0x38, 0x3E, 0x32, 0x34, 0x8B, 0x8A, 0x8C, 0x85, 0x81, 0x80, 0x87, 0x89, 0x86, 0x8F, 0x8D, 0x83, 0x88, 0x8E, 0x82, 0x84, 0xEB, 0xEA, 0xEC, 0xE5, 0xE1, 0xE0, 0xE7, 0xE9, 0xE6, 0xEF, 0xED, 0xE3, 0xE8, 0xEE, 0xE2, 0xE4, 0x2B, 0x2A, 0x2C, 0x25, 0x21, 0x20, 0x27, 0x29, 0x26, 0x2F, 0x2D, 0x23, 0x28, 0x2E, 0x22, 0x24, 0x4B, 0x4A, 0x4C, 0x45, 0x41, 0x40, 0x47, 0x49, 0x46, 0x4F, 0x4D, 0x43, 0x48, 0x4E, 0x42, 0x44};
unsigned char LED_128_8::mul4[] = {0x55, 0x57, 0x5B, 0x5A, 0x52, 0x50, 0x5E, 0x51, 0x5C, 0x5D, 0x59, 0x56, 0x53, 0x5F, 0x54, 0x58, 0x75, 0x77, 0x7B, 0x7A, 0x72, 0x70, 0x7E, 0x71, 0x7C, 0x7D, 0x79, 0x76, 0x73, 0x7F, 0x74, 0x78, 0xB5, 0xB7, 0xBB, 0xBA, 0xB2, 0xB0, 0xBE, 0xB1, 0xBC, 0xBD, 0xB9, 0xB6, 0xB3, 0xBF, 0xB4, 0xB8, 0xA5, 0xA7, 0xAB, 0xAA, 0xA2, 0xA0, 0xAE, 0xA1, 0xAC, 0xAD, 0xA9, 0xA6, 0xA3, 0xAF, 0xA4, 0xA8, 0x25, 0x27, 0x2B, 0x2A, 0x22, 0x20, 0x2E, 0x21, 0x2C, 0x2D, 0x29, 0x26, 0x23, 0x2F, 0x24, 0x28, 0x05, 0x07, 0x0B, 0x0A, 0x02, 0x00, 0x0E, 0x01, 0x0C, 0x0D, 0x09, 0x06, 0x03, 0x0F, 0x04, 0x08, 0xE5, 0xE7, 0xEB, 0xEA, 0xE2, 0xE0, 0xEE, 0xE1, 0xEC, 0xED, 0xE9, 0xE6, 0xE3, 0xEF, 0xE4, 0xE8, 0x15, 0x17, 0x1B, 0x1A, 0x12, 0x10, 0x1E, 0x11, 0x1C, 0x1D, 0x19, 0x16, 0x13, 0x1F, 0x14, 0x18, 0xC5, 0xC7, 0xCB, 0xCA, 0xC2, 0xC0, 0xCE, 0xC1, 0xCC, 0xCD, 0xC9, 0xC6, 0xC3, 0xCF, 0xC4, 0xC8, 0xD5, 0xD7, 0xDB, 0xDA, 0xD2, 0xD0, 0xDE, 0xD1, 0xDC, 0xDD, 0xD9, 0xD6, 0xD3, 0xDF, 0xD4, 0xD8, 0x95, 0x97, 0x9B, 0x9A, 0x92, 0x90, 0x9E, 0x91, 0x9C, 0x9D, 0x99, 0x96, 0x93, 0x9F, 0x94, 0x98, 0x65, 0x67, 0x6B, 0x6A, 0x62, 0x60, 0x6E, 0x61, 0x6C, 0x6D, 0x69, 0x66, 0x63, 0x6F, 0x64, 0x68, 0x35, 0x37, 0x3B, 0x3A, 0x32, 0x30, 0x3E, 0x31, 0x3C, 0x3D, 0x39, 0x36, 0x33, 0x3F, 0x34, 0x38, 0xF5, 0xF7, 0xFB, 0xFA, 0xF2, 0xF0, 0xFE, 0xF1, 0xFC, 0xFD, 0xF9, 0xF6, 0xF3, 0xFF, 0xF4, 0xF8, 0x45, 0x47, 0x4B, 0x4A, 0x42, 0x40, 0x4E, 0x41, 0x4C, 0x4D, 0x49, 0x46, 0x43, 0x4F, 0x44, 0x48, 0x85, 0x87, 0x8B, 0x8A, 0x82, 0x80, 0x8E, 0x81, 0x8C, 0x8D, 0x89, 0x86, 0x83, 0x8F, 0x84, 0x88};
unsigned char LED_128_8::mul5[] = {0x99, 0x92, 0x9D, 0x91, 0x9B, 0x90, 0x94, 0x9C, 0x9F, 0x93, 0x96, 0x9E, 0x97, 0x98, 0x95, 0x9A, 0x29, 0x22, 0x2D, 0x21, 0x2B, 0x20, 0x24, 0x2C, 0x2F, 0x23, 0x26, 0x2E, 0x27, 0x28, 0x25, 0x2A, 0xD9, 0xD2, 0xDD, 0xD1, 0xDB, 0xD0, 0xD4, 0xDC, 0xDF, 0xD3, 0xD6, 0xDE, 0xD7, 0xD8, 0xD5, 0xDA, 0x19, 0x12, 0x1D, 0x11, 0x1B, 0x10, 0x14, 0x1C, 0x1F, 0x13, 0x16, 0x1E, 0x17, 0x18, 0x15, 0x1A, 0xB9, 0xB2, 0xBD, 0xB1, 0xBB, 0xB0, 0xB4, 0xBC, 0xBF, 0xB3, 0xB6, 0xBE, 0xB7, 0xB8, 0xB5, 0xBA, 0x09, 0x02, 0x0D, 0x01, 0x0B, 0x00, 0x04, 0x0C, 0x0F, 0x03, 0x06, 0x0E, 0x07, 0x08, 0x05, 0x0A, 0x49, 0x42, 0x4D, 0x41, 0x4B, 0x40, 0x44, 0x4C, 0x4F, 0x43, 0x46, 0x4E, 0x47, 0x48, 0x45, 0x4A, 0xC9, 0xC2, 0xCD, 0xC1, 0xCB, 0xC0, 0xC4, 0xCC, 0xCF, 0xC3, 0xC6, 0xCE, 0xC7, 0xC8, 0xC5, 0xCA, 0xF9, 0xF2, 0xFD, 0xF1, 0xFB, 0xF0, 0xF4, 0xFC, 0xFF, 0xF3, 0xF6, 0xFE, 0xF7, 0xF8, 0xF5, 0xFA, 0x39, 0x32, 0x3D, 0x31, 0x3B, 0x30, 0x34, 0x3C, 0x3F, 0x33, 0x36, 0x3E, 0x37, 0x38, 0x35, 0x3A, 0x69, 0x62, 0x6D, 0x61, 0x6B, 0x60, 0x64, 0x6C, 0x6F, 0x63, 0x66, 0x6E, 0x67, 0x68, 0x65, 0x6A, 0xE9, 0xE2, 0xED, 0xE1, 0xEB, 0xE0, 0xE4, 0xEC, 0xEF, 0xE3, 0xE6, 0xEE, 0xE7, 0xE8, 0xE5, 0xEA, 0x79, 0x72, 0x7D, 0x71, 0x7B, 0x70, 0x74, 0x7C, 0x7F, 0x73, 0x76, 0x7E, 0x77, 0x78, 0x75, 0x7A, 0x89, 0x82, 0x8D, 0x81, 0x8B, 0x80, 0x84, 0x8C, 0x8F, 0x83, 0x86, 0x8E, 0x87, 0x88, 0x85, 0x8A, 0x59, 0x52, 0x5D, 0x51, 0x5B, 0x50, 0x54, 0x5C, 0x5F, 0x53, 0x56, 0x5E, 0x57, 0x58, 0x55, 0x5A, 0xA9, 0xA2, 0xAD, 0xA1, 0xAB, 0xA0, 0xA4, 0xAC, 0xAF, 0xA3, 0xA6, 0xAE, 0xA7, 0xA8, 0xA5, 0xAA};
unsigned char LED_128_8::mul6[] = {0xEE, 0xED, 0xE7, 0xEF, 0xE3, 0xE0, 0xE9, 0xE8, 0xEA, 0xE2, 0xE4, 0xE5, 0xEB, 0xE1, 0xE6, 0xEC, 0xDE, 0xDD, 0xD7, 0xDF, 0xD3, 0xD0, 0xD9, 0xD8, 0xDA, 0xD2, 0xD4, 0xD5, 0xDB, 0xD1, 0xD6, 0xDC, 0x7E, 0x7D, 0x77, 0x7F, 0x73, 0x70, 0x79, 0x78, 0x7A, 0x72, 0x74, 0x75, 0x7B, 0x71, 0x76, 0x7C, 0xFE, 0xFD, 0xF7, 0xFF, 0xF3, 0xF0, 0xF9, 0xF8, 0xFA, 0xF2, 0xF4, 0xF5, 0xFB, 0xF1, 0xF6, 0xFC, 0x3E, 0x3D, 0x37, 0x3F, 0x33, 0x30, 0x39, 0x38, 0x3A, 0x32, 0x34, 0x35, 0x3B, 0x31, 0x36, 0x3C, 0x0E, 0x0D, 0x07, 0x0F, 0x03, 0x00, 0x09, 0x08, 0x0A, 0x02, 0x04, 0x05, 0x0B, 0x01, 0x06, 0x0C, 0x9E, 0x9D, 0x97, 0x9F, 0x93, 0x90, 0x99, 0x98, 0x9A, 0x92, 0x94, 0x95, 0x9B, 0x91, 0x96, 0x9C, 0x8E, 0x8D, 0x87, 0x8F, 0x83, 0x80, 0x89, 0x88, 0x8A, 0x82, 0x84, 0x85, 0x8B, 0x81, 0x86, 0x8C, 0xAE, 0xAD, 0xA7, 0xAF, 0xA3, 0xA0, 0xA9, 0xA8, 0xAA, 0xA2, 0xA4, 0xA5, 0xAB, 0xA1, 0xA6, 0xAC, 0x2E, 0x2D, 0x27, 0x2F, 0x23, 0x20, 0x29, 0x28, 0x2A, 0x22, 0x24, 0x25, 0x2B, 0x21, 0x26, 0x2C, 0x4E, 0x4D, 0x47, 0x4F, 0x43, 0x40, 0x49, 0x48, 0x4A, 0x42, 0x44, 0x45, 0x4B, 0x41, 0x46, 0x4C, 0x5E, 0x5D, 0x57, 0x5F, 0x53, 0x50, 0x59, 0x58, 0x5A, 0x52, 0x54, 0x55, 0x5B, 0x51, 0x56, 0x5C, 0xBE, 0xBD, 0xB7, 0xBF, 0xB3, 0xB0, 0xB9, 0xB8, 0xBA, 0xB2, 0xB4, 0xB5, 0xBB, 0xB1, 0xB6, 0xBC, 0x1E, 0x1D, 0x17, 0x1F, 0x13, 0x10, 0x19, 0x18, 0x1A, 0x12, 0x14, 0x15, 0x1B, 0x11, 0x16, 0x1C, 0x6E, 0x6D, 0x67, 0x6F, 0x63, 0x60, 0x69, 0x68, 0x6A, 0x62, 0x64, 0x65, 0x6B, 0x61, 0x66, 0x6C, 0xCE, 0xCD, 0xC7, 0xCF, 0xC3, 0xC0, 0xC9, 0xC8, 0xCA, 0xC2, 0xC4, 0xC5, 0xCB, 0xC1, 0xC6, 0xCC};
unsigned char LED_128_8::mul8[] = {0xAA, 0xAE, 0xA5, 0xA7, 0xA4, 0xA0, 0xAF, 0xA2, 0xAB, 0xA9, 0xA1, 0xAC, 0xA6, 0xAD, 0xA8, 0xA3, 0xEA, 0xEE, 0xE5, 0xE7, 0xE4, 0xE0, 0xEF, 0xE2, 0xEB, 0xE9, 0xE1, 0xEC, 0xE6, 0xED, 0xE8, 0xE3, 0x5A, 0x5E, 0x55, 0x57, 0x54, 0x50, 0x5F, 0x52, 0x5B, 0x59, 0x51, 0x5C, 0x56, 0x5D, 0x58, 0x53, 0x7A, 0x7E, 0x75, 0x77, 0x74, 0x70, 0x7F, 0x72, 0x7B, 0x79, 0x71, 0x7C, 0x76, 0x7D, 0x78, 0x73, 0x4A, 0x4E, 0x45, 0x47, 0x44, 0x40, 0x4F, 0x42, 0x4B, 0x49, 0x41, 0x4C, 0x46, 0x4D, 0x48, 0x43, 0x0A, 0x0E, 0x05, 0x07, 0x04, 0x00, 0x0F, 0x02, 0x0B, 0x09, 0x01, 0x0C, 0x06, 0x0D, 0x08, 0x03, 0xFA, 0xFE, 0xF5, 0xF7, 0xF4, 0xF0, 0xFF, 0xF2, 0xFB, 0xF9, 0xF1, 0xFC, 0xF6, 0xFD, 0xF8, 0xF3, 0x2A, 0x2E, 0x25, 0x27, 0x24, 0x20, 0x2F, 0x22, 0x2B, 0x29, 0x21, 0x2C, 0x26, 0x2D, 0x28, 0x23, 0xBA, 0xBE, 0xB5, 0xB7, 0xB4, 0xB0, 0xBF, 0xB2, 0xBB, 0xB9, 0xB1, 0xBC, 0xB6, 0xBD, 0xB8, 0xB3, 0x9A, 0x9E, 0x95, 0x97, 0x94, 0x90, 0x9F, 0x92, 0x9B, 0x99, 0x91, 0x9C, 0x96, 0x9D, 0x98, 0x93, 0x1A, 0x1E, 0x15, 0x17, 0x14, 0x10, 0x1F, 0x12, 0x1B, 0x19, 0x11, 0x1C, 0x16, 0x1D, 0x18, 0x13, 0xCA, 0xCE, 0xC5, 0xC7, 0xC4, 0xC0, 0xCF, 0xC2, 0xCB, 0xC9, 0xC1, 0xCC, 0xC6, 0xCD, 0xC8, 0xC3, 0x6A, 0x6E, 0x65, 0x67, 0x64, 0x60, 0x6F, 0x62, 0x6B, 0x69, 0x61, 0x6C, 0x66, 0x6D, 0x68, 0x63, 0xDA, 0xDE, 0xD5, 0xD7, 0xD4, 0xD0, 0xDF, 0xD2, 0xDB, 0xD9, 0xD1, 0xDC, 0xD6, 0xDD, 0xD8, 0xD3, 0x8A, 0x8E, 0x85, 0x87, 0x84, 0x80, 0x8F, 0x82, 0x8B, 0x89, 0x81, 0x8C, 0x86, 0x8D, 0x88, 0x83, 0x3A, 0x3E, 0x35, 0x37, 0x34, 0x30, 0x3F, 0x32, 0x3B, 0x39, 0x31, 0x3C, 0x36, 0x3D, 0x38, 0x33};
unsigned char LED_128_8::mul9[] = {0x66, 0x6B, 0x63, 0x6C, 0x6D, 0x60, 0x65, 0x6F, 0x68, 0x67, 0x6E, 0x64, 0x62, 0x6A, 0x69, 0x61, 0xB6, 0xBB, 0xB3, 0xBC, 0xBD, 0xB0, 0xB5, 0xBF, 0xB8, 0xB7, 0xBE, 0xB4, 0xB2, 0xBA, 0xB9, 0xB1, 0x36, 0x3B, 0x33, 0x3C, 0x3D, 0x30, 0x35, 0x3F, 0x38, 0x37, 0x3E, 0x34, 0x32, 0x3A, 0x39, 0x31, 0xC6, 0xCB, 0xC3, 0xCC, 0xCD, 0xC0, 0xC5, 0xCF, 0xC8, 0xC7, 0xCE, 0xC4, 0xC2, 0xCA, 0xC9, 0xC1, 0xD6, 0xDB, 0xD3, 0xDC, 0xDD, 0xD0, 0xD5, 0xDF, 0xD8, 0xD7, 0xDE, 0xD4, 0xD2, 0xDA, 0xD9, 0xD1, 0x06, 0x0B, 0x03, 0x0C, 0x0D, 0x00, 0x05, 0x0F, 0x08, 0x07, 0x0E, 0x04, 0x02, 0x0A, 0x09, 0x01, 0x56, 0x5B, 0x53, 0x5C, 0x5D, 0x50, 0x55, 0x5F, 0x58, 0x57, 0x5E, 0x54, 0x52, 0x5A, 0x59, 0x51, 0xF6, 0xFB, 0xF3, 0xFC, 0xFD, 0xF0, 0xF5, 0xFF, 0xF8, 0xF7, 0xFE, 0xF4, 0xF2, 0xFA, 0xF9, 0xF1, 0x86, 0x8B, 0x83, 0x8C, 0x8D, 0x80, 0x85, 0x8F, 0x88, 0x87, 0x8E, 0x84, 0x82, 0x8A, 0x89, 0x81, 0x76, 0x7B, 0x73, 0x7C, 0x7D, 0x70, 0x75, 0x7F, 0x78, 0x77, 0x7E, 0x74, 0x72, 0x7A, 0x79, 0x71, 0xE6, 0xEB, 0xE3, 0xEC, 0xED, 0xE0, 0xE5, 0xEF, 0xE8, 0xE7, 0xEE, 0xE4, 0xE2, 0xEA, 0xE9, 0xE1, 0x46, 0x4B, 0x43, 0x4C, 0x4D, 0x40, 0x45, 0x4F, 0x48, 0x47, 0x4E, 0x44, 0x42, 0x4A, 0x49, 0x41, 0x26, 0x2B, 0x23, 0x2C, 0x2D, 0x20, 0x25, 0x2F, 0x28, 0x27, 0x2E, 0x24, 0x22, 0x2A, 0x29, 0x21, 0xA6, 0xAB, 0xA3, 0xAC, 0xAD, 0xA0, 0xA5, 0xAF, 0xA8, 0xA7, 0xAE, 0xA4, 0xA2, 0xAA, 0xA9, 0xA1, 0x96, 0x9B, 0x93, 0x9C, 0x9D, 0x90, 0x95, 0x9F, 0x98, 0x97, 0x9E, 0x94, 0x92, 0x9A, 0x99, 0x91, 0x16, 0x1B, 0x13, 0x1C, 0x1D, 0x10, 0x15, 0x1F, 0x18, 0x17, 0x1E, 0x14, 0x12, 0x1A, 0x19, 0x11};
unsigned char LED_128_8::mula[] = {0x11, 0x14, 0x19, 0x12, 0x15, 0x10, 0x18, 0x1B, 0x1D, 0x16, 0x1C, 0x1F, 0x1E, 0x13, 0x1A, 0x17, 0x41, 0x44, 0x49, 0x42, 0x45, 0x40, 0x48, 0x4B, 0x4D, 0x46, 0x4C, 0x4F, 0x4E, 0x43, 0x4A, 0x47, 0x91, 0x94, 0x99, 0x92, 0x95, 0x90, 0x98, 0x9B, 0x9D, 0x96, 0x9C, 0x9F, 0x9E, 0x93, 0x9A, 0x97, 0x21, 0x24, 0x29, 0x22, 0x25, 0x20, 0x28, 0x2B, 0x2D, 0x26, 0x2C, 0x2F, 0x2E, 0x23, 0x2A, 0x27, 0x51, 0x54, 0x59, 0x52, 0x55, 0x50, 0x58, 0x5B, 0x5D, 0x56, 0x5C, 0x5F, 0x5E, 0x53, 0x5A, 0x57, 0x01, 0x04, 0x09, 0x02, 0x05, 0x00, 0x08, 0x0B, 0x0D, 0x06, 0x0C, 0x0F, 0x0E, 0x03, 0x0A, 0x07, 0x81, 0x84, 0x89, 0x82, 0x85, 0x80, 0x88, 0x8B, 0x8D, 0x86, 0x8C, 0x8F, 0x8E, 0x83, 0x8A, 0x87, 0xB1, 0xB4, 0xB9, 0xB2, 0xB5, 0xB0, 0xB8, 0xBB, 0xBD, 0xB6, 0xBC, 0xBF, 0xBE, 0xB3, 0xBA, 0xB7, 0xD1, 0xD4, 0xD9, 0xD2, 0xD5, 0xD0, 0xD8, 0xDB, 0xDD, 0xD6, 0xDC, 0xDF, 0xDE, 0xD3, 0xDA, 0xD7, 0x61, 0x64, 0x69, 0x62, 0x65, 0x60, 0x68, 0x6B, 0x6D, 0x66, 0x6C, 0x6F, 0x6E, 0x63, 0x6A, 0x67, 0xC1, 0xC4, 0xC9, 0xC2, 0xC5, 0xC0, 0xC8, 0xCB, 0xCD, 0xC6, 0xCC, 0xCF, 0xCE, 0xC3, 0xCA, 0xC7, 0xF1, 0xF4, 0xF9, 0xF2, 0xF5, 0xF0, 0xF8, 0xFB, 0xFD, 0xF6, 0xFC, 0xFF, 0xFE, 0xF3, 0xFA, 0xF7, 0xE1, 0xE4, 0xE9, 0xE2, 0xE5, 0xE0, 0xE8, 0xEB, 0xED, 0xE6, 0xEC, 0xEF, 0xEE, 0xE3, 0xEA, 0xE7, 0x31, 0x34, 0x39, 0x32, 0x35, 0x30, 0x38, 0x3B, 0x3D, 0x36, 0x3C, 0x3F, 0x3E, 0x33, 0x3A, 0x37, 0xA1, 0xA4, 0xA9, 0xA2, 0xA5, 0xA0, 0xA8, 0xAB, 0xAD, 0xA6, 0xAC, 0xAF, 0xAE, 0xA3, 0xAA, 0xA7, 0x71, 0x74, 0x79, 0x72, 0x75, 0x70, 0x78, 0x7B, 0x7D, 0x76, 0x7C, 0x7F, 0x7E, 0x73, 0x7A, 0x77};
unsigned char LED_128_8::mulb[] = {0xDD, 0xD1, 0xDF, 0xD9, 0xDC, 0xD0, 0xD2, 0xD6, 0xDE, 0xD8, 0xD3, 0xD7, 0xDA, 0xD4, 0xDB, 0xD5, 0x1D, 0x11, 0x1F, 0x19, 0x1C, 0x10, 0x12, 0x16, 0x1E, 0x18, 0x13, 0x17, 0x1A, 0x14, 0x1B, 0x15, 0xFD, 0xF1, 0xFF, 0xF9, 0xFC, 0xF0, 0xF2, 0xF6, 0xFE, 0xF8, 0xF3, 0xF7, 0xFA, 0xF4, 0xFB, 0xF5, 0x9D, 0x91, 0x9F, 0x99, 0x9C, 0x90, 0x92, 0x96, 0x9E, 0x98, 0x93, 0x97, 0x9A, 0x94, 0x9B, 0x95, 0xCD, 0xC1, 0xCF, 0xC9, 0xCC, 0xC0, 0xC2, 0xC6, 0xCE, 0xC8, 0xC3, 0xC7, 0xCA, 0xC4, 0xCB, 0xC5, 0x0D, 0x01, 0x0F, 0x09, 0x0C, 0x00, 0x02, 0x06, 0x0E, 0x08, 0x03, 0x07, 0x0A, 0x04, 0x0B, 0x05, 0x2D, 0x21, 0x2F, 0x29, 0x2C, 0x20, 0x22, 0x26, 0x2E, 0x28, 0x23, 0x27, 0x2A, 0x24, 0x2B, 0x25, 0x6D, 0x61, 0x6F, 0x69, 0x6C, 0x60, 0x62, 0x66, 0x6E, 0x68, 0x63, 0x67, 0x6A, 0x64, 0x6B, 0x65, 0xED, 0xE1, 0xEF, 0xE9, 0xEC, 0xE0, 0xE2, 0xE6, 0xEE, 0xE8, 0xE3, 0xE7, 0xEA, 0xE4, 0xEB, 0xE5, 0x8D, 0x81, 0x8F, 0x89, 0x8C, 0x80, 0x82, 0x86, 0x8E, 0x88, 0x83, 0x87, 0x8A, 0x84, 0x8B, 0x85, 0x3D, 0x31, 0x3F, 0x39, 0x3C, 0x30, 0x32, 0x36, 0x3E, 0x38, 0x33, 0x37, 0x3A, 0x34, 0x3B, 0x35, 0x7D, 0x71, 0x7F, 0x79, 0x7C, 0x70, 0x72, 0x76, 0x7E, 0x78, 0x73, 0x77, 0x7A, 0x74, 0x7B, 0x75, 0xAD, 0xA1, 0xAF, 0xA9, 0xAC, 0xA0, 0xA2, 0xA6, 0xAE, 0xA8, 0xA3, 0xA7, 0xAA, 0xA4, 0xAB, 0xA5, 0x4D, 0x41, 0x4F, 0x49, 0x4C, 0x40, 0x42, 0x46, 0x4E, 0x48, 0x43, 0x47, 0x4A, 0x44, 0x4B, 0x45, 0xBD, 0xB1, 0xBF, 0xB9, 0xBC, 0xB0, 0xB2, 0xB6, 0xBE, 0xB8, 0xB3, 0xB7, 0xBA, 0xB4, 0xBB, 0xB5, 0x5D, 0x51, 0x5F, 0x59, 0x5C, 0x50, 0x52, 0x56, 0x5E, 0x58, 0x53, 0x57, 0x5A, 0x54, 0x5B, 0x55};
unsigned char LED_128_8::mule[] = {0x44, 0x43, 0x42, 0x48, 0x47, 0x40, 0x46, 0x4A, 0x41, 0x4B, 0x45, 0x49, 0x4D, 0x4C, 0x4E, 0x4F, 0x34, 0x33, 0x32, 0x38, 0x37, 0x30, 0x36, 0x3A, 0x31, 0x3B, 0x35, 0x39, 0x3D, 0x3C, 0x3E, 0x3F, 0x24, 0x23, 0x22, 0x28, 0x27, 0x20, 0x26, 0x2A, 0x21, 0x2B, 0x25, 0x29, 0x2D, 0x2C, 0x2E, 0x2F, 0x84, 0x83, 0x82, 0x88, 0x87, 0x80, 0x86, 0x8A, 0x81, 0x8B, 0x85, 0x89, 0x8D, 0x8C, 0x8E, 0x8F, 0x74, 0x73, 0x72, 0x78, 0x77, 0x70, 0x76, 0x7A, 0x71, 0x7B, 0x75, 0x79, 0x7D, 0x7C, 0x7E, 0x7F, 0x04, 0x03, 0x02, 0x08, 0x07, 0x00, 0x06, 0x0A, 0x01, 0x0B, 0x05, 0x09, 0x0D, 0x0C, 0x0E, 0x0F, 0x64, 0x63, 0x62, 0x68, 0x67, 0x60, 0x66, 0x6A, 0x61, 0x6B, 0x65, 0x69, 0x6D, 0x6C, 0x6E, 0x6F, 0xA4, 0xA3, 0xA2, 0xA8, 0xA7, 0xA0, 0xA6, 0xAA, 0xA1, 0xAB, 0xA5, 0xA9, 0xAD, 0xAC, 0xAE, 0xAF, 0x14, 0x13, 0x12, 0x18, 0x17, 0x10, 0x16, 0x1A, 0x11, 0x1B, 0x15, 0x19, 0x1D, 0x1C, 0x1E, 0x1F, 0xB4, 0xB3, 0xB2, 0xB8, 0xB7, 0xB0, 0xB6, 0xBA, 0xB1, 0xBB, 0xB5, 0xB9, 0xBD, 0xBC, 0xBE, 0xBF, 0x54, 0x53, 0x52, 0x58, 0x57, 0x50, 0x56, 0x5A, 0x51, 0x5B, 0x55, 0x59, 0x5D, 0x5C, 0x5E, 0x5F, 0x94, 0x93, 0x92, 0x98, 0x97, 0x90, 0x96, 0x9A, 0x91, 0x9B, 0x95, 0x99, 0x9D, 0x9C, 0x9E, 0x9F, 0xD4, 0xD3, 0xD2, 0xD8, 0xD7, 0xD0, 0xD6, 0xDA, 0xD1, 0xDB, 0xD5, 0xD9, 0xDD, 0xDC, 0xDE, 0xDF, 0xC4, 0xC3, 0xC2, 0xC8, 0xC7, 0xC0, 0xC6, 0xCA, 0xC1, 0xCB, 0xC5, 0xC9, 0xCD, 0xCC, 0xCE, 0xCF, 0xE4, 0xE3, 0xE2, 0xE8, 0xE7, 0xE0, 0xE6, 0xEA, 0xE1, 0xEB, 0xE5, 0xE9, 0xED, 0xEC, 0xEE, 0xEF, 0xF4, 0xF3, 0xF2, 0xF8, 0xF7, 0xF0, 0xF6, 0xFA, 0xF1, 0xFB, 0xF5, 0xF9, 0xFD, 0xFC, 0xFE, 0xFF};
unsigned char LED_128_8::mulf[] = {0x88, 0x86, 0x84, 0x83, 0x8E, 0x80, 0x8C, 0x87, 0x82, 0x85, 0x8A, 0x81, 0x89, 0x8B, 0x8F, 0x8D, 0x68, 0x66, 0x64, 0x63, 0x6E, 0x60, 0x6C, 0x67, 0x62, 0x65, 0x6A, 0x61, 0x69, 0x6B, 0x6F, 0x6D, 0x48, 0x46, 0x44, 0x43, 0x4E, 0x40, 0x4C, 0x47, 0x42, 0x45, 0x4A, 0x41, 0x49, 0x4B, 0x4F, 0x4D, 0x38, 0x36, 0x34, 0x33, 0x3E, 0x30, 0x3C, 0x37, 0x32, 0x35, 0x3A, 0x31, 0x39, 0x3B, 0x3F, 0x3D, 0xE8, 0xE6, 0xE4, 0xE3, 0xEE, 0xE0, 0xEC, 0xE7, 0xE2, 0xE5, 0xEA, 0xE1, 0xE9, 0xEB, 0xEF, 0xED, 0x08, 0x06, 0x04, 0x03, 0x0E, 0x00, 0x0C, 0x07, 0x02, 0x05, 0x0A, 0x01, 0x09, 0x0B, 0x0F, 0x0D, 0xC8, 0xC6, 0xC4, 0xC3, 0xCE, 0xC0, 0xCC, 0xC7, 0xC2, 0xC5, 0xCA, 0xC1, 0xC9, 0xCB, 0xCF, 0xCD, 0x78, 0x76, 0x74, 0x73, 0x7E, 0x70, 0x7C, 0x77, 0x72, 0x75, 0x7A, 0x71, 0x79, 0x7B, 0x7F, 0x7D, 0x28, 0x26, 0x24, 0x23, 0x2E, 0x20, 0x2C, 0x27, 0x22, 0x25, 0x2A, 0x21, 0x29, 0x2B, 0x2F, 0x2D, 0x58, 0x56, 0x54, 0x53, 0x5E, 0x50, 0x5C, 0x57, 0x52, 0x55, 0x5A, 0x51, 0x59, 0x5B, 0x5F, 0x5D, 0xA8, 0xA6, 0xA4, 0xA3, 0xAE, 0xA0, 0xAC, 0xA7, 0xA2, 0xA5, 0xAA, 0xA1, 0xA9, 0xAB, 0xAF, 0xAD, 0x18, 0x16, 0x14, 0x13, 0x1E, 0x10, 0x1C, 0x17, 0x12, 0x15, 0x1A, 0x11, 0x19, 0x1B, 0x1F, 0x1D, 0x98, 0x96, 0x94, 0x93, 0x9E, 0x90, 0x9C, 0x97, 0x92, 0x95, 0x9A, 0x91, 0x99, 0x9B, 0x9F, 0x9D, 0xB8, 0xB6, 0xB4, 0xB3, 0xBE, 0xB0, 0xBC, 0xB7, 0xB2, 0xB5, 0xBA, 0xB1, 0xB9, 0xBB, 0xBF, 0xBD, 0xF8, 0xF6, 0xF4, 0xF3, 0xFE, 0xF0, 0xFC, 0xF7, 0xF2, 0xF5, 0xFA, 0xF1, 0xF9, 0xFB, 0xFF, 0xFD, 0xD8, 0xD6, 0xD4, 0xD3, 0xDE, 0xD0, 0xDC, 0xD7, 0xD2, 0xD5, 0xDA, 0xD1, 0xD9, 0xDB, 0xDF, 0xDD};

	unsigned char* LED_128_8::byte2byte(unsigned char b[], int offSet)
	{
		unsigned char* c = new unsigned char[8];
		for (int i = 0; i < 8; i++)
		{
			c[i] = b[offSet + i];
		}
		return c;
	}

	void LED_128_8::byte2byte(unsigned char state[], unsigned char b[], int offSet)
	{
		for (int i = 0; i < 8; i++)
		{
			b[offSet + i] = state[i];
		}
	}

	void LED_128_8::AddKey(unsigned char state[], unsigned char roundKey[])
	{
		for (int i = 0; i < 8; i++)
		{
			state[i] ^= roundKey[i];
		}
	}

	void LED_128_8::AddConstants(unsigned char state[], int round)
	{
		state[0] ^= RC0[round];
		state[2] ^= RC2[round];
		state[4] ^= RC4[round];
		state[6] ^= RC6[round];
	}

	void LED_128_8::SubCellShiftRowAndMixColumns(unsigned char state[])
	{
		unsigned char* temp = new unsigned char[8];
		unsigned char b2, b3, b6, b7;

		b2 = static_cast<unsigned char>((state[2] >> 4) ^ (state[3] << 4));
		b3 = static_cast<unsigned char>((state[2] << 4) ^ (state[3] >> 4));

		b6 = static_cast<unsigned char>((state[6] << 4) ^ (state[7] >> 4));
		b7 = static_cast<unsigned char>((state[6] >> 4) ^ (state[7] << 4));

		temp[0] = static_cast<unsigned char>(mul4[state[0]] ^ sBox[b2] ^ mul2[state[5]] ^ mul2[b6]);
		temp[2] = static_cast<unsigned char>(mul8[state[0]] ^ mul6[b2] ^ mul5[state[5]] ^ mul6[b6]);
		temp[4] = static_cast<unsigned char>(mulb[state[0]] ^ mule[b2] ^ mula[state[5]] ^ mul9[b6]);
		temp[6] = static_cast<unsigned char>(mul2[state[0]] ^ mul2[b2] ^ mulf[state[5]] ^ mulb[b6]);

		temp[1] = static_cast<unsigned char>(mul4[state[1]] ^ sBox[b3] ^ mul2[state[4]] ^ mul2[b7]);
		temp[3] = static_cast<unsigned char>(mul8[state[1]] ^ mul6[b3] ^ mul5[state[4]] ^ mul6[b7]);
		temp[5] = static_cast<unsigned char>(mulb[state[1]] ^ mule[b3] ^ mula[state[4]] ^ mul9[b7]);
		temp[7] = static_cast<unsigned char>(mul2[state[1]] ^ mul2[b3] ^ mulf[state[4]] ^ mulb[b7]);

		for(int i=0;i<8;i++)
            state[i] = temp[i];
	}

	void LED_128_8::Step(unsigned char state[], int step)
	{
		for (int i = 0; i < 4; i++)
		{
			AddConstants(state, (step * 4 + i));
			SubCellShiftRowAndMixColumns(state);
		}
	}

	void LED_128_8::EncryptOneBlock(unsigned char state[], unsigned char sk0[], unsigned char sk1[])
	{
		for (int i = 0; i < 12; i+=2)
		{
			AddKey(state, sk0);
			Step(state, i);
			AddKey(state, sk1);
			Step(state, i+1);
		}
		AddKey(state, sk0);
	}

	unsigned char* LED_128_8::Encrypt(unsigned char input[], unsigned char key[], int len)
	{
		unsigned char* cipherText = new unsigned char[len];

		unsigned char* sk0 = byte2byte(key, 0);
		unsigned char* sk1 = byte2byte(key, 8);

		for (int i = 0; i < len; i += 8)
		{
			unsigned char* state = byte2byte(input, i);

			EncryptOneBlock(state, sk0, sk1);

			byte2byte(state, cipherText, i);
		}

		return cipherText;
	}
}
