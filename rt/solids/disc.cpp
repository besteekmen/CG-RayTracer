#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material): Solid(texMapper, material)
{
    /* TODO */
    this->center = center;
    this->radius = radius;
    this->normal = normal;
}

BBox Disc::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    float denominator = dot(this->normal, ray.d);
    if (abs(denominator) <= std::numeric_limits<float>::epsilon()) {
        return(Intersection::failure());
    }
    float distance = dot(this->normal, this->center - ray.o) / denominator;
    if (distance > 0 && distance<previousBestDistance) {
        float distance_center_to_point = (ray.getPoint(distance) - this->center).length();
        if (distance_center_to_point > this->radius) {
            return(Intersection::failure());
        }
        return(Intersection(distance, ray, this, this->normal, ray.getPoint(distance)));
    }
    return(Intersection::failure());

}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
    /* TODO */
    return(pi * pow(this->radius, 2));
}

}
