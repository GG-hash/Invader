#pragma once
#include"Ball.h"
#include"glm/glm.hpp"
#include"GL/glut.h"
#include<iostream>
#include"Actor.h"
using namespace glm;

class Paddle : public Actor
{
private:
	vec2 _pos;
	float _height;
	vec2 _lastPos;

public:
	Paddle();
	const vec2& GetPosition()const { return _pos; }
	void SetPosition(vec2& pos) { _pos = pos; }

	const float GetHeight()const { return _height; }
	void SetHeight(float height) { _height = height; }

	const vec2& GetLastPosition() const { return _lastPos; }
	void SetLastPosition(const vec2& lastpos) { _lastPos = lastpos; }

	void Update() override;
	void Draw() override;

	bool IntersectBall(class Ball const& ball);
};

