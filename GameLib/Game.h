#pragma once
#include"Actor.h"
#include"GameHeader.h"
#include"Scene.h"
#define MAX_SCORE 9999

//�\����ʂ̎��
enum SceneMode
{
	TITLE_SCENE,
	READY_SCENE,
	MAIN_SCENE,
	MAX_SCENE
};

class Game : public Actor
{
private:
	//�X�R�A
	int _score;
	//�n�C�X�R�A
	int _highScore;
	//���݂̃X�e�[�W
	int _currentStage;
	//�X�N���[���̕\����ԍ��Ŏ擾����ϐ�
	int _sceneOfIndex;
	//Scene�̏�Ԃ��擾����ϐ�
	Scene* _scenes[MAX_SCENE];
	//���݂�Scene
	Scene* _currentScene;
public:
	//�R���X�g���N�^
	Game();
	//Game������������֐�
	int Initialize();
	//�X�V����֐�
	void Update() override;
	//�`�悷��֐�
	void Draw() override;
	//�X�R�A��\��������֐�
	void DrawScore();
	//�X�R�A�𑝂₷�֐�
	void AddScore(int score);
	//�X�R�A���擾����֐�
	int GetScore() { return _score; }
	//�X�R�A��ݒ肷��֐�
	void SetScore(int score) { _score = score; }
	//�n�C�X�R�A���擾����֐�
	int GetHiScore() { return _highScore; }
	//�X�e�[�W�����Z�b�g����֐�
	void ResetStage();
	//���݂̃X�e�[�W���擾����֐�
	int GetCurrentStage() { return _currentStage; }
	//���݂̃X�e�[�W��ύX����
	void SetCurrentStage(int stage) { _currentStage = stage; }
	//Scene�̔ԍ����擾����֐�
	int GetSceneOfIndex() { return _sceneOfIndex; }
	//Scene�̏�Ԃ��擾����֐�
	Scene* GetCurrentScene() { return _currentScene; }
	//Scene��ݒ肷��֐�
	void SetScene(int scene);
	//�Q�[���I�[�o�[���𔻕ʂ���֐�
	bool isGameOver();
};//class Game

