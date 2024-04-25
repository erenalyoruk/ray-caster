#pragma once

#include "Object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include <memory>
#include <utility>

class Transformation : public Object
{
 public:
  Transformation(std::unique_ptr<Object>&& object, const glm::mat4& matrix);

  bool Intersect(const Ray& ray, Hit& hit, float minDistance) const override;

 private:
  glm::mat4 m_inverseMatrix;

  std::unique_ptr<Object> m_object;
};