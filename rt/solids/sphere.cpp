#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
	this->center = center;
	this->radius = radius;
	this->texMapper = texMapper;
	this->material = material;
}

BBox Sphere::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool is_t_valid(float t, float previousBestDistance){
    return (t < previousBestDistance && t >= epsilon);
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    float A = dot(ray.d, ray.d);
		float B = 2.0f * dot(ray.o - center, ray.d);
		float C = dot(ray.o - center, ray.o - center) - (radius * radius);
		float t, d = B * B - 4 * A * C;
    Vector normal;

		if (d < 0.0f) return Intersection::failure();
    else {
  			float t1 = (- B + sqrt(d)) / (2 * A);
  			float t2 = (- B - sqrt(d)) / (2 * A);

  			bool is_t1_valid = is_t_valid(t1, previousBestDistance);
  			bool is_t2_valid = is_t_valid(t2, previousBestDistance);

  			if (!is_t1_valid && !is_t2_valid) return Intersection::failure();
  			if (is_t1_valid && is_t2_valid) t = min(t1, t2);
  			if (!is_t1_valid && is_t2_valid) t = t2;
  			if (is_t1_valid && !is_t2_valid) t = t1;
		}

    normal = ray.getPoint(t) - center;
    return Intersection(t, ray, this, normal.normalize(), ray.getPoint(t));
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    return (4*pi*pow(radius, 2));
}

}
