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

        constexpr Mat4(T x11, T x12, T x13, T x14,
                       T x21, T x22, T x23, T x24,
                       T x31, T x32, T x33, T x34,
                       T x41, T x42, T x43, T x44);

        constexpr explicit Mat4(T diagonal = static_cast<T>(1));

        constexpr explicit Mat4(const T* data);

        // converting constructor
        template <typename U>
        constexpr explicit Mat4(const Mat4<U>& other);

        // common named constructors
        constexpr static Mat4 Identity();
        constexpr static Mat4 Translate(T tx, T ty, T tz);
        constexpr static Mat4 Scale(T sx, T sy, T sz);
        static Mat4 RotateX(T angleRadians);
        static Mat4 RotateY(T angleRadians);
        static Mat4 RotateZ(T angleRadians);
        constexpr static Mat4 Ortho(T left, T right, T bottom, T top, T near, T far);
        // TODO: Add shear for 3D

        // equality operators
        constexpr bool operator==(const Mat4& rhs) const;
        constexpr bool operator!=(const Mat4& rhs) const;

        // compound assignment operators (modifies in-place)
        constexpr Mat4& operator+=(const Mat4& rhs);
        constexpr Mat4& operator-=(const Mat4& rhs);
        constexpr Mat4& operator*=(const Mat4& rhs);
        constexpr Mat4& operator*=(T scalar);
        constexpr Mat4& operator/=(T scalar);

        // math operators (returns a new matrix)
        constexpr Mat4 operator+(const Mat4& rhs) const;
        constexpr Mat4 operator-(const Mat4& rhs) const;
        constexpr Mat4 operator*(const Mat4& rhs) const;
        constexpr Mat4 operator*(T scalar) const;
        constexpr Mat4 operator/(T scalar) const;

        // left-hand scalar multiplication (e.g., 5.0f * matrix)
        // Implemented inline to avoid template linker issues with friends
        constexpr friend Mat4 operator*(T scalar, const Mat4& matrix)
        {
            return matrix * scalar;
        }
    };

    // -- implementation --

    template <typename T>
    constexpr Mat4<T>::Mat4(T x11, T x12, T x13, T x14,
                  T x21, T x22, T x23, T x24,
                  T x31, T x32, T x33, T x34,
                  T x41, T x42, T x43, T x44)
        : m11(x11), m12(x12), m13(x13), m14(x14),
          m21(x21), m22(x22), m23(x23), m24(x24),
          m31(x31), m32(x32), m33(x33), m34(x34),
          m41(x41), m42(x42), m43(x43), m44(x44) {}

    template <typename T>
    constexpr Mat4<T>::Mat4(T diagonal)
        : m11(diagonal), m12(0), m13(0), m14(0),
          m21(0), m22(diagonal), m23(0), m24(0),
          m31(0), m32(0), m33(diagonal), m34(0),
          m41(0), m42(0), m43(0), m44(diagonal) {}

    template <typename T>
    constexpr Mat4<T>::Mat4(const T* data)
        : m11(data[0]),  m12(data[1]),  m13(data[2]),  m14(data[3]),
          m21(data[4]),  m22(data[5]),  m23(data[6]),  m24(data[7]),
          m31(data[8]),  m32(data[9]),  m33(data[10]), m34(data[11]),
          m41(data[12]), m42(data[13]), m43(data[14]), m44(data[15]) {}

    template <typename T>
    template <typename U>
    constexpr Mat4<T>::Mat4(const Mat4<U>& other)
        : m11(static_cast<T>(other.m11)), m12(static_cast<T>(other.m12)), m13(static_cast<T>(other.m13)), m14(static_cast<T>(other.m14)),
          m21(static_cast<T>(other.m21)), m22(static_cast<T>(other.m22)), m23(static_cast<T>(other.m23)), m24(static_cast<T>(other.m24)),
          m31(static_cast<T>(other.m31)), m32(static_cast<T>(other.m32)), m33(static_cast<T>(other.m33)), m34(static_cast<T>(other.m34)),
          m41(static_cast<T>(other.m41)), m42(static_cast<T>(other.m42)), m43(static_cast<T>(other.m43)), m44(static_cast<T>(other.m44)) {}

    template <typename T>
    constexpr Mat4<T> Mat4<T>::Identity()
    {
        return Mat4(static_cast<T>(1));
    }

    template <typename T>
    constexpr Mat4<T> Mat4<T>::Translate(T tx, T ty, T tz)
    {
        auto matrix = Mat4::Identity();

        matrix.m14 = static_cast<T>(tx);
        matrix.m24 = static_cast<T>(ty);
        matrix.m34 = static_cast<T>(tz);

        return matrix;
    }

    template <typename T>
    constexpr Mat4<T> Mat4<T>::Scale(T sx, T sy, T sz)
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
    constexpr Mat4<T> Mat4<T>::Ortho(T left, T right, T bottom, T top, T near, T far)
    {
        auto matrix = Mat4::Identity();

        // Safely cast our constants to the template type T
        const T two = static_cast<T>(2);

        // Scale (Diagonal)
        matrix.m11 = two / (right - left);
        matrix.m22 = two / (top - bottom);
        matrix.m33 = -two / (far - near); // Negative for Right-Handed coordinates (OpenGL)

        // Translation (Fourth Column)
        matrix.m14 = -(right + left) / (right - left);
        matrix.m24 = -(top + bottom) / (top - bottom);
        matrix.m34 = -(far + near) / (far - near);

        return matrix;
    }

    template <typename T>
    constexpr bool Mat4<T>::operator==(const Mat4& rhs) const
    {
        return m11 == rhs.m11 && m12 == rhs.m12 && m13 == rhs.m13 && m14 == rhs.m14 &&
               m21 == rhs.m21 && m22 == rhs.m22 && m23 == rhs.m23 && m24 == rhs.m24 &&
               m31 == rhs.m31 && m32 == rhs.m32 && m33 == rhs.m33 && m34 == rhs.m34 &&
               m41 == rhs.m41 && m42 == rhs.m42 && m43 == rhs.m43 && m44 == rhs.m44;
    }

    template <typename T>
    constexpr bool Mat4<T>::operator!=(const Mat4& rhs) const
    {
        return !(*this == rhs);
    }

    template <typename T>
    constexpr Mat4<T>& Mat4<T>::operator+=(const Mat4& rhs)
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
    constexpr Mat4<T>& Mat4<T>::operator-=(const Mat4& rhs)
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
    constexpr Mat4<T>& Mat4<T>::operator*=(const Mat4& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    template <typename T>
    constexpr Mat4<T>& Mat4<T>::operator*=(T scalar)
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
    constexpr Mat4<T>& Mat4<T>::operator/=(T scalar)
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
    constexpr Mat4<T> Mat4<T>::operator+(const Mat4& rhs) const
    {
        Mat4 result = *this;
        result += rhs;
        return result;
    }

    template <typename T>
    constexpr Mat4<T> Mat4<T>::operator-(const Mat4& rhs) const
    {
        Mat4 result = *this;
        result -= rhs;
        return result;
    }

    template <typename T>
    constexpr Mat4<T> Mat4<T>::operator*(const Mat4& rhs) const
    {
        return Mat4(
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
    constexpr Mat4<T> Mat4<T>::operator*(T scalar) const
    {
        Mat4 result = *this;
        result *= scalar;
        return result;
    }

    template <typename T>
    constexpr Mat4<T> Mat4<T>::operator/(T scalar) const
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
