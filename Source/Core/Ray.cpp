#include "Ray.hpp"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
    : m_origin{origin}, m_direction{glm::normalize(direction)}
{
}

glm::vec3 Ray::AtDistance(float distance) const
{
  return m_origin + distance * m_direction;
}

const glm::vec3& Ray::GetOrigin() const
{
  return m_origin;
}

const glm::vec3& Ray::GetDirection() const
{
  return m_direction;
}
