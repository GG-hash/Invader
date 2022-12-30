#pragma once
#include "Scene.h"
#include"Font.h"
#include"Texture.h"
#include"Color.h"
#include"Ship.h"

//�\������ő�̕�����
#define MAX_TEXT       16

//�e�L�X�g�̃A�j���[�V����
typedef struct TitleText
{
	//������
	char _str[MAX_TEXT];
	//������̈ʒu
	vec2 _pos;
	//�\�����J�n����J�E���^
	int _startCount;
}TitleText;



class TitleScene : public Scene
{
private:
	//�^�C�g���\���̃J�E���^
	int _count;
public:
	//������
	void Initialize() override;
	//�X�V����֐�
	void Update() override;
	//�v���C���[�̓��͏���������֐�
	void Keyboard(unsigned char key) override;
	//�`�悷��֐�
	void Draw() override;
	//���Z�b�g����֐�
	void Reset() override;

};//class TitleScene : public Scene


