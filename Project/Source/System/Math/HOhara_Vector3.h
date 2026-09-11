#pragma once

namespace HOhara
{
    class Matrix4x4;

    //==========================================
    // Vector3関連
    //==========================================
    class Vector3
    {
    public:
        float x;
        float y;
        float z;

    public:
        //==============================
        // コンストラクタ
        //==============================
        Vector3() : x(0), y(0), z(0) {}
        Vector3(float x, float y, float z)
            : x(x), y(y), z(z) {}

        Vector3(const VECTOR& v)
            : x(v.x), y(v.y), z(v.z) {}

        //==============================
        // DXライブラリへ変換
        //==============================
        VECTOR ToDx() const
        {
            return VGet(x, y, z);
        }

        VECTOR ToDxRot() const
        {
            return *this * (DX_PI_F / 180.0f);
        }

        operator VECTOR() const
        {
            return ToDx();
        }

        //==============================
        // 演算子
        //==============================
        Vector3 operator+(const Vector3& rhs) const
        {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        Vector3 operator-(const Vector3& rhs) const
        {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        Vector3 operator*(float s) const
        {
            return Vector3(x * s, y * s, z * s);
        }

        Vector3 operator/(float s) const
        {
            return Vector3(x / s, y / s, z / s);
        }

        Vector3& operator+=(const Vector3& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        Vector3& operator-=(const Vector3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        bool operator!=(const Vector3& rhs) const
        {
            if (x == rhs.x && y == rhs.y && z == rhs.z) return false;
            return true;
        }

        bool operator==(const Vector3& rhs) const
        {
            if (x == rhs.x && y == rhs.y && z == rhs.z) return true;
            return false;
        }

        //==============================
        // 符号反転
        //==============================
        Vector3 operator-() const
        {
            return Vector3(-x, -y, -z);
        }

        //==============================
        // 長さ
        //==============================
        float Magnitude() const;

        float SqrMagnitude() const;

        //==============================
        // 正規化
        //==============================
        Vector3 Normalized() const;

        void Normalize();

        //==============================
        // ベクトルの回転
        //==============================
        Vector3 Rotate(const Matrix4x4& mat) const;

        //==============================
        // 内積
        //==============================
        static float Dot(const Vector3& a, const Vector3& b);

        //==============================
        // 外積
        //==============================
        static Vector3 Cross(const Vector3& a, const Vector3& b);

        //==============================
        // 距離
        //==============================
        static float Distance(const Vector3& a, const Vector3& b);

        //==============================
        // 定数
        //==============================
        static Vector3 Zero();
        static Vector3 One();
        static Vector3 Up();
        static Vector3 Down();
        static Vector3 Right();
        static Vector3 Left();
        static Vector3 Forward();
        static Vector3 Back();
    };
}