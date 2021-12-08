#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    this->archetype = content;
}

Primitive* Instance::content() {
    /* TODO */
    return(archetype);
}

void Instance::reset() {
    /* TODO */
    transform = Matrix::identity();
}

void Instance::translate(const Vector& t) {
    /* TODO */
    // Equivalent to [[I t],[0 1]] * transform.
    transform[0][3] = transform[0][3] + t.x;
    transform[1][3] = transform[1][3] + t.y;
    transform[2][3] = transform[2][3] + t.z;
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    /* TODO */
    Vector s;
    if (nnaxis.x < nnaxis.y && nnaxis.x < nnaxis.z) {
        s = Vector(0, -nnaxis.z, nnaxis.y).normalize();
    }
    else if (nnaxis.y < nnaxis.x && nnaxis.y < nnaxis.z) {
        s = Vector(-nnaxis.z, 0, nnaxis.x).normalize();
    }
    else {
        s = Vector(-nnaxis.y, nnaxis.x, 0).normalize();
    }
    Vector t = cross(nnaxis, s).normalize();
    //Matrix M_T = Matrix(Float4(nnaxis), Float4(s), Float4(t), Float4(0, 0, 0, 1));
    Matrix M = Matrix::system(nnaxis.normalize(), s, t);
    Matrix Rotate = Matrix::identity();
    Rotate[1][1] = cos(angle);
    Rotate[1][2] = -sin(angle);
    Rotate[2][1] = sin(angle);
    Rotate[2][2] = cos(angle);
    transform = product(M, product(Rotate, product(M.transpose(), transform)));
}

void Instance::scale(float f) {
    /* TODO */
    // Equivalent to [[sI 0][0 1]] * transform.
    transform[0] = f * transform[0];
    transform[1] = f * transform[1];
    transform[2] = f * transform[2];
}

void Instance::scale(const Vector& s) {
    /* TODO */
    // Equivalent to [[sI 0][0 1]] * transform.
    transform[0] = s.x * transform[0];
    transform[1] = s.y * transform[1];
    transform[2] = s.z * transform[2];
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    Matrix transform_inverse = transform.invert();
    Ray new_ray = Ray(transform_inverse * ray.o, transform_inverse * ray.d);
    Intersection hit = archetype->intersect(new_ray, previousBestDistance);
    if (hit) {
        return(Intersection(hit.distance, ray, hit.solid, (transform_inverse.transpose() * (hit.normalV)).normalize(), ray.getPoint(hit.distance)));
    }
    return Intersection::failure();
}

BBox Instance::getBounds() const {
    /* TODO */
    BBox b = archetype->getBounds();
    Point corners[8];
    corners[0] = Point(b.min.x, b.min.y, b.min.z);
    corners[1] = Point(b.min.x, b.min.y, b.max.z);
    corners[2] = Point(b.min.x, b.max.y, b.min.z);
    corners[3] = Point(b.min.x, b.max.y, b.max.z);
    corners[4] = Point(b.max.x, b.min.y, b.min.z);
    corners[5] = Point(b.max.x, b.min.y, b.max.z);
    corners[6] = Point(b.max.x, b.max.y, b.min.z);
    corners[7] = Point(b.max.x, b.max.y, b.max.z);
    BBox bbox = BBox::empty();
    for (uint16_t i = 0; i < 8; i++) {
        bbox.extend(transform * corners[i]);
    }
    return bbox;
}

}