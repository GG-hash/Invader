#include "TitleScene.h"
#include<iostream>

//TitleText�̍\���̂̃C���X�^���X
static TitleText gTexts[] = { 
	{"PLAY"           ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 3), DEFAULT_GAME_HEIGHT *  7)},
	{"SPACE  INVADERS",vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 7), DEFAULT_GAME_HEIGHT *  9)},
	{"=? MYSTERY "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 15)},
	{"=30 POINTS "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 17)},
	{"=20 POINTS "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 19)},
	{"=10 POINTS "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 21)},

};

//�ő�̃^�C�g���̃e�L�X�g��
#define MAX_TITLE_TEXT (sizeof(gTexts)/sizeof(TitleText))


void TitleScene::Initialize()
{
	//�e������̕��������i�[����ϐ�
	int total = 0;

	for (int i = 0; i < MAX_TITLE_TEXT; i++)
	{
		//���������J�E���g���āA_startCount�֑������
		gTexts[i]._startCount = total;
		total += strlen(gTexts[i]._str);
	}
}//void TitleScene::Initialize()


void TitleScene::Update()
{
	_count++;
}//void TitleScene::Update()


void TitleScene::Keyboard(unsigned char key)
{
	gGame.SetScene(READY_SCENE);
}//void TitleScene::Keyboard(unsigned char key)


void TitleScene::Draw()
{
	//�J�E���^�̒l�𒲐�����
	//1�b�Ԃ�10�J�E���g�i��
	int count = _count / (60 / 10);

	//�X�R�A�̕`��
	gGame.DrawScore();
	//�^�C�g����ʂ̕`��
	//�摜��Ufo��_startCount�Ɠ����^�C�~���O�ŏo������
	

	Colorub color;
	//�E�ɂ��낦��
	float rightOffset = DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 6);

	//�摜��Ufo��_startCount�Ɠ����^�C�~���O�ŏo������///////
	if (count >= gTexts[2]._startCount)
	{
		//�^�C�g��
	//�������Ȃ��e�L�X�g
		Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 9), DEFAULT_GAME_HEIGHT * 11, "*SCORE ADVANCE TABLE*");
		//�������e�L�X�g
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 3),DEFAULT_GAME_HEIGHT * 7,"PLAY");
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 7),DEFAULT_GAME_HEIGHT * 9,"SPACE  INVADERS");
		//Ufo�̕`��
		vec2 pos = vec2(rightOffset - gUfo.GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 15);
		vec2 size = gUfo.GetSize();
		DrawTexture(pos, size, gUfo.GetTexture(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 15, "=? MYSTERY ");


		//�C�J�^�̃C���x�[�_�[
		pos = vec2(rightOffset - gInvaders[4][0].GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 17);
		size = gInvaders[4][0].GetSize();
		DrawTexture(pos, size, gInvaders[4][0].GetTextures(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 17, "=30 POINTS ");

		//�J�j�^�̃C���x�[�_�[
		pos = vec2(rightOffset - gInvaders[2][0].GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 19);
		size = gInvaders[2][0].GetSize();
		DrawTexture(pos, size, gInvaders[2][0].GetTextures(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 19, "=20 POINTS ");

		//�^�R�^�̃C���x�[�_�[
		pos = vec2(rightOffset - gInvaders[0][0].GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 21);
		size = gInvaders[0][0].GetSize();
		DrawTexture(pos, size, gInvaders[0][0].GetTextures(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 21, "=10 POINTS ");
	}//if (count >= gTexts[2]._startCount)
	

		//�e�L�X�g�̕\��
		//�ꕶ�����\��������
		for (int i = 0; i < MAX_TITLE_TEXT; i++)
		{
			//�����̃J�E���g���n�܂�܂ŁA�e�L�X�g��\�������Ȃ�
			if (count < gTexts[i]._startCount)
			{
				break;
			}

			//�\�����镶����
			int strLength = std::min(count - gTexts[i]._startCount, (int)strlen(gTexts[i]._str));

			char str[MAX_TEXT] = {};
			//������̃R�s�[
			strncpy_s(str, gTexts[i]._str, strLength);

			//�e�L�X�g�̈ʒu
			float x = gTexts[i]._pos.x;
			float y = gTexts[i]._pos.y;

			//�e�L�X�g�̕\��
			Text2D(x, y, str);

		}//for (int i = 0; i < MAX_TITLE_TEXT; i++)
	

}//void TitleScene::Draw()


void TitleScene::Reset()
{
	//�J�E���^�����Z�b�g����
	_count = 0;
	//�v���C���[�̎c�@�����Z�b�g����
	gShip.SetRemaningLives(MAX_SHIP_LIVES);
	//�X�R�A�����Z�b�g����
	gGame.SetScore(0);
}//void TitleScene::Reset()

