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
	//弾が打たれているか判定
	if (!_enable)
	{
		return;
	}
	this->Rect::GetPosition().y -= SHIP_BULLET_SPEED;

	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			//インベーダーに弾が当たった時の処理
			//インベーダーに弾が当たり、倒されていなければ撃墜される
			if (gInvaders[i][j].IntersectRect(Rect::GetPosition()) && (gInvaders[i][j]._isDead == false))
			{
				//撃退音を鳴らす
				AudioStop(AUDIO_CHANNEL_PULSE0);
				AudioWaveForm(AUDIO_CHANNEL_PULSE0, AUDIO_WAVEFORM_PULSE_50);
				AudioFreq(AUDIO_CHANNEL_PULSE0, 440 * 2);
				AudioDecay(AUDIO_CHANNEL_PULSE0, 0.9f);
				AudioSweep(AUDIO_CHANNEL_PULSE0, 0.9f, 440 / 2);
				AudioPlay(AUDIO_CHANNEL_PULSE0);
				//スコアを増やす
				gGame.AddScore(gInvaders[i][j].GetScore());
				//isDeadをtrueにする
				gInvaders[i][j]._isDead = true;

				//弾が敵に当たったら、弾を消す
				_enable = false;

				gInvaderEx.Start(gInvaders[i][j].GetPosition() - (gInvaderEx.GetSize() - gInvaders[i][j].GetSize()) / 2.0f);
			}//if (gInvaders[i][j].IntersectRect(_pos))



		}//for (int j = 0; j < MAX_INVADER_COLUMN; j++)
	}//for (int i = 0; i < MAX_INVADER_ROW; i++)

	//インベーダーの弾に当たった時の処理
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		if (gInvaderBullets[i].IntersectRect(GetPosition())
			&& gInvaderBullets[i]._enable == true)
		{
			//インベーダーの弾を消す
			gInvaderBullets[i]._enable = false;
			//インベーダーの弾の爆破
			//爆発の位置を計算する
			vec2 pos = vec2(GetPosition().x - (gInvaderBulletEx[gInvaderBullets[i]._index].GetSize().x - GetSize().x)
				, GetPosition().y);
			//爆発のアニメーションを再生
			gInvaderBulletEx[gInvaderBullets[i]._index].Start(pos);
			//Shipの弾を消す
			_enable = false;
			//Shipの弾を爆破
			gShipBulletEx.Start(Rect::GetPosition() - gShipBulletEx.GetSize() / 2.0f);
		}//if (gInvaderBullets[i].IntersectRect(GetPosition()) && gInvaderBullets[i]._enable == true)
	}//for (int i = 0; i < MAX_INVADER_BULLET; i++)


	//UfoにShipの弾が当たった時の処理
	//スコア表示の時は当たり判定を処理しない
	if (gUfo.IntersectRect(GetPosition()) && gUfo.GetState() != SCORE)
	{
		//弾を消す
		_enable = false;
		//Ufoを爆発させる
		gUfo.Explosion();

	}//if (gUfo.IntersectRect(GetPosition())

	//ビームが画面外に出たら消す処理
	//UI表示の為適切な幅を開ける
	float deleteLine = DEFAULT_GAME_HEIGHT * 3;
	if (Rect::GetPosition().y < deleteLine)
	{
		_enable = false;
		gShipBulletEx.Start(Rect::GetPosition() - gShipBulletEx.GetSize() / 2.0f);
	}//if (Rect::GetPosition().y < deleteLine)
}//ShipBullet::Update()


void ShipBullet::Draw()
{
	//弾が打たれているか判定
	if (!_enable)
	{
		return;
	}
	//Colorubの実体化
	Colorub colorUb;
	glBindTexture(GL_TEXTURE_2D, _texture);
	//SetColorWithPosition(GetPosition());
	glColor3ubv(colorUb.White);
	Rect::Draw();
}
//ShipBullet::Draw()
