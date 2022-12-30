//�w�b�_�[
#include"GameHeader.h"
#include"Face.h"

//�L�[���i�[����z��̗v�f��
#define MAX_KEY 256

//�L�[�{�[�h�̓��͂�ۑ����邷��z��
bool keys[MAX_KEY];
//Ship��ǉ�����
class Ship gShip;
//Ship�̔���
class ShipExplosion gShipEx;
//Ship�̒e��ǉ�����
class ShipBullet gShipBullet;
//Ship�̒e�̔���
class Explosion gShipBulletEx;
//Invader�̔���
class Explosion gInvaderEx;
//Invader�̒e�̔���
class Explosion gInvaderBulletEx[MAX_INVADER_BULLET];
//Torchka��ǉ�����
class Torchka gTorchka[MAX_TORCHKA];
//�h�q�O��
class LineOfDefence gLineOfDefence;
//Ufo��ǉ�����
class Ufo gUfo;
//Game��ǉ�����
class Game gGame;



void Display()
{
	//��ʂ��N���A����
	glClear(GL_COLOR_BUFFER_BIT);
	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();


	//�w�i�̘f���̕`��
	POINT3D center= { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,-1000.0 };
	LIGHT light = { {0.0f, 0.0,1.0},{1.0,1.0,1.0} };
	CircleWithShading(200.0, center, 200.0, light);

	//�e�N�X�`�����g����悤�ɂ���
	glEnable(GL_TEXTURE_2D);
	//�����x��������悤�ɂ���
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//glDisable(GL_BLEND);

	//Scene�ʂ̕`��
	gGame.GetCurrentScene()->Draw();

	

	//�X�R�A��\������
	vec2 size = vec2(5,DEFAULT_GAME_HEIGHT);
	Text2D( 3 * DEFAULT_GAME_HEIGHT, 0, size, "SCORE<1>");
	Text2D(11 * DEFAULT_GAME_HEIGHT, 0, size, "HI-SCORE");
	Text2D(19 * DEFAULT_GAME_HEIGHT, 0, size, "SCORE<2>");
	size = vec2(5, DEFAULT_GAME_HEIGHT);
	//Text2D( 4 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 2, size, "%04d",gGame.GetScore());
	Text2D(12 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 2, size, "%04d",gGame.GetHiScore());
	//�c�@�̕\��
	gShip.DrawRemaningLives();
	
	 //�N���W�b�g�̕`��
	Text2D(20 * DEFAULT_GAME_HEIGHT, 31 * DEFAULT_GAME_HEIGHT, size, "CREDIT 00");

	//�o�b�t�@��؂�ւ���
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);

}//Display()

//PC�̏������x�Ɉˑ����Ȃ��悤�ɂ��鏈��
void Timer(int value)
{
	//�I�[�f�B�I�̃A�b�v�f�[�g
	AudioUpdate();

	//Scene�̃A�b�v�f�[�g
	gGame.GetCurrentScene()->Update();
	
	//�ċN
	glutTimerFunc(1000/60, Timer, 0);
	//�ĕ`��
	glutPostRedisplay();
}//Timer(int value)

//��ʃT�C�Y���ύX���ꂽ���̏���
void Reshape(int width,int height)
{
	std::cout << "reshshape: width:" << width << " height:" << height << std::endl;
	//��ʃT�C�Y��ύX�����Ƃ��ɁA���؂�镔�����Ȃ���
	glViewport(0,0,width,height);//GLint x, GLint y, GLsizei width, GLsizei height

}//Reshape(int width,int height)

//�L�[�{�[�h���������Ƃ��̏���
//x y �̓}�E�X�̍��W
void Keyboard(unsigned char key, int x, int y)
{
	//Esc�ŃQ�[�����I������
	if (key == 0x1b)
	{
		exit(0);
	}

	keys[key] = true;
	printf("KeyboradDown  : \'%c\' (%#x)\n",key,key);
	//�V�[���ʂ�Keyborad�̊֐����Ăяo��
	gGame.GetCurrentScene()->Keyboard(key);

}//Keyboard(unsigned char key, int x, int y)

//�L�[�{�[�h�𗣂������̏���
void KeyboardUp(unsigned char key, int x, int y)
{
	printf("KeyboradUp    : \'%c\' (%#x)\n", key, key);
	keys[key] = false;
}//KeyboardUp(unsigned char key, int x, int y)

//�}�E�X���������Ƃ��̏���
void PassiveMotion(int x,int y)
{
	vec2 newPos = vec2(x,y);
	//�g�p��
	//paddle.SetPosition(newPos);
}//PassiveMotion(int x,int y)


int main(int argc,char* argv[])
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);//�_�u���o�b�t�@��L���ɂ���
	glutInitWindowPosition(0,0);
	{
		//�E�B���h�E�̃T�C�Y 4:3�ɂ���
		int width = (720 - 32) *4/3;
		int height = 720 - 32;
		glutInitWindowSize(width, height);
	}
	glutCreateWindow("�C���x�[�_�[ !");//�E�B���h�E�̃^�C�g��

	//�����̏�����
	srand((unsigned int)time(NULL));
	//�t�H���g������
	FontInitialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	FontSetXYSize(2,7);

	//�I�[�f�B�I�̏�����
	if (AudioInit() != 0)
	{
		return -1;
	}

	//Game�̏�����
	gGame.Initialize();
	//Ship�̏�����
	gShip.Initialize();
	printf("Ship����������\n");
	//Ship�̔����̏�����
	gShipEx.Initialize();
	printf("ShipExplosion����������\n");
	//Torchka�̏�����
	Torchka::AllInitialize();
	Torchka::InitializeDestroyedTorchka();
	printf("Torchka����������\n");
	//Ufo�̏�����
	gUfo.Initialize();
	printf("Ufo�̏���������\n");
	//�e�̏�����
	gShipBullet.Initialize();
	printf("Bullet����������\n");
	//�e�̔����̏�����
	gShipBulletEx.Initialize("image/BulletExplosion.bmp",vec2(8,8));
	printf("ShipBulletEx����������\n");
	//�G�̔����̏�����
	gInvaderEx.Initialize("image/invader_explosion.bmp",vec2(13,8));
	printf("InvaderEx����������\n");
	//�G�̒e�̔����̏�����
	for (int i = 0; i < MAX_INVADER_BULLET; i++)
	{
		gInvaderBulletEx[i].Initialize("image/invader_bullet_explosion.bmp", vec2(6, 8));
	}
	printf("gInvaderBulletEx����������\n");
	//�C���x�[�_�[�̏�����
	Invader::AllInitialize();
	printf("Invader����������\n");
	//�C���x�[�_�[�̒e�̏�����
	InvaderBullet::AllInitialize();
	printf("InvaderBullet����������\n");
	//�h�q�O���̏�����
	gLineOfDefence.Initialize();
	printf("LineOfDefence����������\n");
	//MainScene�̏�����
	//printf("MainScene�̏���������\n");
	//�X�e�[�W�̃��Z�b�g
	gGame.GetCurrentScene()->Reset();
	

	printf("�S�Ă̏���������\n");

	glutDisplayFunc(Display);
	//glutIdleFunc(Idle);
	glutTimerFunc(0,Timer,0);//0�~���b���Timer�֐����J�n����,value��0
	//��ʃT�C�Y���ύX���ꂽ���ɌĂяo�����A�R�[���o�b�N�֐�
	glutReshapeFunc(Reshape);
	//�L�[�{�[�h����
	glutKeyboardFunc(Keyboard);// void (* callback)( unsigned char, int, int ) 
	//�L�[�{�[�h�𗣂������̏���
	glutKeyboardUpFunc(KeyboardUp);
	//�N���b�N���ꂽ�}�E�X�̈ړ������o����
	//glutMotionFunc(Motion);
	
	//�N���b�N����Ă��Ȃ��}�E�X�̈ړ������o����
	glutPassiveMotionFunc(PassiveMotion);

	//�L�[�{�[�h�̃��s�[�g�i�]��ɂ������A�����́j�𖳌��ɂ���
	//��񂵂����͂���Ȃ�
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore


	//�Q�[�����[�v
	glutMainLoop();

	return 0;
}//main(int argc,char* argv[])