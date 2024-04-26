#include "Scene.hpp"

using json = nlohmann::json;

Scene::Scene(std::string&& filename)
    : m_backgroundColor{0.0F, 0.0F, 0.0F}, m_ambientColor{0.0F, 0.0F, 0.0F}
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

  m_lights = LoadLights(data);

  m_materials = LoadMaterials(data["materials"]);

  m_objectGroup = LoadObjectGroup(data["group"], m_materials);
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

const std::vector<std::shared_ptr<Light>>& Scene::GetLights() const
{
  return m_lights;
}

const ObjectGroup& Scene::GetObjectGroup() const
{
  return m_objectGroup;
}

int Scene::LoadInt(const json& json)
{
  return json.get<int>();
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

std::shared_ptr<Material> Scene::LoadMaterial(const nlohmann::json& json)
{
  if (json.contains("phongMaterial")) {
    const auto& m{json["phongMaterial"]};

    const Color diffuseColor{LoadVector(m["diffuseColor"])};
    auto material{std::make_shared<PhongMaterial>(diffuseColor)};

    if (m.contains("specularColor") && m.contains("exponent")) {
      const Color specularColor{LoadVector(m["specularColor"])};
      const auto exponent{LoadFloat(m["exponent"])};

      material->SetSpecularColor(specularColor);
      material->SetExponent(exponent);
    }

    if (m.contains("reflectiveColor")) {
      const Color reflectiveColor{LoadVector(m["reflectiveColor"])};

      material->SetReflectiveColor(reflectiveColor);
    }

    if (m.contains("transparentColor") && m.contains("idnexOfRefraction")) {
      const Color transparentColor{LoadVector(m["transparentColor"])};
      const auto refractionIndex{LoadFloat(m["indexOfRefraction"])};

      material->SetTransparentColor(transparentColor);
      material->SetRefractionIndex(refractionIndex);
    }

    return material;
  }

  std::cerr << "Material type is not implemented!\n";
  return nullptr;
}

std::shared_ptr<Light> Scene::LoadLight(const nlohmann::json& json)
{
  if (json.contains("directionalLight")) {
    const auto& l{json["directionalLight"]};

    const auto direction{LoadVector(l["direction"])};
    const Color color{LoadVector(l["color"])};

    return std::make_shared<DirectionalLight>(color, direction);
  };

  std::cerr << "Light type is not implemented!\n";
  return nullptr;
}

std::vector<std::shared_ptr<Light>> Scene::LoadLights(const nlohmann::json& json)
{
  std::vector<std::shared_ptr<Light>> lights;

  if (json.contains("light")) {
    const auto& l{json["light"]};

    const auto direction{LoadVector(l["direction"])};
    const Color color{LoadVector(l["color"])};

    lights.push_back(std::make_shared<DirectionalLight>(direction, color));
  } else if (json.contains("lights")) {
    for (const auto& light : json["lights"]) {
      lights.push_back(std::move(LoadLight(light)));
    }
  }

  return lights;
}

std::vector<std::shared_ptr<Material>> Scene::LoadMaterials(const nlohmann::json& json)
{
  std::vector<std::shared_ptr<Material>> materials;

  for (const auto& m : json) {
    materials.push_back(std::move(LoadMaterial(m)));
  }

  return materials;
}

std::unique_ptr<Object> Scene::LoadObject(const nlohmann::json& json,
                                          const std::vector<std::shared_ptr<Material>>& materials)
{
  if (json.contains("sphere")) {
    const auto& s{json["sphere"]};

    const glm::vec3 center{LoadVector(s["center"])};
    const float radius{LoadFloat(s["radius"])};
    const auto materialIndex{LoadInt(s["material"])};
    const auto& material{materials.at(materialIndex)};

    return std::make_unique<Sphere>(material, radius, center);
  }

  if (json.contains("plane")) {
    const auto& p{json["plane"]};

    const glm::vec3 normal{LoadVector(p["normal"])};
    const float offset{LoadFloat(p["offset"])};
    const auto materialIndex{LoadInt(p["material"])};
    const auto& material{materials.at(materialIndex)};

    return std::make_unique<Plane>(material, offset, normal);
  }

  if (json.contains("triangle")) {
    const auto& t{json["triangle"]};

    const glm::vec3 v1{LoadVector(t["v1"])};
    const glm::vec3 v2{LoadVector(t["v2"])};
    const glm::vec3 v3{LoadVector(t["v3"])};
    const auto materialIndex{LoadInt(t["material"])};
    const auto& material{materials.at(materialIndex)};

    return std::make_unique<Triangle>(material, v1, v2, v3);
  }

  std::cerr << "Object type is not implemented!\n";

  return nullptr;
}

ObjectGroup Scene::LoadObjectGroup(const nlohmann::json& json,
                                   const std::vector<std::shared_ptr<Material>>& materials)
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

      objectGroup.Add(
          std::make_unique<Transformation>(std::move(LoadObject(t["object"], materials)), matrix));
    } else {
      auto object{LoadObject(obj, materials)};
      if (object != nullptr) {
        objectGroup.Add(std::move(object));
      }
    }
  }

  return objectGroup;
}