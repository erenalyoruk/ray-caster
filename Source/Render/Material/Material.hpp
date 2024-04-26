#pragma once

#include "Core/Color.hpp"
#include "Core/Hit.hpp"
#include "Core/Ray.hpp"
#include "Render/Light/DirectionalLight.hpp"
#include "Render/Light/Light.hpp"

#include <memory>
#include <optional>

class Hit;

class Material
{
 public:
  Material() = delete;

  explicit Material(const Color& diffuseColor);

  virtual ~Material() = default;

  virtual Color Shade(const Ray& ray, const Hit& hit,
                      const std::shared_ptr<Light>& light) const = 0;

  const Color& GetDiffuseColor() const;

  const std::optional<float>& GetExponent() const;
  const std::optional<float>& GetRefractionIndex() const;

  const std::optional<Color>& GetSpecularColor() const;
  const std::optional<Color>& GetReflectiveColor() const;
  const std::optional<Color>& GetTransparentColor() const;

  void SetExponent(float exponent);
  void SetRefractionIndex(float refractionIndex);

  void SetSpecularColor(const Color& color);
  void SetReflectiveColor(const Color& color);
  void SetTransparentColor(const Color& color);

 private:
  Color m_diffuseColor;

  std::optional<Color> m_specularColor;
  std::optional<float> m_exponent;

  std::optional<Color> m_reflectiveColor;
  std::optional<Color> m_transparentColor;
  std::optional<float> m_refractionIndex;
};