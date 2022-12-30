#pragma once
#include<GL/glut.h>
#include"GL/freeglut.h"
#include"glm/glm.hpp"
#include<time.h>
#include"Text.h"

#define WINDOW_WIDTH  640//1280 //16
#define WINDOW_HEIGHT 360   //720 //9

#define PADDLE_WIDTH  80
#define PADDLE_HEIGHT 45

#define MAX_SCORE 10

#define NORMAL_BALLSPEED 0.1


class GAME
{
public:
	//変数の初期化
	GAME();
	//初期化処理
	void Initialize(int argc, char* argv[], const char* title,int WinWidth, int WinHeight ,unsigned int displayMode);
	void Initialize(int argc, char* argv[], const char* title);

	void InitBallVel();

	void RestartGame();

	//deltaTimeの計算に必要な変数
	float _oldTime;
	float _newTime;

	bool _titleMode;

	//ゲームループ
	void RunLoop(void (*Display)(), void (*Idle)(), void (*Keyboard)(unsigned char, int, int), void (*KeyboardUp)(unsigned char, int, int));
	//void RunLoop(void (*Display)(), void (*Keyboard)(unsigned char, int, int), void (*KeyboardUp)(unsigned char, int, int));

	//出力する関数
	//void Display();

	//Ballの構造体
	typedef struct 
	{
		glm::vec2 pos;
		glm::vec2 vel;
	}Ball;

	Ball _ball;

	//ボールのスピード
	float _ballSpeed = 0.1f;
	
	//プレイヤーの人数
	enum PlayerCount
	{
		OneP, TwoP, MAX_P
	};

	enum DirectionKey { KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_MAX };

	bool _KeysPressed[256];

	//PlayerCount _players[MAX_P];

	//Padleの構造体
	typedef struct
	{
		glm::vec2 pos;
		int score;
		char keys[KEY_MAX]; //= {'w','s','d','a'}; //KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT
	}Paddle;

	const float _paddleSpeed = 0.15f;

	Paddle _paddles[MAX_P];
	
};

//線同士の当たり判定
bool IntersectLine(glm::vec2 startvec1,glm::vec2 endvec1, glm::vec2 startvec2, glm::vec2 endvec2);
//2次元の外積を計算する関数
float CrossProduct(glm::vec2 vec1,glm::vec2 vec2);
