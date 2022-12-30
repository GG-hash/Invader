#include"GL/glut.h"
#include"GAME.h"
#include <iostream>

//#define WINDOW_WIDTH 1280
//#define WINDOW_HEIGHT 720

GAME game;

//描画順に注意する
void Display()
{
	//画面をクリアする
	glClear(GL_COLOR_BUFFER_BIT);
	//射影行列モード
	glMatrixMode(GL_PROJECTION);
	//行列の初期化
	glLoadIdentity();
	//射影行列の設定 画面の左上を(0,0)とする
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	//モデルビュー行列モード
	glMatrixMode(GL_MODELVIEW);
	//行列の初期化
	glLoadIdentity();

	//タイトルスクリーンの間はパドルを表示しない
	if (!game._titleMode)
	{
		//背景の中心線の描画
		glLineWidth(7);
		glBegin(GL_LINES);
		{
			float lineHeight = WINDOW_HEIGHT / 35;
			for (float lineY = 0; lineY < WINDOW_HEIGHT; lineY += lineHeight)
			{
				glVertex2f(WINDOW_WIDTH / 2, lineY);
				glVertex2f(WINDOW_WIDTH / 2, lineY += lineHeight);
			}
		}
		glEnd();
	}




	for (int i = 0; i < GAME::MAX_P; i++)
	{
		glm::vec2 fontSize = {5,7.5};
		glm::vec2 fontPos = {WINDOW_WIDTH/4 - fontSize.x + WINDOW_WIDTH/2* i,fontSize.y+WINDOW_HEIGHT/4};
		
		//10の位の表示
		//Text::Text2D('0' + (game._paddles[i].score / 10) % 10, fontPos.x - WINDOW_WIDTH / 6, fontPos.y);
		Text2D(fontPos.x - WINDOW_WIDTH / 6, fontPos.y, "%d", (game._paddles[i].score / 10) % 10);
		
		//1の位を表示
		//Text::Text2D('0' + (game._paddles[i].score) % 10, fontPos.x, fontPos.y);
		Text2D(fontPos.x , fontPos.y, "%d", (game._paddles[i].score)%10);
	}

	//ボールの描画
	glPointSize(10);
	glBegin(GL_POINTS);
	{
		glVertex2fv((GLfloat*)&game._ball.pos);

	}
	glEnd();




	//タイトルスクリーンの間はパドルを表示しない
	if (!game._titleMode)
	{
		glLineWidth(5);
		glBegin(GL_LINES);
		for (int i = 0; i < GAME::PlayerCount::MAX_P; i++)
		{
			glVertex2fv((GLfloat*)&game._paddles[i].pos);
			glm::vec2 paddleBottom = game._paddles[i].pos + glm::vec2(0, PADDLE_HEIGHT);
			glVertex2fv((GLfloat*)&paddleBottom);
		}
		glEnd();
	}

	//タイトルの表示
	if (game._titleMode)
	{
		Text2D(WINDOW_WIDTH/2-WINDOW_WIDTH/5, WINDOW_HEIGHT/2,"POGN");
	}

	glutSwapBuffers();
}

void Idle()
{
	glm::vec2 lastBallPos = game._ball.pos;

	game._ball.pos += game._ball.vel;



	if (game._ball.pos.y <= 0)
	{
		game._ball.vel.y *= -1;
	}

	if (game._ball.pos.y >= WINDOW_HEIGHT)
	{
		game._ball.vel.y *= -1;
	}

	if (game._titleMode)
	{
		if (game._ball.pos.x <= 0 && game._titleMode)
		{
			game._ball.vel.x *= -1;
		}

		if (game._ball.pos.x >= WINDOW_WIDTH && game._titleMode)
		{
			game._ball.vel.x *= -1;
		}



	}


	else
	{

		if (game._ball.pos.x <= 0)
		{
			//game._ball.vel.x *= -1;
			game._paddles[GAME::TwoP].score++;
			game.InitBallVel();
			game._ball.pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
		}


		if (game._ball.pos.x >= WINDOW_WIDTH )
		{

			//game._ball.vel.x *= -1;
			game._paddles[GAME::OneP].score++;
			game.InitBallVel();
			game._ball.pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };;
		}

		if (game._paddles[GAME::OneP].score >= MAX_SCORE || game._paddles[GAME::TwoP].score >= MAX_SCORE)
		{
			game._titleMode = true;
		}
		
		//glm::vec2 lastBallPos = game._ball.pos;
		
		
		for (int i = 0; i < GAME::MAX_P; i++)
		{
			glm::vec2 paddlePos = game._paddles[i].pos;
			glm::vec2 ballPos = game._ball.pos;
			glm::vec2 ballVel = game._ball.vel;

			if (game._KeysPressed[game._paddles[i].keys[GAME::KEY_UP]])
			{
				game._paddles[i].pos.y -= game._paddleSpeed;

				//パドルの位置を制限する
				if (game._paddles[i].pos.y < 0)
				{
					game._paddles[i].pos.y = 0;
				}
			}

			if (game._KeysPressed[game._paddles[i].keys[GAME::KEY_DOWN]])
			{
				game._paddles[i].pos.y += game._paddleSpeed;

				//パドルの位置を制限する
				if (game._paddles[i].pos.y > WINDOW_HEIGHT - PADDLE_HEIGHT)
				{
					game._paddles[i].pos.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
				}
			}


			glm::vec2 ballFront = game._ball.pos - game._ball.vel ;//* glm::vec2(0.1,0.1);
			glm::vec2 ballBack  = game._ball.pos + game._ball.vel ;//* glm::vec2(0.1, 0.1);
			glm::vec2 paddleBottom = game._paddles[i].pos + glm::vec2(0, PADDLE_HEIGHT);
			glm::vec2 paddleCenter = {game._paddles[i].pos.x,game._paddles[i].pos.y+PADDLE_HEIGHT / 2};

			if (IntersectLine(ballBack,ballFront, game._paddles[i].pos, paddleBottom))
			{
				//game._ball.pos  *= lastBallPos;
				game._ball.vel.x *= -1.0f;

				if (((game._paddles[i].pos.y <= game._ball.pos.y) && (game._ball.pos.y <= game._paddles[i].pos.y + PADDLE_HEIGHT/4)) || ((game._paddles[i].pos.y + 3 * PADDLE_HEIGHT/4<= game._ball.pos.y) && (game._ball.pos.y <= game._paddles[i].pos.y + PADDLE_HEIGHT )))
				{
					game._ballSpeed = 4.0f * game._ballSpeed;
				}
				else
				{
					if (game._ballSpeed > NORMAL_BALLSPEED)
					{
						game._ballSpeed *= 0.9f;
					}
					else
					{
						game._ballSpeed = NORMAL_BALLSPEED;
					}
				}
				
				//std::cout << "BALL SPEED :" << game._ballSpeed << std::endl;
			}
			//game._ball.pos += game._ball.vel;
		}
	}//else


	glutPostRedisplay();
}

		

void Keyboard(unsigned char key, int, int)
{
	game._KeysPressed[key] = true;
	if (game._titleMode)
	{
		game._titleMode = false;

		game.RestartGame();

		//game._ball.pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	}
}

void KeyboardUp(unsigned char key, int, int)
{
	game._KeysPressed[key] = false;
}

int main(int argc, char* argv[])
{
	
	game.Initialize(argc, argv, "POGN");
	
	game.RunLoop(Display,Idle,Keyboard,KeyboardUp);
	//glutDisplayFunc(Display);
	//glutMainLoop();

	return 0;
}