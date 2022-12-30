#pragma once
#include"Rect.h"
#include"Color.h"
#include"Texture.h"
#include"InvaderBullet.h"

//Torchka�̕�
#define TORCHKA_WIDTH 22
//Torchka�̍���
#define TORCHKA_HEIGHT 16
//Torchka�̐�
#define MAX_TORCHKA 4
//Torchka��y���W
#define TORCHKA_POSITION_Y (SCREEN_HEIGHT - DEFAULT_GAME_HEIGHT * 8)
//DestroyedTorchka�̕�
#define DESTROYED_TORCHKA_WIDTH 8
//DestroyedTorchka�̍���
#define DESTROYED_TORCHKA_HEIGHT 16

//�e���N�ɔj�󂳂ꂽ����񋓌^�ŕ\��
enum
{
	DESTROYED_BY_INVADER,
	DESTROYED_BY_SHIP,
	DESTROYED_MAX,
};

class Torchka : public Rect
{
private:
	//Torchka�̉摜���s�N�Z�����ƂɊi�[
	unsigned char _pixels[TORCHKA_HEIGHT][TORCHKA_WIDTH];
	//�e�N�X�`��
	unsigned int _texture;
	
public:
	//Torchka�̔���������������֐�
	int Initialize();
	//�S�Ă�Torchka��������
	static int AllInitialize();
	//�j�󂳂ꂽTorchka�̏�����
	static int InitializeDestroyedTorchka();
	//���Z�b�g����֐�
	void Reset();
	//�s�N�Z������������֐�
	int ErasePixel(vec2 const& pos);
	//�X�V����֐�
	void Update() override;
	static void AllUpdate();
	//�`�悷��֐�
	void Draw() override;
	//Rect�N���X�̓����蔻��̊֐����I�[�o�[���C�h����
	bool IntersectRect(vec2 const& point) override;
	//Torchka�̔j��
	void Destroy(vec2 const& pos,int destroyedBy);
	
};//class Torchka : public Rect

