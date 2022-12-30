#include "LineOfDefence.h"

LineOfDefence::LineOfDefence()
{
	

}//LineOfDefence::LineOfDefence()


int LineOfDefence::Initialize()
{
	//初期位置 スクリーンの高さから一行分( 8 )を引いて、更に1ピクセル引く
	vec2 pos = vec2(0, SCREEN_HEIGHT - 8 - 1);
	SetPosition(pos);

	//サイズの設定
	vec2 size = vec2(SCREEN_WIDTH,1);
	SetSize(size);

	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		//直線で描画
		_texturePixels[i] = 0xff;
		//破線で描画
		//_texturePixels[i] = (i%2)?0xff : 0x00;

	}//for (int i = 0; i < SCREEN_WIDTH; i++)

	//テクスチャの生成
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);


	//拡大時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //画像を拡大したときの処理
		GL_NEAREST //補完をしない
	);
	//縮小時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //画像を縮小したときの処理
		GL_NEAREST //補完をしない
	);

	//クランプの設定　画像の一番下のデータが画像の一番上のデータを参照しないようにする
	//横のクランプ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//縦のクランプ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	return 0;
}//int LineOfDefence::Initialize()


void LineOfDefence::Update()
{
}//void LineOfDefence::Update()


void LineOfDefence::Draw()
{
	//描画
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, SCREEN_WIDTH, 1,
		0, GL_ALPHA, GL_UNSIGNED_BYTE, _texturePixels);
	SetColorWithPosition(GetPosition());
	Rect::Draw();
}
//void LineOfDefence::Draw()

void LineOfDefence::EraseLine(int x)
{
	//範囲外の描画はしない
	if ((0 > x) && (SCREEN_WIDTH <= x))
	{
		return;
	}

	//線を消す
	_texturePixels[x] = 0;
}//void LineOfDefence::EraseLine(float x)

