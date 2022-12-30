#include "TitleScene.h"
#include<iostream>

//TitleTextの構造体のインスタンス
static TitleText gTexts[] = { 
	{"PLAY"           ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 3), DEFAULT_GAME_HEIGHT *  7)},
	{"SPACE  INVADERS",vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 7), DEFAULT_GAME_HEIGHT *  9)},
	{"=? MYSTERY "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 15)},
	{"=30 POINTS "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 17)},
	{"=20 POINTS "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 19)},
	{"=10 POINTS "    ,vec2(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 21)},

};

//最大のタイトルのテキスト数
#define MAX_TITLE_TEXT (sizeof(gTexts)/sizeof(TitleText))


void TitleScene::Initialize()
{
	//各文字列の文字数を格納する変数
	int total = 0;

	for (int i = 0; i < MAX_TITLE_TEXT; i++)
	{
		//文字数をカウントして、_startCountへ代入する
		gTexts[i]._startCount = total;
		total += strlen(gTexts[i]._str);
	}
}//void TitleScene::Initialize()


void TitleScene::Update()
{
	_count++;
}//void TitleScene::Update()


void TitleScene::Keyboard(unsigned char key)
{
	gGame.SetScene(READY_SCENE);
}//void TitleScene::Keyboard(unsigned char key)


void TitleScene::Draw()
{
	//カウンタの値を調整する
	//1秒間に10カウント進む
	int count = _count / (60 / 10);

	//スコアの描画
	gGame.DrawScore();
	//タイトル画面の描画
	//画像はUfoの_startCountと同じタイミングで出現する
	

	Colorub color;
	//右にそろえる
	float rightOffset = DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 6);

	//画像はUfoの_startCountと同じタイミングで出現する///////
	if (count >= gTexts[2]._startCount)
	{
		//タイトル
	//動かさないテキスト
		Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 9), DEFAULT_GAME_HEIGHT * 11, "*SCORE ADVANCE TABLE*");
		//動かすテキスト
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 3),DEFAULT_GAME_HEIGHT * 7,"PLAY");
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 7),DEFAULT_GAME_HEIGHT * 9,"SPACE  INVADERS");
		//Ufoの描画
		vec2 pos = vec2(rightOffset - gUfo.GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 15);
		vec2 size = gUfo.GetSize();
		DrawTexture(pos, size, gUfo.GetTexture(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 15, "=? MYSTERY ");


		//イカ型のインベーダー
		pos = vec2(rightOffset - gInvaders[4][0].GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 17);
		size = gInvaders[4][0].GetSize();
		DrawTexture(pos, size, gInvaders[4][0].GetTextures(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 17, "=30 POINTS ");

		//カニ型のインベーダー
		pos = vec2(rightOffset - gInvaders[2][0].GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 19);
		size = gInvaders[2][0].GetSize();
		DrawTexture(pos, size, gInvaders[2][0].GetTextures(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 19, "=20 POINTS ");

		//タコ型のインベーダー
		pos = vec2(rightOffset - gInvaders[0][0].GetSize().x / 2.0f, DEFAULT_GAME_HEIGHT * 21);
		size = gInvaders[0][0].GetSize();
		DrawTexture(pos, size, gInvaders[0][0].GetTextures(), color.White);
		//Text2D(DEFAULT_GAME_HEIGHT * (SCREEN_CENTER_HEIGHT - 4), DEFAULT_GAME_HEIGHT * 21, "=10 POINTS ");
	}//if (count >= gTexts[2]._startCount)
	

		//テキストの表示
		//一文字ずつ表示させる
		for (int i = 0; i < MAX_TITLE_TEXT; i++)
		{
			//文字のカウントが始まるまで、テキストを表示させない
			if (count < gTexts[i]._startCount)
			{
				break;
			}

			//表示する文字数
			int strLength = std::min(count - gTexts[i]._startCount, (int)strlen(gTexts[i]._str));

			char str[MAX_TEXT] = {};
			//文字列のコピー
			strncpy_s(str, gTexts[i]._str, strLength);

			//テキストの位置
			float x = gTexts[i]._pos.x;
			float y = gTexts[i]._pos.y;

			//テキストの表示
			Text2D(x, y, str);

		}//for (int i = 0; i < MAX_TITLE_TEXT; i++)
	

}//void TitleScene::Draw()


void TitleScene::Reset()
{
	//カウンタをリセットする
	_count = 0;
	//プレイヤーの残機をリセットする
	gShip.SetRemaningLives(MAX_SHIP_LIVES);
	//スコアをリセットする
	gGame.SetScore(0);
}//void TitleScene::Reset()

