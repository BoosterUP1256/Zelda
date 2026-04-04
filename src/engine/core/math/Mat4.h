#pragma once

#include <cstring>

namespace Gas {

    template <typename T>

    // NOTE uses union type punning not standard c++
    struct Mat4
    {
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

        Mat4(T diagonal = static_cast<T>(1));

        explicit Mat4(const T* data);
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
        : m{ {0} }
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

}
