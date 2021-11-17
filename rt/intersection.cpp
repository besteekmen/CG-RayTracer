#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
    /* TODO */
    this->distance = distance;
    this->ray = ray;
    this->solid = solid;
    this->normal_vector = normal;
    this->local_hit_Point = local;
    this->isNull = false;
}

Intersection::operator bool() const {
    /* TODO */
    if (this->isNull) {
        return(false);
    }
    return(true);
}

Intersection Intersection::failure() {
    /* TODO */
    return(Intersection());
}

Point Intersection::hitPoint() const {
    /* TODO */
    return(this->ray.getPoint(this->distance));
}

Vector Intersection::normal() const {
    /* TODO */
    return(this->normal_vector);
}

Point Intersection::local() const {
    /* TODO */
    return(this->local_hit_Point);
}

}
