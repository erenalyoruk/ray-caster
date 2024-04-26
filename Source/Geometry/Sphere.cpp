#include "Sphere.hpp"

Sphere::Sphere(std::shared_ptr<Material> material, float radius, const glm::vec3& center)
    : Object(material), m_radius{radius}, m_center{center}
{
}

bool Sphere::Intersect(const Ray& ray, Hit& hit, float minDistance) const
{
  const auto oc{ray.GetOrigin() - m_center};

  const float a{glm::dot(ray.GetDirection(), ray.GetDirection())};
  const float h{glm::dot(oc, ray.GetDirection())};
  const float c{glm::dot(oc, oc) - m_radius * m_radius};

  const float discriminant{h * h - a * c};

  if (discriminant < 0.0F) {
    return false;
  }

  const float sqrtd{glm::sqrt(discriminant)};

  auto root{(-h - sqrtd) / a};
  if (root < minDistance) {
    root = (-h + sqrtd) / a;
    if (root < minDistance) {
      return false;
    }
  }

  hit.SetDistance(root);
  hit.SetMaterial(this->GetMaterial());
  hit.SetHitPoint(ray.AtDistance(root));
  hit.SetNormal(hit.GetHitPoint() - m_center);

  return true;
}