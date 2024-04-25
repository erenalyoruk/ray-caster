#pragma once

#include "Scene/Scene.hpp"

#include <stb_image_write.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string_view>
#include <utility>
#include <vector>

class Renderer
{
 public:
  Renderer();

  Renderer(int width, int height);

  void Render(const Scene& scene, std::string_view filename) const;

 private:
  int m_width;
  int m_height;
};