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

    //==========================================
    // モデル判定リザルト
    //==========================================
    struct PolygonResult
    {
        Vector3 hitPos;                 //Hitした座標
        Vector3 pos[3];                 //ポリゴンの頂点
        Vector3 normal;                 //法線

        int frameIndex;
        int meshIndex;
        int polygonIndex;
        int materialIndex;
        float positionWeight[3];
        int posMaxWeightFrameIndex[3];

        PolygonResult()
        {
            normal = hitPos = pos[0] = pos[1] = pos[2] = Vector3::Zero();
            frameIndex = meshIndex = polygonIndex = materialIndex = 0;
            positionWeight[0] = positionWeight[1] = positionWeight[2] = 0;
            posMaxWeightFrameIndex[0] = posMaxWeightFrameIndex[1] = posMaxWeightFrameIndex[2] = 0;
        }

        PolygonResult(tagMV1_COLL_RESULT_POLY& dx)
        {
            Set(dx);
        }

        void Set(tagMV1_COLL_RESULT_POLY& dx)
        {
            hitPos = dx.HitPosition;
            memcpy(pos, dx.Position, sizeof(Vector3) * 3);
            normal = dx.Normal;

            frameIndex = dx.FrameIndex;
            meshIndex = dx.MeshIndex;
            polygonIndex = dx.PolygonIndex;
            materialIndex = dx.MaterialIndex;
            memcpy(positionWeight, dx.PositionWeight, sizeof(float) * 3);
            memcpy(posMaxWeightFrameIndex, dx.PosMaxWeightFrameIndex, sizeof(int) * 3);
        }
    };

    //==========================================
    // モデル判定リザルト
    //==========================================
    struct ModelResult
    {
        bool isHit;                     //Hitチェック
        int hitNum;                     //Hitしたポリゴンの数
        PolygonResult* polygonResult;   //Hitしたポリゴン情報の先頭アドレス

        ModelResult()
        {
            isHit = false;
            hitNum = 0;
            polygonResult = nullptr;
        }
        ~ModelResult()
        {
            if (polygonResult != nullptr) SafeDeleteArray(polygonResult);
        }
    };

    //==========================================
    // メッシュと球の判定
    //==========================================
    ModelResult ModelToSphereCheck(int modelHandle, Matrix4x4& modelMat, Vector3& pos, float radius);

    //==========================================
    // メッシュと球のめり込みを補正
    //==========================================
    void WallSlideSphere(int modelHandle, Matrix4x4& modelMat, Vector3& pos, Vector3& moveVec, float radius, int check = 3);
}