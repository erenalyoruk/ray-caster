#pragma once

#include "Core/Color.hpp"
#include "Core/Hit.hpp"
#include "Core/Ray.hpp"

#include <glm/vec3.hpp>

class Object
{
 public:
  Object();

  virtual ~Object() = default;

  explicit Object(const Color& color);

  virtual bool Intersect(const Ray& ray, Hit& hit, float minDistance) const = 0;

  const Color& GetColor() const;

 private:
  Color m_color;
};