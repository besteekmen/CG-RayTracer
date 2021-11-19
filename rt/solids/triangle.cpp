#include <rt/solids/triangle.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material): Solid(texMapper, material)
{
    /* TODO */
    for (int i = 0; i < 3; i++) {
        this->vertices[i] = vertices[i];
    }
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->vertices[0] = v1;
    this->vertices[1] = v2;
    this->vertices[2] = v3;
}

BBox Triangle::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    Vector n_12, n_23, n_31;
    n_12 = cross((vertices[0] - ray.o), (vertices[1] - ray.o));
    n_23 = cross((vertices[1] - ray.o), (vertices[2] - ray.o));
    n_31 = cross((vertices[2] - ray.o), (vertices[0] - ray.o));
    float lam_star_1, lam_star_2, lam_star_3;
    lam_star_3 = dot(n_12, ray.d);
    lam_star_1 = dot(n_23, ray.d);
    lam_star_2 = dot(n_31, ray.d);
    float lamdas[3];
    lamdas[0] = lam_star_1 / (lam_star_1 + lam_star_2 + lam_star_3);
    lamdas[1] = lam_star_2 / (lam_star_1 + lam_star_2 + lam_star_3);
    lamdas[2] = lam_star_3 / (lam_star_1 + lam_star_2 + lam_star_3);
    if (lamdas[0] > 0 && lamdas[1] > 0 && lamdas[2] > 0) {
        Vector resultant_direction = lamdas[0] * (vertices[0] - ray.o) + lamdas[1] * (vertices[1] - ray.o) + lamdas[2] * (vertices[2] - ray.o);
        float distance = resultant_direction.length() / ray.d.length();
        Vector normal = cross(vertices[2] - vertices[1], vertices[0] - vertices[1]).normalize();
        /*if (dot(normal, ray.d) > 0) {
            normal = -normal;
        }*/
        if (distance < previousBestDistance) {
            return(Intersection(distance, ray, this, normal, Point(lamdas[0], lamdas[1], lamdas[2])));
        }
        
    }
    return(Intersection::failure());

}

Solid::Sample Triangle::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Triangle::getArea() const {
    /* TODO */
    return((cross(vertices[2] - vertices[1], vertices[0] - vertices[1])).length()/2);
}

}