#include "Scene.hpp"

using json = nlohmann::json;

Scene::Scene(std::string&& filename) : m_backgroundColor{0.0F, 0.0F, 0.0F}
{
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open scene file: " << filename << "!\n";
    throw std::runtime_error("Failed to open scene file!");
  }

  json data;
  file >> data;
  file.close();

  m_camera = LoadCamera(data);
  m_backgroundColor = LoadBackgroundColor(data["background"]["color"]);
  m_objectGroup = LoadObjectGroup(data["group"]);
}

const std::shared_ptr<Camera>& Scene::GetCamera() const
{
  return m_camera;
}

const Color& Scene::GetBackgroundColor() const
{
  return m_backgroundColor;
}

const ObjectGroup& Scene::GetObjectGroup() const
{
  return m_objectGroup;
}

float Scene::LoadFloat(const json& json)
{
  return json.get<float>();
}

glm::vec3 Scene::LoadVector(const nlohmann::json& json)
{
  glm::vec3 v;
  json.at(0).get_to<float>(v[0]);
  json.at(1).get_to<float>(v[1]);
  json.at(2).get_to<float>(v[2]);

  return v;
}

std::shared_ptr<Camera> Scene::LoadCamera(const nlohmann::json& json)
{
  if (json.contains("orthocamera")) {
    const auto& c{json["orthocamera"]};

    const glm::vec3 center{LoadVector(c["center"])};
    const glm::vec3 direction{LoadVector(c["direction"])};
    const glm::vec3 up{LoadVector(c["up"])};
    const float size{LoadFloat(c["size"])};

    return std::make_shared<OrthoCamera>(size, center, direction, up);
  }

  if (json.contains("perspectivecamera")) {}

  std::cerr << "There is no camera in the scene or camera type not implemented!\n";
  throw std::runtime_error("There is no camera in the scene or camera type not implemented!");
}

Color Scene::LoadBackgroundColor(const nlohmann::json& json)
{
  return LoadVector(json);
}

ObjectGroup Scene::LoadObjectGroup(const nlohmann::json& json)
{
  ObjectGroup objectGroup;

  for (const auto& obj : json) {
    if (obj.contains("sphere")) {
      const auto& s{obj["sphere"]};

      const glm::vec3 center{LoadVector(s["center"])};
      const float radius{LoadFloat(s["radius"])};
      const Color color{LoadVector(s["color"])};

      objectGroup.Add(std::make_unique<Sphere>(color, radius, center));
    }
  }

  return objectGroup;
}
