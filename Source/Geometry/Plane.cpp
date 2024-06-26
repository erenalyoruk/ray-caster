#include "Plane.hpp"

Plane::Plane(std::shared_ptr<Material> material, float distance, const glm::vec3& normal)
    : Object(material), m_distance{distance}, m_normal{glm::normalize(normal)}
{
}

bool Plane::Intersect(const Ray& ray, Hit& hit, float minDistance) const
{
  const float denominator{glm::dot(m_normal, ray.GetDirection())};
  if (glm::abs(denominator) < glm::epsilon<float>()) {
    return false;
  }

  const float distance{(m_distance - glm::dot(m_normal, ray.GetOrigin())) / denominator};
  if (distance < minDistance) {
    return false;
  }

  hit.SetDistance(distance);
  hit.SetHitPoint(ray.AtDistance(distance));
  hit.SetNormal(m_normal);
  hit.SetMaterial(this->GetMaterial());

  return true;
}