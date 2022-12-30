#include "MyEngine.h"


void MyEngine::Initialize(int argc, char* argv[], const char* title, int WinPosX, int WinposY, int WinWidth, int WinHeight)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(WinPosX, WinposY);
	glutInitWindowSize(WinWidth, WinHeight);
	glutCreateWindow(title);
}