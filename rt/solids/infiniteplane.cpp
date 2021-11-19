#include <rt/solids/infiniteplane.h>
#include<cmath>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material): Solid(texMapper, material)
{
    /* TODO */
    this->origin = origin;
    this->normal = normal;
}

BBox InfinitePlane::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    float denominator = dot(this->normal, ray.d);
    if (abs(denominator) <= std::numeric_limits<float>::epsilon()) {
        return(Intersection::failure());
    }
    float distance = dot(this->normal, this->origin - ray.o)/denominator;
    if (distance > 0 && distance<previousBestDistance) {
        return(Intersection(distance, ray, this, this->normal, ray.getPoint(distance)));
    }
    return(Intersection::failure());
    

}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
    return(FLT_MAX);
}

}
