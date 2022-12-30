#pragma once
#include"Rect.h"
#include"Texture.h"
#include"Color.h"

#define MAX_EXPLOSION_COUNT 30

class Explosion : public Rect
{
private:
	//テクスチャ
	unsigned int _texture;
public:
	//初期化する関数
	int Initialize(const char* fileName,vec2 const& size);
	//爆発を開始する関数
	void Start(vec2 const& pos);
	//更新する関数
	void Update() override;
	
	//描画関数
	void Draw() override;
	//爆発のエフェクトが消滅するまでの時間
	int _count;

	
};//class Explosion : public Rect

