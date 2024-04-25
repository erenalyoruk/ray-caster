#pragma once

#include "Object.hpp"

#include <glm/ext/scalar_constants.hpp>

class Plane : public Object
{
 public:
  Plane(const Color& color, float distance, const glm::vec3& normal);

  bool Intersect(const Ray& ray, Hit& hit, float minDistance) const override;

 private:
  float m_distance;

  glm::vec3 m_normal;
};