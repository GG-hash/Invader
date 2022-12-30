#pragma once
#include"Rect.h"
#include"Color.h"
#include"Texture.h"
#include"InvaderBullet.h"

//Torchkaの幅
#define TORCHKA_WIDTH 22
//Torchkaの高さ
#define TORCHKA_HEIGHT 16
//Torchkaの数
#define MAX_TORCHKA 4
//Torchkaのy座標
#define TORCHKA_POSITION_Y (SCREEN_HEIGHT - DEFAULT_GAME_HEIGHT * 8)
//DestroyedTorchkaの幅
#define DESTROYED_TORCHKA_WIDTH 8
//DestroyedTorchkaの高さ
#define DESTROYED_TORCHKA_HEIGHT 16

//弾が誰に破壊されたかを列挙型で表す
enum
{
	DESTROYED_BY_INVADER,
	DESTROYED_BY_SHIP,
	DESTROYED_MAX,
};

class Torchka : public Rect
{
private:
	//Torchkaの画像をピクセルごとに格納
	unsigned char _pixels[TORCHKA_HEIGHT][TORCHKA_WIDTH];
	//テクスチャ
	unsigned int _texture;
	
public:
	//Torchkaの爆発を初期化する関数
	int Initialize();
	//全てのTorchkaを初期化
	static int AllInitialize();
	//破壊されたTorchkaの初期化
	static int InitializeDestroyedTorchka();
	//リセットする関数
	void Reset();
	//ピクセルを消去する関数
	int ErasePixel(vec2 const& pos);
	//更新する関数
	void Update() override;
	static void AllUpdate();
	//描画する関数
	void Draw() override;
	//Rectクラスの当たり判定の関数をオーバーライドする
	bool IntersectRect(vec2 const& point) override;
	//Torchkaの破壊
	void Destroy(vec2 const& pos,int destroyedBy);
	
};//class Torchka : public Rect

