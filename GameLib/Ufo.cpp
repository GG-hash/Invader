#include "Ufo.h"

Ufo::Ufo():_count(0)
			,_score(0)
			,_ufoX(SCREEN_WIDTH)
			, _textureIndex(-1)
{

}//Ufo::Ufo()

int Ufo::Initialize()
{
	//サイズの設定
	vec2 size = vec2(UFO_WIDTH,UFO_HEIGHT);
	SetSize(size);
	
	//テクスチャの生成
	glGenTextures(MAX_UFO_TEXTURE, _textures);
	//ファイル名
	const char* fileName[MAX_UFO_TEXTURE] =
	{
		"image/ufo.bmp", //Ufoの画像
		"image/ufo_explosion.bmp"//Ufoの爆破時の画像
	};

	for (int i = 0; i < MAX_UFO_TEXTURE; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		//ファイルの読み込み
		TextureFromBMP(fileName[i], 0x00, 0xff, 0x00);
	}
	

	return 0;
}//int Ufo::Initialize()


void Ufo::Update()
{
	//ゲームオーバーなら更新しない
	if ((gGame.isGameOver() == true))
	{
		//UfoのBGMを停止する
		AudioStop(AUDIO_CHANNEL_PULSE1);
		return;
	}// if (gShip.GetRemaningLives() <= 0)

	//カウンタを追加する
	_count++;

	//周波数を変化させる
	float fq = (float)sin((2 * M_PI * _count / 45) * 4);
	AudioFreq(AUDIO_CHANNEL_PULSE1, _freq * (float)pow(2,fq * 4/12));
	//状態によって処理を変更する
	switch (_state)
	{
	case WAIT:
		if (_count >= UFO_WAIT_TIME)
		{
			//Ufoの出現したときの音を鳴らす
			AudioStop(AUDIO_CHANNEL_PULSE1);
			AudioWaveForm(AUDIO_CHANNEL_PULSE1, AUDIO_WAVEFORM_PULSE_50);
			_freq = 440;
			AudioFreq(AUDIO_CHANNEL_PULSE1, (float)_freq);
			AudioDecay(AUDIO_CHANNEL_PULSE1, 0.0f);
			AudioSweep(AUDIO_CHANNEL_PULSE1, 0.0f, 440 / 2);
			AudioPlay(AUDIO_CHANNEL_PULSE1);
			_count = 0;
			_state = UfoState::MOVE;
			//画面端へ待機させる
			GetPosition().x = SCREEN_WIDTH;
			
		}//if (_count >= 60)

		break;
	case SCORE:
		
		//1秒間表示する
		if (_count > 60)
		{
			_state = UfoState::WAIT;
			_count = 0;
			//画面端へ待機させる
			GetPosition().x = SCREEN_WIDTH;
		}

		
		break;
	case MOVE:
		//Shipが爆発したらUfoの動きを止める
		if (gShipEx._count > 0)
		{
			break;
		}

		//Ufoを右から左へ移動させる
		GetPosition().x -= UFO_SPEED;
		//ufoが画面外に出たらUfoを削除する
		if (GetPosition().x < -GetSize().x)
		{
			_state = UfoState::WAIT;
			_count = 0;
			//Ufo登場時のBGMを停止する
			AudioStop(AUDIO_CHANNEL_PULSE1);

		}//if (GetPosition().x < -GetSize().x)
		break;
	case EXPLOSION:
		//爆発したら0.5秒だけ爆破時の画像を表示させる
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
	//位置の設定
	//スコア表示の下に出現させる
	vec2 pos = vec2(SCREEN_WIDTH, DEFAULT_GAME_HEIGHT * (3 + 1));
	SetPosition(pos);
	//Ufo登場時のBGMを停止する
	AudioStop(AUDIO_CHANNEL_PULSE1);
	_state = WAIT;
	_count = 0;
	
}//void Ufo::Reset()



void Ufo::Draw()
{
	_textureIndex = -1;
	//文字列の長さ
	float length = 0.0f;
	//状態によって処理を変更する
	switch (_state)
	{
	case WAIT:

		break;
	case SCORE:
		//スコアの描画
		char str[24];
		sprintf_s(str, "%d", _score);
		//スコアの文字をセンタリングする
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

	//textureIndexが0以上なら表示
	if (_textureIndex >= 0)
	{
		glBindTexture(GL_TEXTURE_2D, _textures[_textureIndex]);
		//色の設定
		SetColorWithPosition(GetPosition());
		Rect::Draw();
	}//if (textureIndex >= 0)
	
}//void Ufo::Draw()


void Ufo::Explosion()
{
	_count = 0;
	_state = UfoState::EXPLOSION;

	//Ufoのスコアをランダムで決める
	int score[MAX_UFO_SCORE] = {50,100,150,300};
	_score = score[rand() % MAX_UFO_SCORE];

	//スコアを増やす
	gGame.AddScore(_score);

	//音を1オクターブ下げる
	_freq = 440 / 2;

	AudioDecay(AUDIO_CHANNEL_PULSE1,0.95f);

}//void Ufo::Explosion()



