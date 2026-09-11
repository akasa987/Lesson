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
}