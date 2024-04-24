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