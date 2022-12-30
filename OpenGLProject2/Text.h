#pragma once
#include<cstdio>
//個数と型が可変のリストを使えるようにする
#include<cstdarg>
#include"GL/glut.h"
#include"glm/glm.hpp"
#include"Color.h"
using namespace glm;

#define FONT_DEFAULT_SIZE 100.0f
#define MY_RGB 3

static vec2 _pos;
static float _size = FONT_DEFAULT_SIZE;
static unsigned char _color[MY_RGB];

void FontBegin();
void FontEnd();
void FontSetPosition(float x, float y);
float FontGetSize();
void FontSetSize(float size);
void FontColor(unsigned char r, unsigned char g, unsigned char b);
void FontColor(unsigned char* color);
void FontDraw(const char* charactor, ...);
//Text2D(float X座標, float Y座標, unsigned char* 色, float 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, float size, const char* charactor, ...);
//Text2D(float X座標, float Y座標, float 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, float size, const char* charactor, ...);
//Text2D(float X座標, float Y座標,const char* 文字列, ...)
void Text2D(float posX, float posY, const char* charactor, ...);

//class Font
//{
//public:
//	
//
//public:
//	//Font();
//	void FontBegin();
//	void FontEnd();
//	void FontSetPosition(float x, float y);
//	float FontGetSize();
//	void FontSetSize(float size);
//	void FontColor(unsigned char r, unsigned char g, unsigned char b);
//	void FontDraw(const char* charactor, ...);
//};

