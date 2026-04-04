#pragma once

#include <cstring>
#include <cmath>

namespace Gas {

    template <typename T>
    struct Mat4
    {
        // NOTE uses union type punning not standard c++
        union
        {
            struct
            {
                T m11, m12, m13, m14,
                  m21, m22, m23, m24,
                  m31, m32, m33, m34,
                  m41, m42, m43, m44;
            };

            T m[4][4];
        };

        Mat4(T x11, T x12, T x13, T x14,
             T x21, T x22, T x23, T x24,
             T x31, T x32, T x33, T x34,
             T x41, T x42, T x43, T x44);

        explicit Mat4(T diagonal = static_cast<T>(1));

        explicit Mat4(const T* data);

        // converting constructor
        template <typename U>
        explicit Mat4(const Mat4<U>& other);

        // common named constructors
        static Mat4 Identity();
        static Mat4 Translate(T tx, T ty, T tz);
        static Mat4 Scale(T sx, T sy, T sz);
        static Mat4 RotateX(T angleRadians);
        static Mat4 RotateY(T angleRadians);
        static Mat4 RotateZ(T angleRadians);
        // TODO: Add shear for 3D

        // equality operators
        bool operator==(const Mat4& rhs) const;
        bool operator!=(const Mat4& rhs) const;

        // compound assignment operators (modifies in-place)
        Mat4& operator+=(const Mat4& rhs);
        Mat4& operator-=(const Mat4& rhs);
        Mat4& operator*=(const Mat4& rhs);
        Mat4& operator*=(T scalar);
        Mat4& operator/=(T scalar);

        // math operators (returns a new matrix)
        Mat4 operator+(const Mat4& rhs) const;
        Mat4 operator-(const Mat4& rhs) const;
        Mat4 operator*(const Mat4& rhs) const;
        Mat4 operator*(T scalar) const;
        Mat4 operator/(T scalar) const;

        // left-hand scalar multiplication (e.g., 5.0f * matrix)
        // Implemented inline to avoid template linker issues with friends
        friend Mat4 operator*(T scalar, const Mat4& matrix)
        {
            return matrix * scalar;
        }
    };

    // -- implementation --

    template <typename T>
    Mat4<T>::Mat4(T x11, T x12, T x13, T x14,
                  T x21, T x22, T x23, T x24,
                  T x31, T x32, T x33, T x34,
                  T x41, T x42, T x43, T x44)
        : m{ {x11, x12, x13, x14},
             {x21, x22, x23, x24},
             {x31, x32, x33, x34},
             {x41, x42, x43, x44} } {}

    template <typename T>
    Mat4<T>::Mat4(T diagonal)
        : m{ {static_cast<T>(0)} }
    {
        m11 = diagonal;
        m22 = diagonal;
        m33 = diagonal;
        m44 = diagonal;
    }

    template <typename T>
    Mat4<T>::Mat4(const T* data)
    {
        memcpy(m, data, 16 * sizeof(T));
    }

    template <typename T>
    template <typename U>
    Mat4<T>::Mat4(const Mat4<U>& other)
        : m{ {static_cast<T>(other.m11), static_cast<T>(other.m12), static_cast<T>(other.m13), static_cast<T>(other.m14)},
             {static_cast<T>(other.m21), static_cast<T>(other.m22), static_cast<T>(other.m23), static_cast<T>(other.m24)},
             {static_cast<T>(other.m31), static_cast<T>(other.m32), static_cast<T>(other.m33), static_cast<T>(other.m34)},
             {static_cast<T>(other.m41), static_cast<T>(other.m42), static_cast<T>(other.m43), static_cast<T>(other.m44)} } {}

    template <typename T>
    Mat4<T> Mat4<T>::Identity()
    {
        return Mat4(static_cast<T>(1));
    }

    template <typename T>
    Mat4<T> Mat4<T>::Translate(T tx, T ty, T tz)
    {
        auto matrix = Mat4::Identity();

        matrix.m14 = static_cast<T>(tx);
        matrix.m24 = static_cast<T>(ty);
        matrix.m34 = static_cast<T>(tz);

        return matrix;
    }

    template <typename T>
    Mat4<T> Mat4<T>::Scale(T sx, T sy, T sz)
    {
        auto matrix = Mat4::Identity();

        matrix.m11 = static_cast<T>(sx);
        matrix.m22 = static_cast<T>(sy);
        matrix.m33 = static_cast<T>(sz);
        matrix.m44 = static_cast<T>(1);

        return matrix;
    }

    template <typename T>
    Mat4<T> Mat4<T>::RotateX(T angleRadians)
    {
        auto matrix = Mat4::Identity();

        T cosine = std::cos(angleRadians);
        T sine = std::sin(angleRadians);

        matrix.m22 = cosine;
        matrix.m23 = -sine;
        matrix.m32 = sine;
        matrix.m33 = cosine;

        return matrix;
    }

    template <typename T>
    Mat4<T> Mat4<T>::RotateY(T angleRadians)
    {
        auto matrix = Mat4::Identity();

        T cosine = std::cos(angleRadians);
        T sine = std::sin(angleRadians);

        matrix.m11 = cosine;
        matrix.m13 = sine;
        matrix.m31 = -sine;
        matrix.m33 = cosine;

        return matrix;
    }

    template <typename T>
    Mat4<T> Mat4<T>::RotateZ(T angleRadians)
    {
        auto matrix = Mat4::Identity();

        T cosine = std::cos(angleRadians);
        T sine = std::sin(angleRadians);

        matrix.m11 = cosine;
        matrix.m12 = -sine;
        matrix.m21 = sine;
        matrix.m22 = cosine;

        return matrix;
    }

    template <typename T>
    bool Mat4<T>::operator==(const Mat4& rhs) const
    {
        return m11 == rhs.m11 && m12 == rhs.m12 && m13 == rhs.m13 && m14 == rhs.m14 &&
               m21 == rhs.m21 && m22 == rhs.m22 && m23 == rhs.m23 && m24 == rhs.m24 &&
               m31 == rhs.m31 && m32 == rhs.m32 && m33 == rhs.m33 && m34 == rhs.m34 &&
               m41 == rhs.m41 && m42 == rhs.m42 && m43 == rhs.m43 && m44 == rhs.m44;
    }

    template <typename T>
    bool Mat4<T>::operator!=(const Mat4& rhs) const
    {
        return !(*this == rhs);
    }

    template <typename T>
    Mat4<T>& Mat4<T>::operator+=(const Mat4& rhs)
    {
        m11 += rhs.m11;
        m12 += rhs.m12;
        m13 += rhs.m13;
        m14 += rhs.m14;

        m21 += rhs.m21;
        m22 += rhs.m22;
        m23 += rhs.m23;
        m24 += rhs.m24;

        m31 += rhs.m31;
        m32 += rhs.m32;
        m33 += rhs.m33;
        m34 += rhs.m34;

        m41 += rhs.m41;
        m42 += rhs.m42;
        m43 += rhs.m43;
        m44 += rhs.m44;

        return *this;
    }

    template <typename T>
    Mat4<T>& Mat4<T>::operator-=(const Mat4& rhs)
    {
        m11 -= rhs.m11;
        m12 -= rhs.m12;
        m13 -= rhs.m13;
        m14 -= rhs.m14;

        m21 -= rhs.m21;
        m22 -= rhs.m22;
        m23 -= rhs.m23;
        m24 -= rhs.m24;

        m31 -= rhs.m31;
        m32 -= rhs.m32;
        m33 -= rhs.m33;
        m34 -= rhs.m34;

        m41 -= rhs.m41;
        m42 -= rhs.m42;
        m43 -= rhs.m43;
        m44 -= rhs.m44;

        return *this;
    }

    template <typename T>
    Mat4<T>& Mat4<T>::operator*=(const Mat4& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    template <typename T>
    Mat4<T>& Mat4<T>::operator*=(T scalar)
    {
        m11 *= scalar;
        m12 *= scalar;
        m13 *= scalar;
        m14 *= scalar;

        m21 *= scalar;
        m22 *= scalar;
        m23 *= scalar;
        m24 *= scalar;

        m31 *= scalar;
        m32 *= scalar;
        m33 *= scalar;
        m34 *= scalar;

        m41 *= scalar;
        m42 *= scalar;
        m43 *= scalar;
        m44 *= scalar;

        return *this;
    }

    template <typename T>
    Mat4<T>& Mat4<T>::operator/=(T scalar)
    {
        m11 /= scalar;
        m12 /= scalar;
        m13 /= scalar;
        m14 /= scalar;

        m21 /= scalar;
        m22 /= scalar;
        m23 /= scalar;
        m24 /= scalar;

        m31 /= scalar;
        m32 /= scalar;
        m33 /= scalar;
        m34 /= scalar;

        m41 /= scalar;
        m42 /= scalar;
        m43 /= scalar;
        m44 /= scalar;

        return *this;
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator+(const Mat4& rhs) const
    {
        Mat4 result = *this;
        result += rhs;
        return result;
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator-(const Mat4& rhs) const
    {
        Mat4 result = *this;
        result -= rhs;
        return result;
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator*(const Mat4& rhs) const
    {
        return Mat4<T>(
            // Row 1
            m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31 + m14 * rhs.m41,
            m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32 + m14 * rhs.m42,
            m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33 + m14 * rhs.m43,
            m11 * rhs.m14 + m12 * rhs.m24 + m13 * rhs.m34 + m14 * rhs.m44,

            // Row 2
            m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31 + m24 * rhs.m41,
            m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32 + m24 * rhs.m42,
            m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33 + m24 * rhs.m43,
            m21 * rhs.m14 + m22 * rhs.m24 + m23 * rhs.m34 + m24 * rhs.m44,

            // Row 3
            m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31 + m34 * rhs.m41,
            m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32 + m34 * rhs.m42,
            m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33 + m34 * rhs.m43,
            m31 * rhs.m14 + m32 * rhs.m24 + m33 * rhs.m34 + m34 * rhs.m44,

            // Row 4
            m41 * rhs.m11 + m42 * rhs.m21 + m43 * rhs.m31 + m44 * rhs.m41,
            m41 * rhs.m12 + m42 * rhs.m22 + m43 * rhs.m32 + m44 * rhs.m42,
            m41 * rhs.m13 + m42 * rhs.m23 + m43 * rhs.m33 + m44 * rhs.m43,
            m41 * rhs.m14 + m42 * rhs.m24 + m43 * rhs.m34 + m44 * rhs.m44
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator*(T scalar) const
    {
        Mat4 result = *this;
        result *= scalar;
        return result;
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator/(T scalar) const
    {
        Mat4 result = *this;
        result /= scalar;
        return result;
    }

    // -- common aliases --

    using Mat4i  = Mat4<int32_t>;
    using Mat4ui = Mat4<uint32_t>;
    using Mat4f  = Mat4<float>;
    using Mat4d  = Mat4<double>;

}
