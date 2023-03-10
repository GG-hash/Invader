#pragma once
#include"Matrix.h"
#include"TwoVector.h"
#include"ThreeVector.h"


	typedef struct
	{
		float x;
		float y;
	}vector2;

	typedef struct
	{
		float x;
		float y;
		float z;
	}vector3;

	//D = v x t
	float CalcDisplacement(float vel, float time)
	{
		return vel * time;
	}//CalcDisplacement(float vel, float time)

	//D = vt + v0
	float CalcPositon(float oldPosition, float vel, float time)
	{
		return oldPosition + (vel * time);
	}

	// Average Velocity
	float CalcAvgVel(float start, float end, float time)
	{
		return (end - start) / time;
	}//CalcAvgVel(float start, float end, float time)

	//加速度を毎秒毎秒で計算
	float CalcAccelerationSeconds(float startVel, float finalVel, float time)
	{
		return (finalVel - startVel) / time;
	}//CalcAccelerationSeconds(float startVel, float finalVel, float time)

	ThreeDvector AverageVelocity(const ThreeDvector& Pi, const ThreeDvector& Pf, float intervals)
	{
		ThreeDvector tmp(Pf.x - Pi.x, Pf.y - Pi.y, Pf.z - Pi.z);

		tmp = tmp * (1 / intervals);

		return tmp;
	}//AverageVelocity(const ThreeDvector& Pi, const ThreeDvector& Pf, float intervals)

	//first velocity -> final velocity
	//初速度
	float EqOne_vf(float vi, float a, float t)
	{
		return vi + a * t;
	}

	//求める位置の変化の関数
	float EqTwo_x(float vf, float vi, float t)
	{
		return .5f * (vf + vi) * t;
	}
	//求める位置の変化の関数
	float EqThree_x(float vi, float t, float a)
	{
		return vi * t + 0.5 * a * t * t;
	}

	//求める加速度
	float EqThree_a(float vi, float x, float t)
	{
		return (x - vi * t) * 2 / (t * t);
	}

	//重さのベクトルを表す要素3の配列
	float* CalcWeight3D(float mass, float grav)
	{
		float weight[3] = { 0, };
		weight[1] = mass * grav;

		return weight;
	}

	/*

		fric_coeff 2面間の運動摩擦係数

	*/

	//物体が滑る時はtrue そうでなければfalse
	bool CheckForMotion(float angle, float weight, float fric_coeff)
	{
		//斜面の垂直抗力の計算
		float norm = weight * cosf(angle * PI / 180.0f);
		//斜面下向きの力
		float perpForce = weight * sinf(angle * PI / 180.0f);

		//最大静止摩擦力の計算
		float stat_friction = fric_coeff * norm;

		return perpForce > stat_friction;
	}

	//斜面上の物体が滑り出すときの加速度
	float CalcAccel(float angle, float weight, float fric_coeff, float mass)
	{
		// 斜面の垂直抗力の計算
		float norm = weight * cosf(angle * PI / 180.0f);
		//斜面下向きの力
		float perpForce = weight * sinf(angle * PI / 180.0f);

		//物体の運動を阻止しようとする摩擦力
		float kin_friction = fric_coeff * norm;

		//物体に働く合力の合算
		float total_force = perpForce - kin_friction;

		return total_force / mass;//a = F / m
	}

	float CalculateWork(float force, float friction, float displacment)
	{
		//合力の計算
		float netForce = force - friction;

		//変異を掛ける
		float tmp = displacment * netForce;

		return tmp;
	}

	float CalculateAngleWork(vector2 vect, float friction, float displacement)
	{
		float tmp;

		tmp = cos(DegreesToRads(vect.y));

		//水平方向の力を計算
		float horizForce = vect.x * tmp;

		float work = CalculateWork(horizForce, friction, displacement);

		return work;
	}//CalculateAngleWork(vector2 vect, float friction, float displacement)


