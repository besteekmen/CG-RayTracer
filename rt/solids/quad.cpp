#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material): Solid(texMapper, material)
{
    /* TODO */
    this->vertex = origin;
    this->span1 = span1;
    this->span2 = span2;
}

BBox Quad::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
    /* TODO */
    return(cross(span1, span2).length());
}

}
