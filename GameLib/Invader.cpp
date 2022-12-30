#include "Invader.h"

//static�ϐ��̎��Ԃ̒�`
vec2 Invader::_invaderSpeed = vec2(DEFAULT_INVADER_SPEED, 0);
vec2 Invader::_nextSpeed = vec2(DEFAULT_INVADER_SPEED, 0);
int Invader::_current;
//BGM�̃J�E���g
int Invader::_bgmCount;
//���݂̉�
int Invader::_bgmCurrent;

//�C���x�[�_�[���i�[����z��
class Invader gInvaders[MAX_INVADER_ROW][MAX_INVADER_COLUMN];

Invader::Invader():_isDead(false)
{

}//Invader::Invader()


int Invader::Initialize(const char* fileName0, const char* fileName1, vec2 size, vec2 pos)
{
	SetSize( size);
	SetPosition(pos);
	//Invader::GetPosition() = Rect::GetPosition();
	_animNo = 0;
	//�e�N�X�`���̐���
	glGenTextures(MAX_INVADER_ANIM, _textures);
	glBindTexture(GL_TEXTURE_2D, _textures[0]);
	//�J���[�L�[��ݒ�
	unsigned char colorkey[] = { 0x00,0xff,0x00 };
	TextureFromBMP(fileName0, colorkey);

	glBindTexture(GL_TEXTURE_2D, _textures[1]);
	TextureFromBMP(fileName1, colorkey);

	//�^�[���̏�����
	_turn = 0;

    return 0;
}
//Invader::Initialize(const char* fileName0, const char* fileName1, vec2 size, vec2 pos)

int Invader::AllInitialize()
{
	//�C���x�[�_�[�̏�����
	//�擪���������������邱�ƂŃR�s�[���đ�������
	gInvaders[0][0].Initialize("image/invader0-0.bmp", "image/invader0-1.bmp", vec2(12, INVADER_HEIGHT));
	//�X�R�A�̐ݒ�
	gInvaders[0][0]._score = 10;
	for (int i = 0; i <= FIRST_ROW_INVADER; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			gInvaders[i][j] = gInvaders[0][0];
		}
	}

	gInvaders[2][0].Initialize("image/Invader1-0.bmp", "image/Invader1-1.bmp", vec2(11, INVADER_HEIGHT));
	//�X�R�A�̐ݒ�
	gInvaders[2][0]._score = 20;

	for (int i = FIRST_ROW_INVADER + 1; i <= SECOND_ROW_INVADER; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			gInvaders[i][j] = gInvaders[2][0];
		}
	}

	gInvaders[4][0].Initialize("image/invader2-0.bmp", "image/invader2-1.bmp", vec2(8 , INVADER_HEIGHT));
	//�X�R�A�̐ݒ�
	gInvaders[4][0]._score = 30;
	for (int i = 0; i <= MAX_INVADER_COLUMN; i++)
	{
		gInvaders[4][i] = gInvaders[4][0];
	}

	//�I�t�Z�b�g �C���x�[�_�[����ʂ̍��[��菭���Ԋu�������đ�������
	float offset = DEFAULT_INVADER_INTERVAL * 3;

	//�C���x�[�_�[�̑�����쐬����
	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			
			//�Z���^�����O���s��
			//�X�e�[�W���i�ނ��ƂɃC���x�[�_�[�̏����ʒu���ō�8��O�i����
			vec2 pos = vec2(offset + j * DEFAULT_INVADER_INTERVAL * 2 - (gInvaders[i][j].GetSize().x - DEFAULT_INVADER_INTERVAL) / 2.0f
				          , INVADER_HEIGHT * (SCORE_HEIGHT + FROM_SCORE_TO_INVADER + MAX_INVADER_ROW * 2 + (gGame.GetCurrentStage() % 8)) - INVADER_HEIGHT * i * 2);
			gInvaders[i][j].SetPosition(pos);
		}
	}


	return 0;
}//Invader::AllInitialize()


void Invader::Reset()
{
	_animNo = 0;
	_isDead = false;
	_turn = 0;
}//void Invader::Reset()


void Invader::AllReset()
{
	//���݂̃C���x�[�_�[������������
	_current = 0;

	//�I�t�Z�b�g �C���x�[�_�[����ʂ̍��[��菭���Ԋu�������đ�������
	float offset = DEFAULT_INVADER_INTERVAL * 3;
	//�C���x�[�_�[�̑�����쐬����
	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			//�Z���^�����O���s��
			vec2 pos = vec2(offset + j * DEFAULT_INVADER_INTERVAL * 2 - (gInvaders[i][j].GetSize().x - DEFAULT_INVADER_INTERVAL) / 2.0f
				, INVADER_HEIGHT * (SCORE_HEIGHT + FROM_SCORE_TO_INVADER + MAX_INVADER_ROW * 2 + (gGame.GetCurrentStage() % 8)) - INVADER_HEIGHT * i * 2);
			gInvaders[i][j].SetPosition(pos);
			gInvaders[i][j].Reset();
			gInvaders[i][j]._animNo = 0;
			gInvaders[i][j]._isDead = false;
			gInvaders[i][j]._turn = 0;
		}
	}
}//void Invader::AllReset()



void Invader::Update()
{
	//0�^�[���ڂȂ�Ή������Ȃ�
	if (_turn++ < 1)
	{
		return;
	}

	++_animNo %= MAX_INVADER_ANIM;
	GetPosition() += Invader::_invaderSpeed;

	//printf("In X : %f\n", _invaderSpeed.x);
	//printf("In Y : %f\n", _invaderSpeed.y);

	//�C���x�[�_�[����ʒ[�֍s�������̏���
	//�E�[�̏���
	if ((GetPosition().x >= SCREEN_WIDTH - GetSize().x * 2 - DEFAULT_INVADER_SPEED) && (_invaderSpeed.x > 0))
	{
		_nextSpeed = vec2(-DEFAULT_INVADER_SPEED, INVADER_HEIGHT);
	}
	//�E�[�̏���
	if ((GetPosition().x < DEFAULT_INVADER_SPEED) && (_invaderSpeed.x < 0))
	{
		_nextSpeed = vec2(DEFAULT_INVADER_SPEED, INVADER_HEIGHT);
	}

}
//Invader::Update()

void Invader::AllUpdate()
{

	//�G���������Ă���Ԃ�Ship���������Ă���ԁAShip�̎c�@��0�̏ꍇ�͌R���̓������~�߂�
	if ((Invader::GetCountAlives() <= 0) 
		|| (gShipEx._count > 0)
		|| (gGame.isGameOver() == true))
	{
		return;
	}//if ((Invader::GetCountAlives() <= 0))
	
	//BGM�������Ȃ肷���邱�Ƃ�h�~���� �G��5�̈ȉ��Ȃ炱��ȏ�BGM�𑁂����Ȃ�
	int BgmPhase = Invader::GetCountAlives() > 5 ? Invader::GetCountAlives() : 5;
	
	if (++_bgmCount >= BgmPhase)
	{
		_bgmCount = 0;
		//BGM��炷
		AudioStop(AUDIO_CHANNEL_TRIANGLE);
		AudioWaveForm(AUDIO_CHANNEL_TRIANGLE, AUDIO_WAVEFORM_PULSE_50);
		//�L�[�̃f�[�^���i�[����z��
		int bgmKey[] = {0,-2,-3,2};
		AudioFreq(AUDIO_CHANNEL_TRIANGLE, 440.0f / 4.0f * pow(2.0f, bgmKey[_bgmCurrent] / 12.0f));

		AudioDecay(AUDIO_CHANNEL_TRIANGLE, 0.9f);
		AudioPlay(AUDIO_CHANNEL_TRIANGLE);
		++_bgmCurrent %= MAX_INVADER_BGM_PHASE;
	}//if (++_bgmCount >= BgmPhase)


	//�S�ł̏ꍇ�́A�R���̓������~�߂�
	if (gInvaderEx._count > 0)
	{
		return;
	}

	//���Ă��ꂽ�G�̍X�V���΂�
	while (_current > MAX_INVADER || gInvaders[_current / MAX_INVADER_COLUMN][_current % MAX_INVADER_COLUMN]._isDead == true)
	{
		//_current���z�񐔂�����Ȃ��悤�ɂ���
		if (_current > MAX_INVADER)
		{
			//printf("���ړ�\n");
			_current = 0;
			SetSpeed(_nextSpeed);
			//printf("����������Ƃ���Y : %f\n", _invaderSpeed.y);
			//printf("����������Ƃ���nextY : %f\n", _nextSpeed.y);
			_nextSpeed.y = 0.0f;
		}
		else
		{
			_current++;
		}
	}
	//���̃C���x�[�_�[�̗��S�ăA�b�v�f�[�g������A���̗�֍s��
	gInvaders[_current / MAX_INVADER_COLUMN][_current % MAX_INVADER_COLUMN].Update();
	
	_current++;

	//�e�𔭎˂��鏈�� ////////////////////////////////////////
	//Ship���o�����͍U�����ł��Ȃ�
	if (gInvaders[0][0]._turn > 1)
	{
		//��̂ɂ�2���܂őłĂ�
		for (int i = 0; i < MAX_INVADER_BULLET; i++)
		{
			//�G�������ɂȂ�����G���e��2�����悤�ɂ���

			//�G�̐��������ȏ�c���Ă���A�e���ꔭ�ł������Ă�����
			//�������΂�
			if ((GetCountAlives() >= MAX_INVADER / 2.0f)
				&& (InvaderBullet::GetShootingCount() > 0))
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++)

			//�����_���ɓG����e�𔭎˂�����
			int randNum = rand() % MAX_INVADER;
			int invaderRow = randNum / MAX_INVADER_COLUMN;
			int invaderColumn = randNum % MAX_INVADER_COLUMN;

			Invader* owner = &gInvaders[invaderRow][invaderColumn];

			//�I������Ă����C���x�[�_�[�����Ă���Ă���A
			//�������͒e�������Ă����ԂȂ�e�������Ȃ�(�e�̐����̏������΂�)
			if ((owner->_isDead == true) || (owner->isShooting()))
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++) �֖߂�


			//�O�̗�ɑ��̃C���x�[�_�[�����Ȃ���Βe�𔭎�
			bool stopShoot = false;
			for (int i = invaderRow - 1; 0 <= i; i--)
			{
				//����񕪂�����������
				if (gInvaders[i][invaderColumn]._isDead == false)
				{
					stopShoot = true;
					break;
				}//if (gInvaders[i][invaderColumn]._isDead == false)
			}//for (int i = invaderRow - 1; 0 <= i; i--)

			//�e�̔��˂��~���Ă����珈�����΂�
			if (stopShoot == true)
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++)�֖߂�

			//�e�̐��� ���̍U���ɂ�MAX_INVADER_BULLET�񕪒e�𐶐�����
			InvaderBullet* invaderBullet = &gInvaderBullets[i];

			//�e�̑ҋ@��Ԃ��L���Ȃ珈�����΂�
			if (invaderBullet->_enable == true)
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++)�֖߂�

			//�摜��x���W��������y���W�����ˌ��Əd�Ȃ�悤�ɍ��W�𒲐�����
			vec2 pos = vec2(owner->GetPosition().x + (owner->GetSize().x - invaderBullet->GetSize().x) / 2.0f,
				owner->GetPosition().y + owner->GetSize().y);
			//�U��
			invaderBullet->Attack(pos, owner);



		}//for(int i=0;i<MAX_INVADER_BULLET;i++)
	}//if(_turn > 1)
	///////////////////////////////////////////////////////////////////////
		
}//Invader::AllUpdate()

void Invader::Draw()
{
	//�����|����Ă���A�܂���_turn��1�����Ȃ�C���x�[�_�[�̓o��V�[�����쐬����ו`�悵�Ȃ�
	if ((_isDead) || (_turn < 1))
	{
		return;
	}
	glBindTexture(GL_TEXTURE_2D, _textures[_animNo]);
	SetColorWithPosition(GetPosition());
	Rect::Draw();
	
}
//Invader::Draw()

void Invader::AllDraw()
{
	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			gInvaders[i][j].Draw();
		}
	}
}//Invader::AllDraw()

bool Invader::isShooting()
{
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		InvaderBullet* inBul = &gInvaderBullets[i];

		//�e�̔��˂��L���ł���A���˂��Ă��鏊�L�҂������Ȃ�true��Ԃ�
		if ((inBul->_enable) && (inBul->GetOwner() == this))
		{
			return true;
		}
	}

	return false;
}//bool Invader::isShooting()


int Invader::GetCountAlives()
{
	int count = 0;

	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			if (gInvaders[i][j]._isDead == false)
			{
				count++;
			}
		}
	}

	return count;
}//int Invader::GetCountAlives()
