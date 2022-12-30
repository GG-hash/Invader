#include "ShipExplosion.h"

ShipExplosion::ShipExplosion():_count(0)
{

}

int ShipExplosion::Initialize()
{
    //�e�N�X�`���̐���
    glGenTextures(MAX_SHIP_EXPLOSION_ANIM, _textures);
    //�e�N�X�`���̓ǂݍ���
    for (int i = 0; i < MAX_SHIP_EXPLOSION_ANIM; i++)
    {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        //�t�@�C���𐶐�����
        char fileName[256];
        //�C���x�[�_�[�̒e�̉摜��S�ēǂݍ���ł���
        sprintf_s(fileName, sizeof(fileName), "image/ship_explosion%d.bmp", i);
        //�J���[�L�[��ݒ�
        unsigned char colorkey[] = { 0x00,0xff,0x00 };
        TextureFromBMP(fileName, colorkey);
    }
    

    //�T�C�Y�̐ݒ�
    vec2 size = vec2(SHIP_EXPLOSION_WIDTH, SHIP_EXPLOSION_HEIGHT);
    SetSize(size);



    return 0;
}//int ShipExplosion::Initialize()


void ShipExplosion::Update()
{
    if (_count <= 0)
        return;

    //�\�����Ԃ̃J�E���g�����炷
    _count--;

    //�c�@�����炷����
    if (_count <= 0)
    {
        gShip.SetRemaningLives(gShip.GetRemaningLives() - 1 );
    }
}//void ShipExplosion::Update()


void ShipExplosion::Draw()
{
    //_count��0�ɂȂ�����G�t�F�N�g������
    if (_count <= 0)
    {
        return;
    }
    glBindTexture(GL_TEXTURE_2D, _textures[(_count/8) % MAX_SHIP_EXPLOSION_ANIM]);
    SetColorWithPosition(GetPosition());
    Rect::Draw();
}
//void ShipExplosion::Draw()

void ShipExplosion::Start(vec2 const& pos)
{
    //���j���ꂽ���̉�
    AudioStop(AUDIO_CHANNEL_NOISE);
    AudioFreq(AUDIO_CHANNEL_NOISE, AudioIndexToFreq(14));
    AudioDecay(AUDIO_CHANNEL_NOISE, 0.975f);
    //�X�C�[�v�𖳌��ɂ��Ȃ���΁A�e�������Ă��ꂽ���ɔ��������ς���Ă��܂�
    AudioSweep(AUDIO_CHANNEL_NOISE, 0);
    AudioPlay(AUDIO_CHANNEL_NOISE);
    //�ʒu�̐ݒ�
    SetPosition(pos);
    //�A�j���[�V�����̃J�E���g�̏�����
    _count = MAX_SHIP_EXPLOSION_ANIM_COUNT;

}//void ShipExplosion::Start(vec2 const& pos)




