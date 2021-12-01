#include <rt/bbox.h>

namespace rt {

BBox BBox::empty() {
  BBox bbox;
  bbox.isEmpty = true;
  return bbox;
}

BBox BBox::full() {
  Point minimum = Point(__FLT_MIN__, __FLT_MIN__, __FLT_MIN__);
  Point maximum = Point(__FLT_MAX__, __FLT_MAX__, __FLT_MAX__);
  return BBox(minimum, maximum);
}

void BBox::extend(const Point& point) {
  if (isEmpty) {
    isEmpty = false;
    min = point;
    max = point;
    return;
  }
  min = min(this->min, point);
  max = max(this->max, point);
  return;
}

void BBox::extend(const BBox& bbox) {
  if (isEmpty) {
    isEmpty = bbox.isEmpty;
    min = bbox.min;
    max = bbox.max;
    return;
  }
  min = min(this->min, bbox.min);
  max = max(this->max, bbox.max);
  return;
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
  // element-wise division for two vectors (included in vector class)
  Vector near = (min - ray.o) / ray.d;
  Vector far = (max - ray.o) / ray.d;

  float t_min = max(max(min(near.x, far.x),min(near.y, far.y)),min(near.z, far.z));
  float t_max = min(min(max(near.x, far.x),max(near.y, far.y)),max(near.z, far.z));

  return std::make_pair (t_min, t_max);
}

bool BBox::isUnbound() const {
  Point minimum = min(min, max);
  Point maximum = max(min, max);
  return (minimum.x == -FLT_MAX || minimum.y == -FLT_MAX || minimum.z == -FLT_MAX ||
    maximum.x == FLT_MAX || maximum.y == FLT_MAX || maximum.z == FLT_MAX);
}

Point BBox::centroid() const {
  return Point((min.x + max.x)/2, (min.y + max.y)/2, (min.z + max.z)/2);
}

}
