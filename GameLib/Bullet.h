#pragma once

//’e‚ÌƒNƒ‰ƒX
class Bullet
{
public:
	Bullet();
	//‰Šú‰»
	virtual int Initialize() = 0;
	//’e‚Ì”­Ëó‘Ô
	bool _enable;
};//class Bullet