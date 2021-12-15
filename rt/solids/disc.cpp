#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
	this->center = center;
	this->normal = normal;
	this->radius = radius;
	this->material = material;
}

BBox Disc::getBounds() const {
	Point min = center - Vector(radius, radius, radius);
	Point max = center + Vector(radius, radius, radius);
	return BBox(min, max);
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
	if (dot(ray.d, this->normal) == 0.0) return Intersection::failure();
	float t = - dot(ray.o - center, this->normal) / dot(ray.d, this->normal);
	if (t > previousBestDistance || t < 0) return Intersection::failure();

	Point hit_point = ray.getPoint(t);
	if ((hit_point - center).length() > radius)
		return Intersection::failure();

	return Intersection(t, ray, this, this->normal, hit_point);
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
	return pi * pow(radius,2);
}

}
