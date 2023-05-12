// #Vector2
//Forward declarations of Vector2 non-member operator overloads
#pragma once
#include "cmath"
#include "tuple"
struct Vector2;
inline Vector2 operator+(const Vector2 v1, const Vector2 v2);
inline Vector2 operator-(const Vector2 v1, const Vector2 v2);
inline Vector2 operator*(const Vector2 v1, const Vector2 v2);
inline Vector2 operator/(const Vector2 v1, const Vector2 v2);
inline Vector2 operator+(const Vector2 v1, const float f);
inline Vector2 operator-(const Vector2 v1, const float f);
inline Vector2 operator*(const Vector2 v1, const float f);
inline Vector2 operator/(const Vector2 v1, const float f);

struct Vector2 {
    float X, Y;

    Vector2 minus(const Vector2 other) const {
        return{ X - other.X,  Y - other.Y };
    }
    inline Vector2 operator+=(const Vector2 v2) {
        X += v2.X;
        Y += v2.Y;
        return *this;
    }
    inline Vector2 operator-=(const Vector2 v2) {
        X -= v2.X;
        Y -= v2.Y;
        return *this;
    }
    inline Vector2 operator*=(const Vector2 v2) {
        X *= v2.X;
        Y *= v2.Y;
        return *this;
    }
    inline Vector2 operator/=(const Vector2 v2) {
        X /= v2.X;
        Y /= v2.Y;
        return *this;
    }
    inline Vector2 operator+=(const float f) {
        X += f;
        Y += f;
        return *this;
    }
    inline Vector2 operator-=(const float f) {
        X -= f;
        Y -= f;
        return *this;
    }
    inline Vector2 operator*=(const float f) {
        X *= f;
        Y *= f;
        return *this;
    }
    inline Vector2 operator/=(const float f) {
        X /= f;
        Y /= f;
        return *this;
    }
};

//Vector2 non-member operator overloads

inline Vector2 operator+(const Vector2 v1, const Vector2 v2) {
    return Vector2{ v1.X + v2.X, v1.Y + v2.Y };
}

inline Vector2 operator-(const Vector2 v1, const Vector2 v2) {
    return Vector2{ v1.X - v2.X, v1.Y - v2.Y };
}

inline Vector2 operator*(const Vector2 v1, const Vector2 v2) {
    return Vector2{ v1.X * v2.X, v1.Y * v2.Y };
}

inline Vector2 operator/(const Vector2 v1, const Vector2 v2) {
    return Vector2{ v1.X / v2.X, v1.Y / v2.Y };
}

inline Vector2 operator+(const Vector2 v1, const float f) {
    return Vector2{ v1.X + f, v1.Y + f };
}

inline Vector2 operator-(const Vector2 v1, const float f) {
    return Vector2{ v1.X - f, v1.Y - f };
}

inline Vector2 operator*(const Vector2 v1, const float f) {
    return Vector2{ v1.X * f, v1.Y * f };
}

inline Vector2 operator/(const Vector2 v1, const float f) {
    return Vector2{ v1.X / f, v1.Y / f };
}

inline float getLength(Vector2 v) {
    return std::sqrt(v.X * v.X + v.Y * v.Y);
}

