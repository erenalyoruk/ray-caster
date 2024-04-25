#include "Triangle.hpp"

Triangle::Triangle(const Color& color, const glm::vec3& v1, const glm::vec3& v2,
                   const glm::vec3& v3)
    : Object(color),
      m_v1{v1},
      m_v2{v2},
      m_v3{v3},
      m_edge1{v2 - v1},
      m_edge2{v3 - v1},
      m_normal{glm::normalize(glm::cross(m_edge1, m_edge2))}
{
}

bool Triangle::Intersect(const Ray& ray, Hit& hit, float minDistance) const
{
  const auto h{glm::cross(ray.GetDirection(), m_edge2)};

  const float a{glm::dot(m_edge1, h)};

  if (a > -glm::epsilon<float>() && a < glm::epsilon<float>()) {
    return false;
  }

  const float f{1.0F / a};
  const auto s{ray.GetOrigin() - m_v1};
  const float u{f * glm::dot(s, h)};

  if (u < 0.0F || u > 1.0F) {
    return false;
  }

  const auto q{glm::cross(s, m_edge1)};
  const float v{f * glm::dot(ray.GetDirection(), q)};

  if (v < 0.0F || u + v > 1.0F) {
    return false;
  }

  float distance{f * glm::dot(m_edge2, q)};

  if (distance < minDistance) {
    return false;
  }

  hit.SetDistance(distance);
  hit.SetHitPoint(ray.AtDistance(distance));
  hit.SetNormal(m_normal);
  hit.SetColor(this->GetColor());

  return true;
}