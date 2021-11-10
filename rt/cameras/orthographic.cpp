#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY) : center(center), forward(forward), up(up), scaleX(scaleX), scaleY(scaleY) {}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
  Vector d, spanX, spanY;
  x = x * scaleX * 0.5f;
  y = y * scaleY * 0.5f;

  spanX = cross(forward, up).normalize();
  spanY = cross(spanX, forward).normalize();

  // Generate direction through pixel center
  Point rayPoint  = center + x * spanX + y * spanY;
  Ray primaryRay(rayPoint, forward);
  return primaryRay;
}

}
