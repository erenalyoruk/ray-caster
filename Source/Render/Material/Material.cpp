#include "Material.hpp"

Material::Material(const Color& diffuseColor) : m_diffuseColor{diffuseColor} {}

const Color& Material::GetDiffuseColor() const
{
  return m_diffuseColor;
}

const std::optional<float>& Material::GetExponent() const
{
  return m_exponent;
}

const std::optional<float>& Material::GetRefractionIndex() const
{
  return m_refractionIndex;
}

const std::optional<Color>& Material::GetSpecularColor() const
{
  return m_specularColor;
}

const std::optional<Color>& Material::GetReflectiveColor() const
{
  return m_reflectiveColor;
}

const std::optional<Color>& Material::GetTransparentColor() const
{
  return m_transparentColor;
}

void Material::SetExponent(float exponent)
{
  m_exponent = exponent;
}

void Material::SetRefractionIndex(float refractionIndex)
{
  m_refractionIndex = refractionIndex;
}

void Material::SetSpecularColor(const Color& color)
{
  m_specularColor = color;
}

void Material::SetReflectiveColor(const Color& color)
{
  m_reflectiveColor = color;
}

void Material::SetTransparentColor(const Color& color)
{
  m_transparentColor = color;
}