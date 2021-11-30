#include <rt/solids/aabox.h>
#include <core/point.h>
namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    this->minCorner = min(corner1, corner2);
		this->maxCorner = max(corner1, corner2);
}

BBox AABox::getBounds() const {
    NOT_IMPLEMENTED;
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
  float x = std::abs(maxCorner.x - minCorner.x);
  float y = std::abs(maxCorner.y - minCorner.y);
  float z = std::abs(maxCorner.z - minCorner.z);
  return 2 * (x*y + y*z + z*x) ;
}

bool is_t_valid_aa(float t, float previousBestDistance){
    return (t < previousBestDistance && t >= std::numeric_limits<float>::epsilon());
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
  float ray_dir_x = 1 / ray.d.x;
  float ray_dir_y = 1 / ray.d.y;
  float ray_dir_z = 1 / ray.d.z;

  // For X
  float tx_1 = (minCorner.x - ray.o.x) * ray_dir_x;
  float tx_2 = (maxCorner.x - ray.o.x) * ray_dir_x;

  // For Y
  float ty_3 = (minCorner.y - ray.o.y) * ray_dir_y;
  float ty_4 = (maxCorner.y - ray.o.y) * ray_dir_y;

  // For Z
  float tz_5 = (minCorner.z - ray.o.z) * ray_dir_z;
  float tz_6 = (maxCorner.z - ray.o.z) * ray_dir_z;

  float t_min = std::max(
    std::max(std::min(tx_1, tx_2), std::min(ty_3, ty_4)),
    std::min(tz_5, tz_6));
  float t_max = std::min(
    std::min(std::max(tx_1, tx_2), std::max(ty_3, ty_4)),
    std::max(tz_5, tz_6));

  if (t_max < 0 || t_min > t_max || t_max > FLT_MAX) { return Intersection::failure(); };
  if (t_min > previousBestDistance || t_min < 0) { return Intersection::failure(); };

  Vector n;
  n = t_min == tx_1 ? Vector(-1, 0, 0) : n;
  n = t_min == tx_2 ? Vector(1, 0, 0) : n;
  n = t_min == ty_3 ? Vector(0, -1, 0) : n;
  n = t_min == ty_4 ? Vector(0, 1, 0) : n;
  n = t_min == tz_5 ? Vector(0, 0, -1) : n;
  n = t_min == tz_6 ? Vector(0, 0, 1) : n;

  return Intersection(t_min, ray, this, n, ray.getPoint(t_min));
}

}
