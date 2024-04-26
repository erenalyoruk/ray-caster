#pragma once

#include "Core/Color.hpp"
#include "Geometry/Object.hpp"
#include "Geometry/ObjectGroup.hpp"
#include "Geometry/Plane.hpp"
#include "Geometry/Sphere.hpp"
#include "Geometry/Transformation.hpp"
#include "Geometry/Triangle.hpp"
#include "Render/Camera/Camera.hpp"
#include "Render/Camera/OrthoCamera.hpp"
#include "Render/Camera/PerspectiveCamera.hpp"
#include "Render/Light/DirectionalLight.hpp"
#include "Render/Light/Light.hpp"
#include "Render/Material/Material.hpp"
#include "Render/Material/PhongMaterial.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

class Scene
{
 public:
  Scene() = delete;

  explicit Scene(std::string&& filename);

  const std::shared_ptr<Camera>& GetCamera() const;

  const Color& GetBackgroundColor() const;
  const Color& GetAmbientColor() const;

  const std::vector<std::shared_ptr<Light>>& GetLights() const;

  const ObjectGroup& GetObjectGroup() const;

 private:
  std::shared_ptr<Camera> m_camera;

  Color m_backgroundColor;
  Color m_ambientColor;

  std::vector<std::shared_ptr<Light>> m_lights;

  std::vector<std::shared_ptr<Material>> m_materials;

  ObjectGroup m_objectGroup;

  static int LoadInt(const nlohmann::json& json);
  static float LoadFloat(const nlohmann::json& json);
  static glm::vec3 LoadVector(const nlohmann::json& json);
  static Color LoadColor(const nlohmann::json& json);

  static std::shared_ptr<Camera> LoadCamera(const nlohmann::json& json);

  static std::shared_ptr<Light> LoadLight(const nlohmann::json& json);
  static std::vector<std::shared_ptr<Light>> LoadLights(const nlohmann::json& json);

  static std::shared_ptr<Material> LoadMaterial(const nlohmann::json& json);
  static std::vector<std::shared_ptr<Material>> LoadMaterials(const nlohmann::json& json);

  static std::unique_ptr<Object> LoadObject(
      const nlohmann::json& json, const std::vector<std::shared_ptr<Material>>& materials);
  static ObjectGroup LoadObjectGroup(const nlohmann::json& json,
                                     const std::vector<std::shared_ptr<Material>>& materials);
};