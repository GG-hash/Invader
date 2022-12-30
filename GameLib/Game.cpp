#include "Game.h"

Game::Game()
{

}//Game::Game()


int Game::Initialize()
{
    //スコアの初期化
    _score = 0;
    _highScore = 0;
    //シーンの代入
    _scenes[TITLE_SCENE] = new TitleScene();
    _scenes[READY_SCENE] = new ReadyScene();
    _scenes[MAIN_SCENE]  = new MainScene();

    //シーンを全て初期化
    for (int i = 0; i < MAX_SCENE; i++)
    {
        _scenes[i]->Initialize();
    }//for (int i = 0; i < MAX_SCENE; i++)

     //シーンのモード
    _sceneOfIndex = TITLE_SCENE;
    _currentScene = _scenes[_sceneOfIndex];
   

    return 0;
}//int Game::Initialize()

void Game::Update()
{
    //ゲームをクリアしたときの処理
    if (gInvaderEx._count <= 0)
    {
        //インベーダがすべて倒され、Shipの残機が残っていたらクリア
        if ((Invader::GetCountAlives() <= 0) && gShip.GetRemaningLives() <= 0) 
        {
            //次のステージへ設定する
            _currentStage++;
            //ステージをリセットする
            ResetStage();
        }
    }// if (gInvaderEx._count <= 0)
}//void Game::Update()


void Game::Draw()
{
}//void Game::Draw()


void Game::DrawScore()
{
    vec2 size = vec2(5, DEFAULT_GAME_HEIGHT);
    Text2D(4 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 2, size, "%04d", gGame.GetScore());
}//void Game::DrawScore()


void Game::AddScore(int score)
{
    _score += score;
    //スコアが最大になった時の処理
    if (_score > MAX_SCORE)
    {
        _score = MAX_SCORE;
    }//if (_score >> MAX_SCORE)

    //ハイスコアの更新
    if (_score > _highScore)
    {
        _highScore = _score;
    }//if (_score > _highScore)

}//void Game::AddScore()

void Game::ResetStage()
{
    //Shipのリセット
    gShip.Reset();
    //インベーダーのリセット
    Invader::AllReset();
    //Torchkaのリセット
    for (int i = 0;i < MAX_TORCHKA; i++)
    {
        gTorchka[i].Reset();
    }//for (int i = 0;i < MAX_TORCHKA; i++)
    //Ufoのリセット
    gUfo.Reset();

}//void Game::ResetStage()


void Game::SetScene(int scene)
{
    //シーンのモード
    //_sceneOfIndex = READY_SCENE;
    _sceneOfIndex = scene;
    _currentScene = _scenes[_sceneOfIndex];
    //次のシーンに切り替えたらリセットする
    _currentScene->Reset();

}//void Game::SetScene(int scene)


bool Game::isGameOver()
{
    //printf("isGameOverが呼び出された\n");
    //Shipの残機がなくなったらtrueを返す
    if ((gShip.GetRemaningLives() <= 0))
    {
        return true;
    }//if ((gShip.GetRemaningLives() <= 0))

    //インベーダーがTorchkaを超えたらゲームオーバー
    //全てのインベーダーをチェックする
    for (int i = 0; i < MAX_INVADER_ROW; i++)
    {
        for (int j = 0; j < MAX_INVADER_COLUMN; j++)
        {
            //torchkaを超えたか判定する
            if (gInvaders[i][j].GetPosition().y >= SHIP_DEFAULT_Y)
            {
                return true;
            }
        }//for (int j = 0; j < MAX_INVADER; j++)
    }//for (int i = 0; i < MAX_INVADER; i++)

    return false;
}//bool Game::isGameOver()





