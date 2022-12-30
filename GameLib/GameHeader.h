#pragma once

//��ʃT�C�Y �t�@�~�R���̉�ʃT�C�Y�́@256 * 256
#define SCREEN_WIDTH  224
#define SCREEN_HEIGHT 256
//�X�R�A�̕�����\�����鍂��
#define SCORE_HEIGHT    3
//�X�R�A�̕����񂩂�C���x�[�_�[�������c�̕�
#define FROM_SCORE_TO_INVADER 3
//�Q�[���Ŋ�ƂȂ�傫��
#define DEFAULT_GAME_HEIGHT   8
//��ʂ̒��S�̍���
#define SCREEN_CENTER_HEIGHT 16

#include<iostream>
#include<time.h>
#include"Font.h"
#include"GL/glut.h"
#include"Rect.h"
#include"Audio.h"
#include"Ship.h"
#include"ShipExplosion.h"
#include"Torchka.h"
#include"Invader.h"
#include"Ufo.h"
#include"Bullet.h"
#include"ShipBullet.h"
#include"InvaderBullet.h"
#include"Explosion.h"
#include"Game.h"
#include"LineOfDefence.h"
#include"TitleScene.h"
#include"ReadyScene.h"
#include"MainScene.h"
#include"Color.h"
using namespace std;

//�L�[�{�[�h�̓��͂�ۑ����邷��z��@�O������A�N�Z�X�ł���悤�ɂ���
extern bool keys[256];
//Ship�̃f�[�^���O������A�N�Z�X�ł���悤�ɂ���
extern class Ship gShip;
//Ship�̔��� 
extern class ShipExplosion gShipEx;
//�e�̃f�[�^���O������A�N�Z�X�ł���悤�ɂ���
extern class ShipBullet gShipBullet;
//Ship�̒e�̔���
extern class Explosion gShipBulletEx;
//Invader�̔���
extern class Explosion gInvaderEx;
//InvaderBullet�̒ǉ�
//extern class InvaderBullet gInvaderBullets[MAX_INVADER_BULLET];
//Invader�̒e�̔���      MAX_INVADER_BULLET (2) �������m��
extern class Explosion gInvaderBulletEx[2];
//�h�q�O��
extern class LineOfDefence gLineOfDefence;
//Torchka MAX_INVADER_BULLET (4) �������m��
extern class Torchka gTorchka[4];
//Ufo��ǉ�����
extern class Ufo gUfo;
//Game��ǉ�����
extern class Game gGame;
//TitleScene��ǉ�����
//extern class TitleScene gTitleScene;
////ReadyScene��ǉ�����
//extern class ReadyScene gReadyScene;
////MainScene��ǉ�����@�^�C�g����ʂ�Q�[����ʂ𑀍삷��
//extern class MainScene gMainScene;
