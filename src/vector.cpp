#include <palmx/vector.h>

#include <glm/gtx/string_cast.hpp>

namespace palmx
{
    Vector3::Vector3()
    {
        vec3_ = glm::vec3();
    }

    Vector3::Vector3(float x, float y, float z)
    {
        vec3_ = glm::vec3(x, y, z);
    }

    Vector3::Vector3(const glm::vec3& vec3)
    {
        vec3_ = vec3;
    }

    float& Vector3::X()
    {
        return vec3_.x;
    }

    float& Vector3::Y()
    {
        return vec3_.y;
    }

    float& Vector3::Z()
    {
        return vec3_.z;
    }

    Vector3 Vector3::Right() const
    {
        return glm::normalize(glm::cross(Forward().vec3_, glm::vec3(0, 1, 0)));
    }

    Vector3 Vector3::Up() const
    {
        return glm::normalize(glm::cross(Right().vec3_, Forward().vec3_));
    }

    Vector3 Vector3::Forward() const
    {
        glm::vec3 forward;
        forward.x = cos(glm::radians(vec3_.y)) * cos(glm::radians(vec3_.x));
        forward.y = sin(glm::radians(vec3_.x));
        forward.z = sin(glm::radians(vec3_.y)) * cos(glm::radians(vec3_.x));
        return glm::normalize(forward);
    }

    Vector3 Vector3::Normalize() const
    {
        return glm::normalize(vec3_);
    }

    float Vector3::Dot(Vector3 other) const
    {
        return glm::dot(vec3_, other.vec3_);
    }

    float Vector3::Length() const
    {
        return glm::length(vec3_);
    }

    std::string Vector3::ToString() const
    {
        return glm::to_string(vec3_);
    }

    Vector3 Vector3::operator=(const Vector3& other) const
    {
        if (this == &other)
        {
            return *this;
        }

        vec3_ = other.vec3_;

        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return Vector3(vec3_ + other.vec3_);
    }

    Vector3 Vector3::operator+=(const Vector3& other) const
    {
        vec3_ = vec3_ + other.vec3_;
        return *this;
    }

    Vector3 Vector3::operator-() const
    {
        return Vector3(-vec3_);
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return Vector3(vec3_ - other.vec3_);
    }

    Vector3 Vector3::operator-=(const Vector3& other) const
    {
        vec3_ = vec3_ - other.vec3_;
        return *this;
    }

    Vector3 Vector3::operator*(const Vector3& other) const
    {
        return Vector3(vec3_ * other.vec3_);
    }

    Vector3 Vector3::operator*=(const Vector3& other) const
    {
        vec3_ = vec3_ * other.vec3_;
        return *this;
    }

    Vector3 Vector3::operator*(const float& other) const
    {
        return Vector3(vec3_ * other);
    }

    Vector3 Vector3::operator/(const Vector3& other) const
    {
        return Vector3(vec3_ / other.vec3_);
    }

    Vector3 Vector3::operator/=(const Vector3& other) const
    {
        vec3_ = vec3_ / other.vec3_;
        return *this;
    }

    Vector3 Vector3::operator/(const float& other) const
    {
        return Vector3(vec3_ * other);
    }

    Vector3::operator glm::vec3() const
    {
        return vec3_;
    }
}