#ifndef PALMX_VECTOR_H
#define PALMX_VECTOR_H

#include <glm/glm.hpp>

#include <string>

#define VECTOR_3_ZERO Vector3(0, 0, 0)
#define VECTOR_3_ONE Vector3(1, 1, 1)
// x
#define VECTOR_3_RIGHT Vector3(1, 0, 0)
#define VECTOR_3_LEFT Vector3(-1, 0, 0)
// y
#define VECTOR_3_UP Vector3(0, 1, 0)
#define VECTOR_3_DOWN Vector3(0, -1, 0)
// z
#define VECTOR_3_FORWARD Vector3(0, 0, -1)
#define VECTOR_3_BACK Vector3(0, 0, 1)

namespace palmx
{
    class Vector3
    {
    public:
        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const glm::vec3& vec3);

        float& X();
        float& Y();
        float& Z();

        Vector3 Right() const;
        Vector3 Up() const;
        Vector3 Forward() const;

        Vector3 Normalize() const;
        float Dot(Vector3 other) const;
        float Length() const;

        std::string ToString() const;

        Vector3 operator=(const Vector3& other) const;

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator+=(const Vector3& other) const;

        Vector3 operator-() const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator-=(const Vector3& other) const;

        Vector3 operator*(const Vector3& other) const;
        Vector3 operator*=(const Vector3& other) const;
        Vector3 operator*(const float& other) const;

        Vector3 operator/(const Vector3& other) const;
        Vector3 operator/=(const Vector3& other) const;
        Vector3 operator/(const float& other) const;

        explicit operator glm::vec3() const;

    private:
        mutable glm::vec3 vec3_;
    };
}

#endif