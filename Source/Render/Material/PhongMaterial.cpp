#include "PhongMaterial.hpp"

PhongMaterial::PhongMaterial(const Color& diffuseColor) : Material(diffuseColor) {}

Color PhongMaterial::Shade(const Ray& ray, const Hit& hit,
                           const std::shared_ptr<Light>& light) const
{
  auto directionalLight{std::dynamic_pointer_cast<DirectionalLight>(light)};
  if (directionalLight == nullptr) {
    return {0.0F, 0.0F, 0.0F};
  }

  const auto lightDir{-directionalLight->GetDirection()};
  const auto normal{hit.GetNormal()};

  const auto diffuseFactor{glm::max(glm::dot(lightDir, normal), 0.0F)};
  const auto diffusePart{this->GetDiffuseColor() * light->GetColor() * diffuseFactor};
  Color finalColor{diffusePart};

  if (this->GetSpecularColor().has_value() && this->GetExponent().has_value()) {
    const auto viewDir{ray.GetDirection()};
    const auto reflectionDir{glm::reflect(lightDir, normal)};
    const auto specularFactor{
        glm::pow(glm::max(glm::dot(viewDir, reflectionDir), 0.0F), this->GetExponent().value())};
    const auto specularPart{this->GetSpecularColor().value() * light->GetColor() * specularFactor};

    finalColor += specularPart;
  }

  return glm::clamp(finalColor, 0.0F, 1.0F);
}