#pragma once

#include "Color.hpp"

#include <glm/vec3.hpp>

class Hit
{
 public:
  float GetDistance() const;

  const Color& GetColor() const;

  const glm::vec3& GetHitPoint() const;

  void SetDistance(float distance);

  void SetColor(const Color& color);

  void SetHitPoint(const glm::vec3& hitPoint);

 private:
  float m_distance;

  Color m_color;

  glm::vec3 m_hitPoint;
};