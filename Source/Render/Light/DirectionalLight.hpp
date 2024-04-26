#pragma once

#include "Light.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class DirectionalLight : public Light
{
 public:
  DirectionalLight(const Color& color, const glm::vec3& direction);

  const glm::vec3& GetDirection() const;

 private:
  glm::vec3 m_direction;
};