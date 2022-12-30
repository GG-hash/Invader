#pragma once
#include"Texture.h"
#include"Invader.h"
#include"Bullet.h"
#include"Rect.h"
//#include"GameHeader.h"

//最大のインベーダーの弾の数
#define MAX_INVADER_BULLET    2
//弾の幅
#define INVADER_BULLET_WIDTH  3
//幅の高さ
#define INVADER_BULLET_HEIGHT 8
//インベーダーの弾の速さ
#define INVADER_BULLET_SPEED  3
//インベーダーの弾のアニメーションの種類
#define MAX_INVADER_BULLET_ANIMATION_TYPE 3
//インベーダーの弾のアニメーションのコマ数
#define INVADER_BULLET_ANIMATION_LENGTH   4
//アニメーションの一コマ一コマ表示時間 wait
#define INVADER_BULLET_ANIM_DISPLAY       3

class InvaderBullet : public Bullet,
					  public Rect
{
private:
	//アニメーションのタイプ
	int _animType;
	//現在のテクスチャ　ビームのアニメーションに使う animFrame
	int _currentAnimPhase;
	//アニメーションの表示時間 wait
	int _animDisplayFrame;
	//所有者(owner)へのInvaderへのポインタを持つ
	//これによりInvaderBulletからInvaderへの位置などの情報にアクセスできる
	class Invader* _owner;
	
public:
	//コンストラクタ
	InvaderBullet();
	//弾を初期化する関数
	int Initialize() override;
	//全ての弾を初期化する関数
	static int AllInitialize();
	//攻撃するときに呼び出される関数
	void Attack(vec2 const& pos, class Invader* owner);
	//更新する関数
	void Update() override;
	//全ての弾を更新する関数
	static void AllUpdate();
	//描画する関数
	void Draw() override;
	//全ての弾を更新描画する関数
	static void AllDraw();
	//弾のインデックス
	int _index;
	//所有者を返す関数
	class Invader* GetOwner() { return _owner; }
	//弾を撃った数をカウントする関数
	static int GetShootingCount();
};//class InvaderBullet

//外部からアクセスできるようにする
extern class InvaderBullet gInvaderBullets[MAX_INVADER_BULLET];