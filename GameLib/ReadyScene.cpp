#include "ReadyScene.h"
#include"GameHeader.h"

ReadyScene::ReadyScene() :_count(0)
{

}//ReadyScene::ReadyScene()

void ReadyScene::Initialize()
{

}//void ReadyScene::Initialize()


void ReadyScene::Update()
{
	//カウンタを増やす
	if (++_count > 60)
	{
		gGame.SetScene(MAIN_SCENE);
	}
}//void ReadyScene::Update()


void ReadyScene::Keyboard(unsigned char key)
{
}//void ReadyScene::Keyboard(unsigned char key)


void ReadyScene::Draw()
{
	//スコアを点滅させる
	if (_count/10 % 2 == 0)
	{
		//スコアの描画
		gGame.DrawScore();
	}//if (_count % 2 == 0)

	//Shipの残機の描画
	gShip.DrawRemaningLives();
	vec2 pos = vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 7),DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 1));
	Text2D(pos.x,pos.y,"PLAY PLAYER<1>");

}//void ReadyScene::Draw()


void ReadyScene::Reset()
{
	_count = 0;
}//void ReadyScene::Reset()

