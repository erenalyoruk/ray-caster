#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Render/Renderer.hpp"

int main()
{
  constexpr int width{800};
  constexpr int height{800};

  Renderer renderer{width, height};

  Scene scene1("Assets/scene1_diffuse.json");
  renderer.Render(scene1, "scene1.png");

  Scene scene2("Assets/scene2_ambient.json");
  renderer.Render(scene2, "scene2.png");

  Scene scene3("Assets/scene3_perspective.json");
  renderer.Render(scene3, "scene3.png");

  Scene scene4("Assets/scene4_plane.json");
  renderer.Render(scene4, "scene4.png");

  Scene scene5("Assets/scene5_sphere_triangle.json");
  renderer.Render(scene5, "scene5.png");

  Scene scene6("Assets/scene6_squashed_sphere.json");
  renderer.Render(scene6, "scene6.png");

  Scene scene7("Assets/scene7_squashed_rotated_sphere.json");
  renderer.Render(scene7, "scene7.png");

  return 0;
}