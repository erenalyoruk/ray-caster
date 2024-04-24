#pragma once

#include "Core/Color.hpp"
#include "Geometry/Object.hpp"
#include "Geometry/ObjectGroup.hpp"
#include "Geometry/Sphere.hpp"
#include "Render/Camera/Camera.hpp"
#include "Render/Camera/OrthoCamera.hpp"

#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Scene
{
 public:
  Scene() = delete;

  explicit Scene(std::string&& filename);

  const std::shared_ptr<Camera>& GetCamera() const;

  const Color& GetBackgroundColor() const;

  const ObjectGroup& GetObjectGroup() const;

 private:
  std::shared_ptr<Camera> m_camera;

  Color m_backgroundColor;

  ObjectGroup m_objectGroup;

  static float LoadFloat(const nlohmann::json& json);
  static glm::vec3 LoadVector(const nlohmann::json& json);

  static std::shared_ptr<Camera> LoadCamera(const nlohmann::json& json);

  static Color LoadBackgroundColor(const nlohmann::json& json);

  static ObjectGroup LoadObjectGroup(const nlohmann::json& json);
};