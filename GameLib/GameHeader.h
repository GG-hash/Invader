#pragma once

//画面サイズ ファミコンの画面サイズは　256 * 256
#define SCREEN_WIDTH  224
#define SCREEN_HEIGHT 256
//スコアの文字を表示する高さ
#define SCORE_HEIGHT    3
//スコアの文字列からインベーダーが現れる縦の幅
#define FROM_SCORE_TO_INVADER 3
//ゲームで基準となる大きさ
#define DEFAULT_GAME_HEIGHT   8
//画面の中心の高さ
#define SCREEN_CENTER_HEIGHT 16

#include<iostream>
#include<time.h>
#include"Font.h"
#include"GL/glut.h"
#include"Rect.h"
#include"Audio.h"
#include"Ship.h"
#include"ShipExplosion.h"
#include"Torchka.h"
#include"Invader.h"
#include"Ufo.h"
#include"Bullet.h"
#include"ShipBullet.h"
#include"InvaderBullet.h"
#include"Explosion.h"
#include"Game.h"
#include"LineOfDefence.h"
#include"TitleScene.h"
#include"ReadyScene.h"
#include"MainScene.h"
#include"Color.h"
using namespace std;

//キーボードの入力を保存するする配列　外部からアクセスできるようにする
extern bool keys[256];
//Shipのデータを外部からアクセスできるようにする
extern class Ship gShip;
//Shipの爆発 
extern class ShipExplosion gShipEx;
//弾のデータを外部からアクセスできるようにする
extern class ShipBullet gShipBullet;
//Shipの弾の爆発
extern class Explosion gShipBulletEx;
//Invaderの爆発
extern class Explosion gInvaderEx;
//InvaderBulletの追加
//extern class InvaderBullet gInvaderBullets[MAX_INVADER_BULLET];
//Invaderの弾の爆発      MAX_INVADER_BULLET (2) 分だけ確保
extern class Explosion gInvaderBulletEx[2];
//防衛前線
extern class LineOfDefence gLineOfDefence;
//Torchka MAX_INVADER_BULLET (4) 分だけ確保
extern class Torchka gTorchka[4];
//Ufoを追加する
extern class Ufo gUfo;
//Gameを追加する
extern class Game gGame;
//TitleSceneを追加する
//extern class TitleScene gTitleScene;
////ReadySceneを追加する
//extern class ReadyScene gReadyScene;
////MainSceneを追加する　タイトル画面やゲーム画面を操作する
//extern class MainScene gMainScene;
