#include "HOhara_Vector3.h"
#include "HOhara_Matrix4x4.h"
#include "HOhara_Math.h"

namespace HOhara
{
    float Vector3::Magnitude() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    float  Vector3::SqrMagnitude() const
    {
        return x * x + y * y + z * z;
    }

    Vector3 Vector3::Normalized() const
    {
        float len = Magnitude();

        if (len == 0.0f)
            return Zero();

        return *this / len;
    }

    void Vector3::Normalize()
    {
        *this = Normalized();
    }

    Vector3 Vector3::Rotate(const Matrix4x4& mat) const
    {
        const MATRIX& m = mat.ToDx();

        return Vector3(
            x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0],
            x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1],
            x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2]
        );
    }

    float Vector3::Dot(const Vector3& a, const Vector3& b)
    {
        return a.x * b.x +
            a.y * b.y +
            a.z * b.z;
    }

    Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
    {
        return Vector3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    float Vector3::Distance(const Vector3& a, const Vector3& b)
    {
        return (a - b).Magnitude();
    }


    inline Vector3 operator*(float s, const Vector3& v)
    {
        return v * s;
    }

    Vector3 Vector3::Zero()
    {
        return Vector3(0, 0, 0);
    }

    Vector3 Vector3::One()
    {
        return Vector3(1, 1, 1);
    }

    Vector3 Vector3::Up()
    {
        return Vector3(0, 1, 0);
    }

    Vector3 Vector3::Down()
    {
        return Vector3(0, -1, 0);
    }

    Vector3 Vector3::Right()
    {
        return Vector3(1, 0, 0);
    }

    Vector3 Vector3::Left()
    {
        return Vector3(-1, 0, 0);
    }

    Vector3 Vector3::Forward()
    {
        return Vector3(0, 0, 1);
    }

    Vector3 Vector3::Back()
    {
        return Vector3(0, 0, -1);
    }
}