#include "Color.h"

//Colorubの実体化
Colorub colorUb;
//今回はインベーダ仕様
void SetColorWithPosition(vec2 const& pos)
{

	if (pos.y < INVADER_HEIGHT * 8)
	{
		glColor3ubv(colorUb.Red);
	}//if (pos.y < INVADER_HEIGHT * 8)
	else if (pos.y < INVADER_HEIGHT * 10)//一番上の列のインベーダーの高さ
	{
		glColor3ubv(colorUb.LightBlue);
	}//else if (pos.y < INVADER_HEIGHT * 10)
	else if (pos.y < INVADER_HEIGHT * 13)//上から二番目から三番目列のインベーダーの高さ
	{
		glColor3ubv(colorUb.Green);
	}//else if (pos.y < INVADER_HEIGHT * 13)
	else if (pos.y < INVADER_HEIGHT * 17)//上から四番目から五番目列のインベーダーの高さ
	{
		glColor3ubv(colorUb.Yellow);
	}//else if (pos.y < INVADER_HEIGHT * 17)
	else if (pos.y < INVADER_HEIGHT * 21)//上から六番目から七番目列のインベーダーの高さ
	{
		glColor3ubv(colorUb.Purple);
	}//else if (pos.y < INVADER_HEIGHT * 17)
	else
	{
		glColor3ubv(colorUb.Red);
	}//else


}//void SetColorWthposition(vec2 const& pos)
