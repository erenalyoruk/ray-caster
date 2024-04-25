#pragma once

#include "Color.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Hit
{
 public:
  float GetDistance() const;

  const Color& GetColor() const;

  const glm::vec3& GetHitPoint() const;
  const glm::vec3& GetNormal() const;

  void SetDistance(float distance);

  void SetColor(const Color& color);

  void SetHitPoint(const glm::vec3& hitPoint);
  void SetNormal(const glm::vec3& normal);

 private:
  float m_distance;

  Color m_color;

  glm::vec3 m_hitPoint;
  glm::vec3 m_normal;
};