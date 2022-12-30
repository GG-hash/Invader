#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include "Rect.h"
#include"Texture.h"
#include"Color.h"
#include"Font.h"
#include"Audio.h"
//UFOの幅
#define UFO_WIDTH 16
//UFOの高さ
#define UFO_HEIGHT 7
//UFOの速さ
#define UFO_SPEED 0.5
//UFOの待機時間 25秒に一回現れる
#define UFO_WAIT_TIME (60 * 25)
//UFOの撃墜で得られるスコアの種類
#define MAX_UFO_SCORE 4

//テクスチャの種類を列挙型で定義する
enum
{
	TEXTURE_UFO,
	EXPLOSION_TEXTURE_UFO,
	MAX_UFO_TEXTURE
};

//UFOの状態
enum UfoState
{
	WAIT,
	SCORE,
	MOVE,
	EXPLOSION,
	MAX_STATE
};

class Ufo : public Rect
{
private:
	//テクスチャ
	unsigned int _textures[MAX_UFO_TEXTURE];
	//状態を保存する変数
	UfoState _state;
	//状態を変更するカウンタ
	int _count;
	//Ufoのスコア
	int _score;
	//Ufoのx座標を保存する変数
	float _ufoX;
	//ufoの効果音の周波数
	int _freq;
	//テクスチャの番号
	int _textureIndex;
public:
	//Ufoのコンストラクタ
	Ufo();
	//Ufoを初期化する関数
	int Initialize();
	//Ufoをリセットする関数
	void Reset();
	//更新する関数
	void Update() override;
	//描画する関数
	void Draw() override;
	//Ufoの爆発
	void Explosion();
	//テクスチャの番号を取得する
	int GetTextureIndex() { return _textureIndex; }
	//Ufoのスコアを取得する関数
	int GetScore() { return _score; }
	//Ufoの状態を取得する関数
	UfoState GetState() {return _state; }
	//テクスチャを取得する関数
	unsigned int GetTexture() { return _textures[TEXTURE_UFO]; }
	
};//class Ufo : public Rect

