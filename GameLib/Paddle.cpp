#include "Paddle.h"

Paddle::Paddle()
	:_pos(0,0),
	_height(300)
{
}//Paddle::Paddle()

void Paddle::Update()
{

}//Paddle::Update()

void Paddle::Draw()
{
	//描画設定 属性スタック
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLfloat range[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE,range);//ラインの太さの最小値、最大値を取る

	glLineWidth(range[1]/3);//最大の幅をセット
	glBegin(GL_LINES);
	{
		glVertex2f(_pos.x, _pos.y);
		vec2 v = _pos + vec2(0, _height);
		glVertex2f(v.x, v.y);
	}
	glEnd();
	glPopAttrib();

	//std::cout << "描画終了" << std::endl;
}//Paddle::Draw()



bool Paddle::IntersectBall(Ball const& ball)
{
	//x軸方向の当たり判定
	if (   ((ball.GetPosition().x >= _pos.x) && (ball.GetLastPosition().x < _pos.x))
		|| ((ball.GetPosition().x < _pos.x) && (ball.GetLastPosition().x >= _pos.x))  )
	{
		//y軸方向の当たり判定
		if ((ball.GetPosition().y >= _pos.y) && (ball.GetPosition().y < _pos.y + _height))
		{
			return true;
		}
	}

	return false;
}//Paddle::IntersectBall(Ball const& ball)
