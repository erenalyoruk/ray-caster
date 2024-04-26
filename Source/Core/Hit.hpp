#pragma once

#include "Color.hpp"
#include "Render/Material/Material.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <memory>

class Material;

class Hit
{
 public:
  float GetDistance() const;

  const std::shared_ptr<Material>& GetMaterial() const;

  const glm::vec3& GetHitPoint() const;
  const glm::vec3& GetNormal() const;

  void SetDistance(float distance);

  void SetMaterial(std::shared_ptr<Material> Material);

  void SetHitPoint(const glm::vec3& hitPoint);
  void SetNormal(const glm::vec3& normal);

 private:
  float m_distance;

  std::shared_ptr<Material> m_material;

  glm::vec3 m_hitPoint;
  glm::vec3 m_normal;
};