#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->center = center;
    this->radius = radius;
}

BBox Sphere::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    float denominator = dot(ray.d, ray.d);
    if (abs(denominator) <= std::numeric_limits<float>::epsilon()) {
        return(Intersection::failure());
    }
    float center_projection_distance = dot(ray.d, this->center - ray.o) / denominator;
    if (center_projection_distance > 0) {
        Point center_projection_point = ray.getPoint(center_projection_distance);
        float distance_center_to_point = (center_projection_point - this->center).length();
        if (distance_center_to_point > this->radius) {
            return(Intersection::failure());
        }
        else {
            float distance = center_projection_distance - (sqrt(pow(this->radius, 2) - (center_projection_point - this->center).lensqr())/ray.d.length());
            return(Intersection(distance, ray, this, (ray.getPoint(distance) - this->center).normalize(), ray.getPoint(distance)));
        }
    }
    return(Intersection::failure());
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    /* TODO */
    return(4 * pi * pow(radius, 2));
}

}
