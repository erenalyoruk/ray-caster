#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Ray
{
 public:
  Ray() = delete;

  Ray(const glm::vec3& origin, const glm::vec3& direction);

  glm::vec3 AtDistance(float distance) const;

  const glm::vec3& GetOrigin() const;
  const glm::vec3& GetDirection() const;

 private:
  glm::vec3 m_origin;
  glm::vec3 m_direction;
};