#pragma once
#include"Actor.h"
#include"GameHeader.h"
#include"Scene.h"
#define MAX_SCORE 9999

//表示画面の種類
enum SceneMode
{
	TITLE_SCENE,
	READY_SCENE,
	MAIN_SCENE,
	MAX_SCENE
};

class Game : public Actor
{
private:
	//スコア
	int _score;
	//ハイスコア
	int _highScore;
	//現在のステージ
	int _currentStage;
	//スクリーンの表示を番号で取得する変数
	int _sceneOfIndex;
	//Sceneの状態を取得する変数
	Scene* _scenes[MAX_SCENE];
	//現在のScene
	Scene* _currentScene;
public:
	//コンストラクタ
	Game();
	//Gameを初期化する関数
	int Initialize();
	//更新する関数
	void Update() override;
	//描画する関数
	void Draw() override;
	//スコアを表示させる関数
	void DrawScore();
	//スコアを増やす関数
	void AddScore(int score);
	//スコアを取得する関数
	int GetScore() { return _score; }
	//スコアを設定する関数
	void SetScore(int score) { _score = score; }
	//ハイスコアを取得する関数
	int GetHiScore() { return _highScore; }
	//ステージをリセットする関数
	void ResetStage();
	//現在のステージを取得する関数
	int GetCurrentStage() { return _currentStage; }
	//現在のステージを変更する
	void SetCurrentStage(int stage) { _currentStage = stage; }
	//Sceneの番号を取得する関数
	int GetSceneOfIndex() { return _sceneOfIndex; }
	//Sceneの状態を取得する関数
	Scene* GetCurrentScene() { return _currentScene; }
	//Sceneを設定する関数
	void SetScene(int scene);
	//ゲームオーバーかを判別する関数
	bool isGameOver();
};//class Game

