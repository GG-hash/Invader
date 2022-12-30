#pragma once
#include"Rect.h"
#include"Texture.h"
#include"GameHeader.h"

#define DEFAULT_INVADER_SPEED    3
#define DEFAULT_INVADER_INTERVAL 8
#define INVADER_HEIGHT           8
#define MAX_INVADER_ANIM         2
#define MAX_INVADER_ROW          5
#define MAX_INVADER_COLUMN      11
#define MAX_INVADER              (MAX_INVADER_ROW*MAX_INVADER_COLUMN)
#define FIRST_ROW_INVADER        1
#define SECOND_ROW_INVADER       3
#define LAST_ROW_INVADER         4
#define MAX_INVADER_BGM_PHASE    4


class Invader : public Rect
{
private:
	//Invaderのスピード
	static vec2 _invaderSpeed;
	static vec2 _nextSpeed;
	//テクスチャを格納する配列
	unsigned int _textures[MAX_INVADER_ANIM];
	//アニメーションの番号
	int _animNo;
	//1フレームずつインベーダーを動かす
	//現在のインベーダーの位置(ブロック)を保存する変数
	static int _current;
	//BGMのカウント
	static int _bgmCount;
	//現在の音
	static int _bgmCurrent;
	//スコア
	int _score;
	//ゲームのターン数
	int _turn;
public:
	Invader();
	//プレイヤーの初期化関数
	int Initialize(const char* fileName0,const char* fileName1,vec2 size,vec2 pos = vec2());
	//全インベーダーの初期化
	static int AllInitialize();
	//全てのインベーダーをリセットするのに必要な関数
	void Reset();
	static void AllReset();
	//更新する関数
	void Update() override;
	static void AllUpdate();
	//描画関数
	void Draw() override;
	static void AllDraw();

	//スピードのゲッタとセッタ
	static vec2& GetSpeed() { return _invaderSpeed; }
	static void SetSpeed(vec2& speed) {_invaderSpeed = speed;}

	//テクスチャを取得する関数
	unsigned int GetTextures() { return _textures[_animNo]; }

	//インベーダーが倒されたか判定する処理
	bool _isDead;

	//弾を撃っている状態か判別する関数
	bool isShooting();
	//生きてるインベーダーの数
	static int GetCountAlives();
	//スコアを取得する関数
	int GetScore() { return _score; }
	//ターンを取得する関数
	int GetTurn() { return _turn; }
};//class Invader

//インベーダーを格納する配列
extern class Invader gInvaders[MAX_INVADER_ROW][MAX_INVADER_COLUMN];