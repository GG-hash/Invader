#pragma once
#include<cstdio>
//���ƌ^���ς̃��X�g���g����悤�ɂ���
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
//Text2D(float X���W, float Y���W, unsigned char* �F, float �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, float size, const char* charactor, ...);
//Text2D(float X���W, float Y���W, float �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, float size, const char* charactor, ...);
//Text2D(float X���W, float Y���W,const char* ������, ...)
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

