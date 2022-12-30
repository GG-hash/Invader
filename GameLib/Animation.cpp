#include "Animation.h"

//void JetAnim(float x1, float y1, float x2, float y2,mat4 mat)
//{
//    //頂点のデータ
//    vec2 v[] = { {x1, y1}, {x2,y2} };
//
//    for (int i = 0; i < 2; i++)
//    {
//        v[i] = (vec2)(mat * vec4(v[i].x, v[i].y, 0, 1));
//    }
//
//    glVertexPointer(2, GL_FLOAT, 0, v);
//
//    glDrawArrays(GL_LINES, 0, 2);
//}//JetAnim(float x1, float y1, float x2, float y2)

//void BulletAnim(vector<Bullet> &bullets)
//{
//    //stride : 頂点データの間隔
//    //const GLvoid stride = data->GetPositon();
//    //弾の頂点配列
//    vec2 data = bullets.data()->GetPositon();
//    glVertexPointer(2, GL_FLOAT, sizeof(Bullet), &data);
//    glDrawArrays(GL_POINTS, 0, bullets.size());
//}//BulletAnim(vector<Bullet> bullets)
