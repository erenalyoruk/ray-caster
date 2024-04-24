#include "OrthoCamera.hpp"

OrthoCamera::OrthoCamera(float size, const glm::vec3& center, const glm::vec3& direction,
                         const glm::vec3& up)
    : Camera(center, direction, up),
      m_size{size},
      m_horizontal{glm::cross(this->GetDirection(), this->GetUp())}
{
}

Ray OrthoCamera::GenerateRay(float x, float y) const
{
  const auto rayOrigin{this->GetCenter() + m_horizontal * m_size * (x - 0.5F) +
                       this->GetUp() * m_size * (y - 0.5F)};

  return {rayOrigin, this->GetDirection()};
}