#pragma once
#include "Scene.h"

class ReadyScene : public Scene
{
private:
	//文字数を表示させるカウンタ
	int _count;

public:
	//コンストラクタ
	ReadyScene();
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
};//class ReadyScene : public Scene

