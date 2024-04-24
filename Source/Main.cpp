#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Render/Renderer.hpp"

int main()
{
  constexpr int width{800};
  constexpr int height{800};

  Renderer renderer{width, height};

  Scene scene1("Assets/scene1.json");
  renderer.Render(scene1, "scene1.png");

  Scene scene2("Assets/scene2.json");
  renderer.Render(scene2, "scene2.png");

  return 0;
}