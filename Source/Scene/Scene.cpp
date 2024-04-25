#include "Scene.hpp"

using json = nlohmann::json;

Scene::Scene(std::string&& filename)
    : m_backgroundColor{0.0F, 0.0F, 0.0F},
      m_ambientColor{0.0F, 0.0F, 0.0F},
      m_lightDirection{0.0F, 0.0F, 0.0F},
      m_lightColor{0.0F, 0.0F, 0.0F}
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

  m_backgroundColor = LoadColor(data["background"]["color"]);
  m_ambientColor = LoadColor(data["background"]["ambient"]);

  m_lightDirection = glm::normalize(LoadVector(data["light"]["direction"]));
  m_lightColor = LoadColor(data["light"]["color"]);

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

const Color& Scene::GetAmbientColor() const
{
  return m_ambientColor;
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

  if (json.contains("perspectivecamera")) {
    const auto& c{json["perspectivecamera"]};

    const glm::vec3 center{LoadVector(c["center"])};
    const glm::vec3 direction{LoadVector(c["direction"])};
    const glm::vec3 up{LoadVector(c["up"])};
    const float angle{LoadFloat(c["angle"])};

    return std::make_shared<PerspectiveCamera>(angle, center, direction, up);
  }

  std::cerr << "There is no camera in the scene or camera type not implemented!\n";
  throw std::runtime_error("There is no camera in the scene or camera type not implemented!");
}

Color Scene::LoadColor(const nlohmann::json& json)
{
  return LoadVector(json);
}

const glm::vec3& Scene::GetLightDirection() const
{
  return m_lightDirection;
}

const Color& Scene::GetLightColor() const
{
  return m_lightColor;
}

std::unique_ptr<Object> Scene::LoadObject(const nlohmann::json& json)
{
  if (json.contains("sphere")) {
    const auto& s{json["sphere"]};

    const glm::vec3 center{LoadVector(s["center"])};
    const float radius{LoadFloat(s["radius"])};
    const Color color{LoadVector(s["color"])};

    return std::make_unique<Sphere>(color, radius, center);
  }

  if (json.contains("plane")) {
    const auto& p{json["plane"]};

    const glm::vec3 normal{LoadVector(p["normal"])};
    const float offset{LoadFloat(p["offset"])};
    const Color color{LoadVector(p["color"])};

    return std::make_unique<Plane>(color, offset, normal);
  }

  if (json.contains("triangle")) {
    const auto& t{json["triangle"]};

    const glm::vec3 v1{LoadVector(t["v1"])};
    const glm::vec3 v2{LoadVector(t["v2"])};
    const glm::vec3 v3{LoadVector(t["v3"])};
    const Color color{LoadVector(t["color"])};

    return std::make_unique<Triangle>(color, v1, v2, v3);
  }

  std::cerr << "Object type is not implemented!\n";

  return nullptr;
}

ObjectGroup Scene::LoadObjectGroup(const nlohmann::json& json)
{
  ObjectGroup objectGroup;

  for (const auto& obj : json) {
    if (obj.contains("transform")) {
      glm::mat4 scaleMatrix{1.0F};
      glm::mat4 rotateMatrix{1.0F};
      glm::mat4 translateMatrix{1.0F};

      const auto& t{obj["transform"]};
      for (const auto& transform : t["transformations"]) {
        if (transform.contains("translate")) {
          const auto translate{LoadVector(transform["translate"])};
          translateMatrix = glm::translate(translateMatrix, translate);
        } else if (transform.contains("scale")) {
          const auto scale{LoadVector(transform["scale"])};
          scaleMatrix = glm::scale(scaleMatrix, scale);
        } else if (transform.contains("xrotate")) {
          const glm::vec3 axis{1.0F, 0.0F, 0.0F};
          const auto rotate{LoadFloat(transform["xrotate"])};
          rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotate), axis);
        } else if (transform.contains("yrotate")) {
          const glm::vec3 axis{0.0F, 1.0F, 0.0F};
          const auto rotate{LoadFloat(transform["yrotate"])};
          rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotate), axis);
        } else if (transform.contains("zrotate")) {
          const glm::vec3 axis{0.0F, 0.0F, 1.0F};
          const auto rotate{LoadFloat(transform["zrotate"])};
          rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotate), axis);
        }
      }

      glm::mat4 matrix{translateMatrix * rotateMatrix * scaleMatrix};

      objectGroup.Add(std::make_unique<Transformation>(std::move(LoadObject(t["object"])), matrix));
    } else {
      auto object{LoadObject(obj)};
      if (object != nullptr) {
        objectGroup.Add(std::move(object));
      }
    }
  }

  return objectGroup;
}