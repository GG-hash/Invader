#include "Color.h"

//Colorub�̎��̉�
Colorub colorUb;
//����̓C���x�[�_�d�l
void SetColorWithPosition(vec2 const& pos)
{

	if (pos.y < INVADER_HEIGHT * 8)
	{
		glColor3ubv(colorUb.Red);
	}//if (pos.y < INVADER_HEIGHT * 8)
	else if (pos.y < INVADER_HEIGHT * 10)//��ԏ�̗�̃C���x�[�_�[�̍���
	{
		glColor3ubv(colorUb.LightBlue);
	}//else if (pos.y < INVADER_HEIGHT * 10)
	else if (pos.y < INVADER_HEIGHT * 13)//�ォ���Ԗڂ���O�Ԗڗ�̃C���x�[�_�[�̍���
	{
		glColor3ubv(colorUb.Green);
	}//else if (pos.y < INVADER_HEIGHT * 13)
	else if (pos.y < INVADER_HEIGHT * 17)//�ォ��l�Ԗڂ���ܔԖڗ�̃C���x�[�_�[�̍���
	{
		glColor3ubv(colorUb.Yellow);
	}//else if (pos.y < INVADER_HEIGHT * 17)
	else if (pos.y < INVADER_HEIGHT * 21)//�ォ��Z�Ԗڂ��玵�Ԗڗ�̃C���x�[�_�[�̍���
	{
		glColor3ubv(colorUb.Purple);
	}//else if (pos.y < INVADER_HEIGHT * 17)
	else
	{
		glColor3ubv(colorUb.Red);
	}//else


}//void SetColorWthposition(vec2 const& pos)
