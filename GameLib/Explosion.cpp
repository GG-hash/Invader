#include "Explosion.h"

int Explosion::Initialize(const char* fileName, vec2 const& size)
{
	SetSize(size);
	//�e�N�X�`���̐���
	glGenTextures(1, &_texture);
	//glGenTextures(1,&tex[TEX_SHIP].texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	_count = 0;

	//�J���[�L�[��ݒ�
	unsigned char colorkey[] = { 0x00,0xff,0x00 };
	TextureFromBMP(fileName, colorkey);
	return 0;
}//Explosion::Initialize(const char* fileName, vec2 const& size, unsigned char red, unsigned char green, unsigned char blue)

void Explosion::Start(vec2 const& pos)
{
	//�ʒu�̐ݒ�
	SetPosition(pos);
	_count = MAX_EXPLOSION_COUNT;
}//Explosion::Start(vec2 const& pos)

void Explosion::Update()
{
	//_count��0���傫����΃f�N�������g����
	//�A�j���[�V�����̕\�����Ԃ����炵�Ă���
	if (_count > 0)
	{
		_count--;
	}
}//Explosion::Update()

void Explosion::Draw()
{
	//_count��0�ɂȂ�����G�t�F�N�g������
	if (_count <= 0)
	{
		return;
	}
	glBindTexture(GL_TEXTURE_2D, _texture);
	SetColorWithPosition(GetPosition());
	Rect::Draw();
}//Explosion::Draw()
