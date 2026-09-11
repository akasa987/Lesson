#pragma once

namespace HOhara
{
    class Vector3;

    //==========================================
    // 行列関連
    //==========================================
    class Matrix4x4
    {
    private:
        MATRIX m_matrix;

    public:
        //==============================
        // コンストラクタ
        //==============================
        Matrix4x4()
            : m_matrix(MGetIdent())
        {
        }

        Matrix4x4(const MATRIX& matrix)
            : m_matrix(matrix)
        {
        }

        // DXライブラリ用
        const MATRIX& ToDx() const
        {
            return m_matrix;
        }

        MATRIX& ToDx()
        {
            return m_matrix;
        }

        operator MATRIX() const
        {
            return ToDx();
        }

        //==============================
        // 単位行列
        //==============================
        static Matrix4x4 Identity();

        //==============================
        // 平行移動
        //==============================
        static Matrix4x4 Translate(const Vector3& pos);

        //==============================
        // 拡大縮小
        //==============================
        static Matrix4x4 Scale(const Vector3& scale);

        //==============================
        // 回転（度数法）
        //==============================
        static Matrix4x4 RotateX(float degree);

        static Matrix4x4 RotateY(float degree);

        static Matrix4x4 RotateZ(float degree);

        static Matrix4x4 RotateXYZ(const Vector3& rot);

        //==============================
        // 行列積
        //==============================
        Matrix4x4 operator*(const Matrix4x4& rhs) const
        {
            return Matrix4x4(MMult(m_matrix, rhs.m_matrix));
        }

        Matrix4x4& operator*=(const Matrix4x4& rhs)
        {
            m_matrix = MMult(m_matrix, rhs.m_matrix);
            return *this;
        }

        //==============================
        // 転置
        //==============================
        Matrix4x4 Transpose() const;

        //==============================
        // 逆行列
        //==============================
        Matrix4x4 Inverse() const;

        //==============================
        // ベクトル変換
        //==============================
        Vector3 MultiplyPoint(const Vector3& point) const;

        Vector3 MultiplyVector(const Vector3& vec) const;

        //==============================
        // Unity風 TRS
        //==============================
        static Matrix4x4 TRS(const Vector3& position, const Vector3& rotation, const Vector3& scale);

        Vector3 GetPosition() const;

        Vector3 GetRotation() const;

        Vector3 GetScale() const;

        //==============================
        // 軸ベクトル取得
        //==============================
        Vector3 GetRight() const;
        Vector3 GetUp() const;
        Vector3 GetForward() const;

        Vector3 GetLeft() const;
        Vector3 GetDown() const;
        Vector3 GetBack() const;
    };
}