#include "LineOfDefence.h"

LineOfDefence::LineOfDefence()
{
	

}//LineOfDefence::LineOfDefence()


int LineOfDefence::Initialize()
{
	//�����ʒu �X�N���[���̍��������s��( 8 )�������āA�X��1�s�N�Z������
	vec2 pos = vec2(0, SCREEN_HEIGHT - 8 - 1);
	SetPosition(pos);

	//�T�C�Y�̐ݒ�
	vec2 size = vec2(SCREEN_WIDTH,1);
	SetSize(size);

	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		//�����ŕ`��
		_texturePixels[i] = 0xff;
		//�j���ŕ`��
		//_texturePixels[i] = (i%2)?0xff : 0x00;

	}//for (int i = 0; i < SCREEN_WIDTH; i++)

	//�e�N�X�`���̐���
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);


	//�g�厞�̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //�摜���g�債���Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);
	//�k�����̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //�摜���k�������Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);

	//�N�����v�̐ݒ�@�摜�̈�ԉ��̃f�[�^���摜�̈�ԏ�̃f�[�^���Q�Ƃ��Ȃ��悤�ɂ���
	//���̃N�����v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//�c�̃N�����v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	return 0;
}//int LineOfDefence::Initialize()


void LineOfDefence::Update()
{
}//void LineOfDefence::Update()


void LineOfDefence::Draw()
{
	//�`��
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, SCREEN_WIDTH, 1,
		0, GL_ALPHA, GL_UNSIGNED_BYTE, _texturePixels);
	SetColorWithPosition(GetPosition());
	Rect::Draw();
}
//void LineOfDefence::Draw()

void LineOfDefence::EraseLine(int x)
{
	//�͈͊O�̕`��͂��Ȃ�
	if ((0 > x) && (SCREEN_WIDTH <= x))
	{
		return;
	}

	//��������
	_texturePixels[x] = 0;
}//void LineOfDefence::EraseLine(float x)

