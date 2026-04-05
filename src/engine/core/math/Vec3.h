#pragma once

#include "Vec2.h"

namespace Gas {

    template <typename T>
    struct Vec3
    {
        // NOTE uses union type punning not standard c++
        union
        {
            struct { T x, y, z; };
            struct { T r, g, b; };
            T data[3];
        };

        Vec3(T x, T y, T z);
        Vec3(const Vec2<T>& xy, T z);

        // converting constructor
        template <typename U>
        explicit Vec3(const Vec3<U>& other);

        // common named constructors
        static Vec3 Zero();

        // equality operators
        bool operator==(const Vec3& rhs) const;
        bool operator!=(const Vec3& rhs) const;

        // compound assignment operators (modifies in-place)
        Vec3& operator+=(const Vec3& rhs);
        Vec3& operator-=(const Vec3& rhs);
        Vec3& operator*=(T scalar);
        Vec3& operator/=(T scalar);

        // math operators (returns new vector)
        Vec3 operator+(const Vec3& rhs) const;
        Vec3 operator-(const Vec3& rhs) const;
        Vec3 operator*(T scalar) const;
        Vec3 operator/(T scalar) const;

        // left-hand scalar multiplication
        // Implemented inline to avoid template linker issues with friends
        friend Vec3 operator*(T scalar, const Vec3& vector)
        {
            return vector * scalar; // Reuses our operator*(T scalar) const
        }

        // utilities
        [[nodiscard]] static T dot(const Vec3& lhs, const Vec3& rhs);
        [[nodiscard]] T dot(const Vec3& other) const;
        [[nodiscard]] double length() const;
        [[nodiscard]] T lengthSquared() const;
        [[nodiscard]] Vec3 normalized() const;

        // debug printing
        // Implemented inline to avoid template linker issues with frineds
        friend std::ostream& operator<<(std::ostream& os, const Vec3& vector)
        {
            os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
            return os;
        }
    };

    // --- implementation ---

    template <typename T>
    Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    template <typename T>
    Vec3<T>::Vec3(const Vec2<T>& xy, T z) : x(xy.x), y(xy.y), z(z) {}

    template <typename T>
    template <typename U>
    Vec3<T>::Vec3(const Vec3<U>& other)
        : x(static_cast<T>(other.x)),
          y(static_cast<T>(other.y)),
          z(static_cast<T>(other.z)) {}

    template <typename T>
    Vec3<T> Vec3<T>::Zero()
    {
        return Vec3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
    }

    // --- Equality Operators ---

    template <typename T>
    bool Vec3<T>::operator==(const Vec3& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    template <typename T>
    bool Vec3<T>::operator!=(const Vec3& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    // --- Compound Assignment Operators ---

    template <typename T>
    Vec3<T>& Vec3<T>::operator+=(const Vec3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    template <typename T>
    Vec3<T>& Vec3<T>::operator-=(const Vec3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    template <typename T>
    Vec3<T>& Vec3<T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    template <typename T>
    Vec3<T>& Vec3<T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // --- Math Operators (Implemented using compound assignment) ---

    template <typename T>
    Vec3<T> Vec3<T>::operator+(const Vec3& rhs) const
    {
        Vec3 result = *this;
        result += rhs;
        return result;
    }

    template <typename T>
    Vec3<T> Vec3<T>::operator-(const Vec3& rhs) const
    {
        Vec3 result = *this;
        result -= rhs;
        return result;
    }

    template <typename T>
    Vec3<T> Vec3<T>::operator*(T scalar) const
    {
        Vec3 result = *this;
        result *= scalar;
        return result;
    }

    template <typename T>
    Vec3<T> Vec3<T>::operator/(T scalar) const
    {
        Vec3 result = *this;
        result /= scalar;
        return result;
    }

    // -- Utilities --
}
