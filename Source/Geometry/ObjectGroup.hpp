#pragma once

#include "Object.hpp"

#include <limits>
#include <memory>
#include <utility>
#include <vector>

class ObjectGroup : public Object
{
 public:
  bool Intersect(const Ray& ray, Hit& hit, float minDistance) const override;

  void Add(std::unique_ptr<Object>&& object);

  void Clear();

 private:
  std::vector<std::unique_ptr<Object>> m_objects;
};