#include "MainScene.h"


void MainScene::Initialize()
{

}//void MainScene::Initialize()


void MainScene::Update()
{
	//敵の弾の爆発のアップデート
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		gInvaderBulletEx[i].Update();
	}
	//Ufoのアップデート
	gUfo.Update();
	//Torchkaのアップデート
	Torchka::AllUpdate();
	//Shipの弾のアップデート
	gShipBulletEx.Update();
	//敵の爆発のアップデート
	gInvaderEx.Update();
	//Shipの爆発のアップデート
	gShipEx.Update();
	//Shipのアップデート
	gShip.Update();
	//Shipの爆発のアップデート
	gShipBullet.Update();
	//インベーダーの更新
	Invader::AllUpdate();
	//インベーダーの弾の更新
	InvaderBullet::AllUpdate();
	//Gameのアップデート
	gGame.Update();

	//ゲームオーバーのカウンタを増やす条件は
	//Shipの残機が全てなくなり、一定時間が経過したら
	//タイトルへ戻る
	if ((gGame.isGameOver() == true)
		&& (++_gameOverCount >= MAX_GAMEOVER_COUNT))
	{
		gGame.SetScene(TITLE_SCENE);
		
	}//if (gShip.GetRemaningLives() <= 0)
	
}//void MainScene::Update()


void MainScene::Keyboard(unsigned char key)
{
	//攻撃
	//jを押して、ゲームオーバーでなく
	//爆破のアニメーションが無くインベーダーが出現したら攻撃できる
	if (key == 'j' 
		&& (gGame.isGameOver() == false)
		&& (gShipEx._count <= 0)
		&& (gInvaders[0][0].GetTurn() > 1))
	{
		//Ship爆破時の弾を撃てなくする
		if (gShipBulletEx._count <= 0)
			gShip.Shoot();
	}
}//void MainScene::Keyboard(unsigned char key)


void MainScene::Draw()
{
	//スコアの描画
	gGame.DrawScore();

	//残機の表示
	gShip.DrawRemaningLives();
	//Ufoの描画
	gUfo.Draw();

	//敵の弾の爆発の描画
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		gInvaderBulletEx[i].Draw();
	}

	//Torchkaの描画
	for (int i = 0; i < MAX_TORCHKA; i++)
	{
		gTorchka[i].Draw();
	}
	//インベーダーの爆発の描画
	gInvaderEx.Draw();
	//インベーダーの描画
	Invader::AllDraw();
	//インベーダーの弾の描画
	InvaderBullet::AllDraw();

	//弾で爆発する描画
	gShipBulletEx.Draw();

	//弾の描画
	gShipBullet.Draw();

	//Shipの描画
	gShip.Draw();

	//DestroyedTorchka

	//ShipExplosionの描画
	gShipEx.Draw();

	//防衛前線の描画
	gLineOfDefence.Draw();

	if (gGame.isGameOver() == true)
	{
		//ゲームオーバー時の描画
		Colorub color;
		vec2 pos = vec2(SCREEN_WIDTH / 2 - DEFAULT_GAME_HEIGHT * 3, DEFAULT_GAME_HEIGHT * (3 + 2));
		const char* text = "GAME OVER";
		char str[10] = {};
		int strLength = std::min(_gameOverCount / 8, 10);
		strncpy_s(str, text, strLength);
		Text2D(pos.x, pos.y, color.Red, str);
	}//if (gGame.isGameOver() == true)

}//void MainScene::Draw()


void MainScene::Reset()
{
	//最初のステージにする
	gGame.SetCurrentStage(0);
	//スコアをリセットする
	gGame.SetScore(0);
	//ステージのリセット
	gGame.ResetStage();
	//ゲームオーバーのカウンタを0にする
	_gameOverCount = 0;
}//void MainScene::Reset()

