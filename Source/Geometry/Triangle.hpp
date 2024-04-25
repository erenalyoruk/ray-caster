#pragma once

#include "Object.hpp"

#include <glm/ext/scalar_constants.hpp>

class Triangle : public Object
{
 public:
  Triangle(const Color& color, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);

  bool Intersect(const Ray& ray, Hit& hit, float minDistance) const override;

 private:
  glm::vec3 m_v1;
  glm::vec3 m_v2;
  glm::vec3 m_v3;

  glm::vec3 m_edge1;
  glm::vec3 m_edge2;

  glm::vec3 m_normal;
};