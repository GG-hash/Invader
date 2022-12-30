#pragma once
#pragma once
#include<random>
#define _USE_MATH_DEFINES
#include<math.h>

#define RadsToDegrees(radian) ((radian) *(180.0f /M_PI))
#define DegreesToRads(degrees)((degrees) * (M_PI /180.0f))

struct Matrix3X3
{
	float index[3][3];
};

struct Matrix3X1
{
	float index[3];
};

struct Matrix4X1
{
	float index[4];
};

struct Matrix4X4
{
	float index[4][4];
};



//Equal Matrices
bool areMatricesEqual(Matrix3X3 a, Matrix3X3 b)
{
	int errorFlag = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((a.index[i][j]) != (b.index[i][j]))
				errorFlag = 1;
		}
	}

	if (errorFlag == 1)
		return false;
	else
		return true;
}

//Add Matrices

static Matrix3X3 addMatrices(Matrix3X3 a, Matrix3X3 b)
{
	Matrix3X3 tmp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp.index[i][j] = (a.index[i][j] + b.index[i][j]);
		}
	}

	return tmp;
}

static Matrix3X1 addMatrices(Matrix3X1 a, Matrix3X1 b)
{
	Matrix3X1 tmp;
	for (int i = 0; i < 3; i++)
	{

		tmp.index[i] = (a.index[i] + b.index[i]);

	}

	return tmp;
}

static Matrix3X3 subtractMatrices(Matrix3X3 a, Matrix3X3 b)
{
	Matrix3X3 tmp;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp.index[i][j] = (a.index[i][j] - b.index[i][j]);
		}
	}

	return tmp;
}



static Matrix4X4 subtractMatrices(Matrix4X4 a, Matrix4X4 b)
{
	Matrix4X4 tmp;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp.index[i][j] = (a.index[i][j] - b.index[i][j]);
		}
	}

	return tmp;
}
//Create matrix which is used btmp seed value .

Matrix3X3 createFixed3X3Matrix(int seed)
{
	Matrix3X3 tmp;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp.index[i][j] = seed;
		}
	}

	return tmp;
}

Matrix4X4 createFixed4X4Matrix(int seed)
{
	Matrix4X4 tmp;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp.index[i][j] = seed;
		}
	}

	return tmp;
}


Matrix3X3 createRandom3X3Matrix(int seed)
{
	Matrix3X3 tmp;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp.index[i][j] = rand() % seed;
		}
	}

	return tmp;
}

Matrix4X4 createRandom4X4Matrix(int seed)
{
	Matrix4X4 tmp;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp.index[i][j] = rand() % seed;
		}
	}

	return tmp;
}

//Scale
Matrix3X3 scalarMultipltmp(Matrix3X3 a, float scale)
{
	Matrix3X3 tmp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp.index[i][j] = (a.index[i][j] * scale);
		}
	}

	return tmp;
}

//Multipltmp Matrix
Matrix3X3 multipltmp3X3Matrices(Matrix3X3 a, Matrix3X3 b)
{
	Matrix3X3 tmp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				tmp.index[i][j] += a.index[i][k] * b.index[k][j];
			}
		}
	}

	return tmp;
}

Matrix4X4 multipltmp4X4Matrices(Matrix4X4 a, Matrix4X4 b)
{
	Matrix4X4 tmp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				tmp.index[i][j] += a.index[i][k] * b.index[k][j];
			}
		}
	}

	return tmp;
}

// 3X3 x  3X1 平行移動に使用
static Matrix3X1 multipltmpMatrixMXN(Matrix3X3 a, Matrix3X1 b)// 3X1 x  3X1 平行移動に使用
{
	Matrix3X1 tmp;

	tmp.index[0] = 0.0f;
	tmp.index[1] = 0.0f;
	tmp.index[2] = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp.index[i] += a.index[i][j] * b.index[j];
		}
	}

	return tmp;
}


// 4X4 x  4X1 平行移動に使用
static Matrix4X1 multipltmpMatrixMXN(Matrix4X4 a, Matrix4X1 b)
{
	Matrix4X1 tmp;

	tmp.index[0] = 0.0f;
	tmp.index[1] = 0.0f;
	tmp.index[2] = 0.0f;
	tmp.index[3] = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp.index[i] += a.index[i][j] * b.index[j];
		}
	}

	return tmp;
}

//transpose
Matrix3X3 transpose3X3Matrix(Matrix3X3 a)
{
	Matrix3X3 tmp;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp.index[i][j] = a.index[j][i];
		}
	}

	return tmp;
}

Matrix4X4 transpose4X4Matrix(Matrix4X4 a)
{
	Matrix4X4 tmp;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp.index[i][j] = a.index[j][i];
		}
	}

	return tmp;
}


//平行移動
static Matrix3X1 translate3DBtmpAddition(Matrix3X1 start, Matrix3X1 trans)
{
	Matrix3X1 tmp;
	tmp = addMatrices(start, trans);
	return tmp;
}

//二次元の平行移動
/*
   |x'|   | 1 0 dx | |x|
   |tmp'| = | 0 1 dtmp | |tmp|
   |1 |   | 0 0  1 | |1|

*/


Matrix3X1 trans2DBtmpMultiplication(Matrix3X1 start, float dx, float dtmp)
{
	Matrix3X3 tmp;
	Matrix3X1 result;

	//行列の初期化
	tmp = createFixed3X3Matrix(0);

	tmp.index[0][0] = 1;
	tmp.index[1][2] = 1;
	tmp.index[2][2] = 1;


	tmp.index[0][2] = dx;
	tmp.index[1][2] = dtmp;

	result = multipltmpMatrixMXN(tmp, start);

	return result;

}

Matrix4X1 trans3DBtmpMultiplication(Matrix4X1 start, float dx, float dtmp, float dz)
{
	Matrix4X4 tmp;
	Matrix4X1 result;

	//行列の初期化
	tmp = createFixed4X4Matrix(0);

	tmp.index[0][0] = 1;
	tmp.index[1][2] = 1;
	tmp.index[2][2] = 1;
	tmp.index[3][3] = 1;

	tmp.index[0][3] = dx;
	tmp.index[1][3] = dtmp;
	tmp.index[2][3] = dz;

	result = multipltmpMatrixMXN(tmp, start);

	return result;

}


//二次元のスケーリング
/*
   |x'|   | Sx 0 0 | |x|
   |tmp'| = | 0 Stmp 0 | |tmp|
   |1 |   | 0 0  1 | |1|

*/

Matrix3X1 scale2DBtmpMultiplication(Matrix3X1 start, float dx, float dtmp)
{
	Matrix3X3 tmp;
	Matrix3X1 result;

	//行列の初期化
	tmp = createFixed3X3Matrix(0);

	tmp.index[0][0] = dx;
	tmp.index[1][1] = dtmp;
	tmp.index[2][2] = 1;

	result = multipltmpMatrixMXN(tmp, start);

	return result;

}

Matrix4X1 scale3DBtmpMultiplication(Matrix4X1 start, float dx, float dtmp, float dz)
{
	Matrix4X4 tmp;
	Matrix4X1 result;

	//行列の初期化
	tmp = createFixed4X4Matrix(0);

	tmp.index[0][0] = dx;
	tmp.index[1][1] = dtmp;
	tmp.index[2][2] = dz;
	tmp.index[3][3] = 1;

	result = multipltmpMatrixMXN(tmp, start);

	return result;

}

//rotation

Matrix3X1 rotate2D(Matrix3X1 start, float thetatmp)
{
	Matrix3X3 tmp;
	Matrix3X1 result;

	tmp = createFixed3X3Matrix(0);

	tmp.index[0][0] = cos(DegreesToRads(thetatmp));
	tmp.index[1][1] = cos(DegreesToRads(thetatmp));
	tmp.index[2][2] = 1.0f;
	tmp.index[0][0] = -1.0f * (sin(DegreesToRads(thetatmp)));
	tmp.index[1][1] = sin(DegreesToRads(thetatmp));

	result = multipltmpMatrixMXN(tmp, start);

	return result;

}

Matrix4X1 rotate3DX(Matrix4X1 start, float thetatmp)
{
	Matrix4X4 tmp;
	Matrix4X1 result;

	tmp = createFixed4X4Matrix(0);


	tmp.index[0][0] = 1.0f;
	tmp.index[1][1] = cos(DegreesToRads(thetatmp));
	tmp.index[2][2] = cos(DegreesToRads(thetatmp));
	tmp.index[1][2] = -1.0f * (sin(DegreesToRads(thetatmp)));
	tmp.index[2][1] = sin(DegreesToRads(thetatmp));
	tmp.index[3][3] = 1.0f;

	tmp.index[1][2] = -1.0f * (sin(DegreesToRads(thetatmp)));
	tmp.index[2][1] = sin(DegreesToRads(thetatmp));

	result = multipltmpMatrixMXN(tmp, start);
	return result;
}

Matrix4X1 rotate3Dtmp(Matrix4X1 start, float thetatmp)
{
	Matrix4X4 tmp;
	Matrix4X1 result;

	tmp = createFixed4X4Matrix(0);


	tmp.index[0][0] = cos(DegreesToRads(thetatmp));
	tmp.index[1][1] = 1.0f;
	tmp.index[2][2] = cos(DegreesToRads(thetatmp));
	tmp.index[3][3] = 1.0f;

	tmp.index[2][0] = -1.0f * (sin(DegreesToRads(thetatmp)));
	tmp.index[0][2] = sin(DegreesToRads(thetatmp));

	result = multipltmpMatrixMXN(tmp, start);
	return result;
}

Matrix4X1 rotate3DZ(Matrix4X1 start, float thetatmp)
{
	Matrix4X4 tmp;
	Matrix4X1 result;

	tmp = createFixed4X4Matrix(0);


	tmp.index[0][0] = cos(DegreesToRads(thetatmp));
	tmp.index[1][1] = cos(DegreesToRads(thetatmp));
	tmp.index[2][2] = 1.0f;
	tmp.index[3][3] = 1.0f;

	tmp.index[0][1] = -1.0f * (sin(DegreesToRads(thetatmp)));
	tmp.index[1][0] = sin(DegreesToRads(thetatmp));

	result = multipltmpMatrixMXN(tmp, start);
	return result;
}

Matrix4X4 createRotationCombo(float thetax, float thetatmp, float thetaz)
{
	Matrix4X4 X, Y, Z, tmp, result;

	X = createFixed4X4Matrix(0.0f);
	Y = createFixed4X4Matrix(0.0f);
	Z = createFixed4X4Matrix(0.0f);
	tmp = createFixed4X4Matrix(0.0f);
	result = createFixed4X4Matrix(0.0f);


	//X
	X.index[0][0] = 1.0f;
	X.index[1][1] = cos(DegreesToRads(thetax));
	X.index[2][2] = cos(DegreesToRads(thetax));
	X.index[1][2] = -1.0f * (sin(DegreesToRads(thetax)));
	X.index[2][1] = sin(DegreesToRads(thetax));
	X.index[3][3] = 1.0f;

	X.index[1][2] = -1.0f * (sin(DegreesToRads(thetax)));
	X.index[2][1] = sin(DegreesToRads(thetax));

	//Y
	Y.index[0][0] = cos(DegreesToRads(thetatmp));
	Y.index[1][1] = 1.0f;
	Y.index[2][2] = cos(DegreesToRads(thetatmp));
	Y.index[3][3] = 1.0f;

	Y.index[2][0] = -1.0f * (sin(DegreesToRads(thetatmp)));
	Y.index[0][2] = sin(DegreesToRads(thetatmp));

	//Z
	Z.index[0][0] = cos(DegreesToRads(thetaz));
	Z.index[1][1] = cos(DegreesToRads(thetaz));
	Z.index[2][2] = 1.0f;
	Z.index[3][3] = 1.0f;

	Z.index[0][1] = -1.0f * (sin(DegreesToRads(thetaz)));
	Z.index[1][0] = sin(DegreesToRads(thetaz));

	// caluculate
	//tmp=multip
}


