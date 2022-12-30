#pragma once
#include "Bullet.h"
#include"Rect.h"

#define SHIP_BULLET_WIDTH  1
#define SHIP_BULLET_HEIGHT 4
#define SHIP_BULLET_SPEED  4

class ShipBullet :public Bullet,
				  public Rect
{
private:
	//テクスチャ
	unsigned int _texture;
public:
	ShipBullet();
	//初期化
	int Initialize() override;
	//弾の発射状態
	bool _enable;
	//更新する関数
	void Update() override;
	void Draw() override;
};//class ShipBullet :public Bullet

