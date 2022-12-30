#include "Ball.h"
#include<iostream>


//static


//_pos(0, 0),_lastPos(_pos),
Ball::Ball() :_pos(0, 0),
			 _ballspeed(2, 2),
			 _lastPos(_pos),
             _radius(1),
	         _size(16)
{
	//Vector2i(_windowSize.x, _windowSize.y);
	_ballspeed = normalize(_ballspeed);
}

//_pos(0,0),_lastPos(Ball::_pos),
Ball::Ball(Vector2int& windowSize):_pos(0, 0),
							       _ballspeed(2, 2),
	                               _lastPos(0,0),
							       _radius(1),
								   _size(16)
{
	_windowSize=Vector2int(windowSize.x, windowSize.y);
	_ballspeed = normalize(_ballspeed);
}

Ball::Ball(Vector2int& windowSize, vec2& pos, vec2& speed)
{
	_windowSize = Vector2int(windowSize.x, windowSize.y);
	Ball::_pos = vec2(pos.x, pos.y);
	_ballspeed = vec2(speed.x, speed.y);
	_ballspeed = normalize(_ballspeed);
	_size = 16;
	_lastPos = _pos;
	_radius = 1;
}

Ball::Ball(Vector2int& windowSize, const vec2& pos, const vec2& speed)
{
	_windowSize = Vector2int(windowSize.x, windowSize.y);
	Ball::_pos = vec2(pos.x, pos.y);
	_ballspeed = vec2(speed.x, speed.y);
	_ballspeed = normalize(_ballspeed);
	_size = 16;
	_lastPos = _pos;
	_radius = 1;
}

Ball::Ball(Vector2int& windowSize, const vec2& pos, const vec2& speed,Ball* ball)
{
	_windowSize = Vector2int(windowSize.x, windowSize.y);
	Ball::_pos = vec2(pos.x, pos.y);
	_ballspeed = vec2(speed.x, speed.y);
	_ballspeed = normalize(_ballspeed);
	_size = 16;
	_lastPos = _pos;
	_radius = 1;
}

void Ball::SetWindowSize(Vector2int& windowSize)
{
	_windowSize.x = windowSize.x;
	_windowSize.y = windowSize.y;
}



void Ball::SetSpeed(vec2& speed)
{
	_ballspeed=normalize(speed);
}

void Ball::SetSpeed(const vec2& speed)
{
	_ballspeed = speed;
	_ballspeed = normalize(speed);
}


void Ball::SetPosition(const vec2& pos)
{
	_pos = pos;
}

void ReflectInWindow(Ball& ball)
{
	
	//x軸方向の跳ね返り
	if (ball.GetPosition().x + ball.GetRadius() >= ball.GetWindowSize().x || ball.GetPosition().x + ball.GetRadius() <= 0)
	{
		ball.SetPosition(ball.GetLastPosition());
		ball.SetSpeedX(ball.GetSpeed().x * -1.0f);
	}
	//y軸方向の跳ね返り
	if (ball.GetPosition().y + ball.GetRadius() >= ball.GetWindowSize().y || ball.GetPosition().y + ball.GetRadius() <= 0)
	{
		ball.SetPosition(ball.GetLastPosition());
		ball.SetSpeedY(ball.GetSpeed().y * -1.0f);

	}
}

void Ball::Update()
{
	_lastPos = _pos;
	_pos += _ballspeed;
}
//Ball::Update()

vec2& Ball::UpdatePosition()
{

	_lastPos = _pos;
	_pos += _ballspeed;

	SetPosition(_pos);

	std::cout << "Update() Position   x : " << Ball::_pos.x << " y : " << Ball::_pos.y << std::endl;

	//ReflectInWindow(_windowSize, Ball::_pos, _lastPos, _ballspeed);

	return _pos;
}

void Ball::Draw()
{
	//std::cout << "DrawBall() 1   Position   x : " << _pos.x << " y : " << _pos.y << std::endl << std::endl;
	glPushMatrix();
	{
		glTranslatef(_pos.x, _pos.y, 0);
		//std::cout << "DrawBall() Position   x : " << _pos.x << " y : " << _pos.y << std::endl << std::endl;
		//2次元でも見えるように、球をつぶす
		glScalef(16,16,0);
		//球の描画
		glutSolidSphere(1, 16, 16);//GLdouble radius, GLint slices 周を囲むドット数, GLint stacks
	}
	glPopMatrix();
}//Ball::DrawBall()

void Ball::Draw(float radius)
{
	glPushMatrix();
	{
		glTranslatef(Ball::_pos.x, Ball::_pos.y, 0);
		//2次元でも見えるように、球をつぶす
		glScalef(16, 16, 0);
		//球の描画
		glutSolidSphere(radius, 16, 16);//GLdouble radius, GLint slices 周を囲むドット数, GLint stacks
	}
	glPopMatrix();
}//Ball::DrawBall(float radius)
