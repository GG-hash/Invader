#include "GAME.h"
#include<iostream>

GAME::GAME()
{
	_ball.pos = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
	_ball.vel = glm::vec2(1, 1) * _ballSpeed;

	

	_paddles[OneP].pos = {WINDOW_WIDTH/15 , WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2};
	_paddles[TwoP].pos = {WINDOW_WIDTH-WINDOW_WIDTH/15 , WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2};

	_paddles[OneP].keys[KEY_UP]    = 'w';
	_paddles[OneP].keys[KEY_DOWN]  = 's';
	_paddles[OneP].keys[KEY_RIGHT] = 'd';
	_paddles[OneP].keys[KEY_LEFT]  = 'a';

	_paddles[TwoP].keys[KEY_UP]    = 'i';
	_paddles[TwoP].keys[KEY_DOWN]  = 'k';
	_paddles[TwoP].keys[KEY_RIGHT] = 'l';
	_paddles[TwoP].keys[KEY_LEFT]  = 'j';

	_paddles[OneP].score = 0;
	_paddles[TwoP].score = 0;

	_titleMode = true;
	
}

void GAME::Initialize(int argc, char* argv[], const char* title, int WinWidth, int WinHeight, unsigned int displayMode)
{
	glutInit(&argc, argv);
	_oldTime = glutGet(GLUT_ELAPSED_TIME);
	glutInitDisplayMode(displayMode);
	//glutInitWindowPosition(WinPosX, WinposY);
	glutInitWindowSize(WinWidth, WinHeight);
	glutCreateWindow(title);
}

void GAME::Initialize(int argc, char* argv[], const char* title)
{

	glutInit(&argc, argv);
	_oldTime = glutGet(GLUT_ELAPSED_TIME);
	glutInitDisplayMode(GL_DOUBLE);
	//glutInitWindowPosition(WinPosX, WinposY);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(title);
}

void GAME::InitBallVel()
{
	//�{�[���̌����𗐐��Ō��߂�
	srand((unsigned int)time(NULL));
	float ballVelX = rand() % 2 == 0 ? -1 : 1;
	srand((unsigned int)time(NULL));
	float ballVelY = rand() % 2 == 0 ? -1 : 1;
	_ballSpeed = 0.1f;
	_ball.vel = glm::vec2(ballVelX, ballVelY) * _ballSpeed;
}

void GAME::RestartGame()
{

	InitBallVel();

	_ball.pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	

	_paddles[OneP].pos = { WINDOW_WIDTH / 15 , WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
	_paddles[TwoP].pos = { WINDOW_WIDTH - WINDOW_WIDTH / 15 , WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2 };

	
	_paddles[OneP].score = 0;
	_paddles[TwoP].score = 0;

}




void GAME::RunLoop(void (*Display)(), void (*Idle)(), void (*Keyboard)(unsigned char, int, int), void (*KeyboardUp)(unsigned char, int, int))
{
	glutDisplayFunc((*Display));
	glutIdleFunc((*Idle));
	glutKeyboardFunc((*Keyboard));
	glutKeyboardUpFunc((*KeyboardUp));
	glutMainLoop();
}

//void GAME::RunLoop(void(*Display)(), void(*Keyboard)(unsigned char, int, int), void(*KeyboardUp)(unsigned char, int, int))
//{
//	glutDisplayFunc((*Display));
//	glutKeyboardFunc((*Keyboard));
//	glutKeyboardUpFunc((*KeyboardUp));
//	glutMainLoop();
//}

//�����m�̓����蔻��
bool IntersectLine(glm::vec2 startvec1, glm::vec2 endvec1, glm::vec2 startvec2, glm::vec2 endvec2)
{
	//2�x�N�g���̒�`
	glm::vec2 vec1 = endvec1 - startvec1;
	glm::vec2 vec2 = endvec2 - startvec2;

	//2�̋N�_�ƂȂ�x�N�g��
	glm::vec2 Startvec1To2 = startvec2 - startvec1;
	//2�̏I�_�ƂȂ�x�N�g��
	glm::vec2 Vec1StartToVec2Endvec = endvec2 - startvec1;

	//2��ނ̊O�ς��`
	float crossStartVec1          = CrossProduct(vec1,Startvec1To2);
	float crossVec1StartToVec2End = CrossProduct(vec1,Vec1StartToVec2Endvec);

	//����������������
	if (crossStartVec1 * crossVec1StartToVec2End < 0)
	{
		//std::cout << "�������Ă܂���" << std::endl;

		//2�̋N�_�ƂȂ�x�N�g��
		glm::vec2 Startvec2To1 = startvec1 - startvec2;
		//2�̏I�_�ƂȂ�x�N�g��
		glm::vec2 Vec2StartToVec1Endvec = endvec1 - startvec2;

		//2��ނ̊O�ς��`
		float crossStartVec2 = CrossProduct(vec2, Startvec2To1);
		float crossVec2StartToVec1End = CrossProduct(vec2, Vec2StartToVec1Endvec);

		if (crossStartVec2 * crossVec2StartToVec1End < 0)
		{
			return true;
		}
	}

	////2�̋N�_�ƂȂ�x�N�g��
	//glm::vec2 Startvec2To1 = startvec1 - startvec2;
	////2�̏I�_�ƂȂ�x�N�g��
	//glm::vec2 Vec2StartToVec1Endvec = endvec1 - startvec2;

	////2��ނ̊O�ς��`
	//float crossStartVec2          = CrossProduct(vec2, Startvec2To1);
	//float crossVec2StartToVec1End = CrossProduct(vec2, Vec2StartToVec1Endvec);

	//����������������
	//�ٕ����łȂ��Ȃ�false
	/*if ((crossStartVec1 * crossVec1StartToVec2End >= 0)&&(crossStartVec2 * crossVec2StartToVec1End >= 0))
	{
		return false;
	}*/
	//std::cout << "������܂���" << std::endl;
	return false;
}

//2�����̊O�ς��v�Z����֐�
float CrossProduct(glm::vec2 vec1, glm::vec2 vec2)
{
	return vec1.x * vec2.y - vec2.x * vec1.y;
}
