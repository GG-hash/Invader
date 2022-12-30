#include "Invader.h"

//static変数の実態の定義
vec2 Invader::_invaderSpeed = vec2(DEFAULT_INVADER_SPEED, 0);
vec2 Invader::_nextSpeed = vec2(DEFAULT_INVADER_SPEED, 0);
int Invader::_current;
//BGMのカウント
int Invader::_bgmCount;
//現在の音
int Invader::_bgmCurrent;

//インベーダーを格納する配列
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
	//テクスチャの生成
	glGenTextures(MAX_INVADER_ANIM, _textures);
	glBindTexture(GL_TEXTURE_2D, _textures[0]);
	//カラーキーを設定
	unsigned char colorkey[] = { 0x00,0xff,0x00 };
	TextureFromBMP(fileName0, colorkey);

	glBindTexture(GL_TEXTURE_2D, _textures[1]);
	TextureFromBMP(fileName1, colorkey);

	//ターンの初期化
	_turn = 0;

    return 0;
}
//Invader::Initialize(const char* fileName0, const char* fileName1, vec2 size, vec2 pos)

int Invader::AllInitialize()
{
	//インベーダーの初期化
	//先頭だけを初期化することでコピーして隊列を作る
	gInvaders[0][0].Initialize("image/invader0-0.bmp", "image/invader0-1.bmp", vec2(12, INVADER_HEIGHT));
	//スコアの設定
	gInvaders[0][0]._score = 10;
	for (int i = 0; i <= FIRST_ROW_INVADER; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			gInvaders[i][j] = gInvaders[0][0];
		}
	}

	gInvaders[2][0].Initialize("image/Invader1-0.bmp", "image/Invader1-1.bmp", vec2(11, INVADER_HEIGHT));
	//スコアの設定
	gInvaders[2][0]._score = 20;

	for (int i = FIRST_ROW_INVADER + 1; i <= SECOND_ROW_INVADER; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			gInvaders[i][j] = gInvaders[2][0];
		}
	}

	gInvaders[4][0].Initialize("image/invader2-0.bmp", "image/invader2-1.bmp", vec2(8 , INVADER_HEIGHT));
	//スコアの設定
	gInvaders[4][0]._score = 30;
	for (int i = 0; i <= MAX_INVADER_COLUMN; i++)
	{
		gInvaders[4][i] = gInvaders[4][0];
	}

	//オフセット インベーダーが画面の左端より少し間隔をあけて隊列を作る
	float offset = DEFAULT_INVADER_INTERVAL * 3;

	//インベーダーの隊列を作成する
	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			
			//センタリングも行う
			//ステージが進むごとにインベーダーの初期位置が最高8列前進する
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
	//現在のインベーダーを初期化する
	_current = 0;

	//オフセット インベーダーが画面の左端より少し間隔をあけて隊列を作る
	float offset = DEFAULT_INVADER_INTERVAL * 3;
	//インベーダーの隊列を作成する
	for (int i = 0; i < MAX_INVADER_ROW; i++)
	{
		for (int j = 0; j < MAX_INVADER_COLUMN; j++)
		{
			//センタリングも行う
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
	//0ターン目ならば何もしない
	if (_turn++ < 1)
	{
		return;
	}

	++_animNo %= MAX_INVADER_ANIM;
	GetPosition() += Invader::_invaderSpeed;

	//printf("In X : %f\n", _invaderSpeed.x);
	//printf("In Y : %f\n", _invaderSpeed.y);

	//インベーダーが画面端へ行った時の処理
	//右端の処理
	if ((GetPosition().x >= SCREEN_WIDTH - GetSize().x * 2 - DEFAULT_INVADER_SPEED) && (_invaderSpeed.x > 0))
	{
		_nextSpeed = vec2(-DEFAULT_INVADER_SPEED, INVADER_HEIGHT);
	}
	//右端の処理
	if ((GetPosition().x < DEFAULT_INVADER_SPEED) && (_invaderSpeed.x < 0))
	{
		_nextSpeed = vec2(DEFAULT_INVADER_SPEED, INVADER_HEIGHT);
	}

}
//Invader::Update()

void Invader::AllUpdate()
{

	//敵が爆発している間やShipが爆発している間、Shipの残機が0の場合は軍隊の動きを止める
	if ((Invader::GetCountAlives() <= 0) 
		|| (gShipEx._count > 0)
		|| (gGame.isGameOver() == true))
	{
		return;
	}//if ((Invader::GetCountAlives() <= 0))
	
	//BGMが速くなりすぎることを防止する 敵が5体以下ならこれ以上BGMを早くしない
	int BgmPhase = Invader::GetCountAlives() > 5 ? Invader::GetCountAlives() : 5;
	
	if (++_bgmCount >= BgmPhase)
	{
		_bgmCount = 0;
		//BGMを鳴らす
		AudioStop(AUDIO_CHANNEL_TRIANGLE);
		AudioWaveForm(AUDIO_CHANNEL_TRIANGLE, AUDIO_WAVEFORM_PULSE_50);
		//キーのデータを格納する配列
		int bgmKey[] = {0,-2,-3,2};
		AudioFreq(AUDIO_CHANNEL_TRIANGLE, 440.0f / 4.0f * pow(2.0f, bgmKey[_bgmCurrent] / 12.0f));

		AudioDecay(AUDIO_CHANNEL_TRIANGLE, 0.9f);
		AudioPlay(AUDIO_CHANNEL_TRIANGLE);
		++_bgmCurrent %= MAX_INVADER_BGM_PHASE;
	}//if (++_bgmCount >= BgmPhase)


	//全滅の場合は、軍隊の動きを止める
	if (gInvaderEx._count > 0)
	{
		return;
	}

	//撃墜された敵の更新を飛ばす
	while (_current > MAX_INVADER || gInvaders[_current / MAX_INVADER_COLUMN][_current % MAX_INVADER_COLUMN]._isDead == true)
	{
		//_currentが配列数を上回らないようにする
		if (_current > MAX_INVADER)
		{
			//printf("横移動\n");
			_current = 0;
			SetSpeed(_nextSpeed);
			//printf("列を下げたときのY : %f\n", _invaderSpeed.y);
			//printf("列を下げたときのnextY : %f\n", _nextSpeed.y);
			_nextSpeed.y = 0.0f;
		}
		else
		{
			_current++;
		}
	}
	//横のインベーダーの列を全てアップデートしたら、次の列へ行く
	gInvaders[_current / MAX_INVADER_COLUMN][_current % MAX_INVADER_COLUMN].Update();
	
	_current++;

	//弾を発射する処理 ////////////////////////////////////////
	//Shipが出現中は攻撃ができない
	if (gInvaders[0][0]._turn > 1)
	{
		//一体につき2発まで打てる
		for (int i = 0; i < MAX_INVADER_BULLET; i++)
		{
			//敵が半分になったら敵が弾を2発撃つようにする

			//敵の数が半分以上残っており、弾を一発でも撃っていたら
			//処理を飛ばす
			if ((GetCountAlives() >= MAX_INVADER / 2.0f)
				&& (InvaderBullet::GetShootingCount() > 0))
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++)

			//ランダムに敵から弾を発射させる
			int randNum = rand() % MAX_INVADER;
			int invaderRow = randNum / MAX_INVADER_COLUMN;
			int invaderColumn = randNum % MAX_INVADER_COLUMN;

			Invader* owner = &gInvaders[invaderRow][invaderColumn];

			//選択されていたインベーダーが撃墜されている、
			//もしくは弾を撃っている状態なら弾を撃たない(弾の生成の処理を飛ばす)
			if ((owner->_isDead == true) || (owner->isShooting()))
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++) へ戻る


			//前の列に他のインベーダーがいなければ弾を発射
			bool stopShoot = false;
			for (int i = invaderRow - 1; 0 <= i; i--)
			{
				//横一列分だけ処理する
				if (gInvaders[i][invaderColumn]._isDead == false)
				{
					stopShoot = true;
					break;
				}//if (gInvaders[i][invaderColumn]._isDead == false)
			}//for (int i = invaderRow - 1; 0 <= i; i--)

			//弾の発射を停止していたら処理を飛ばす
			if (stopShoot == true)
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++)へ戻る

			//弾の生成 一回の攻撃につきMAX_INVADER_BULLET回分弾を生成する
			InvaderBullet* invaderBullet = &gInvaderBullets[i];

			//弾の待機状態が有効なら処理を飛ばす
			if (invaderBullet->_enable == true)
				continue;//for(int i=0;i<MAX_INVADER_BULLET;i++)へ戻る

			//画像のx座標が中央でy座標が発射口と重なるように座標を調整する
			vec2 pos = vec2(owner->GetPosition().x + (owner->GetSize().x - invaderBullet->GetSize().x) / 2.0f,
				owner->GetPosition().y + owner->GetSize().y);
			//攻撃
			invaderBullet->Attack(pos, owner);



		}//for(int i=0;i<MAX_INVADER_BULLET;i++)
	}//if(_turn > 1)
	///////////////////////////////////////////////////////////////////////
		
}//Invader::AllUpdate()

void Invader::Draw()
{
	//もし倒されている、または_turnが1未満ならインベーダーの登場シーンを作成する為描画しない
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

		//弾の発射が有効であり、発射している所有者が自分ならtrueを返す
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
