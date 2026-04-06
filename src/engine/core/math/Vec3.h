#pragma once

#include <ostream>
#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

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

        constexpr Vec3();
        constexpr Vec3(T x, T y, T z);
        constexpr Vec3(const Vec2<T>& xy, T z);

        // converting constructor
        template <typename U>
        constexpr explicit Vec3(const Vec3<U>& other);

        // common named constructors
        constexpr static Vec3 Zero();

        // array access operators
        constexpr T& operator[](size_t index);
        constexpr const T& operator[](size_t index) const;

        // unary negation operator
        constexpr Vec3 operator-() const;

        // equality operators
        constexpr bool operator==(const Vec3& rhs) const;
        constexpr bool operator!=(const Vec3& rhs) const;

        // is approximately equal to comparisons for floating point numbers
        [[nodiscard]] static bool approxEqual(const Vec3& lhs, const Vec3& rhs,
            T tolerance = std::numeric_limits<T>::epsilon() * 100);

        [[nodiscard]] bool isApprox(const Vec3& other, T tolerance = std::numeric_limits<T>::epsilon() * 100) const;

        // compound assignment operators (modifies in-place)
        constexpr Vec3& operator+=(const Vec3& rhs);
        constexpr Vec3& operator-=(const Vec3& rhs);
        constexpr Vec3& operator*=(T scalar);
        constexpr Vec3& operator/=(T scalar);

        // math operators (returns new vector)
        constexpr Vec3 operator+(const Vec3& rhs) const;
        constexpr Vec3 operator-(const Vec3& rhs) const;
        constexpr Vec3 operator*(T scalar) const;
        constexpr Vec3 operator/(T scalar) const;

        // left-hand scalar multiplication
        // Implemented inline to avoid template linker issues with friends
        constexpr friend Vec3 operator*(T scalar, const Vec3& vector)
        {
            return vector * scalar; // Reuses our operator*(T scalar) const
        }

        // utilities
        [[nodiscard]] constexpr static T dot(const Vec3& lhs, const Vec3& rhs);
        [[nodiscard]] constexpr T dot(const Vec3& other) const;
        [[nodiscard]] constexpr static Vec3 cross(const Vec3& lhs, const Vec3& rhs);
        [[nodiscard]] constexpr Vec3 cross(const Vec3& other) const;
        [[nodiscard]] auto length() const;
        [[nodiscard]] constexpr T lengthSquared() const;
        [[nodiscard]] Vec3 normalized() const;

        // debug printing
        // Implemented inline to avoid template linker issues with friends
        friend std::ostream& operator<<(std::ostream& os, const Vec3& vector)
        {
            os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
            return os;
        }
    };

    // --- implementation ---

    template <typename T>
    constexpr Vec3<T>::Vec3() : x(0), y(0), z(0) {}

    template <typename T>
    constexpr Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    template <typename T>
    constexpr Vec3<T>::Vec3(const Vec2<T>& xy, T z) : x(xy.x), y(xy.y), z(z) {}

    template <typename T>
    template <typename U>
    constexpr Vec3<T>::Vec3(const Vec3<U>& other)
        : x(static_cast<T>(other.x)),
          y(static_cast<T>(other.y)),
          z(static_cast<T>(other.z)) {}

    template <typename T>
    constexpr Vec3<T> Vec3<T>::Zero()
    {
        return Vec3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
    }

    template <typename T>
    constexpr T& Vec3<T>::operator[](size_t index)
    {
        return data[index];
    }

    template <typename T>
    constexpr const T& Vec3<T>::operator[](size_t index) const
    {
        return data[index];
    }

    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator-() const
    {
        return { -x, -y, -z };
    }

    // --- Equality Operators ---

    template <typename T>
    constexpr bool Vec3<T>::operator==(const Vec3& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    template <typename T>
    constexpr bool Vec3<T>::operator!=(const Vec3& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    template <typename T>
    bool Vec3<T>::approxEqual(const Vec3& lhs, const Vec3& rhs, T tolerance)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::abs(lhs.x - rhs.x) <= tolerance &&
                   std::abs(lhs.y - rhs.y) <= tolerance &&
                   std::abs(lhs.z - rhs.z) <= tolerance;
        }

        // if integer exact comparison is safe
        return lhs == rhs;
    }

    // --- Compound Assignment Operators ---

    template <typename T>
    bool Vec3<T>::isApprox(const Vec3& other, T tolerance) const
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::abs(x - other.x) <= tolerance &&
                   std::abs(y - other.y) <= tolerance &&
                   std::abs(z - other.z) <= tolerance;
        }

        // if integer exact comparison is safe
        return *this == other;
    }

    template <typename T>
    constexpr Vec3<T>& Vec3<T>::operator+=(const Vec3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    template <typename T>
    constexpr Vec3<T>& Vec3<T>::operator-=(const Vec3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    template <typename T>
    constexpr Vec3<T>& Vec3<T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    template <typename T>
    constexpr Vec3<T>& Vec3<T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // --- Math Operators (Implemented using compound assignment) ---

    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator+(const Vec3& rhs) const
    {
        Vec3 result = *this;
        result += rhs;
        return result;
    }

    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator-(const Vec3& rhs) const
    {
        Vec3 result = *this;
        result -= rhs;
        return result;
    }

    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator*(T scalar) const
    {
        Vec3 result = *this;
        result *= scalar;
        return result;
    }

    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator/(T scalar) const
    {
        Vec3 result = *this;
        result /= scalar;
        return result;
    }

    // -- Utilities --

    template <typename T>
    constexpr T Vec3<T>::dot(const Vec3& lhs, const Vec3& rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    template <typename T>
    constexpr T Vec3<T>::dot(const Vec3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    template <typename T>
    constexpr Vec3<T> Vec3<T>::cross(const Vec3& lhs, const Vec3& rhs)
    {
        T resultX = lhs.y * rhs.z - lhs.z * rhs.y;
        T resultY = lhs.z * rhs.x - lhs.x * rhs.z;
        T resultZ = lhs.x * rhs.y - lhs.y * rhs.x;

        return Vec3{ resultX, resultY, resultZ };
    }

    template <typename T>
    constexpr Vec3<T> Vec3<T>::cross(const Vec3& other) const
    {
        T resultX = y * other.z - z * other.y;
        T resultY = z * other.x - x * other.z;
        T resultZ = x * other.y - y * other.x;

        return Vec3{ resultX, resultY, resultZ };
    }

    template <typename T>
    auto Vec3<T>::length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    template <typename T>
    constexpr T Vec3<T>::lengthSquared() const
    {
        return x * x + y * y + z * z;
    }

    template <typename T>
    Vec3<T> Vec3<T>::normalized() const
    {
        static_assert(std::is_floating_point_v<T>, "T must be a floating point type");

        if (const T len = static_cast<T>(length()); len > static_cast<T>(0))
        {
            // Multiplying by the reciprocal is generally faster than dividing
            return *this * static_cast<T>(1.0 / len);
        }

        return { static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
    }

    // --- common aliases ---

    using Vec3i  = Vec3<int32_t>;
    using Vec3ui = Vec3<uint32_t>;
    using Vec3f  = Vec3<float>;
    using Vec3d  = Vec3<double>;

}
