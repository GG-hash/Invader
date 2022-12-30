#include "InvaderBullet.h"

//弾のデータ
class InvaderBullet gInvaderBullets[MAX_INVADER_BULLET];
//ビームのテクスチャ
static GLuint gTextures[MAX_INVADER_BULLET_ANIMATION_TYPE][INVADER_BULLET_ANIMATION_LENGTH];

//コンストラクタ
InvaderBullet::InvaderBullet():_index(0)
{

}//InvaderBullet::InvaderBullet()


int InvaderBullet::Initialize()
{

    //テクスチャの生成
    glGenTextures(MAX_INVADER_BULLET_ANIMATION_TYPE * INVADER_BULLET_ANIMATION_LENGTH, *gTextures);
   
    //画像の読み込み
    {
        char fileName[256];
        for (int i = 0; i < MAX_INVADER_BULLET_ANIMATION_TYPE; i++)
        {
            for (int j = 0; j < INVADER_BULLET_ANIMATION_LENGTH; j++)
            {
                //インベーダーの弾の画像を全て読み込んでいく
                sprintf_s(fileName,sizeof(fileName),"image/invader_bullet%d-%d.bmp",i,j);
                //張り付けるテクスチャを設定する
                glBindTexture(GL_TEXTURE_2D, gTextures[i][j]);
                //画像ファイルを読み込む
                TextureFromBMP(fileName,0x00,0xff,0x00);
            }//for (int j = 0; j < INVADER_BULLET_ANIMATION_LENGTH; j++)
        }//for (int i = 2; i < MAX_INVADER_BULLET_ANIMATION_TYPE; i++)
    }
    //弾の幅を設定する
    vec2 size = vec2(INVADER_BULLET_WIDTH,INVADER_BULLET_HEIGHT);
    SetSize(size);


    return 0;
}//int InvaderBullet::Initialize()


int InvaderBullet::AllInitialize()
{
    for (int i = 0; i < MAX_INVADER_BULLET; i++)
    {
        //弾にインデックスを持たせる
        gInvaderBullets[i]._index = i;
        gInvaderBullets[i].Initialize();
    }//    for (int i = 0; i < MAX_INVADER_BULLET; i++)

    return 0;
}
//int InvaderBullet::AllInitialize()

void InvaderBullet::Attack(vec2 const& pos, class Invader* owner)
{
    //弾を有効にする
    _enable = true;
    //弾の初期位置を設定する
    SetPosition(pos);
    //どのインベーダーが弾を発射したか保存する
    _owner = owner;
    //アニメーションを進める
    //ビームの種類はMAX_INVADER_BULLET_ANIMATION_TYPEの数あり、ランダムで画像が選ばれる
    _animType = rand() % MAX_INVADER_BULLET_ANIMATION_TYPE;
    //一コマ一コマの表示時間をリセットしておく
    _animDisplayFrame = INVADER_BULLET_ANIM_DISPLAY;
}//void InvaderBullet::Attack(vec2 const& pos)


void InvaderBullet::Update()
{
    //もし待機状態が有効なら、弾を描画する
    if (_enable == false)
    {
        return;
    }

    //弾の位置を更新する
    this->InvaderBullet::GetPosition().y += INVADER_BULLET_SPEED;

    //弾がShipに当たった時の処理
    //弾がShipにぶつかるかつ、爆破のアニメーションが再生されていなければ処理する
    vec2 bulletPos = Rect::GetPosition() + vec2((int)GetSize().x / 2.0, GetSize().y);
    if (gShip.IntersectRect(bulletPos) && (gShipEx._count <= 0))
    {
        vec2 pos = vec2(gShip.GetPosition().x - (gShipEx.GetSize().x - gShip.GetSize().x)/2.0, gShip.GetPosition().y);
        gShipEx.Start(pos);
        //Shipに弾が当たったら、弾を消滅させる
        _enable = false;
        //Shipの位置をゲーム開始時の場所に戻す
        gShip.GetPosition().x = SHIP_DEFAULT_X;
        //弾の処理を終える
        return;

    }//if (gShip.IntersectRect(GetPosition() + vec2((int)GetSize().x/2.0,GetSize().y)))

    //弾が画面外へ出たときの処理
    if (this->GetPosition().y >= SCREEN_HEIGHT - 8 - GetSize().y)
    {
        //待機状態にする ビームを消す
        _enable = false;
        //敵の弾の爆発の描画
            //爆発するまでのカウントが0以下なら爆発のアニメーションを再生する
           /* if (gInvaderBulletEx[_index]._count <= 0)
            {*/
                //爆発の位置を計算する
                vec2 pos = vec2(GetPosition().x - (gInvaderBulletEx[_index].GetSize().x - GetSize().x)
                               ,GetPosition().y);
                //爆発のアニメーションを再生
                gInvaderBulletEx[_index].Start(pos);
                
            //}//if (gInvaderBulletEx[i]._count <= 0)


        //弾が当たったところの防衛前線を削除する
        int x = (int)GetPosition().x + (int)(GetSize().x / 2.0f);
        for (int i = x - 2; i <= x + 2; i+=2)
        {
            gLineOfDefence.EraseLine(x);
        }//for (int i = x - 1; i < x + 1; i++)

         //弾の処理を終える
        return;
    }//if (this->GetPosition().y >= SCREEN_HEIGHT - 8 - GetSize().y)

    //INVADER_BULLET_ANIM_DISPLAY フレーム分だけビームの画像一コマ分を表示する
    if (_animDisplayFrame > 0)
    {
        _animDisplayFrame--;
    }//if (_animDisplayFrame > 0)
    else
    {
        //弾のアニメーションを進める 0～3の値が繰り返される
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
    //もし待機状態が有効なら、弾を描画する
    if (_enable == false)
    {
        return;
    }

    //弾のアニメーションを張り付ける
    glBindTexture(GL_TEXTURE_2D, gTextures[_animType][_currentAnimPhase]);
    //弾の色を設定する
    SetColorWithPosition(GetPosition());
    //矩形の描画
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
        //もし弾が有効ならcountを1増やす
        if (gInvaderBullets[i]._enable)
        {
            count++;
        }
    }//for (int i = 0; i < MAX_INVADER_BULLET; i++)
    return count;
}//int InvaderBullet::GetShootingCount()


