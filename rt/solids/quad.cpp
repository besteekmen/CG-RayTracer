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
    /* TODO */ 
    Vector normal = cross(span1, span2).normalize();
    float denominator = dot(normal, ray.d);
    if (abs(denominator) <= std::numeric_limits<float>::epsilon()) {
        return(Intersection::failure());
    }
    float distance = dot(normal, this->vertex - ray.o) / denominator;
    if (distance > 0) {
        Point point_on_plane = ray.getPoint(distance);
        float lam1, lam2;
        denominator = dot(this->span1, this->span2);
            if (abs(denominator) > std::numeric_limits<float>::epsilon()) {
                lam1 = dot((point_on_plane - this->vertex), this->span2) / denominator;
                lam2 = dot((point_on_plane - this->vertex), this->span1) / denominator;
                if (0 < lam1 && 0 < lam2 && lam1 < 1 && lam2 < 1) {
                    return(Intersection(distance, ray, this, normal, Point(1, lam1, lam2)));
                }
            }
            else {
                lam1 = dot((point_on_plane - this->vertex), this->span1) / (dot(span1, span1));
                lam2 = dot((point_on_plane - this->vertex), this->span2) / (dot(span2, span2));
                if (0 < lam1 && 0 < lam2 && lam1 < 1 && lam2 < 1) {
                    return(Intersection(distance, ray, this, normal, Point(1, lam1, lam2)));
                }
            }
    }
    return(Intersection::failure());

}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
    /* TODO */
    return(cross(span1, span2).length());
}

}
