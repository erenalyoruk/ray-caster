#pragma once

#include "Object.hpp"

#include <glm/glm.hpp>

class Sphere : public Object
{
 public:
  Sphere(std::shared_ptr<Material> material, float radius, const glm::vec3& center);

  bool Intersect(const Ray& ray, Hit& hit, float minDistance) const override;

 private:
  float m_radius;

  glm::vec3 m_center;
};