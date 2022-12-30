#include "Ship.h"

int Ship::Initialize()
{
	//初期位置を設定する
	vec2 pos = vec2(SHIP_DEFAULT_X, SHIP_DEFAULT_Y);
	SetPosition(pos);
	//画像の大きさに合わせる
	vec2 size = vec2(SHIP_WIDTH,SHIP_HEIGHT);
	SetSize(size);

	//残機の初期化
	_remaningLives = MAX_SHIP_LIVES;

	//テクスチャの生成
	glGenTextures(1,&_shipTexture);
	glBindTexture(GL_TEXTURE_2D,_shipTexture);
	//カラーキーを設定
	unsigned char colorkey[] = { 0x00,0xff,0x00 };
	TextureFromBMP("image/Ship.bmp",colorkey);


	return 0;
}//Ship::Initialize()

void Ship::Input(bool left, bool right, bool attack)
{
	//シーン別のキーボードの処理
	gGame.GetCurrentScene()->Keyboard(attack);

	if (left)
	{
		//画面の端まで動けるようにする
		if (GetPosition().x > 0)
		{
			GetPosition().x--;
		}
	}
	if (right)
	{
		//画面の端まで動けるようにする
		if (GetPosition().x + GetSize().x < SCREEN_WIDTH)
		{
			GetPosition().x++;
		}
	}
	

}//Ship::Input(bool left, bool right, bool attack)

void Ship::Shoot()
{
	//弾が画面内にあれば次のビームは撃てない
	if (gShipBullet._enable == true)
	{
		return;
	}

	//砲撃音を鳴らす
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
	//最初に登場するインベーダのターン数が1以下や残機がなくなったらなら
	//Shipを動かせないようにする
	if ((gInvaders[0][0].GetTurn() <= 1) 
		|| (gGame.isGameOver() == true))
	{
		return;
	}//if (gInvaders[0][0].GetTurn() <= 1)

	//Shipが爆発したら更新を終了する
	//_count > 0なら爆破のアニメーションが再生されるということなので、
	//爆破したとみなせる
	if (gShipEx._count > 0)
	{
		return;
	}

	//1500点ごとに1機増やす 最大はMAX_SHIP_LIVES
	if ((gGame.GetScore() % 1500 == 0)
		&& (gGame.GetScore() > 0))
	{
		_remaningLives++;
		if (_remaningLives > MAX_SHIP_LIVES)
		{
			_remaningLives = MAX_SHIP_LIVES;
		}

	}//if (gGame.GetScore() % 1500 == 0)

	//プレイヤーによる入力処理
	Ship::Input(keys['a'],keys['d'],keys['j']);

}//Ship::Update()

void Ship::Draw()
{
	

	//最初に登場するインベーダのターン数が1以下なら
	//Shipを動かせないようにする
	if (gInvaders[0][0].GetTurn() <= 1
		|| (gGame.isGameOver() == true))
	{
		return;
	}//if (gInvaders[0][0].GetTurn() <= 1)

	//Shipが爆発したら更新を終了する
	//_count > 0なら爆破のアニメーションが再生されるということなので、
	//爆破したとみなせる
	if (gShipEx._count > 0)
	{
		return;
	}
	//Colorubの実体化
	Colorub colorUb;
	glBindTexture(GL_TEXTURE_2D, _shipTexture);
	glColor3ubv(colorUb.LightBlue);
	//SetColorWithPosition(GetPosition());
	Rect::Draw();
}//Ship::Draw()

void Ship::Draw(vec2 const& pos)
{
	//テクスチャの貼り付け、位置とサイズ 

	//Colorubの実体化
	Colorub colorUb;
	glBindTexture(GL_TEXTURE_2D, _shipTexture);
	glColor3ubv(colorUb.LightBlue);
	//SetColorWithPosition(GetPosition());
	Rect rect(pos,GetSize());
	rect.Draw();
}//void Ship::Draw(vec2 const& pos)

void Ship::DrawRemaningLives()
{
	//表示する文字のサイズ
	vec2 size = vec2(5, DEFAULT_GAME_HEIGHT);
	//残機の表示
	Text2D(1 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 31, size, "%d", GetRemaningLives());
	for (int i = 0; i < GetRemaningLives() - 1; i++)
	{

		//Colorubの実体化
		Colorub color;
		vec2 pos = vec2(DEFAULT_GAME_HEIGHT * 3 + (SHIP_WIDTH + 2) * i,
			DEFAULT_GAME_HEIGHT * 31);
		DrawTexture(pos, GetSize(), GetTexture(), color.LightBlue);
		//gShip.Draw(pos);
	}//for (int i = 0; i < gShip.GetRemaningLives() - 1; i++)
}//void Ship::DrawRemaningLives()

void Ship::Reset()
{
	//位置を初期化する
	vec2 pos = vec2(SHIP_DEFAULT_X, SHIP_DEFAULT_Y);
	SetPosition(pos);
}//void Ship::Reset()



