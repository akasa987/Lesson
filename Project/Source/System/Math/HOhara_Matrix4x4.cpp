#include "HOhara_Matrix4x4.h"
#include "HOhara_Vector3.h"
#include "HOhara_Math.h"


namespace HOhara
{
    Matrix4x4 Matrix4x4::Identity()
    {
        return Matrix4x4(MGetIdent());
    }

    Matrix4x4 Matrix4x4::Translate(const Vector3& pos)
    {
        return Matrix4x4(MGetTranslate(pos.ToDx()));
    }

    Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
    {
        return Matrix4x4(MGetScale(scale.ToDx()));
    }

    Matrix4x4 Matrix4x4::RotateX(float degree)
    {
        return Matrix4x4(MGetRotX(DegToRad(degree)));
    }

    Matrix4x4 Matrix4x4::RotateY(float degree)
    {
        return Matrix4x4(MGetRotY(DegToRad(degree)));
    }

    Matrix4x4 Matrix4x4::RotateZ(float degree)
    {
        return Matrix4x4(MGetRotZ(DegToRad(degree)));
    }

    Matrix4x4 Matrix4x4::RotateXYZ(const Vector3& rot)
    {
        MATRIX mat = MGetRotX(DegToRad(rot.x));
        mat = MMult(mat, MGetRotY(DegToRad(rot.y)));
        mat = MMult(mat, MGetRotZ(DegToRad(rot.z)));

        return Matrix4x4(mat);
    }

    Matrix4x4 Matrix4x4::Transpose() const
    {
        return Matrix4x4(MTranspose(m_matrix));
    }

    Matrix4x4 Matrix4x4::Inverse() const
    {
        return Matrix4x4(MInverse(m_matrix));
    }

    Vector3 Matrix4x4::MultiplyPoint(const Vector3& point) const
    {
        return Vector3(VTransform(point.ToDx(), m_matrix));
    }

    Vector3 Matrix4x4::MultiplyVector(const Vector3& vec) const
    {
        return Vector3(VTransformSR(vec.ToDx(), m_matrix));
    }

    Matrix4x4 Matrix4x4::TRS(const Vector3& position, const Vector3& rotation, const Vector3& scale)
    {
        return Translate(position) * RotateXYZ(rotation) * Scale(scale);
    }

    Vector3 Matrix4x4::GetPosition() const
    {
        return Vector3(m_matrix.m[3][0], m_matrix.m[3][1], m_matrix.m[3][2]);
    }


    Vector3 Matrix4x4::GetRotation() const
    {
        Vector3 scale = GetScale();

        float m00 = m_matrix.m[0][0] / scale.x;
        float m01 = m_matrix.m[0][1] / scale.x;
        float m02 = m_matrix.m[0][2] / scale.x;

        float m10 = m_matrix.m[1][0] / scale.y;
        float m11 = m_matrix.m[1][1] / scale.y;
        float m12 = m_matrix.m[1][2] / scale.y;

        float m20 = m_matrix.m[2][0] / scale.z;
        float m21 = m_matrix.m[2][1] / scale.z;
        float m22 = m_matrix.m[2][2] / scale.z;

        Vector3 rot;

        rot.y = asinf(-m20);

        if (fabsf(cosf(rot.y)) > 0.0001f)
        {
            rot.x = atan2f(m21, m22);
            rot.z = atan2f(m10, m00);
        }
        else
        {
            // ジンバルロック
            rot.x = atan2f(-m12, m11);
            rot.z = 0.0f;
        }

        return Vector3(
            RadToDeg(rot.x),
            RadToDeg(rot.y),
            RadToDeg(rot.z));
    }

    Vector3 Matrix4x4::GetScale() const
    {
        Vector3 x(
            m_matrix.m[0][0],
            m_matrix.m[0][1],
            m_matrix.m[0][2]);

        Vector3 y(
            m_matrix.m[1][0],
            m_matrix.m[1][1],
            m_matrix.m[1][2]);

        Vector3 z(
            m_matrix.m[2][0],
            m_matrix.m[2][1],
            m_matrix.m[2][2]);

        return Vector3(
            x.Magnitude(),
            y.Magnitude(),
            z.Magnitude());
    }

    //==============================
    // 右方向(X軸)
    //==============================
    Vector3 Matrix4x4::GetRight() const
    {
        return Vector3(
            m_matrix.m[0][0],
            m_matrix.m[0][1],
            m_matrix.m[0][2]
        ).Normalized();
    }

    //==============================
    // 上方向(Y軸)
    //==============================
    Vector3 Matrix4x4::GetUp() const
    {
        return Vector3(
            m_matrix.m[1][0],
            m_matrix.m[1][1],
            m_matrix.m[1][2]
        ).Normalized();
    }

    //==============================
    // 前方向(Z軸)
    //==============================
    Vector3 Matrix4x4::GetForward() const
    {
        return Vector3(
            m_matrix.m[2][0],
            m_matrix.m[2][1],
            m_matrix.m[2][2]
        ).Normalized();
    }

    //==============================
    // 左方向
    //==============================
    Vector3 Matrix4x4::GetLeft() const
    {
        return -GetRight();
    }

    //==============================
    // 下方向
    //==============================
    Vector3 Matrix4x4::GetDown() const
    {
        return -GetUp();
    }

    //==============================
    // 後方向
    //==============================
    Vector3 Matrix4x4::GetBack() const
    {
        return -GetForward();
    }
}