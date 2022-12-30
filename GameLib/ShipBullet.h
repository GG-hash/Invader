#pragma once
#include "Bullet.h"
#include"Rect.h"

#define SHIP_BULLET_WIDTH  1
#define SHIP_BULLET_HEIGHT 4
#define SHIP_BULLET_SPEED  4

class ShipBullet :public Bullet,
				  public Rect
{
private:
	//�e�N�X�`��
	unsigned int _texture;
public:
	ShipBullet();
	//������
	int Initialize() override;
	//�e�̔��ˏ��
	bool _enable;
	//�X�V����֐�
	void Update() override;
	void Draw() override;
};//class ShipBullet :public Bullet

