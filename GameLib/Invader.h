#pragma once
#include"Rect.h"
#include"Texture.h"
#include"GameHeader.h"

#define DEFAULT_INVADER_SPEED    3
#define DEFAULT_INVADER_INTERVAL 8
#define INVADER_HEIGHT           8
#define MAX_INVADER_ANIM         2
#define MAX_INVADER_ROW          5
#define MAX_INVADER_COLUMN      11
#define MAX_INVADER              (MAX_INVADER_ROW*MAX_INVADER_COLUMN)
#define FIRST_ROW_INVADER        1
#define SECOND_ROW_INVADER       3
#define LAST_ROW_INVADER         4
#define MAX_INVADER_BGM_PHASE    4


class Invader : public Rect
{
private:
	//Invader�̃X�s�[�h
	static vec2 _invaderSpeed;
	static vec2 _nextSpeed;
	//�e�N�X�`�����i�[����z��
	unsigned int _textures[MAX_INVADER_ANIM];
	//�A�j���[�V�����̔ԍ�
	int _animNo;
	//1�t���[�����C���x�[�_�[�𓮂���
	//���݂̃C���x�[�_�[�̈ʒu(�u���b�N)��ۑ�����ϐ�
	static int _current;
	//BGM�̃J�E���g
	static int _bgmCount;
	//���݂̉�
	static int _bgmCurrent;
	//�X�R�A
	int _score;
	//�Q�[���̃^�[����
	int _turn;
public:
	Invader();
	//�v���C���[�̏������֐�
	int Initialize(const char* fileName0,const char* fileName1,vec2 size,vec2 pos = vec2());
	//�S�C���x�[�_�[�̏�����
	static int AllInitialize();
	//�S�ẴC���x�[�_�[�����Z�b�g����̂ɕK�v�Ȋ֐�
	void Reset();
	static void AllReset();
	//�X�V����֐�
	void Update() override;
	static void AllUpdate();
	//�`��֐�
	void Draw() override;
	static void AllDraw();

	//�X�s�[�h�̃Q�b�^�ƃZ�b�^
	static vec2& GetSpeed() { return _invaderSpeed; }
	static void SetSpeed(vec2& speed) {_invaderSpeed = speed;}

	//�e�N�X�`�����擾����֐�
	unsigned int GetTextures() { return _textures[_animNo]; }

	//�C���x�[�_�[���|���ꂽ�����肷�鏈��
	bool _isDead;

	//�e�������Ă����Ԃ����ʂ���֐�
	bool isShooting();
	//�����Ă�C���x�[�_�[�̐�
	static int GetCountAlives();
	//�X�R�A���擾����֐�
	int GetScore() { return _score; }
	//�^�[�����擾����֐�
	int GetTurn() { return _turn; }
};//class Invader

//�C���x�[�_�[���i�[����z��
extern class Invader gInvaders[MAX_INVADER_ROW][MAX_INVADER_COLUMN];