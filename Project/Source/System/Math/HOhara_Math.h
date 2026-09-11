#pragma once

namespace HOhara
{
    //==============================
    // 度⇔ラジアン変換
    //==============================
    static float DegToRad(float degree)
    {
        return degree * DX_PI_F / 180.0f;
    }

    static float RadToDeg(float rad)
    {
        return rad * 180.0f / DX_PI_F;
    }

    //==========================================
    // レイリザルト
    //==========================================
    struct RayResult
    {
        RayResult()
        {
            isHit = false;
            distance = 0;
            hitPos = Vector3::Zero();
            normalVec = Vector3::Zero();
        }
        bool isHit;         //Hitチェック
        Vector3 hitPos;     //Hitした座標
        Vector3 normalVec;  //Hitした場所の法線
        float distance;     //距離
    };

    //==========================================
    // レイ判定
    //==========================================
    RayResult RayModelCheck(int modelHandle, Matrix4x4 modelMat, Vector3& pos, Vector3& look);
}