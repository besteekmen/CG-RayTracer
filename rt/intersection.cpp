#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
  this->ray = ray;
  this->solid = solid;
  this->distance = distance; // t
  this->normal = normal;
  this->local = local;
  this->intersect = true;
}

Intersection::operator bool() const {
  return this->intersect;
}

Intersection Intersection::failure() {
  return Intersection();
}

Point Intersection::hitPoint() const {
  Point hit = ray.o + distance * ray.d;
  return hit;
}

Vector Intersection::normal() const {
  return normal;
}

Point Intersection::local() const {
  return local;
}

}
