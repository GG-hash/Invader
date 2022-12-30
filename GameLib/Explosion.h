#pragma once
#include"Rect.h"
#include"Texture.h"
#include"Color.h"

#define MAX_EXPLOSION_COUNT 30

class Explosion : public Rect
{
private:
	//�e�N�X�`��
	unsigned int _texture;
public:
	//����������֐�
	int Initialize(const char* fileName,vec2 const& size);
	//�������J�n����֐�
	void Start(vec2 const& pos);
	//�X�V����֐�
	void Update() override;
	
	//�`��֐�
	void Draw() override;
	//�����̃G�t�F�N�g�����ł���܂ł̎���
	int _count;

	
};//class Explosion : public Rect

