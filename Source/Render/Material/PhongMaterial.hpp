#pragma once

#include "Material.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class PhongMaterial : public Material
{
 public:
  explicit PhongMaterial(const Color& diffuseColor);

  Color Shade(const Ray& ray, const Hit& hit, const std::shared_ptr<Light>& light) const override;
};