#pragma once
#include"Actor.h"

class Scene : public Actor
{
private:

public:
	//初期化
	virtual void Initialize() = 0;
	//更新する関数
	void Update() override;
	//プレイヤーの入力処理をする関数
	virtual void Keyboard(unsigned char key) = 0;
	//リセットする関数
	virtual void Reset() = 0;

};//class Scene


