#include <rt/solids/triangle.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
  this->v1 = vertices[0];
  this->v2 = vertices[1];
  this->v3 = vertices[2];
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
{
  this->v1 = v1;
  this->v2 = v2;
  this->v3 = v3;
  Vector v21 = (v2 - v1).normalize();
  Vector v31 = (v3 - v1).normalize();
  this->normal = cross(v21, v31).normalize();
}

BBox Triangle::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {

		/*if (dot(ray.d, this->normal) == 0.0) return Intersection::failure();
		float t = - dot(ray.o - v1, normal) / dot(ray.d, this->normal);

		if (t > previousBestDistance || t < epsilon) return Intersection::failure();

		Point hit_point = ray.getPoint(t);

		Vector e1 = v2 - v1;
		Vector e2 = v3 - v1;
		Vector u = cross(e1, e2);

		Vector e11 = v2 - hit_point;
		Vector e12 = v3 - hit_point;
		Vector u1 = cross(e11, e12);

		Vector e21 = hit_point - v1;
		Vector e22 = v3 - v1;
		Vector u2 = cross(e21, e22);

		Vector e31 = v2 - v1;
		Vector e32 = hit_point - v1;
		Vector u3 = cross(e31, e32);

		float lambda1 =  u1.length() / u.length();
		float lambda2 = u2.length() / u.length();
		float lambda3 = u3.length() / u.length();

		float uu1 = dot(u, u1);
		float uu2 = dot(u, u2);
		float uu3 = dot(u, u3);

		if (uu1 < 0 || uu2 < 0 || uu3 < 0) return Intersection::failure();

		return Intersection(t, ray, this, normal, Point(lambda1, lambda2, lambda3));*/

    if (dot(ray.d, this->normal) == 0.0) return Intersection::failure();
    float t = - dot(ray.o - v1, normal) / dot(ray.d, this->normal);
		if (t > previousBestDistance || t < epsilon) return Intersection::failure();

    Vector e1 = v2 - v1;
    Vector e2 = v3 - v1;
    Vector pvec = cross(ray.d, e2);
    float det = dot(e1, pvec);

    if (fabs(det) < epsilon)
      return Intersection::failure();

    float invDet = 1.0 / det;
    Vector tvec = ray.o - v1;

    float u = dot(tvec, pvec) * invDet;

    if (u < 0 || u > 1)
      return Intersection::failure();

    Vector qvec = cross(tvec, e1);
    float v = dot(ray.d, qvec) * invDet;

    if (v < 0 || u + v > 1)
      return Intersection::failure();

    t = dot(e2, qvec) * invDet;
    return Intersection(t, ray, this, normal, ray.getPoint(t));

}

Solid::Sample Triangle::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Triangle::getArea() const {
  return cross(v2 - v1, v3 - v1).length() / 2;
}

}
