#include "Torchka.h"

//破壊されたTorchkaのテクスチャ
static unsigned int _destroyedTorchkaTexture[DESTROYED_MAX]={};
//破壊されたTorchkaのピクセルデータ
static unsigned char  _destroyedTorchkaPixels[DESTROYED_MAX][DESTROYED_TORCHKA_HEIGHT][DESTROYED_TORCHKA_WIDTH] = {};

int Torchka::Initialize()
{
    //サイズの設定
    vec2 size = vec2(TORCHKA_WIDTH, TORCHKA_HEIGHT);
    SetSize(size);

    //テクスチャの生成
    glGenTextures(1, &_texture);
    //glBindTexture(GL_TEXTURE_2D, _texture);

    //アルファの情報のみの画像を取得
    TextureAlphaFromBMP("image/torchka.bmp", *_pixels);



    return 0;
}//int Torchka::Initialize()

int Torchka::AllInitialize()
{
    int x = (SCREEN_WIDTH - TORCHKA_WIDTH * (MAX_TORCHKA * 2 - 1)) / 2;

    for (int y = 0; y < MAX_TORCHKA; y++)
    {
        gTorchka[y].Initialize();
        //Torchkaの座標の設定
        vec2 pos = vec2(x, TORCHKA_POSITION_Y);
        gTorchka[y].SetPosition(pos);

        x += 2 * TORCHKA_WIDTH;
    }
    return 0;
}//int Torchka::AllInitializer()



int Torchka::InitializeDestroyedTorchka()
{
    //テクスチャの生成
    glGenTextures(DESTROYED_MAX, _destroyedTorchkaTexture);
    //ファイルの名前
    const char* fileName[] =
    {
        "image/destroyed_torchka_by_invader.bmp", //インベーダーに破壊された時のTorchkaの画像
        "image/destroyed_torchka_by_ship.bmp"     //Shipに破壊された時のTorchkaの画像
    };
    for (int i = 0; i < DESTROYED_MAX; i++)
    {
        glBindTexture(GL_TEXTURE_2D, _destroyedTorchkaTexture[i]);
        //アルファ(透明度)の情報のみの画像を取得
        TextureAlphaFromBMP(fileName[i], *_destroyedTorchkaPixels[i]);
    }// for (int i = 0; i < DESTROYED_MAX; i++)
    return 0;
}//int Torchka::InitializeDestroyedTorchka()


void Torchka::Reset()
{
    glBindTexture(GL_TEXTURE_2D, _texture);
    //アルファの情報のみの画像を取得
    TextureAlphaFromBMP("image/torchka.bmp", *_pixels);

}//void Torchka::Reset()



int Torchka::ErasePixel(vec2 const& pos)
{
    //弾との当たり判定の処理
    if (Rect::IntersectRect(pos) == false)
    {
        return 1;
    }

    //Torchka内の座標を計算する
    //ローカル座標にする
    ivec2 localPos = (ivec2)pos - (ivec2)Torchka::GetPosition();
    //unsigned char pixel = _pixels[localPos.y][localPos.x];

    //配列の要素数を超えないようにする
    if (localPos.x < 0)
    {
        localPos.x = 0;
    }
    else if (localPos.x >= TORCHKA_WIDTH)
    {
        localPos.x = TORCHKA_WIDTH - 1;
    }
    if (localPos.y < 0)
    {
        localPos.y = 0;
    }
    else if (localPos.y >= TORCHKA_HEIGHT)
    {
        localPos.y = TORCHKA_HEIGHT - 1;
    }

    //printf("Erase2: x = %d, y = %d\n", localPos.x, localPos.y);

    //pixcelにTorchkaの画像が入っていたらその画像（1ピクセル）消す
    if (_pixels[localPos.y][localPos.x] != 0)
    {
        _pixels[localPos.y][localPos.x] = 0;
        return 0;
    }
    else
    {
        return 1;
    }
}//int Torchka::ErasePixel(vec2 const& pos)



void Torchka::Update()
{
   
}//void Torchka::Update()

void Torchka::AllUpdate()
{
    for (int i = 0; i < MAX_TORCHKA; i++)
    {
        //Shipの弾がTorchkaに当たった時の処理
        if (gTorchka[i].IntersectRect(gShipBullet.GetPosition()))
        {
            //弾を削除する
            gShipBullet._enable = false;
            //弾の当たった場所を削除する
            gTorchka[i].Destroy(gShipBullet.GetPosition(),DESTROYED_BY_SHIP);
            

            //ビームがTorchkaに当たったら消す処理
            gShipBulletEx.Start(gShipBullet.GetPosition() - gShipBulletEx.GetSize() / 2.0f);
            
        }//if (gTorchka[i].IntersectRect(gBullet.GetPosition()))
        

        for (int j = 0; j < MAX_INVADER_BULLET; j++)
        {
            vec2 pos = gInvaderBullets[j].GetPosition() +
                vec2((int)gInvaderBullets[j].GetSize().x / 2, gInvaderBullets[j].GetSize().y);

            //当たり判定
            if (gTorchka[i].IntersectRect(pos))
            {
                // printf("%d番目 Destroy : x = %f, y = %f\n",i,pos.x,pos.y);
                gTorchka[i].Destroy(pos, DESTROYED_BY_INVADER);
                //Torchkaに当たったインベーダの弾を消滅させる
                gInvaderBullets[j]._enable = false;
                //弾が爆発するアニメーションの開始
                {
                    // 爆発の位置を計算する
                    vec2 pos = vec2(gInvaderBullets[j].GetPosition().x - (gInvaderBulletEx[gInvaderBullets[j]._index].
                        GetSize().x - gInvaderBullets[j].GetSize().x),
                        gInvaderBullets[j].GetPosition().y + gInvaderBullets[j].GetSize().y);
                    //爆発のアニメーションを再生
                    gInvaderBulletEx[gInvaderBullets[j]._index].Start(pos);
                }
            }
            //if (gTorchka[i].IntersectRect(pos))
        }
        //gTorchka[y].Update();


        //インベーダーがTorchkaに触れたときの処理
        for (int j = 0; j < MAX_INVADER_ROW; j++)
        {
            for (int k = 0; k < MAX_INVADER_COLUMN; k++)
            {
                //Torchkaを削除する処理
                if (gInvaders[j][k].IntersectRect(gTorchka[i]))
                {
                    for (int l = 0; l < gInvaders[j][k].GetSize().y; l++)
                    {
                        for (int m = 0; m < gInvaders[j][k].GetSize().x; m++)
                        {
                            //インベーダーの左隅の画像からの位置
                            vec2 pos = gInvaders[j][k].GetPosition() + vec2(m, l);
                            gTorchka[i].ErasePixel(pos);
                        }//for (int m = 0; m < gInvaders[j][k].GetSize().x; m++)

                    }//for (int l = 0; l < gInvaders[j][k].GetSize().y; l++)

                }//if (gInvaders[j][k].IntersectRect(gTorchka[i].GetPosition()))

            }//for (int k = 0; k < MAX_INVADER_COLUMN; k++)

        }//for (int j = 0; j < MAX_INVADER_ROW; j++)

    }//for (int i = 0; i < MAX_TORCHKA; i++)

   
}
//void Torchka::AllUpdate()

void Torchka::Draw()
{
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, TORCHKA_WIDTH, TORCHKA_HEIGHT,
        0, GL_ALPHA, GL_UNSIGNED_BYTE, _pixels);
    SetColorWithPosition(GetPosition());
    Rect::Draw();

}
//void Torchka::Draw()

bool Torchka::IntersectRect(vec2 const& point)
{
    //弾との当たり判定の処理
    //Rectの範囲で当たらなかったらfalse
    if (Rect::IntersectRect(point) == false)
    {
        return false;
    }

    //Torchka内の座標を計算する
    //ローカル座標にする
    ivec2 localPos = point - GetPosition();

    return _pixels[localPos.y][localPos.x] != 0;
}//bool Torchka::IntersectRect(vec2 const& point)


void Torchka::Destroy(vec2 const& pos, int destroyedBy)
{
    //ローカル座標にする
    ivec2 localPos = pos - Torchka::GetPosition() - vec2(DESTROYED_TORCHKA_WIDTH, DESTROYED_TORCHKA_HEIGHT) / 2.0f;

    for (int i = 0; i < DESTROYED_TORCHKA_HEIGHT; i++)
    {
        for (int j = 0; j < DESTROYED_TORCHKA_WIDTH; j++)
        {
            int x = localPos.x + j;
            int y = localPos.y + i;

            //配列の要素数を超えないようにする
            if (x < 0)
            {
                x = 0;
            }
            else if (x >= TORCHKA_WIDTH)
            {
                x = TORCHKA_WIDTH-1;
            }
            if (y < 0)
            {
                y = 0;
            }
            else if (y >= TORCHKA_HEIGHT)
            {
                y = TORCHKA_HEIGHT-1;
            }

            //弾があたった時に元のTorchkaのピクセルと
            //destroyed_torchkaのピクセルを入れ替える
            if ((_pixels[y][x] != 0) && (_destroyedTorchkaPixels[destroyedBy][i][j] != 0))
            {
                //printf("Erase : x = %d, y = %d\n", x, y);
                //ローカル座標でTorchkaの座標から(j, i)のピクセルを消去する
                vec2 pos = Torchka::GetPosition() + vec2(x, y);
                ErasePixel(pos);
               
            }//if ((_pixels[i][j] != 0) && (_destroyedTorchkaPixels[i][j] != 0))

        }//for (int j = 0; j < DESTROYED_TORCHKA_WIDTH; j++)

    }// for (int i = 0; i < DESTROYED_TORCHKA_HEIGHT; i++)

}//void Torchka::Destroy()



