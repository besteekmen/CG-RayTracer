#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>

namespace rt {

RGBColor::RGBColor(const Float4& f4)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
  return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
  return RGBColor(r - c.r, g - c.g, b - c.b);
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
  return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator == (const RGBColor& c) const {
  if(r == c.r && g == c.g && b == c.b)
    return true;
  else
    return false;
}

bool RGBColor::operator != (const RGBColor& b) const {
  return !((*this) == b);
}

RGBColor RGBColor::clamp() const {
  RGBColor clamped(r,g,b);
  float min = 0.0f;
  float max = 1.0f;

  if(r < min)
    clamped.r = min;
  else if(r > max)
    clamped.r = max;

  if(g < min)
    clamped.g = min;
  else if(g > max)
    clamped.g = max;

  if(b < min)
    clamped.b = min;
  else if(b > max)
    clamped.b = max;

  return clamped;
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
  return RGBColor(scalar * c.r, scalar * c.g, scalar * c.b);
}

RGBColor operator * (const RGBColor& c, float scalar) {
  return RGBColor(scalar * c.r, scalar * c.g, scalar * c.b);
}

RGBColor operator / (const RGBColor& c, float scalar) {
  assert(scalar != 0.0);
  scalar = 1.0 / scalar;
  return scalar * c;
}

}
