#include "Transformation.hpp"

Transformation::Transformation(std::unique_ptr<Object>&& object, const glm::mat4& matrix)
    : m_object{std::move(object)}, m_matrix{matrix}, m_inverseMatrix{glm::inverse(matrix)}
{
}

bool Transformation::Intersect(const Ray& ray, Hit& hit, float minDistance) const
{
  Ray transformedRay{m_inverseMatrix * glm::vec4{ray.GetOrigin(), 1.0F},
                     m_inverseMatrix * glm::vec4{ray.GetDirection(), 0.0F}};

  if (!m_object->Intersect(transformedRay, hit, minDistance)) {
    return false;
  }

  hit.SetHitPoint(m_matrix * glm::vec4{hit.GetHitPoint(), 1.0F});
  hit.SetNormal(m_inverseMatrix * glm::vec4{hit.GetNormal(), 0.0F});
  hit.SetDistance(glm::length(hit.GetHitPoint() - ray.GetOrigin()));

  return true;
}