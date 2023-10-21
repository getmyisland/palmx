#include <palmx_math.h>

#include <glm/glm.hpp>

namespace palmx
{
    glm::vec3 Vector3Forward(glm::vec3 vec3)
    {
        glm::vec3 forward;
        forward.x = cos(glm::radians(vec3.y)) * cos(glm::radians(vec3.x));
        forward.y = sin(glm::radians(vec3.x));
        forward.z = sin(glm::radians(vec3.y)) * cos(glm::radians(vec3.x));
        return glm::normalize(forward);
    }

    glm::vec3 Vector3Right(glm::vec3 vec3)
    {
        return glm::normalize(glm::cross(Vector3Forward(vec3), glm::vec3(0, 1, 0)));
    }

    glm::vec3 Vector3Up(glm::vec3 vec3)
    {
        return glm::normalize(glm::cross(Vector3Right(vec3), Vector3Forward(vec3)));
    }
}