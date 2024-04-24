#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Scene/Scene.hpp"

#include <stb_image_write.h>

#include <vector>

std::vector<unsigned char> Render(const Scene& scene, int width, int height);

int main()
{
  constexpr int width{800};
  constexpr int height{800};

  Scene scene("Assets/scene2.json");

  std::vector<unsigned char> imageData{Render(scene, width, height)};

  stbi_flip_vertically_on_write(static_cast<int>(true));
  stbi_write_png("test.png", width, height, 3, imageData.data(), width * 3);

  return 0;
}

std::vector<unsigned char> Render(const Scene& scene, int width, int height)
{
  std::vector<unsigned char> imageData(width * height * 3);

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      const int index{(y * width + x) * 3};

      const float u{static_cast<float>(x) / static_cast<float>(width)};
      const float v{static_cast<float>(y) / static_cast<float>(height)};

      Ray ray{scene.GetCamera()->GenerateRay(u, v)};

      Hit hit;
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

  return imageData;
}