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
	//�ϐ��̏�����
	GAME();
	//����������
	void Initialize(int argc, char* argv[], const char* title,int WinWidth, int WinHeight ,unsigned int displayMode);
	void Initialize(int argc, char* argv[], const char* title);

	void InitBallVel();

	void RestartGame();

	//deltaTime�̌v�Z�ɕK�v�ȕϐ�
	float _oldTime;
	float _newTime;

	bool _titleMode;

	//�Q�[�����[�v
	void RunLoop(void (*Display)(), void (*Idle)(), void (*Keyboard)(unsigned char, int, int), void (*KeyboardUp)(unsigned char, int, int));
	//void RunLoop(void (*Display)(), void (*Keyboard)(unsigned char, int, int), void (*KeyboardUp)(unsigned char, int, int));

	//�o�͂���֐�
	//void Display();

	//Ball�̍\����
	typedef struct 
	{
		glm::vec2 pos;
		glm::vec2 vel;
	}Ball;

	Ball _ball;

	//�{�[���̃X�s�[�h
	float _ballSpeed = 0.1f;
	
	//�v���C���[�̐l��
	enum PlayerCount
	{
		OneP, TwoP, MAX_P
	};

	enum DirectionKey { KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_MAX };

	bool _KeysPressed[256];

	//PlayerCount _players[MAX_P];

	//Padle�̍\����
	typedef struct
	{
		glm::vec2 pos;
		int score;
		char keys[KEY_MAX]; //= {'w','s','d','a'}; //KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT
	}Paddle;

	const float _paddleSpeed = 0.15f;

	Paddle _paddles[MAX_P];
	
};

//�����m�̓����蔻��
bool IntersectLine(glm::vec2 startvec1,glm::vec2 endvec1, glm::vec2 startvec2, glm::vec2 endvec2);
//2�����̊O�ς��v�Z����֐�
float CrossProduct(glm::vec2 vec1,glm::vec2 vec2);
