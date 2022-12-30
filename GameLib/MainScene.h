#pragma once
#include "Scene.h"
#include"Ship.h"
#include"Font.h"

//�Q�[���I�[�o�[�̕\�����Ԃ̍ő�l
#define MAX_GAMEOVER_COUNT (60*4)

class MainScene : public Scene
{
private:
	//�Q�[���I�[�o�[�̕����̕\��
	int _gameOverCount;
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
	//�Q�[���I�[�o�[�̕����̕\�����擾����֐�
	int GetGameOverCount() { return _gameOverCount; }

};//class MainScene : public Scene, public Actor

