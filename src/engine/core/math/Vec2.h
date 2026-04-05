#pragma once

#include <ostream>
#include <cmath>
#include <cstdint>

// TODO (FUTURE): add Lerp static method
//      add isNearlyEqual method (epsilon comparison)
//

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

        Vec2(T x, T y);

        // converting constructor
        template <typename U>
        explicit Vec2(const Vec2<U>& other);

        // common named constructors
        static Vec2 Zero();

        // equality operators
        bool operator==(const Vec2& rhs) const;
        bool operator!=(const Vec2& rhs) const;

        // compound assignment operators (modifies in-place)
        Vec2& operator+=(const Vec2& rhs);
        Vec2& operator-=(const Vec2& rhs);
        Vec2& operator*=(T scalar);
        Vec2& operator/=(T scalar);

        // math operators (returns new vector)
        Vec2 operator+(const Vec2& rhs) const;
        Vec2 operator-(const Vec2& rhs) const;
        Vec2 operator*(T scalar) const;
        Vec2 operator/(T scalar) const;

        // left-hand scalar multiplication (e.g., 5.0f * vector)
        // Implemented inline to avoid template linker issues with friends
        friend Vec2 operator*(T scalar, const Vec2& vector)
        {
            return vector * scalar; // Reuses our operator*(T scalar) const
        }

        // utilities
        [[nodiscard]] static T dot(const Vec2& lhs, const Vec2& rhs);
        [[nodiscard]] T dot(const Vec2& other) const;
        [[nodiscard]] double length() const;
        [[nodiscard]] T lengthSquared() const;
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

    template<typename T>
    Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

    template<typename T>
    template<typename U>
    Vec2<T>::Vec2(const Vec2<U> &other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    template<typename T>
    Vec2<T> Vec2<T>::Zero()
    {
        return Vec2(static_cast<T>(0), static_cast<T>(0));
    }

    // --- Equality Operators ---

    template<typename T>
    bool Vec2<T>::operator==(const Vec2 &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    template<typename T>
    bool Vec2<T>::operator!=(const Vec2 &rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    // --- Compound Assignment Operators ---

    template<typename T>
    Vec2<T>& Vec2<T>::operator+=(const Vec2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<typename T>
    Vec2<T>& Vec2<T>::operator-=(const Vec2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<typename T>
    Vec2<T>& Vec2<T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template<typename T>
    Vec2<T>& Vec2<T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // --- Math Operators (Implemented using compound assignment) ---

    template<typename T>
    Vec2<T> Vec2<T>::operator+(const Vec2 &rhs) const
    {
        Vec2 result = *this;
        result += rhs;
        return result;
    }

    template<typename T>
    Vec2<T> Vec2<T>::operator-(const Vec2 &rhs) const
    {
        Vec2 result = *this;
        result -= rhs;
        return result;
    }

    template<typename T>
    Vec2<T> Vec2<T>::operator*(T scalar) const
    {
        Vec2 result = *this;
        result *= scalar;
        return result;
    }

    template<typename T>
    Vec2<T> Vec2<T>::operator/(T scalar) const
    {
        Vec2 result = *this;
        result /= scalar;
        return result;
    }

    // --- Utilities ---

    template<typename T>
    T Vec2<T>::dot(const Vec2 &lhs, const Vec2 &rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    template<typename T>
    T Vec2<T>::dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    template<typename T>
    double Vec2<T>::length() const
    {
        return std::sqrt(x * x + y * y);
    }

    template<typename T>
    T Vec2<T>::lengthSquared() const
    {
        return x * x + y * y;
    }

    template<typename T>
    Vec2<T> Vec2<T>::normalized() const
    {
        if (const double len = length(); len > 0)
        {
            // Multiplying by reciprocal is generally faster than dividing
            return *this * static_cast<T>(1.0 / len);
        }

        return { static_cast<T>(0), static_cast<T>(0) };
    }

    // -- common aliases --

    using Vec2i  = Vec2<int32_t>;
    using Vec2ui = Vec2<uint32_t>;
    using Vec2f  = Vec2<float>;
    using Vec2d  = Vec2<double>;

}