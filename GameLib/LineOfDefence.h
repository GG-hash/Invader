#pragma once
#include"Rect.h"
#include"GameHeader.h"

class LineOfDefence : public Rect
{
private:
	//テクスチャ
	unsigned char _texturePixels[SCREEN_WIDTH];
	unsigned int   _texture;
public:
	//コンストラクタ
	LineOfDefence();
	//弾を初期化する関数
	int Initialize();
	//更新する関数
	void Update() override;
	//描画する関数
	void Draw() override;
	//破線を生成する関数
	void EraseLine(int x);

};//class BulletMark : public Rect

