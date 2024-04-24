#include "Object.hpp"

Object::Object() : Object({0.0F, 0.0F, 0.0F}) {}

Object::Object(const Color& color) : m_color{color} {}

const Color& Object::GetColor() const
{
  return m_color;
}