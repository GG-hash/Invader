#pragma once
#include<cstdio>
#include<vector>
#include<Windows.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GL/glut.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"Rect.h"
#include"Font.h"
#include"GameHeader.h"
using namespace std;
using namespace glm;

#define SHIP_WIDTH     13
#define SHIP_HEIGHT    8
#define SHIP_DEFAULT_X SHIP_WIDTH
#define SHIP_DEFAULT_Y (SCREEN_HEIGHT - SHIP_HEIGHT * 5)
//�c�@�̍ő�l
#define MAX_SHIP_LIVES 3

class Ship :public Rect
{
private:
	
	//�e�N�X�`��
	unsigned int _shipTexture;
	//�c�@
	int _remaningLives;
public:

	//�v���C���[�̏������֐�
	int Initialize();
	//Ship�̓�������͂���֐�
	void Input(bool left,bool right,bool attack);
	//�U�����̏���
	void Shoot();
	//�X�V����֐�
	void Update() override;
	//�`��֐�
	void Draw() override;
	void Draw(vec2 const& pos) ;
	//Ship�̎c�@��`�悷��֐�
	void DrawRemaningLives();
	//Ship�����Z�b�g����֐�
	void Reset();
	//�c��̎c�@���擾����֐�
	int  GetRemaningLives() { return _remaningLives; }
	//�c��̎c�@���Z�b�g����֐�
	void SetRemaningLives(int life) { _remaningLives = life; }
	//�e�N�X�`�����擾����֐�
	unsigned int GetTexture() { return _shipTexture; }
	
};//class Ship


