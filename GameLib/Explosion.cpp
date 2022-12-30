#include "Explosion.h"

int Explosion::Initialize(const char* fileName, vec2 const& size)
{
	SetSize(size);
	//テクスチャの生成
	glGenTextures(1, &_texture);
	//glGenTextures(1,&tex[TEX_SHIP].texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	_count = 0;

	//カラーキーを設定
	unsigned char colorkey[] = { 0x00,0xff,0x00 };
	TextureFromBMP(fileName, colorkey);
	return 0;
}//Explosion::Initialize(const char* fileName, vec2 const& size, unsigned char red, unsigned char green, unsigned char blue)

void Explosion::Start(vec2 const& pos)
{
	//位置の設定
	SetPosition(pos);
	_count = MAX_EXPLOSION_COUNT;
}//Explosion::Start(vec2 const& pos)

void Explosion::Update()
{
	//_countが0より大きければデクリメントする
	//アニメーションの表示時間を減らしていく
	if (_count > 0)
	{
		_count--;
	}
}//Explosion::Update()

void Explosion::Draw()
{
	//_countが0になったらエフェクトを消す
	if (_count <= 0)
	{
		return;
	}
	glBindTexture(GL_TEXTURE_2D, _texture);
	SetColorWithPosition(GetPosition());
	Rect::Draw();
}//Explosion::Draw()
