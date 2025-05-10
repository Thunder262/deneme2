#pragma once
#include <cmath>
#include <limits>

#define PI 3.14159265358979323846f
#define PI_2 (PI / 2.0f)
#define RAD2DEG(x) ((x) * (180.0f / PI))
#define DEG2RAD(x) ((x) * (PI / 180.0f))

namespace Math
{
    inline float Epsilon = std::numeric_limits<float>::epsilon();

    inline float Increment(float f) {
        if (f == 0.0f) return Epsilon;
        int i = *(int*)&f;
        i = (f > 0.0f) ? i + 1 : i - 1;
        return *(float*)&i;
    }

    inline float Decrement(float f) {
        if (f == 0.0f) return -Epsilon;
        int i = *(int*)&f;
        i = (f > 0.0f) ? i - 1 : i + 1;
        return *(float*)&i;
    }

    inline float Clamp(float value, float min, float max) {
        return std::fmax(min, std::fmin(value, max));
    }

    inline int Clamp(int value, int min, int max) {
        return std::max(min, std::min(value, max));
    }

    inline float Pow(float base, int exp) {
        float result = 1.0f;
        bool negative = exp < 0;
        if (negative) exp = -exp;
        for (int i = 0; i < exp; ++i) result *= base;
        return negative ? 1.0f / result : result;
    }

    inline float Lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }

    inline float NormalizeAngle(float angle) {
        while (angle > 360.0f) angle -= 360.0f;
        while (angle < 0.0f) angle += 360.0f;
        return angle;
    }

    inline float FastSqrt(float number) {
        long i;
        float x2, y;
        const float threehalfs = 1.5F;
        x2 = number * 0.5F;
        y = number;
        i = *(long*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        y = y * (threehalfs - (x2 * y * y));
        return 1.0f / y;
    }

    inline float Sin(float x) {
        // Taylor approximation up to x^7
        const float x2 = x * x;
        return x - x2 * x / 6.0f + x2 * x2 * x / 120.0f;
    }

    inline float Cos(float x) {
        return Sin(x + PI_2);
    }

    inline float Tan(float x) {
        float sinVal = Sin(x);
        float cosVal = Cos(x);
        return (std::fabs(cosVal) < Epsilon) ? std::numeric_limits<float>::infinity() : sinVal / cosVal;
    }

    inline float Abs(float x) {
        return (x < 0.0f) ? -x : x;
    }

    inline float Mod(float x, float y) {
        if (y == 0.0f) return std::numeric_limits<float>::quiet_NaN();
        float result = std::fmod(x, y);
        if (result < 0.0f) result += y;
        return result;
    }
}

// ------------- Vector3 -------------
class Vector3
{
public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

    float Magnitude() const {
        return Math::FastSqrt(x * x + y * y + z * z);
    }

    float Magnitude2D() const {
        return Math::FastSqrt(x * x + z * z);
    }

    Vector3 Normalized() const {
        float mag = Magnitude();
        if (mag == 0.0f) return *this;
        return Vector3(x / mag, y / mag, z / mag);
    }

    float Distance(const Vector3& v) const {
        return Math::FastSqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z));
    }

    float Distance2D(const Vector3& v) const {
        return Math::FastSqrt((x - v.x) * (x - v.x) + (z - v.z) * (z - v.z));
    }

    float Dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 Midpoint(const Vector3& v) const {
        return Vector3((x + v.x) / 2.0f, (y + v.y) / 2.0f, (z + v.z) / 2.0f);
    }

    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float val) const { return Vector3(x * val, y * val, z * val); }
    Vector3 operator/(float val) const { return Vector3(x / val, y / val, z / val); }

    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }

    static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDelta) {
        Vector3 diff = target - current;
        float dist = diff.Magnitude();
        if (dist <= maxDelta || dist == 0.0f)
            return target;
        return current + diff / dist * maxDelta;
    }

    static Vector3 Zero() { return Vector3(0, 0, 0); }
};

// ------------- Vector2 -------------
class Vector2 {
public:
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float X, float Y) : x(X), y(Y) {}

    float Magnitude() const {
        return Math::FastSqrt(x * x + y * y);
    }

    Vector2 Normalized() const {
        float mag = Magnitude();
        return (mag == 0.0f) ? *this : Vector2(x / mag, y / mag);
    }

    Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    Vector2 operator*(float val) const { return Vector2(x * val, y * val); }
    Vector2 operator/(float val) const { return Vector2(x / val, y / val); }

    Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }

    static Vector2 Zero() { return Vector2(0, 0); }
};
