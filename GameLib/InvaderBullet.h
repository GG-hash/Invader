#pragma once
#include"Texture.h"
#include"Invader.h"
#include"Bullet.h"
#include"Rect.h"
//#include"GameHeader.h"

//�ő�̃C���x�[�_�[�̒e�̐�
#define MAX_INVADER_BULLET    2
//�e�̕�
#define INVADER_BULLET_WIDTH  3
//���̍���
#define INVADER_BULLET_HEIGHT 8
//�C���x�[�_�[�̒e�̑���
#define INVADER_BULLET_SPEED  3
//�C���x�[�_�[�̒e�̃A�j���[�V�����̎��
#define MAX_INVADER_BULLET_ANIMATION_TYPE 3
//�C���x�[�_�[�̒e�̃A�j���[�V�����̃R�}��
#define INVADER_BULLET_ANIMATION_LENGTH   4
//�A�j���[�V�����̈�R�}��R�}�\������ wait
#define INVADER_BULLET_ANIM_DISPLAY       3

class InvaderBullet : public Bullet,
					  public Rect
{
private:
	//�A�j���[�V�����̃^�C�v
	int _animType;
	//���݂̃e�N�X�`���@�r�[���̃A�j���[�V�����Ɏg�� animFrame
	int _currentAnimPhase;
	//�A�j���[�V�����̕\������ wait
	int _animDisplayFrame;
	//���L��(owner)�ւ�Invader�ւ̃|�C���^������
	//����ɂ��InvaderBullet����Invader�ւ̈ʒu�Ȃǂ̏��ɃA�N�Z�X�ł���
	class Invader* _owner;
	
public:
	//�R���X�g���N�^
	InvaderBullet();
	//�e������������֐�
	int Initialize() override;
	//�S�Ă̒e������������֐�
	static int AllInitialize();
	//�U������Ƃ��ɌĂяo�����֐�
	void Attack(vec2 const& pos, class Invader* owner);
	//�X�V����֐�
	void Update() override;
	//�S�Ă̒e���X�V����֐�
	static void AllUpdate();
	//�`�悷��֐�
	void Draw() override;
	//�S�Ă̒e���X�V�`�悷��֐�
	static void AllDraw();
	//�e�̃C���f�b�N�X
	int _index;
	//���L�҂�Ԃ��֐�
	class Invader* GetOwner() { return _owner; }
	//�e�������������J�E���g����֐�
	static int GetShootingCount();
};//class InvaderBullet

//�O������A�N�Z�X�ł���悤�ɂ���
extern class InvaderBullet gInvaderBullets[MAX_INVADER_BULLET];