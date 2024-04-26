#pragma once

#include "Core/Color.hpp"

class Light
{
 public:
  explicit Light(const Color& color);

  virtual ~Light() = default;

  const Color& GetColor();

 private:
  Color m_color;
};