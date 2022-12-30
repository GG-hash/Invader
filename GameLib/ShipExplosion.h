#pragma once
#include"Rect.h"
#include"Texture.h"
#include"Color.h"
#include"Audio.h"
//#include"Explosion.h"

#define SHIP_EXPLOSION_WIDTH   16
#define SHIP_EXPLOSION_HEIGHT   8
#define MAX_SHIP_EXPLOSION_ANIM 2
//2秒間アニメーションを再生する
#define MAX_SHIP_EXPLOSION_ANIM_COUNT (60 * 2)

class ShipExplosion : public Rect
{
private:
	//テクスチャ
	unsigned int _textures[MAX_SHIP_EXPLOSION_ANIM];
	
public:
	ShipExplosion();
	//Shipの爆発を初期化する関数
	int Initialize();
	//更新する関数
	void Update() override;
	//描画する関数
	void Draw() override;
	//爆発を開始する関数
	void Start(vec2 const& pos);
	//爆発のエフェクトが消滅するまでの時間
	int _count;
};//class ShipExplosion : public Rect

