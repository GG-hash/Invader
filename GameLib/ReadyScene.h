#pragma once
#include "Scene.h"

class ReadyScene : public Scene
{
private:
	//��������\��������J�E���^
	int _count;

public:
	//�R���X�g���N�^
	ReadyScene();
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
};//class ReadyScene : public Scene

