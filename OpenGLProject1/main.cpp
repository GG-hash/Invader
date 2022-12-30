#include"MyEngine.h"
#include<iostream>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 640

#define TEXTURE_WIDTH  1024
#define TEXTURE_HEIGHT 1024

glm::u8vec3 pixels[TEXTURE_HEIGHT][TEXTURE_WIDTH];

void Initialize(int argc, char* argv[],const char* title,int WinPosX,int WinposY,int WinWidth,int WinHeight)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(WinPosX, WinposY);
	glutInitWindowSize(WinWidth,WinHeight);
	glutCreateWindow(title);
}

void Display()
{
	//テクスチャの張り付け
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,TEXTURE_WIDTH,TEXTURE_HEIGHT,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
	//画面を拡大したときの処理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//画面を縮小したときの処理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	{
		//テクスチャの座標を設定
		glTexCoord2f(0,0);
		glVertex2f(-1,1);
		glTexCoord2f(-1, 1);
		glVertex2f(-1,-1);
		glTexCoord2f(1, 1);
		glVertex2f(1,-1);
		glTexCoord2f(1, 0);
		glVertex2f(1,1);
	}
	glEnd();
	glutSwapBuffers();
}

void Idle()
{
	//pixelsを0で初期化
	memset(pixels, 0, sizeof pixels);
	//フレームのカウント
	static unsigned int frameCount;
	//std::cout << "frameCount : "+frameCount<<std::endl;
	//pixelsを何回か描画させる
	//double x = 0.0, y = 0.0;
	//double x_n = 0.0, y_n = 0.0;

	for (int i = 0; i < TEXTURE_HEIGHT; i++)
	{
		for (int j = 0; j < TEXTURE_WIDTH; j++)
		{
			double x = 0.0;
			double y = 0.0;

			double a = (j - TEXTURE_WIDTH / 2.0) / (TEXTURE_WIDTH / 4.0);
			double b = (i - TEXTURE_HEIGHT / 2.0) / (TEXTURE_HEIGHT / 4.0);

			for (int k = 0; k < (int)(frameCount % 64); k++)
			{
				double x_n = x * x - y * y + a;
				double y_n = 2 * x * y + b;
				x = x_n;
				y = y_n;
				//発散の処理
				if (x * x + y * y >= 4)
				{
					const glm::u8vec3 colors[] =
					{
						{0xff,0x00,0x00},
						{0xff,0xff,0x00},
						{0x00,0xff,0xff},
						{0xff,0x00,0xff},
						{0x00,0x00,0xff},
						{0x00,0xff,0x00}
					};
					//色の数を求める
					pixels[i][j] = colors[k%(sizeof (colors)/sizeof(glm::u8vec3))];
					break;
				}
			}
		}
	}


	glutPostRedisplay();
	frameCount = frameCount + 1;
}

int main(int argc, char* argv[])
{
	MyEngine *myengine = new MyEngine();
	myengine->Initialize(argc, argv, "マンデルブロ集合", 633, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInit(&argc,argv);
	//Initialize(argc, argv,"マンデルブロ集合", 633,0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glutDisplayFunc(Display);
	//Idle状態時の実行
	glutIdleFunc(Idle);
	glutMainLoop();

	return 0;
}