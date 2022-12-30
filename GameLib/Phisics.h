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

	//�����x�𖈕b���b�Ōv�Z
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
	//�����x
	float EqOne_vf(float vi, float a, float t)
	{
		return vi + a * t;
	}

	//���߂�ʒu�̕ω��̊֐�
	float EqTwo_x(float vf, float vi, float t)
	{
		return .5f * (vf + vi) * t;
	}
	//���߂�ʒu�̕ω��̊֐�
	float EqThree_x(float vi, float t, float a)
	{
		return vi * t + 0.5 * a * t * t;
	}

	//���߂�����x
	float EqThree_a(float vi, float x, float t)
	{
		return (x - vi * t) * 2 / (t * t);
	}

	//�d���̃x�N�g����\���v�f3�̔z��
	float* CalcWeight3D(float mass, float grav)
	{
		float weight[3] = { 0, };
		weight[1] = mass * grav;

		return weight;
	}

	/*

		fric_coeff 2�ʊԂ̉^�����C�W��

	*/

	//���̂����鎞��true �����łȂ����false
	bool CheckForMotion(float angle, float weight, float fric_coeff)
	{
		//�Ζʂ̐����R�͂̌v�Z
		float norm = weight * cosf(angle * PI / 180.0f);
		//�Ζʉ������̗�
		float perpForce = weight * sinf(angle * PI / 180.0f);

		//�ő�Î~���C�͂̌v�Z
		float stat_friction = fric_coeff * norm;

		return perpForce > stat_friction;
	}

	//�Ζʏ�̕��̂�����o���Ƃ��̉����x
	float CalcAccel(float angle, float weight, float fric_coeff, float mass)
	{
		// �Ζʂ̐����R�͂̌v�Z
		float norm = weight * cosf(angle * PI / 180.0f);
		//�Ζʉ������̗�
		float perpForce = weight * sinf(angle * PI / 180.0f);

		//���̂̉^����j�~���悤�Ƃ��門�C��
		float kin_friction = fric_coeff * norm;

		//���̂ɓ������͂̍��Z
		float total_force = perpForce - kin_friction;

		return total_force / mass;//a = F / m
	}

	float CalculateWork(float force, float friction, float displacment)
	{
		//���͂̌v�Z
		float netForce = force - friction;

		//�ψق��|����
		float tmp = displacment * netForce;

		return tmp;
	}

	float CalculateAngleWork(vector2 vect, float friction, float displacement)
	{
		float tmp;

		tmp = cos(DegreesToRads(vect.y));

		//���������̗͂��v�Z
		float horizForce = vect.x * tmp;

		float work = CalculateWork(horizForce, friction, displacement);

		return work;
	}//CalculateAngleWork(vector2 vect, float friction, float displacement)


