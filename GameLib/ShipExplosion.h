#pragma once
#include"Rect.h"
#include"Texture.h"
#include"Color.h"
#include"Audio.h"
//#include"Explosion.h"

#define SHIP_EXPLOSION_WIDTH   16
#define SHIP_EXPLOSION_HEIGHT   8
#define MAX_SHIP_EXPLOSION_ANIM 2
//2�b�ԃA�j���[�V�������Đ�����
#define MAX_SHIP_EXPLOSION_ANIM_COUNT (60 * 2)

class ShipExplosion : public Rect
{
private:
	//�e�N�X�`��
	unsigned int _textures[MAX_SHIP_EXPLOSION_ANIM];
	
public:
	ShipExplosion();
	//Ship�̔���������������֐�
	int Initialize();
	//�X�V����֐�
	void Update() override;
	//�`�悷��֐�
	void Draw() override;
	//�������J�n����֐�
	void Start(vec2 const& pos);
	//�����̃G�t�F�N�g�����ł���܂ł̎���
	int _count;
};//class ShipExplosion : public Rect

