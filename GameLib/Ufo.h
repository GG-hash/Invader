#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include "Rect.h"
#include"Texture.h"
#include"Color.h"
#include"Font.h"
#include"Audio.h"
//UFO�̕�
#define UFO_WIDTH 16
//UFO�̍���
#define UFO_HEIGHT 7
//UFO�̑���
#define UFO_SPEED 0.5
//UFO�̑ҋ@���� 25�b�Ɉ�񌻂��
#define UFO_WAIT_TIME (60 * 25)
//UFO�̌��Ăœ�����X�R�A�̎��
#define MAX_UFO_SCORE 4

//�e�N�X�`���̎�ނ�񋓌^�Œ�`����
enum
{
	TEXTURE_UFO,
	EXPLOSION_TEXTURE_UFO,
	MAX_UFO_TEXTURE
};

//UFO�̏��
enum UfoState
{
	WAIT,
	SCORE,
	MOVE,
	EXPLOSION,
	MAX_STATE
};

class Ufo : public Rect
{
private:
	//�e�N�X�`��
	unsigned int _textures[MAX_UFO_TEXTURE];
	//��Ԃ�ۑ�����ϐ�
	UfoState _state;
	//��Ԃ�ύX����J�E���^
	int _count;
	//Ufo�̃X�R�A
	int _score;
	//Ufo��x���W��ۑ�����ϐ�
	float _ufoX;
	//ufo�̌��ʉ��̎��g��
	int _freq;
	//�e�N�X�`���̔ԍ�
	int _textureIndex;
public:
	//Ufo�̃R���X�g���N�^
	Ufo();
	//Ufo������������֐�
	int Initialize();
	//Ufo�����Z�b�g����֐�
	void Reset();
	//�X�V����֐�
	void Update() override;
	//�`�悷��֐�
	void Draw() override;
	//Ufo�̔���
	void Explosion();
	//�e�N�X�`���̔ԍ����擾����
	int GetTextureIndex() { return _textureIndex; }
	//Ufo�̃X�R�A���擾����֐�
	int GetScore() { return _score; }
	//Ufo�̏�Ԃ��擾����֐�
	UfoState GetState() {return _state; }
	//�e�N�X�`�����擾����֐�
	unsigned int GetTexture() { return _textures[TEXTURE_UFO]; }
	
};//class Ufo : public Rect

