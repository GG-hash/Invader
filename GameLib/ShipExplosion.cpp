#include "ShipExplosion.h"

ShipExplosion::ShipExplosion():_count(0)
{

}

int ShipExplosion::Initialize()
{
    //テクスチャの生成
    glGenTextures(MAX_SHIP_EXPLOSION_ANIM, _textures);
    //テクスチャの読み込み
    for (int i = 0; i < MAX_SHIP_EXPLOSION_ANIM; i++)
    {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        //ファイルを生成する
        char fileName[256];
        //インベーダーの弾の画像を全て読み込んでいく
        sprintf_s(fileName, sizeof(fileName), "image/ship_explosion%d.bmp", i);
        //カラーキーを設定
        unsigned char colorkey[] = { 0x00,0xff,0x00 };
        TextureFromBMP(fileName, colorkey);
    }
    

    //サイズの設定
    vec2 size = vec2(SHIP_EXPLOSION_WIDTH, SHIP_EXPLOSION_HEIGHT);
    SetSize(size);



    return 0;
}//int ShipExplosion::Initialize()


void ShipExplosion::Update()
{
    if (_count <= 0)
        return;

    //表示時間のカウントを減らす
    _count--;

    //残機を減らす処理
    if (_count <= 0)
    {
        gShip.SetRemaningLives(gShip.GetRemaningLives() - 1 );
    }
}//void ShipExplosion::Update()


void ShipExplosion::Draw()
{
    //_countが0になったらエフェクトを消す
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
    //爆破された時の音
    AudioStop(AUDIO_CHANNEL_NOISE);
    AudioFreq(AUDIO_CHANNEL_NOISE, AudioIndexToFreq(14));
    AudioDecay(AUDIO_CHANNEL_NOISE, 0.975f);
    //スイープを無効にしなければ、弾を撃ってやられた時に爆発音が変わってしまう
    AudioSweep(AUDIO_CHANNEL_NOISE, 0);
    AudioPlay(AUDIO_CHANNEL_NOISE);
    //位置の設定
    SetPosition(pos);
    //アニメーションのカウントの初期化
    _count = MAX_SHIP_EXPLOSION_ANIM_COUNT;

}//void ShipExplosion::Start(vec2 const& pos)




