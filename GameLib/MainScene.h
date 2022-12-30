#pragma once
#include "Scene.h"
#include"Ship.h"
#include"Font.h"

//ゲームオーバーの表示時間の最大値
#define MAX_GAMEOVER_COUNT (60*4)

class MainScene : public Scene
{
private:
	//ゲームオーバーの文字の表示
	int _gameOverCount;
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
	//ゲームオーバーの文字の表示を取得する関数
	int GetGameOverCount() { return _gameOverCount; }

};//class MainScene : public Scene, public Actor

