#include "Ufo.h"

Ufo::Ufo():_count(0)
			,_score(0)
			,_ufoX(SCREEN_WIDTH)
			, _textureIndex(-1)
{

}//Ufo::Ufo()

int Ufo::Initialize()
{
	//�T�C�Y�̐ݒ�
	vec2 size = vec2(UFO_WIDTH,UFO_HEIGHT);
	SetSize(size);
	
	//�e�N�X�`���̐���
	glGenTextures(MAX_UFO_TEXTURE, _textures);
	//�t�@�C����
	const char* fileName[MAX_UFO_TEXTURE] =
	{
		"image/ufo.bmp", //Ufo�̉摜
		"image/ufo_explosion.bmp"//Ufo�̔��j���̉摜
	};

	for (int i = 0; i < MAX_UFO_TEXTURE; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		//�t�@�C���̓ǂݍ���
		TextureFromBMP(fileName[i], 0x00, 0xff, 0x00);
	}
	

	return 0;
}//int Ufo::Initialize()


void Ufo::Update()
{
	//�Q�[���I�[�o�[�Ȃ�X�V���Ȃ�
	if ((gGame.isGameOver() == true))
	{
		//Ufo��BGM���~����
		AudioStop(AUDIO_CHANNEL_PULSE1);
		return;
	}// if (gShip.GetRemaningLives() <= 0)

	//�J�E���^��ǉ�����
	_count++;

	//���g����ω�������
	float fq = (float)sin((2 * M_PI * _count / 45) * 4);
	AudioFreq(AUDIO_CHANNEL_PULSE1, _freq * (float)pow(2,fq * 4/12));
	//��Ԃɂ���ď�����ύX����
	switch (_state)
	{
	case WAIT:
		if (_count >= UFO_WAIT_TIME)
		{
			//Ufo�̏o�������Ƃ��̉���炷
			AudioStop(AUDIO_CHANNEL_PULSE1);
			AudioWaveForm(AUDIO_CHANNEL_PULSE1, AUDIO_WAVEFORM_PULSE_50);
			_freq = 440;
			AudioFreq(AUDIO_CHANNEL_PULSE1, (float)_freq);
			AudioDecay(AUDIO_CHANNEL_PULSE1, 0.0f);
			AudioSweep(AUDIO_CHANNEL_PULSE1, 0.0f, 440 / 2);
			AudioPlay(AUDIO_CHANNEL_PULSE1);
			_count = 0;
			_state = UfoState::MOVE;
			//��ʒ[�֑ҋ@������
			GetPosition().x = SCREEN_WIDTH;
			
		}//if (_count >= 60)

		break;
	case SCORE:
		
		//1�b�ԕ\������
		if (_count > 60)
		{
			_state = UfoState::WAIT;
			_count = 0;
			//��ʒ[�֑ҋ@������
			GetPosition().x = SCREEN_WIDTH;
		}

		
		break;
	case MOVE:
		//Ship������������Ufo�̓������~�߂�
		if (gShipEx._count > 0)
		{
			break;
		}

		//Ufo���E���獶�ֈړ�������
		GetPosition().x -= UFO_SPEED;
		//ufo����ʊO�ɏo����Ufo���폜����
		if (GetPosition().x < -GetSize().x)
		{
			_state = UfoState::WAIT;
			_count = 0;
			//Ufo�o�ꎞ��BGM���~����
			AudioStop(AUDIO_CHANNEL_PULSE1);

		}//if (GetPosition().x < -GetSize().x)
		break;
	case EXPLOSION:
		//����������0.5�b�������j���̉摜��\��������
		if (_count > 30)
		{
			_ufoX = GetPosition().x;
			_state = UfoState::SCORE;
			_count = 0;
		}
		break;
	default:
		break;
	}


	
}//void Ufo::Update()


void Ufo::Reset()
{
	//�ʒu�̐ݒ�
	//�X�R�A�\���̉��ɏo��������
	vec2 pos = vec2(SCREEN_WIDTH, DEFAULT_GAME_HEIGHT * (3 + 1));
	SetPosition(pos);
	//Ufo�o�ꎞ��BGM���~����
	AudioStop(AUDIO_CHANNEL_PULSE1);
	_state = WAIT;
	_count = 0;
	
}//void Ufo::Reset()



void Ufo::Draw()
{
	_textureIndex = -1;
	//������̒���
	float length = 0.0f;
	//��Ԃɂ���ď�����ύX����
	switch (_state)
	{
	case WAIT:

		break;
	case SCORE:
		//�X�R�A�̕`��
		char str[24];
		sprintf_s(str, "%d", _score);
		//�X�R�A�̕������Z���^�����O����
		length = FontGetLength((unsigned char*)str);
		Text2D(_ufoX - (length -GetSize().x)/2.0f, GetPosition().y, "%d", _score);
		break;
	case MOVE:
		_textureIndex = TEXTURE_UFO;
		break;
	case EXPLOSION:
		_textureIndex = EXPLOSION_TEXTURE_UFO;
		break;
	default:
		break;
	}

	//textureIndex��0�ȏ�Ȃ�\��
	if (_textureIndex >= 0)
	{
		glBindTexture(GL_TEXTURE_2D, _textures[_textureIndex]);
		//�F�̐ݒ�
		SetColorWithPosition(GetPosition());
		Rect::Draw();
	}//if (textureIndex >= 0)
	
}//void Ufo::Draw()


void Ufo::Explosion()
{
	_count = 0;
	_state = UfoState::EXPLOSION;

	//Ufo�̃X�R�A�������_���Ō��߂�
	int score[MAX_UFO_SCORE] = {50,100,150,300};
	_score = score[rand() % MAX_UFO_SCORE];

	//�X�R�A�𑝂₷
	gGame.AddScore(_score);

	//����1�I�N�^�[�u������
	_freq = 440 / 2;

	AudioDecay(AUDIO_CHANNEL_PULSE1,0.95f);

}//void Ufo::Explosion()



