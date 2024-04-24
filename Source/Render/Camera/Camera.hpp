#pragma once

#include "Core/Ray.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Camera
{
 public:
  Camera() = delete;

  Camera(const glm::vec3& center, const glm::vec3& direction, const glm::vec3& up);

  virtual ~Camera() = default;

  virtual Ray GenerateRay(float x, float y) const = 0;

  const glm::vec3& GetCenter() const;

  const glm::vec3& GetDirection() const;

  const glm::vec3& GetUp() const;

 private:
  glm::vec3 m_center;
  glm::vec3 m_direction;
  glm::vec3 m_up;
};