#include "HOhara_Math.h"

namespace HOhara
{
    RayResult RayModelCheck(int modelHandle, Matrix4x4 modelMat, Vector3& pos, Vector3& look)
    {
        RayResult rayResult;
        MV1SetMatrix(modelHandle, modelMat);
        MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(modelHandle, -1, pos, look);
        if (result.HitFlag)
        {
            rayResult.isHit = true;
            rayResult.hitPos = result.HitPosition;
            rayResult.normalVec = result.Normal;
            rayResult.distance = HOhara::Vector3::Distance(pos, result.HitPosition);
        }
        return rayResult;
    }

    ModelResult ModelToSphereCheck(int modelHandle, Matrix4x4& modelMat, Vector3& pos, float radius)
    {
        ModelResult meshResult;
        MV1SetMatrix(modelHandle, modelMat);
        MV1_COLL_RESULT_POLY_DIM result = MV1CollCheck_Sphere(modelHandle, -1, pos, radius);
        meshResult.isHit = result.HitNum != 0;
        meshResult.hitNum = result.HitNum;
        if (meshResult.isHit)
        {
            meshResult.polygonResult = new PolygonResult[meshResult.hitNum];
            for (int i = 0; i < meshResult.hitNum; i++)
            {
                meshResult.polygonResult[i].Set(result.Dim[i]);
            }
        }
        else
        {
            meshResult.polygonResult = nullptr;
        }

        MV1CollResultPolyDimTerminate(result);
        return meshResult;
    }

    void WallSlideSphere(int modelHandle, Matrix4x4& modelMat, Vector3& pos, Vector3& moveVec, float radius, int check)
    {
        // 座標補正をしたか?
        bool isPush = false;
        Vector3 tempPos = pos;
        // 仮移動
        tempPos += moveVec;
        // 指定回数補正
        for (int i = 0; i < check; i++)
        {
            ModelResult result = ModelToSphereCheck(modelHandle, modelMat, tempPos, radius);

            if (!result.isHit)
            {
                break;
            }

            for (int j = 0; j < result.hitNum; j++)
            {
                PolygonResult* poly = result.polygonResult + j;
                Vector3 normal = poly->normal.Normalized();
                // 球中心から接触点まで
                Vector3 centerToHit = tempPos - poly->hitPos;
                float distance = centerToHit.Magnitude();
                // めり込み量
                float push = radius - distance;
                if (push > 0)
                {
                    isPush = true;
                    tempPos = tempPos + (normal * push);
                }
            }
        }
        // 座標補正をしていればベクトルを調整
        if (isPush) moveVec = tempPos - pos;
    }
}