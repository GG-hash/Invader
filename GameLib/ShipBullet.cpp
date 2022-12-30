#include "ShipBullet.h"
#include"Texture.h"
#include"Invader.h"
#include"Audio.h"
#include"GameHeader.h"
ShipBullet::ShipBullet() :_texture(0)
					     ,_enable(false)
{

}//ShipBullet::Bullet()

int ShipBullet::Initialize()
{
	vec2 size = vec2(SHIP_BULLET_WIDTH, SHIP_BULLET_HEIGHT);
	Rect::SetSize(size);

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	TextureFromBMP("bullet.bmp", 0x00, 0xff, 0x00);

	return 0;
} //ShipBullet::Initialize()



void ShipBullet::Update()
{
	//�e���ł���Ă��邩����
	if (!_enable)
	{
		return;
	}
	this->Rect::GetPosition().y -= SHIP_BULLET_SPEED;

	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			//�C���x�[�_�[�ɒe�������������̏���
			//�C���x�[�_�[�ɒe��������A�|����Ă��Ȃ���Ό��Ă����
			if (gInvaders[i][j].IntersectRect(Rect::GetPosition()) && (gInvaders[i][j]._isDead == false))
			{
				//���މ���炷
				AudioStop(AUDIO_CHANNEL_PULSE0);
				AudioWaveForm(AUDIO_CHANNEL_PULSE0, AUDIO_WAVEFORM_PULSE_50);
				AudioFreq(AUDIO_CHANNEL_PULSE0, 440 * 2);
				AudioDecay(AUDIO_CHANNEL_PULSE0, 0.9f);
				AudioSweep(AUDIO_CHANNEL_PULSE0, 0.9f, 440 / 2);
				AudioPlay(AUDIO_CHANNEL_PULSE0);
				//�X�R�A�𑝂₷
				gGame.AddScore(gInvaders[i][j].GetScore());
				//isDead��true�ɂ���
				gInvaders[i][j]._isDead = true;

				//�e���G�ɓ���������A�e������
				_enable = false;

				gInvaderEx.Start(gInvaders[i][j].GetPosition() - (gInvaderEx.GetSize() - gInvaders[i][j].GetSize()) / 2.0f);
			}//if (gInvaders[i][j].IntersectRect(_pos))



		}//for (int j = 0; j < MAX_INVADER_COLUMN; j++)
	}//for (int i = 0; i < MAX_INVADER_ROW; i++)

	//�C���x�[�_�[�̒e�ɓ����������̏���
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		if (gInvaderBullets[i].IntersectRect(GetPosition())
			&& gInvaderBullets[i]._enable == true)
		{
			//�C���x�[�_�[�̒e������
			gInvaderBullets[i]._enable = false;
			//�C���x�[�_�[�̒e�̔��j
			//�����̈ʒu���v�Z����
			vec2 pos = vec2(GetPosition().x - (gInvaderBulletEx[gInvaderBullets[i]._index].GetSize().x - GetSize().x)
				, GetPosition().y);
			//�����̃A�j���[�V�������Đ�
			gInvaderBulletEx[gInvaderBullets[i]._index].Start(pos);
			//Ship�̒e������
			_enable = false;
			//Ship�̒e�𔚔j
			gShipBulletEx.Start(Rect::GetPosition() - gShipBulletEx.GetSize() / 2.0f);
		}//if (gInvaderBullets[i].IntersectRect(GetPosition()) && gInvaderBullets[i]._enable == true)
	}//for (int i = 0; i < MAX_INVADER_BULLET; i++)


	//Ufo��Ship�̒e�������������̏���
	//�X�R�A�\���̎��͓����蔻����������Ȃ�
	if (gUfo.IntersectRect(GetPosition()) && gUfo.GetState() != SCORE)
	{
		//�e������
		_enable = false;
		//Ufo�𔚔�������
		gUfo.Explosion();

	}//if (gUfo.IntersectRect(GetPosition())

	//�r�[������ʊO�ɏo�����������
	//UI�\���̈דK�؂ȕ����J����
	float deleteLine = DEFAULT_GAME_HEIGHT * 3;
	if (Rect::GetPosition().y < deleteLine)
	{
		_enable = false;
		gShipBulletEx.Start(Rect::GetPosition() - gShipBulletEx.GetSize() / 2.0f);
	}//if (Rect::GetPosition().y < deleteLine)
}//ShipBullet::Update()


void ShipBullet::Draw()
{
	//�e���ł���Ă��邩����
	if (!_enable)
	{
		return;
	}
	//Colorub�̎��̉�
	Colorub colorUb;
	glBindTexture(GL_TEXTURE_2D, _texture);
	//SetColorWithPosition(GetPosition());
	glColor3ubv(colorUb.White);
	Rect::Draw();
}
//ShipBullet::Draw()
