#pragma once
#include"GL/glut.h"
#include"glm/glm.hpp"
using namespace glm;
#include"Math.h"
#include"Paddle.h"
#include"Actor.h"

#define BALL_MAX 256


class Ball : public Actor
{
private:
	vec2 _pos;
	vec2 _lastPos;
	vec2 _ballspeed;
	float _size;
	Vector2int _windowSize;
	float _radius;

public:
	Ball();
	Ball(Vector2int& windowSize);
	Ball(Vector2int& windowSize,vec2& pos,vec2& speed);
	Ball(Vector2int& windowSize,const vec2& pos,const vec2& speed);
	Ball(Vector2int& windowSize, const vec2& pos, const vec2& speed, Ball* ball);
	const Vector2int GetWindowSize() const{return _windowSize;}
	void SetWindowSize(Vector2int& windowSize);

	const float GetSize() { return _size; }
	


	const vec2& GetSpeed() const{ return _ballspeed; }
	void SetSpeed(vec2& speed);
	void SetSpeed(const vec2& speed);

	void  SetSpeedX(float value) { _ballspeed.x = value; }
	void  SetSpeedY(float value) { _ballspeed.y = value; }

	const vec2& GetPosition() const { return _pos; }
	float GetPositionX()  { return _pos.x; }
	float GetPositionY()  { return _pos.y; }
	void  SetPositionX(float value) { _pos.x = value; }
	void  SetPositionY(float value) { _pos.y = value; }
	//void SetPosition(const vec2& pos) {_pos = pos;}
	void SetPosition(const vec2& pos);

	const vec2& GetLastPosition() const{ return _lastPos; }
	void SetLastPosition(const vec2& lastpos) { _lastPos = lastpos; }

	const float GetRadius()const { return _radius; }
	void SetRadius(float radius) { _radius = radius; }

	
	void Update() override;
	vec2& UpdatePosition();
	void Draw() override;
	void Draw(float radius);

	//bool IntersectPaddle(Paddle& paddle);

};//class Ball

//ボールがウィンドウに当たった時の処理
void ReflectInWindow(Ball& ball);

