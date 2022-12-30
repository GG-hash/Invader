#pragma once
#include "Scene.h"
#include"Font.h"
#include"Texture.h"
#include"Color.h"
#include"Ship.h"

//表示する最大の文字数
#define MAX_TEXT       16

//テキストのアニメーション
typedef struct TitleText
{
	//文字列
	char _str[MAX_TEXT];
	//文字列の位置
	vec2 _pos;
	//表示を開始するカウンタ
	int _startCount;
}TitleText;



class TitleScene : public Scene
{
private:
	//タイトル表示のカウンタ
	int _count;
public:
	//初期化
	void Initialize() override;
	//更新する関数
	void Update() override;
	//プレイヤーの入力処理をする関数
	void Keyboard(unsigned char key) override;
	//描画する関数
	void Draw() override;
	//リセットする関数
	void Reset() override;

};//class TitleScene : public Scene


