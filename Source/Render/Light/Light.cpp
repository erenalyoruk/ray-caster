#include "Light.hpp"

Light::Light(const Color& color) : m_color{color} {}

const Color& Light::GetColor()
{
  return m_color;
}