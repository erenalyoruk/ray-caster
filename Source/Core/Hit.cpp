#include "Hit.hpp"

float Hit::GetDistance() const
{
  return m_distance;
}

const Color& Hit::GetColor() const
{
  return m_color;
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

void Hit::SetColor(const Color& color)
{
  m_color = color;
}

void Hit::SetHitPoint(const glm::vec3& hitPoint)
{
  m_hitPoint = hitPoint;
}

void Hit::SetNormal(const glm::vec3& normal)
{
  m_normal = glm::normalize(normal);
}