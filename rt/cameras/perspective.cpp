#include <rt/cameras/perspective.h>
#include <math.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle) : center(center), forward(forward), up(up), verticalOpeningAngle(verticalOpeningAngle), horizontalOpeningAngle(horizontalOpeningAngle) {}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
  Vector d, spanX, spanY;
  x = x * tanf(horizontalOpeningAngle * 0.5f);
  y = y * tanf(verticalOpeningAngle * 0.5f);

  spanX = cross(forward, up).normalize();
  spanY = cross(spanX, forward).normalize();

  d = forward + x * spanX + y * spanY;
  d = d.normalize();
  return Ray(center, d);
}

}
