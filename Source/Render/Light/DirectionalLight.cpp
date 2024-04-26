#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(const Color& color, const glm::vec3& direction)
    : Light(color), m_direction{glm::normalize(direction)}
{
}

const glm::vec3& DirectionalLight::GetDirection() const
{
  return m_direction;
}