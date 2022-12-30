//ヘッダー
#include"GameHeader.h"
#include"Face.h"

//キーを格納する配列の要素数
#define MAX_KEY 256

//キーボードの入力を保存するする配列
bool keys[MAX_KEY];
//Shipを追加する
class Ship gShip;
//Shipの爆発
class ShipExplosion gShipEx;
//Shipの弾を追加する
class ShipBullet gShipBullet;
//Shipの弾の爆発
class Explosion gShipBulletEx;
//Invaderの爆発
class Explosion gInvaderEx;
//Invaderの弾の爆発
class Explosion gInvaderBulletEx[MAX_INVADER_BULLET];
//Torchkaを追加する
class Torchka gTorchka[MAX_TORCHKA];
//防衛前線
class LineOfDefence gLineOfDefence;
//Ufoを追加する
class Ufo gUfo;
//Gameを追加する
class Game gGame;



void Display()
{
	//画面をクリアする
	glClear(GL_COLOR_BUFFER_BIT);
	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();


	//背景の惑星の描画
	POINT3D center= { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,-1000.0 };
	LIGHT light = { {0.0f, 0.0,1.0},{1.0,1.0,1.0} };
	CircleWithShading(200.0, center, 200.0, light);

	//テクスチャを使えるようにする
	glEnable(GL_TEXTURE_2D);
	//透明度を扱えるようにする
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//glDisable(GL_BLEND);

	//Scene別の描画
	gGame.GetCurrentScene()->Draw();

	

	//スコアを表示する
	vec2 size = vec2(5,DEFAULT_GAME_HEIGHT);
	Text2D( 3 * DEFAULT_GAME_HEIGHT, 0, size, "SCORE<1>");
	Text2D(11 * DEFAULT_GAME_HEIGHT, 0, size, "HI-SCORE");
	Text2D(19 * DEFAULT_GAME_HEIGHT, 0, size, "SCORE<2>");
	size = vec2(5, DEFAULT_GAME_HEIGHT);
	//Text2D( 4 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 2, size, "%04d",gGame.GetScore());
	Text2D(12 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 2, size, "%04d",gGame.GetHiScore());
	//残機の表示
	gShip.DrawRemaningLives();
	
	 //クレジットの描画
	Text2D(20 * DEFAULT_GAME_HEIGHT, 31 * DEFAULT_GAME_HEIGHT, size, "CREDIT 00");

	//バッファを切り替える
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);

}//Display()

//PCの処理速度に依存しないようにする処理
void Timer(int value)
{
	//オーディオのアップデート
	AudioUpdate();

	//Sceneのアップデート
	gGame.GetCurrentScene()->Update();
	
	//再起
	glutTimerFunc(1000/60, Timer, 0);
	//再描画
	glutPostRedisplay();
}//Timer(int value)

//画面サイズが変更された時の処理
void Reshape(int width,int height)
{
	std::cout << "reshshape: width:" << width << " height:" << height << std::endl;
	//画面サイズを変更したときに、見切れる部分をなくす
	glViewport(0,0,width,height);//GLint x, GLint y, GLsizei width, GLsizei height

}//Reshape(int width,int height)

//キーボードを押したときの処理
//x y はマウスの座標
void Keyboard(unsigned char key, int x, int y)
{
	//Escでゲームを終了する
	if (key == 0x1b)
	{
		exit(0);
	}

	keys[key] = true;
	printf("KeyboradDown  : \'%c\' (%#x)\n",key,key);
	//シーン別のKeyboradの関数を呼び出す
	gGame.GetCurrentScene()->Keyboard(key);

}//Keyboard(unsigned char key, int x, int y)

//キーボードを離した時の処理
void KeyboardUp(unsigned char key, int x, int y)
{
	printf("KeyboradUp    : \'%c\' (%#x)\n", key, key);
	keys[key] = false;
}//KeyboardUp(unsigned char key, int x, int y)

//マウスが動いたときの処理
void PassiveMotion(int x,int y)
{
	vec2 newPos = vec2(x,y);
	//使用例
	//paddle.SetPosition(newPos);
}//PassiveMotion(int x,int y)


int main(int argc,char* argv[])
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);//ダブルバッファを有効にする
	glutInitWindowPosition(0,0);
	{
		//ウィンドウのサイズ 4:3にする
		int width = (720 - 32) *4/3;
		int height = 720 - 32;
		glutInitWindowSize(width, height);
	}
	glutCreateWindow("インベーダー !");//ウィンドウのタイトル

	//乱数の初期化
	srand((unsigned int)time(NULL));
	//フォント初期化
	FontInitialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	FontSetXYSize(2,7);

	//オーディオの初期化
	if (AudioInit() != 0)
	{
		return -1;
	}

	//Gameの初期化
	gGame.Initialize();
	//Shipの初期化
	gShip.Initialize();
	printf("Ship初期化完了\n");
	//Shipの爆発の初期化
	gShipEx.Initialize();
	printf("ShipExplosion初期化完了\n");
	//Torchkaの初期化
	Torchka::AllInitialize();
	Torchka::InitializeDestroyedTorchka();
	printf("Torchka初期化完了\n");
	//Ufoの初期化
	gUfo.Initialize();
	printf("Ufoの初期化完了\n");
	//弾の初期化
	gShipBullet.Initialize();
	printf("Bullet初期化完了\n");
	//弾の爆発の初期化
	gShipBulletEx.Initialize("image/BulletExplosion.bmp",vec2(8,8));
	printf("ShipBulletEx初期化完了\n");
	//敵の爆発の初期化
	gInvaderEx.Initialize("image/invader_explosion.bmp",vec2(13,8));
	printf("InvaderEx初期化完了\n");
	//敵の弾の爆発の初期化
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		gInvaderBulletEx[i].Initialize("image/invader_bullet_explosion.bmp", vec2(6, 8));
	}
	printf("gInvaderBulletEx初期化完了\n");
	//インベーダーの初期化
	Invader::AllInitialize();
	printf("Invader初期化完了\n");
	//インベーダーの弾の初期化
	InvaderBullet::AllInitialize();
	printf("InvaderBullet初期化完了\n");
	//防衛前線の初期化
	gLineOfDefence.Initialize();
	printf("LineOfDefence初期化完了\n");
	//MainSceneの初期化
	//printf("MainSceneの初期化完了\n");
	//ステージのリセット
	gGame.GetCurrentScene()->Reset();
	

	printf("全ての初期化完了\n");

	glutDisplayFunc(Display);
	//glutIdleFunc(Idle);
	glutTimerFunc(0,Timer,0);//0ミリ秒後にTimer関数を開始して,valueは0
	//画面サイズが変更された時に呼び出される、コールバック関数
	glutReshapeFunc(Reshape);
	//キーボード入力
	glutKeyboardFunc(Keyboard);// void (* callback)( unsigned char, int, int ) 
	//キーボードを離した時の処理
	glutKeyboardUpFunc(KeyboardUp);
	//クリックされたマウスの移動を検出する
	//glutMotionFunc(Motion);
	
	//クリックされていないマウスの移動を検出する
	glutPassiveMotionFunc(PassiveMotion);

	//キーボードのリピート（余りにも早い連続入力）を無効にする
	//一回しか入力されない
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore


	//ゲームループ
	glutMainLoop();

	return 0;
}//main(int argc,char* argv[])