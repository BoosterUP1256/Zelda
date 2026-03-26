#pragma once
#include <iosfwd>

// TODO: consider adding converting constructor
// template <typename U>
// explicit Vector2(const Vector2<U>& other)
//   : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

//

namespace Gas {

    template <typename T>
    struct Vector2
    {
        T x, y;

        Vector2(T x, T y);

        // common named constructors
        static Vector2 zero();

        // equality operators
        bool operator==(const Vector2& rhs) const;
        bool operator!=(const Vector2& rhs) const;

        // math operators
        Vector2 operator+(const Vector2& rhs) const;
        Vector2 operator-(const Vector2& rhs) const;
        Vector2 operator*(T scalar) const;
        Vector2 operator/(T scalar) const;

        // utilities
        T dot(const Vector2& other) const;
        [[nodiscard]] double length() const;
        T lengthSquared() const;
        Vector2 normalized() const;

        // debug printing
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);
    };

    // implementation
    template<typename T>
    Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

    template<typename T>
    Vector2<T> Vector2<T>::zero()
    {
        return Vector2<T>(static_cast<T>(0), static_cast<T>(0));
    }

    template<typename T>
    bool Vector2<T>::operator==(const Vector2 &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    template<typename T>
    bool Vector2<T>::operator!=(const Vector2 &rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator+(const Vector2 &rhs) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator-(const Vector2 &rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator*(T scalar) const
    {
        return { x * scalar, y * scalar };
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator/(T scalar) const
    {
        return { x / scalar, y / scalar };
    }

    template<typename T>
    T Vector2<T>::dot(const Vector2 &other) const
    {
        return x * other.x + y * other.y;
    }

    template<typename T>
    double Vector2<T>::length() const
    {
        return sqrt(x * x + y * y);
    }

    template<typename T>
    T Vector2<T>::lengthSquared() const
    {
        return x * x + y * y;
    }

    template<typename T>
    Vector2<T> Vector2<T>::normalized() const
    {
        if (const double len = length(); len > 0)
            return *this * (1.0 / len);

        return { 0, 0 };
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector)
    {
        os << "(" << vector.x << ", " << vector.y << ")";
        return os;
    }

}
