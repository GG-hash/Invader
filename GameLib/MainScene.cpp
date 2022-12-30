#include "MainScene.h"


void MainScene::Initialize()
{

}//void MainScene::Initialize()


void MainScene::Update()
{
	//�G�̒e�̔����̃A�b�v�f�[�g
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		gInvaderBulletEx[i].Update();
	}
	//Ufo�̃A�b�v�f�[�g
	gUfo.Update();
	//Torchka�̃A�b�v�f�[�g
	Torchka::AllUpdate();
	//Ship�̒e�̃A�b�v�f�[�g
	gShipBulletEx.Update();
	//�G�̔����̃A�b�v�f�[�g
	gInvaderEx.Update();
	//Ship�̔����̃A�b�v�f�[�g
	gShipEx.Update();
	//Ship�̃A�b�v�f�[�g
	gShip.Update();
	//Ship�̔����̃A�b�v�f�[�g
	gShipBullet.Update();
	//�C���x�[�_�[�̍X�V
	Invader::AllUpdate();
	//�C���x�[�_�[�̒e�̍X�V
	InvaderBullet::AllUpdate();
	//Game�̃A�b�v�f�[�g
	gGame.Update();

	//�Q�[���I�[�o�[�̃J�E���^�𑝂₷������
	//Ship�̎c�@���S�ĂȂ��Ȃ�A��莞�Ԃ��o�߂�����
	//�^�C�g���֖߂�
	if ((gGame.isGameOver() == true)
		&& (++_gameOverCount >= MAX_GAMEOVER_COUNT))
	{
		gGame.SetScene(TITLE_SCENE);
		
	}//if (gShip.GetRemaningLives() <= 0)
	
}//void MainScene::Update()


void MainScene::Keyboard(unsigned char key)
{
	//�U��
	//j�������āA�Q�[���I�[�o�[�łȂ�
	//���j�̃A�j���[�V�����������C���x�[�_�[���o��������U���ł���
	if (key == 'j' 
		&& (gGame.isGameOver() == false)
		&& (gShipEx._count <= 0)
		&& (gInvaders[0][0].GetTurn() > 1))
	{
		//Ship���j���̒e�����ĂȂ�����
		if (gShipBulletEx._count <= 0)
			gShip.Shoot();
	}
}//void MainScene::Keyboard(unsigned char key)


void MainScene::Draw()
{
	//�X�R�A�̕`��
	gGame.DrawScore();

	//�c�@�̕\��
	gShip.DrawRemaningLives();
	//Ufo�̕`��
	gUfo.Draw();

	//�G�̒e�̔����̕`��
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		gInvaderBulletEx[i].Draw();
	}

	//Torchka�̕`��
	for (int i = 0; i < MAX_TORCHKA; i++)
	{
		gTorchka[i].Draw();
	}
	//�C���x�[�_�[�̔����̕`��
	gInvaderEx.Draw();
	//�C���x�[�_�[�̕`��
	Invader::AllDraw();
	//�C���x�[�_�[�̒e�̕`��
	InvaderBullet::AllDraw();

	//�e�Ŕ�������`��
	gShipBulletEx.Draw();

	//�e�̕`��
	gShipBullet.Draw();

	//Ship�̕`��
	gShip.Draw();

	//DestroyedTorchka

	//ShipExplosion�̕`��
	gShipEx.Draw();

	//�h�q�O���̕`��
	gLineOfDefence.Draw();

	if (gGame.isGameOver() == true)
	{
		//�Q�[���I�[�o�[���̕`��
		Colorub color;
		vec2 pos = vec2(SCREEN_WIDTH / 2 - DEFAULT_GAME_HEIGHT * 3, DEFAULT_GAME_HEIGHT * (3 + 2));
		const char* text = "GAME OVER";
		char str[10] = {};
		int strLength = std::min(_gameOverCount / 8, 10);
		strncpy_s(str, text, strLength);
		Text2D(pos.x, pos.y, color.Red, str);
	}//if (gGame.isGameOver() == true)

}//void MainScene::Draw()


void MainScene::Reset()
{
	//�ŏ��̃X�e�[�W�ɂ���
	gGame.SetCurrentStage(0);
	//�X�R�A�����Z�b�g����
	gGame.SetScore(0);
	//�X�e�[�W�̃��Z�b�g
	gGame.ResetStage();
	//�Q�[���I�[�o�[�̃J�E���^��0�ɂ���
	_gameOverCount = 0;
}//void MainScene::Reset()

