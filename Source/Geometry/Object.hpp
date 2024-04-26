#pragma once

#include "Core/Hit.hpp"
#include "Core/Ray.hpp"
#include "Render/Material/Material.hpp"

#include <glm/vec3.hpp>

#include <memory>

class Object
{
 public:
  Object();

  virtual ~Object() = default;

  explicit Object(std::shared_ptr<Material> material);

  virtual bool Intersect(const Ray& ray, Hit& hit, float minDistance) const = 0;

  std::shared_ptr<Material> GetMaterial() const;

 private:
  std::shared_ptr<Material> m_material;
};