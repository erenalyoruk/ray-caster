#pragma once

#include "Camera.hpp"

class OrthoCamera : public Camera
{
 public:
  OrthoCamera() = delete;

  OrthoCamera(float size, const glm::vec3& center, const glm::vec3& direction, const glm::vec3& up);

  Ray GenerateRay(float x, float y) const override;

 private:
  float m_size;

  glm::vec3 m_horizontal;
};