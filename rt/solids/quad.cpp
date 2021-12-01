#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
{
  this->v1 = origin;
  this->span1 = span1;
  this->span2 = span2;
  this->normal = cross(span1, span2).normalize();

  v2 = v1 + this->span1;
  v3 = v1 + this->span1 + this->span2;
  v4 = v1 + this->span2;

  this->center = v1 + (0.5*this->span1) + (0.5*this->span2);

  //t1 = Triangle(v1, v2, v4, texMapper, material);
	//t2 = Triangle(v2, v4, v3, texMapper, material);
}

BBox Quad::getBounds() const {
  Point min = rt::min(rt::min(v1, v2), rt::min(v3, v4));
  Point max = rt::max(rt::max(v1, v2), rt::max(v3, v4));
	return BBox(min, max);
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
  if (dot(ray.d, this->normal) == 0.0) return Intersection::failure();
  float t = dot(center - ray.o, normal) / dot(ray.d, this->normal);
  if (t > previousBestDistance || t < 0.001) return Intersection::failure();
  Point hit_point = ray.getPoint(t);

  bool check1 = dot(cross(v2-v1, hit_point - v1), normal) >= 0;
  bool check2 = dot(cross(v3-v2, hit_point - v2), normal) >= 0;
  bool check3 = dot(cross(v4-v3, hit_point - v3), normal) >= 0;
  bool check4 = dot(cross(v1-v4, hit_point - v4), normal) >= 0;

  if (check1 && check2 && check3 && check4)
    return Intersection(t, ray, this, normal, hit_point);
  else
    return Intersection::failure();
}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
	return cross(span1, span2).length();
}

}
