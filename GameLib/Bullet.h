#pragma once

//弾のクラス
class Bullet
{
public:
	Bullet();
	//初期化
	virtual int Initialize() = 0;
	//弾の発射状態
	bool _enable;
};//class Bullet