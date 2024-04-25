#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fov, const glm::vec3& center, const glm::vec3& direction,
                                     const glm::vec3& up)
    : Camera(center, direction, up),
      m_halfTanFov{glm::tan(glm::radians(fov / 2.0F))},
      m_inverseViewMatrix{
          glm::inverse(glm::lookAt(GetCenter(), GetCenter() + GetDirection(), GetUp()))}
{
}

Ray PerspectiveCamera::GenerateRay(float x, float y) const
{
  float ndcX = (2.0F * x) - 1.0F;
  float ndcY = 2.0F * y - 1.0F;

  const glm::vec3 rayDirection{ndcX * m_halfTanFov, ndcY * m_halfTanFov, -1.0F};
  const auto rayDirectionWorld{m_inverseViewMatrix * rayDirection};

  return {GetCenter(), rayDirectionWorld};
}