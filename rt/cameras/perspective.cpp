#include <rt/cameras/perspective.h>
#include <math.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->x_basis = cross(forward, up);
    this->y_basis = cross(this->x_basis, forward);
    this->x_basis = this->x_basis * forward.length() * tan(horizontalOpeningAngle / 2) / this->x_basis.length();
    this->y_basis = this->y_basis * forward.length() * tan(verticalOpeningAngle / 2) / this->y_basis.length();
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO NOT_IMPLEMENTED;*/
    return(Ray(this->center, (forward + x * this->x_basis + y * this->y_basis).normalize()));
}

}
