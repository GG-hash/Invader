#pragma once
#include"Actor.h"

class Scene : public Actor
{
private:

public:
	//������
	virtual void Initialize() = 0;
	//�X�V����֐�
	void Update() override;
	//�v���C���[�̓��͏���������֐�
	virtual void Keyboard(unsigned char key) = 0;
	//���Z�b�g����֐�
	virtual void Reset() = 0;

};//class Scene


