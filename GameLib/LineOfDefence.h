#pragma once
#include"Rect.h"
#include"GameHeader.h"

class LineOfDefence : public Rect
{
private:
	//�e�N�X�`��
	unsigned char _texturePixels[SCREEN_WIDTH];
	unsigned int   _texture;
public:
	//�R���X�g���N�^
	LineOfDefence();
	//�e������������֐�
	int Initialize();
	//�X�V����֐�
	void Update() override;
	//�`�悷��֐�
	void Draw() override;
	//�j���𐶐�����֐�
	void EraseLine(int x);

};//class BulletMark : public Rect

