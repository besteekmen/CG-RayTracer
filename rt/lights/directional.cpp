#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
{
    this->dir = direction;
    this->color = color;
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    LightHit hit;
    hit.direction = -this->dir;
    hit.normal = this->dir;
    hit.distance = FLT_MAX;
    return hit;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    return this->color;
}

}
