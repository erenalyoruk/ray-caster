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

      Hit hit{};
      if (scene.GetObjectGroup().Intersect(ray, hit, FLT_EPSILON)) {
        const auto color{hit.GetColor()};

        imageData[index] = static_cast<unsigned char>(color[0] * 255.999F);
        imageData[index + 1] = static_cast<unsigned char>(color[1] * 255.999F);
        imageData[index + 2] = static_cast<unsigned char>(color[2] * 255.999F);
      } else {
        const auto color{scene.GetBackgroundColor()};

        imageData[index] = static_cast<unsigned char>(color[0] * 255.999F);
        imageData[index + 1] = static_cast<unsigned char>(color[1] * 255.999F);
        imageData[index + 2] = static_cast<unsigned char>(color[2] * 255.999F);
      }
    }
  }

  stbi_flip_vertically_on_write(static_cast<int>(true));
  stbi_write_png(filename.begin(), m_width, m_height, 3, imageData.data(), m_width * 3);

  std::cout << filename << " rendered!\n";
}
