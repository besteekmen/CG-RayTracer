#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    //this->x_basis = cross(forward, up).normalize();
    //this->y_basis = cross(this->x_basis, forward).normalize();
    //this->x_basis = scaleX * this->x_basis;
    //this->y_basis = scaleY * this->y_basis;
    this->x_basis = cross(forward, up);
    this->y_basis = cross(this->x_basis, forward);
    this->x_basis = (scaleX/(2*this->x_basis.length())) * this->x_basis;
    this->y_basis = (scaleY/(2*this->y_basis.length())) * this->y_basis;
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    /* TODO NOT_IMPLEMENTED;*/
    return(Ray(this->center + x * this->x_basis + y * this->y_basis, this->forward.normalize()));
}

}
