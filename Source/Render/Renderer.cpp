#include "Renderer.hpp"

Renderer::Renderer() : Renderer(800, 800) {}

Renderer::Renderer(int width, int height) : m_width{width}, m_height{height} {}

void Renderer::Render(const Scene& scene, std::string_view filename) const
{
  std::vector<unsigned char> imageData(m_width * m_height * 3);

  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      const int index{(y * m_width + x) * 3};

      const float u{static_cast<float>(x) / static_cast<float>(m_width)};
      const float v{static_cast<float>(y) / static_cast<float>(m_width)};

      Ray ray{scene.GetCamera()->GenerateRay(u, v)};

      Hit hit;
      if (scene.GetObjectGroup().Intersect(ray, hit, FLT_EPSILON)) {
        const Color color{TraceRay(scene, ray, glm::epsilon<float>(), 1, 1.0F, 0.0F, hit) *
                          255.999F};

        imageData[index] = static_cast<unsigned char>(color[0]);
        imageData[index + 1] = static_cast<unsigned char>(color[1]);
        imageData[index + 2] = static_cast<unsigned char>(color[2]);
      } else {
        const auto color{scene.GetBackgroundColor() * 255.999F};

        imageData[index] = static_cast<unsigned char>(color[0]);
        imageData[index + 1] = static_cast<unsigned char>(color[1]);
        imageData[index + 2] = static_cast<unsigned char>(color[2]);
      }
    }
  }

  stbi_flip_vertically_on_write(static_cast<int>(true));
  stbi_write_png(filename.begin(), m_width, m_height, 3, imageData.data(), m_width * 3);

  std::cout << filename << " rendered!\n";
}

Color Renderer::TraceRay(const Scene& scene, const Ray& ray, float minDistance, int /*bounces*/,
                         float /*weight*/, float /*refractionIndex*/, Hit& hit)
{
  Color color{scene.GetAmbientColor() * hit.GetMaterial()->GetDiffuseColor()};

  // Shadows
  for (const auto& light : scene.GetLights()) {
    if (auto directionalLight{std::dynamic_pointer_cast<DirectionalLight>(light)}) {
      const Ray shadowRay{hit.GetHitPoint() + hit.GetNormal() * 0.0001F,
                          -directionalLight->GetDirection()};

      Hit tempHit;
      if (!scene.GetObjectGroup().Intersect(shadowRay, tempHit, minDistance)) {
        color += hit.GetMaterial()->Shade(ray, hit, light);
      }
    }
  }

  return glm::clamp(color, 0.0F, 1.0F);
}