#pragma once

#include <ostream>
#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

// TODO (FUTURE): add Lerp static method

namespace Gas {

    template <typename T>
    struct Vec2
    {
        // NOTE uses union type punning not standard c++
        union
        {
            struct { T x, y; };
            T data[2];
        };

        constexpr Vec2();
        constexpr Vec2(T x, T y);

        // converting constructor
        template <typename U>
        constexpr explicit Vec2(const Vec2<U>& other);

        // common named constructors
        constexpr static Vec2 Zero();

        // array access operators
        constexpr T& operator[](size_t index);
        constexpr const T& operator[](size_t index) const;

        // unary negation operator
        constexpr Vec2 operator-() const;

        // equality operators
        constexpr bool operator==(const Vec2& rhs) const;
        constexpr bool operator!=(const Vec2& rhs) const;

        // is approximately equal comparisons for floating point numbers
        [[nodiscard]] static bool approxEqual(const Vec2& lhs, const Vec2& rhs,
            T tolerance = std::numeric_limits<T>::epsilon() * 100);

        [[nodiscard]] bool isApprox(const Vec2& other, T tolerance = std::numeric_limits<T>::epsilon() * 100) const;

        // compound assignment operators (modifies in-place)
        constexpr Vec2& operator+=(const Vec2& rhs);
        constexpr Vec2& operator-=(const Vec2& rhs);
        constexpr Vec2& operator*=(T scalar);
        constexpr Vec2& operator/=(T scalar);

        // math operators (returns new vector)
        constexpr Vec2 operator+(const Vec2& rhs) const;
        constexpr Vec2 operator-(const Vec2& rhs) const;
        constexpr Vec2 operator*(T scalar) const;
        constexpr Vec2 operator/(T scalar) const;

        // left-hand scalar multiplication (e.g., 5.0f * vector)
        // Implemented inline to avoid template linker issues with friends
        constexpr friend Vec2 operator*(T scalar, const Vec2& vector)
        {
            return vector * scalar; // Reuses our operator*(T scalar) const
        }

        // utilities
        [[nodiscard]] constexpr static T dot(const Vec2& lhs, const Vec2& rhs);
        [[nodiscard]] constexpr T dot(const Vec2& other) const;
        [[nodiscard]] constexpr auto length() const;
        [[nodiscard]] constexpr T lengthSquared() const;
        [[nodiscard]] Vec2 normalized() const;

        // debug printing
        // Implemented inline to avoid template linker issues with friends
        friend std::ostream& operator<<(std::ostream& os, const Vec2& vector)
        {
            os << "(" << vector.x << ", " << vector.y << ")";
            return os;
        }
    };

    // --- implementation ---

    template <typename T>
    constexpr Vec2<T>::Vec2() : x(0), y(0) {}

    template<typename T>
    constexpr Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

    template<typename T>
    template<typename U>
    constexpr Vec2<T>::Vec2(const Vec2<U> &other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    template<typename T>
    constexpr Vec2<T> Vec2<T>::Zero()
    {
        return Vec2();
    }

    template <typename T>
    constexpr T& Vec2<T>::operator[](size_t index)
    {
        return data[index];
    }

    template <typename T>
    constexpr const T& Vec2<T>::operator[](size_t index) const
    {
        return data[index];
    }

    template <typename T>
    constexpr Vec2<T> Vec2<T>::operator-() const
    {
        return { -x, -y };
    }

    // --- Equality Operators ---

    template<typename T>
    constexpr bool Vec2<T>::operator==(const Vec2 &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    template<typename T>
    constexpr bool Vec2<T>::operator!=(const Vec2 &rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    template <typename T>
    bool Vec2<T>::approxEqual(const Vec2& lhs, const Vec2& rhs, T tolerance)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::abs(lhs.x - rhs.x) <= tolerance &&
                   std::abs(lhs.y - rhs.y) <= tolerance;
        }

        // if integer exact comparison is safe
        return lhs == rhs;
    }

    template <typename T>
    bool Vec2<T>::isApprox(const Vec2& other, T tolerance) const
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::abs(x - other.x) <= tolerance &&
                   std::abs(y - other.y) <= tolerance;
        }

        // if integer exact comparison is safe
        return *this == other;
    }

    // --- Compound Assignment Operators ---

    template<typename T>
    constexpr Vec2<T>& Vec2<T>::operator+=(const Vec2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<typename T>
    constexpr Vec2<T>& Vec2<T>::operator-=(const Vec2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<typename T>
    constexpr Vec2<T>& Vec2<T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template<typename T>
    constexpr Vec2<T>& Vec2<T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // --- Math Operators (Implemented using compound assignment) ---

    template<typename T>
    constexpr Vec2<T> Vec2<T>::operator+(const Vec2 &rhs) const
    {
        Vec2 result = *this;
        result += rhs;
        return result;
    }

    template<typename T>
    constexpr Vec2<T> Vec2<T>::operator-(const Vec2 &rhs) const
    {
        Vec2 result = *this;
        result -= rhs;
        return result;
    }

    template<typename T>
    constexpr Vec2<T> Vec2<T>::operator*(T scalar) const
    {
        Vec2 result = *this;
        result *= scalar;
        return result;
    }

    template<typename T>
    constexpr Vec2<T> Vec2<T>::operator/(T scalar) const
    {
        Vec2 result = *this;
        result /= scalar;
        return result;
    }

    // --- Utilities ---

    template<typename T>
    constexpr T Vec2<T>::dot(const Vec2 &lhs, const Vec2 &rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    template<typename T>
    constexpr T Vec2<T>::dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    template<typename T>
    constexpr auto Vec2<T>::length() const
    {
        return std::sqrt(x * x + y * y);
    }

    template<typename T>
    constexpr T Vec2<T>::lengthSquared() const
    {
        return x * x + y * y;
    }

    template<typename T>
    Vec2<T> Vec2<T>::normalized() const
    {
        static_assert(std::is_floating_point_v<T>, "T must be a floating point type");

        if (const T len = static_cast<T>(length()); len > static_cast<T>(0))
        {
            // Multiplying by reciprocal is generally faster than dividing
            return *this * static_cast<T>(1.0 / len);
        }

        return Vec2();
    }

    // --- common aliases ---

    using Vec2i  = Vec2<int32_t>;
    using Vec2ui = Vec2<uint32_t>;
    using Vec2f  = Vec2<float>;
    using Vec2d  = Vec2<double>;

}