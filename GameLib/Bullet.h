#pragma once

//�e�̃N���X
class Bullet
{
public:
	Bullet();
	//������
	virtual int Initialize() = 0;
	//�e�̔��ˏ��
	bool _enable;
};//class Bullet