#pragma once

#pragma once
#define MY_RGB 3
#pragma warning(suppress : 5208)



//êFÇÃíËã`
typedef struct Color {
	unsigned char Red[MY_RGB] = { 0xff,0,0 };
	unsigned char Green[MY_RGB] = { 0,0xff,0 };
	unsigned char Blue[MY_RGB] = { 0,0,0xff };
	unsigned char White[MY_RGB] = { 0xff,0xff,0xff };
	unsigned char LightGray[MY_RGB] = { 0xc0,0xc0,0xc0 };
	unsigned char LightBlue[MY_RGB] = { 0,0xff,0xff };
	unsigned char Gray[MY_RGB] = { 0x80,0x80,0x80 };
	unsigned char Ocher[MY_RGB] = { 0x80,0x80,0 };
	unsigned char Dark_Pink[MY_RGB] = { 0xff,0,0xff };
	unsigned char Blue_Green[MY_RGB] = { 0,0x80,0x80 };
	unsigned char Purple[MY_RGB] = { 0x80,0,0x80 };
	unsigned char Brown[MY_RGB] = { 0x80,0,0 };
	unsigned char Black[MY_RGB] = { 0,0,0 };
	unsigned char Yellow[MY_RGB] = { 0xff,0xff,0 };
};