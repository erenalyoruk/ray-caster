#pragma once

#include "Camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/mat3x3.hpp>

class PerspectiveCamera : public Camera
{
 public:
  PerspectiveCamera() = delete;

  PerspectiveCamera(float fov, const glm::vec3& center, const glm::vec3& direction,
                    const glm::vec3& up);

  Ray GenerateRay(float x, float y) const override;

 private:
  float m_halfTanFov;

  glm::mat3 m_inverseViewMatrix;
};