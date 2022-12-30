#pragma once
#include<cstdio>
#include<vector>
#include<Windows.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GL/glut.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"Rect.h"
#include"Font.h"
#include"GameHeader.h"
using namespace std;
using namespace glm;

#define SHIP_WIDTH     13
#define SHIP_HEIGHT    8
#define SHIP_DEFAULT_X SHIP_WIDTH
#define SHIP_DEFAULT_Y (SCREEN_HEIGHT - SHIP_HEIGHT * 5)
//残機の最大値
#define MAX_SHIP_LIVES 3

class Ship :public Rect
{
private:
	
	//テクスチャ
	unsigned int _shipTexture;
	//残機
	int _remaningLives;
public:

	//プレイヤーの初期化関数
	int Initialize();
	//Shipの動きを入力する関数
	void Input(bool left,bool right,bool attack);
	//攻撃時の処理
	void Shoot();
	//更新する関数
	void Update() override;
	//描画関数
	void Draw() override;
	void Draw(vec2 const& pos) ;
	//Shipの残機を描画する関数
	void DrawRemaningLives();
	//Shipをリセットする関数
	void Reset();
	//残りの残機を取得する関数
	int  GetRemaningLives() { return _remaningLives; }
	//残りの残機をセットする関数
	void SetRemaningLives(int life) { _remaningLives = life; }
	//テクスチャを取得する関数
	unsigned int GetTexture() { return _shipTexture; }
	
};//class Ship


