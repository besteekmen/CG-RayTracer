#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Point::Point(const Float4& f4)
{
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Point::operator - (const Point& b) const {
  return Vector(x - b.x, y - b.y, z - b.z);
}

bool Point::operator == (const Point& b) const {
  if(x == b.x && y == b.y && z == b.z)
    return true;
  else
    return false;
}

bool Point::operator != (const Point& b) const {
  return !((*this) == b);
}

Point operator * (float scalar, const Point& b) {
  return Point(scalar * b.x, scalar * b.y, scalar * b.z);
}

Point operator * (const Point& a, float scalar) {
  return Point(scalar * a.x, scalar * a.y, scalar * a.z);
}

Point min(const Point& a, const Point& b) {
  return Point(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point max(const Point& a, const Point& b) {
  return Point(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

}
