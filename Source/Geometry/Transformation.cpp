#include "Transformation.hpp"

Transformation::Transformation(std::unique_ptr<Object>&& object, const glm::mat4& matrix)
    : m_object{std::move(object)}, m_inverseMatrix{glm::inverse(matrix)}
{
}

bool Transformation::Intersect(const Ray& ray, Hit& hit, float minDistance) const
{
  const glm::vec3 transformedOrigin{m_inverseMatrix * glm::vec4(ray.GetOrigin(), 1.0F)};
  const glm::vec3 transformedDirection{glm::mat3{m_inverseMatrix} * ray.GetDirection()};

  const Ray transformedRay{transformedOrigin, transformedDirection};

  return m_object->Intersect(transformedRay, hit, minDistance);
}