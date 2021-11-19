#include <rt/cameras/perspective.h>
#include <math.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    this->center = center;
  	this->forward = forward;
  	this->up = up;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;

    this->scaleX = tan(this->horizontalOpeningAngle/2.0f);
    this->scaleY = tan(this->verticalOpeningAngle/2.0f);

    this->CamZAxis = this->forward.normalize();
    this->CamXAxis = cross(this->forward, this->up.normalize()).normalize();
    this->CamYAxis = cross(this->CamXAxis, this->CamZAxis).normalize();

}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
		Vector dir = (x * CamXAxis * scaleX + y * CamYAxis * scaleY +  CamZAxis).normalize();
		return Ray(center, dir);

}

}
