#include "Text.h"

//Font()
//{
//	/*_pos = {};
//	_size = FONT_DEFAULT_SIZE;
//	_color[0] = 1;
//	_color[1] = 1;
//	_color[2] = 1;*/
//}

void FontBegin()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//�񎟌���Ԃ��`
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void FontEnd()
{
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
}

void FontSetPosition(float x, float y)
{
	_pos = vec2(x, y);
}

float FontGetSize()
{
	return _size;
}

void FontSetSize(float size)
{
	_size = size;
}

void FontColor(unsigned char r, unsigned char g, unsigned char b)
{
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
}

void FontColor(unsigned char* color)
{
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];
}

void FontDraw(const char* charactor, ...)
{
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(_pos.x, _pos.y + _size, 0);
		float s = _size / FONT_DEFAULT_SIZE;
		glScalef(s, -s, s);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();
}

//Text2D(float X���W, float Y���W, unsigned char* �F, float �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, float size, const char* charactor, ...)
{

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//�񎟌���Ԃ��`
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//�F�̐ݒ�
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//�����T�C�Y
	_size = size;

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(_pos.x, _pos.y + _size, 0);
		float s = _size / FONT_DEFAULT_SIZE;
		glScalef(s, -s, s);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�

	/*FontBegin();

	FontColor(Color.LightGray);
	FontSetPosition(0, WINDOW_HEIGHT - FontGetSize() * 1.5);
	FontSetSize(FONT_DEFAULT_SIZE / 2);
	FontDraw("angle : %f", angle);

	FontEnd();*/
}

//Text2D(float X���W, float Y���W, float �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, float size, const char* charactor, ...)
{
	//������
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//�񎟌���Ԃ��`
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//���F�̐ݒ�
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//�����T�C�Y
	_size = size;

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(posX, posY + size, 0);
		float scale = size / FONT_DEFAULT_SIZE;
		glScalef(scale, -scale, scale);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
}

//Text2D(float X���W, float Y���W,const char* ������, ...)
void Text2D(float posX, float posY, const char* charactor, ...)
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	GLint viewport[4];
	//The params parameter returns four values: 
	//the x and y window coordinates of the viewport, 
	//followed by its width and height. See glViewport.
	glGetIntegerv(GL_VIEWPORT, viewport);

	//�񎟌���Ԃ��`
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//���F�̐ݒ�
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//�����T�C�Y
	float size = FONT_DEFAULT_SIZE / 2;

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	{
		glTranslatef(posX, posY + size, 0);
		float scale = size / FONT_DEFAULT_SIZE;
		glScalef(scale, -scale, scale);
		for (char* ptr = str; *ptr != '\0'; ptr++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *ptr);
	}
	glPopMatrix();

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
}
