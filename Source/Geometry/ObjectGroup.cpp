#include "ObjectGroup.hpp"

bool ObjectGroup::Intersect(const Ray& ray, Hit& hit, float minDistance) const
{
  bool hitFound{false};
  float closestDistance{std::numeric_limits<float>::infinity()};

  for (const auto& object : m_objects) {
    Hit objHit{};
    if (object->Intersect(ray, objHit, minDistance)) {
      hitFound = true;

      if (objHit.GetDistance() < closestDistance) {
        closestDistance = objHit.GetDistance();
        hit = objHit;
      }
    }
  }

  return hitFound;
}

void ObjectGroup::Add(std::unique_ptr<Object>&& object)
{
  m_objects.push_back(std::move(object));
}

void ObjectGroup::Clear()
{
  m_objects.clear();
}