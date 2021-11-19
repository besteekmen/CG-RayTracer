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

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {

		float A = dot (ray.d, ray.d);
		float B = 2 * dot(ray.d, (ray.o - Point(0,0,0))) - 2 * dot((center - Point(0,0,0)), ray.d);
		float C =  (ray.o - Point(0,0,0)).lensqr() - 2 * dot ((center - Point(0,0,0)), (ray.o - Point(0,0,0))) + (center - Point(0,0,0)).lensqr() - radius * radius;

		float t;

		if (A == 0){
			t = - C / B;
      Vector n = -(this->center - ray.getPoint(t)).normalize();
			if (t <= previousBestDistance && t >= 0) return Intersection(t, ray, this, n, ray.getPoint(t));
		}
		else
		{
			float d = B * B - 4 * A * C;

			if (d < 0.0) return Intersection::failure();

			float t1 = ( - B + sqrt(d)) / (2 * A);
			float t2 = ( - B - sqrt(d)) / (2 * A);

			bool is_t1_valid = (t1 <= previousBestDistance && t >= 0);
			bool is_t2_valid = (t2 <= previousBestDistance && t >= 0);

			if (!is_t1_valid && !is_t2_valid) return Intersection::failure();

			float t;

			if (is_t1_valid && is_t2_valid) t = min(t1, t2);
			if (!is_t1_valid && is_t2_valid) t = t2;
			if (is_t1_valid && !is_t2_valid) t = t1;

      Vector n = -(this->center - ray.getPoint(t)).normalize();
			return Intersection(t, ray, this, n, ray.getPoint(t));
		}
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    return (4*pi*pow(radius, 2));
}

}
