#include "Hit.hpp"

float Hit::GetDistance() const
{
  return m_distance;
}

const std::shared_ptr<Material>& Hit::GetMaterial() const
{
  return m_material;
}

const glm::vec3& Hit::GetHitPoint() const
{
  return m_hitPoint;
}

const glm::vec3& Hit::GetNormal() const
{
  return m_normal;
}

void Hit::SetDistance(float distance)
{
  m_distance = distance;
}

void Hit::SetMaterial(std::shared_ptr<Material> material)
{
  // i know, i want to share ownership
  m_material = material;
}

void Hit::SetHitPoint(const glm::vec3& hitPoint)
{
  m_hitPoint = hitPoint;
}

void Hit::SetNormal(const glm::vec3& normal)
{
  m_normal = glm::normalize(normal);
}