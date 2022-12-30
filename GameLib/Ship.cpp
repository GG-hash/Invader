#include "Ship.h"

int Ship::Initialize()
{
	//�����ʒu��ݒ肷��
	vec2 pos = vec2(SHIP_DEFAULT_X, SHIP_DEFAULT_Y);
	SetPosition(pos);
	//�摜�̑傫���ɍ��킹��
	vec2 size = vec2(SHIP_WIDTH,SHIP_HEIGHT);
	SetSize(size);

	//�c�@�̏�����
	_remaningLives = MAX_SHIP_LIVES;

	//�e�N�X�`���̐���
	glGenTextures(1,&_shipTexture);
	glBindTexture(GL_TEXTURE_2D,_shipTexture);
	//�J���[�L�[��ݒ�
	unsigned char colorkey[] = { 0x00,0xff,0x00 };
	TextureFromBMP("image/Ship.bmp",colorkey);


	return 0;
}//Ship::Initialize()

void Ship::Input(bool left, bool right, bool attack)
{
	//�V�[���ʂ̃L�[�{�[�h�̏���
	gGame.GetCurrentScene()->Keyboard(attack);

	if (left)
	{
		//��ʂ̒[�܂œ�����悤�ɂ���
		if (GetPosition().x > 0)
		{
			GetPosition().x--;
		}
	}
	if (right)
	{
		//��ʂ̒[�܂œ�����悤�ɂ���
		if (GetPosition().x + GetSize().x < SCREEN_WIDTH)
		{
			GetPosition().x++;
		}
	}
	

}//Ship::Input(bool left, bool right, bool attack)

void Ship::Shoot()
{
	//�e����ʓ��ɂ���Ύ��̃r�[���͌��ĂȂ�
	if (gShipBullet._enable == true)
	{
		return;
	}

	//�C������炷
	AudioStop(AUDIO_CHANNEL_PULSE0);
	AudioWaveForm(AUDIO_CHANNEL_PULSE0,AUDIO_WAVEFORM_PULSE_50);
	AudioFreq(AUDIO_CHANNEL_PULSE0, 440 * 8);
	AudioDecay(AUDIO_CHANNEL_PULSE0,0.92f);
	AudioSweep(AUDIO_CHANNEL_PULSE0,0.99f,440);
	AudioPlay(AUDIO_CHANNEL_PULSE0);

	AudioStop(AUDIO_CHANNEL_NOISE);
	AudioFreq(AUDIO_CHANNEL_NOISE, AudioIndexToFreq(0));
	AudioDecay(AUDIO_CHANNEL_NOISE, 0.92f);
	AudioSweep(AUDIO_CHANNEL_NOISE, 0.95f, AudioIndexToFreq(15));
	AudioPlay(AUDIO_CHANNEL_NOISE);

	gShipBullet._enable = true;
	vec2 pos = vec2(GetPosition().x + SHIP_WIDTH / 2, GetPosition().y - SHIP_BULLET_HEIGHT / 2);
	gShipBullet.SetPosition(pos);
}//Ship::Shoot()

void Ship::Update()
{
	//�ŏ��ɓo�ꂷ��C���x�[�_�̃^�[������1�ȉ���c�@���Ȃ��Ȃ�����Ȃ�
	//Ship�𓮂����Ȃ��悤�ɂ���
	if ((gInvaders[0][0].GetTurn() <= 1) 
		|| (gGame.isGameOver() == true))
	{
		return;
	}//if (gInvaders[0][0].GetTurn() <= 1)

	//Ship������������X�V���I������
	//_count > 0�Ȃ甚�j�̃A�j���[�V�������Đ������Ƃ������ƂȂ̂ŁA
	//���j�����Ƃ݂Ȃ���
	if (gShipEx._count > 0)
	{
		return;
	}

	//1500�_���Ƃ�1�@���₷ �ő��MAX_SHIP_LIVES
	if ((gGame.GetScore() % 1500 == 0)
		&& (gGame.GetScore() > 0))
	{
		_remaningLives++;
		if (_remaningLives > MAX_SHIP_LIVES)
		{
			_remaningLives = MAX_SHIP_LIVES;
		}

	}//if (gGame.GetScore() % 1500 == 0)

	//�v���C���[�ɂ����͏���
	Ship::Input(keys['a'],keys['d'],keys['j']);

}//Ship::Update()

void Ship::Draw()
{
	

	//�ŏ��ɓo�ꂷ��C���x�[�_�̃^�[������1�ȉ��Ȃ�
	//Ship�𓮂����Ȃ��悤�ɂ���
	if (gInvaders[0][0].GetTurn() <= 1
		|| (gGame.isGameOver() == true))
	{
		return;
	}//if (gInvaders[0][0].GetTurn() <= 1)

	//Ship������������X�V���I������
	//_count > 0�Ȃ甚�j�̃A�j���[�V�������Đ������Ƃ������ƂȂ̂ŁA
	//���j�����Ƃ݂Ȃ���
	if (gShipEx._count > 0)
	{
		return;
	}
	//Colorub�̎��̉�
	Colorub colorUb;
	glBindTexture(GL_TEXTURE_2D, _shipTexture);
	glColor3ubv(colorUb.LightBlue);
	//SetColorWithPosition(GetPosition());
	Rect::Draw();
}//Ship::Draw()

void Ship::Draw(vec2 const& pos)
{
	//�e�N�X�`���̓\��t���A�ʒu�ƃT�C�Y 

	//Colorub�̎��̉�
	Colorub colorUb;
	glBindTexture(GL_TEXTURE_2D, _shipTexture);
	glColor3ubv(colorUb.LightBlue);
	//SetColorWithPosition(GetPosition());
	Rect rect(pos,GetSize());
	rect.Draw();
}//void Ship::Draw(vec2 const& pos)

void Ship::DrawRemaningLives()
{
	//�\�����镶���̃T�C�Y
	vec2 size = vec2(5, DEFAULT_GAME_HEIGHT);
	//�c�@�̕\��
	Text2D(1 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 31, size, "%d", GetRemaningLives());
	for (int i = 0; i < GetRemaningLives() - 1; i++)
	{

		//Colorub�̎��̉�
		Colorub color;
		vec2 pos = vec2(DEFAULT_GAME_HEIGHT * 3 + (SHIP_WIDTH + 2) * i,
			DEFAULT_GAME_HEIGHT * 31);
		DrawTexture(pos, GetSize(), GetTexture(), color.LightBlue);
		//gShip.Draw(pos);
	}//for (int i = 0; i < gShip.GetRemaningLives() - 1; i++)
}//void Ship::DrawRemaningLives()

void Ship::Reset()
{
	//�ʒu������������
	vec2 pos = vec2(SHIP_DEFAULT_X, SHIP_DEFAULT_Y);
	SetPosition(pos);
}//void Ship::Reset()



