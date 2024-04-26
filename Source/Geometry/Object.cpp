#include "Object.hpp"

Object::Object() : Object(nullptr) {}

// i just want to share ownership
Object::Object(std::shared_ptr<Material> material) : m_material{material} {}

std::shared_ptr<Material> Object::GetMaterial() const
{
  return m_material;
}