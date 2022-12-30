#include "InvaderBullet.h"

//�e�̃f�[�^
class InvaderBullet gInvaderBullets[MAX_INVADER_BULLET];
//�r�[���̃e�N�X�`��
static GLuint gTextures[MAX_INVADER_BULLET_ANIMATION_TYPE][INVADER_BULLET_ANIMATION_LENGTH];

//�R���X�g���N�^
InvaderBullet::InvaderBullet():_index(0)
{

}//InvaderBullet::InvaderBullet()


int InvaderBullet::Initialize()
{

    //�e�N�X�`���̐���
    glGenTextures(MAX_INVADER_BULLET_ANIMATION_TYPE * INVADER_BULLET_ANIMATION_LENGTH, *gTextures);
   
    //�摜�̓ǂݍ���
    {
        char fileName[256];
        for (int i = 0; i < MAX_INVADER_BULLET_ANIMATION_TYPE; i++)
        {
            for (int j = 0; j < INVADER_BULLET_ANIMATION_LENGTH; j++)
            {
                //�C���x�[�_�[�̒e�̉摜��S�ēǂݍ���ł���
                sprintf_s(fileName,sizeof(fileName),"image/invader_bullet%d-%d.bmp",i,j);
                //����t����e�N�X�`����ݒ肷��
                glBindTexture(GL_TEXTURE_2D, gTextures[i][j]);
                //�摜�t�@�C����ǂݍ���
                TextureFromBMP(fileName,0x00,0xff,0x00);
            }//for (int j = 0; j < INVADER_BULLET_ANIMATION_LENGTH; j++)
        }//for (int i = 2; i < MAX_INVADER_BULLET_ANIMATION_TYPE; i++)
    }
    //�e�̕���ݒ肷��
    vec2 size = vec2(INVADER_BULLET_WIDTH,INVADER_BULLET_HEIGHT);
    SetSize(size);


    return 0;
}//int InvaderBullet::Initialize()


int InvaderBullet::AllInitialize()
{
    for (int i = 0; i < MAX_INVADER_BULLET; i++)
    {
        //�e�ɃC���f�b�N�X����������
        gInvaderBullets[i]._index = i;
        gInvaderBullets[i].Initialize();
    }//    for (int i = 0; i < MAX_INVADER_BULLET; i++)

    return 0;
}
//int InvaderBullet::AllInitialize()

void InvaderBullet::Attack(vec2 const& pos, class Invader* owner)
{
    //�e��L���ɂ���
    _enable = true;
    //�e�̏����ʒu��ݒ肷��
    SetPosition(pos);
    //�ǂ̃C���x�[�_�[���e�𔭎˂������ۑ�����
    _owner = owner;
    //�A�j���[�V������i�߂�
    //�r�[���̎�ނ�MAX_INVADER_BULLET_ANIMATION_TYPE�̐�����A�����_���ŉ摜���I�΂��
    _animType = rand() % MAX_INVADER_BULLET_ANIMATION_TYPE;
    //��R�}��R�}�̕\�����Ԃ����Z�b�g���Ă���
    _animDisplayFrame = INVADER_BULLET_ANIM_DISPLAY;
}//void InvaderBullet::Attack(vec2 const& pos)


void InvaderBullet::Update()
{
    //�����ҋ@��Ԃ��L���Ȃ�A�e��`�悷��
    if (_enable == false)
    {
        return;
    }

    //�e�̈ʒu���X�V����
    this->InvaderBullet::GetPosition().y += INVADER_BULLET_SPEED;

    //�e��Ship�ɓ����������̏���
    //�e��Ship�ɂԂ��邩�A���j�̃A�j���[�V�������Đ�����Ă��Ȃ���Ώ�������
    vec2 bulletPos = Rect::GetPosition() + vec2((int)GetSize().x / 2.0, GetSize().y);
    if (gShip.IntersectRect(bulletPos) && (gShipEx._count <= 0))
    {
        vec2 pos = vec2(gShip.GetPosition().x - (gShipEx.GetSize().x - gShip.GetSize().x)/2.0, gShip.GetPosition().y);
        gShipEx.Start(pos);
        //Ship�ɒe������������A�e�����ł�����
        _enable = false;
        //Ship�̈ʒu���Q�[���J�n���̏ꏊ�ɖ߂�
        gShip.GetPosition().x = SHIP_DEFAULT_X;
        //�e�̏������I����
        return;

    }//if (gShip.IntersectRect(GetPosition() + vec2((int)GetSize().x/2.0,GetSize().y)))

    //�e����ʊO�֏o���Ƃ��̏���
    if (this->GetPosition().y >= SCREEN_HEIGHT - 8 - GetSize().y)
    {
        //�ҋ@��Ԃɂ��� �r�[��������
        _enable = false;
        //�G�̒e�̔����̕`��
            //��������܂ł̃J�E���g��0�ȉ��Ȃ甚���̃A�j���[�V�������Đ�����
           /* if (gInvaderBulletEx[_index]._count <= 0)
            {*/
                //�����̈ʒu���v�Z����
                vec2 pos = vec2(GetPosition().x - (gInvaderBulletEx[_index].GetSize().x - GetSize().x)
                               ,GetPosition().y);
                //�����̃A�j���[�V�������Đ�
                gInvaderBulletEx[_index].Start(pos);
                
            //}//if (gInvaderBulletEx[i]._count <= 0)


        //�e�����������Ƃ���̖h�q�O�����폜����
        int x = (int)GetPosition().x + (int)(GetSize().x / 2.0f);
        for (int i = x - 2; i <= x + 2; i+=2)
        {
            gLineOfDefence.EraseLine(x);
        }//for (int i = x - 1; i < x + 1; i++)

         //�e�̏������I����
        return;
    }//if (this->GetPosition().y >= SCREEN_HEIGHT - 8 - GetSize().y)

    //INVADER_BULLET_ANIM_DISPLAY �t���[���������r�[���̉摜��R�}����\������
    if (_animDisplayFrame > 0)
    {
        _animDisplayFrame--;
    }//if (_animDisplayFrame > 0)
    else
    {
        //�e�̃A�j���[�V������i�߂� 0�`3�̒l���J��Ԃ����
        ++_currentAnimPhase %= INVADER_BULLET_ANIMATION_LENGTH;
        _animDisplayFrame = INVADER_BULLET_ANIM_DISPLAY;
    }

}//void InvaderBullet::Update()


void InvaderBullet::AllUpdate()
{
    for (int i = 0; i < MAX_INVADER_BULLET; i++)
    {
        gInvaderBullets[i].Update();
    }//    for (int i = 0; i < MAX_INVADER_BULLET; i++)
}//void InvaderBullet::Allupdate()                          


void InvaderBullet::Draw()
{
    //�����ҋ@��Ԃ��L���Ȃ�A�e��`�悷��
    if (_enable == false)
    {
        return;
    }

    //�e�̃A�j���[�V�����𒣂�t����
    glBindTexture(GL_TEXTURE_2D, gTextures[_animType][_currentAnimPhase]);
    //�e�̐F��ݒ肷��
    SetColorWithPosition(GetPosition());
    //��`�̕`��
    Rect::Draw();

}//void InvaderBullet::Draw()


void InvaderBullet::AllDraw()
{
    for (int i = 0; i < MAX_INVADER_BULLET; i++)
    {
        gInvaderBullets[i].Draw();
    }//    for (int i = 0; i < MAX_INVADER_BULLET; i++)
}
//void InvaderBullet::DrawAll()

int InvaderBullet::GetShootingCount()
{
    int count = 0;
    for (int i = 0; i < MAX_INVADER_BULLET; i++)
    {
        //�����e���L���Ȃ�count��1���₷
        if (gInvaderBullets[i]._enable)
        {
            count++;
        }
    }//for (int i = 0; i < MAX_INVADER_BULLET; i++)
    return count;
}//int InvaderBullet::GetShootingCount()


