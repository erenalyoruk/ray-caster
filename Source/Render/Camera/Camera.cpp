#include "Camera.hpp"

Camera::Camera(const glm::vec3& center, const glm::vec3& direction, const glm::vec3& up)
    : m_center{center}, m_direction{glm::normalize(direction)}, m_up{glm::normalize(up)}
{
}

const glm::vec3& Camera::GetCenter() const
{
  return m_center;
}

const glm::vec3& Camera::GetDirection() const
{
  return m_direction;
}

const glm::vec3& Camera::GetUp() const
{
  return m_up;
}