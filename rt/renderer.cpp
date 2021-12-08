#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <rt/cameras/orthographic.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/integrator.h>
#include <iostream>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
  for (uint y = 0; y < img.height(); ++y) {
      for (uint x = 0; x < img.width(); ++x) {
          float cameraX = (2.0f * float(x + 0.5f) / float(img.width()) - 1.f);
          float cameraY = 1.f - 2.0 * float(y + 0.5f) / float(img.height());
          Ray r = this->cam->getPrimaryRay(cameraX, cameraY);
          img(x, y) = this->integrator->getRadiance(r);
      }
  }
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
  for (uint y = 0; y < img.height(); ++y)
      for (uint x = 0; x < img.width(); ++x)
          img(x, y) = a1computeColor(x, y, img.width(), img.height());
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
  float ImageAspectRatio = img.width()/img.height();

  for (uint y = 0; y < img.height(); ++y) {
      for (uint x = 0; x < img.width(); ++x) {
          float cameraX = (2.0f * float(x + 0.5f) / float(img.width()) - 1.f);
          float cameraY = 1.f - 2.0 * float(y + 0.5f) / float(img.height());
          Ray r = this->cam->getPrimaryRay(cameraX, cameraY);
          img(x, y) = a2computeColor(r);
      }
  }
}

}
