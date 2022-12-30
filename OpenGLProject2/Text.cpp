#include "Text.h"

//Font()
//{
//	/*_pos = {};
//	_size = FONT_DEFAULT_SIZE;
//	_color[0] = 1;
//	_color[1] = 1;
//	_color[2] = 1;*/
//}

void FontBegin()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//二次元空間を定義
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void FontEnd()
{
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}

void FontSetPosition(float x, float y)
{
	_pos = vec2(x, y);
}

float FontGetSize()
{
	return _size;
}

void FontSetSize(float size)
{
	_size = size;
}

void FontColor(unsigned char r, unsigned char g, unsigned char b)
{
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
}

void FontColor(unsigned char* color)
{
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];
}

void FontDraw(const char* charactor, ...)
{
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(_pos.x, _pos.y + _size, 0);
		float s = _size / FONT_DEFAULT_SIZE;
		glScalef(s, -s, s);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();
}

//Text2D(float X座標, float Y座標, unsigned char* 色, float 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, float size, const char* charactor, ...)
{

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//二次元空間を定義
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//色の設定
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//文字サイズ
	_size = size;

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(_pos.x, _pos.y + _size, 0);
		float s = _size / FONT_DEFAULT_SIZE;
		glScalef(s, -s, s);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す

	/*FontBegin();

	FontColor(Color.LightGray);
	FontSetPosition(0, WINDOW_HEIGHT - FontGetSize() * 1.5);
	FontSetSize(FONT_DEFAULT_SIZE / 2);
	FontDraw("angle : %f", angle);

	FontEnd();*/
}

//Text2D(float X座標, float Y座標, float 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, float size, const char* charactor, ...)
{
	//初期化
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//二次元空間を定義
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//白色の設定
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//文字サイズ
	_size = size;

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(posX, posY + size, 0);
		float scale = size / FONT_DEFAULT_SIZE;
		glScalef(scale, -scale, scale);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}

//Text2D(float X座標, float Y座標,const char* 文字列, ...)
void Text2D(float posX, float posY, const char* charactor, ...)
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//二次元空間を定義
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//白色の設定
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//文字サイズ
	float size = FONT_DEFAULT_SIZE / 2;

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(posX, posY + size, 0);
		float scale = size / FONT_DEFAULT_SIZE;
		glScalef(scale, -scale, scale);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}
