#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <rt/cameras/camera.h>
#include <iostream>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
    /* TODO */ NOT_IMPLEMENTED;
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
  int resx = img.width();
  int resy = img.height();
  int prcx, prcy;

  // For given image resolution {resx, resy}
  // Loop over pixel raster coordinates [0, res-1]
  // Assign the a1computeColor
  for(prcx = 0; prcx < resx; prcx++) {
    for(prcy = 0; prcy < resy; prcy++) {
      img(prcx, prcy) = a1computeColor(prcx, prcy, resx, resy);
    }
  }
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
  int resx = img.width();
  int resy = img.height();
  int prcx, prcy;
  float ndcx, ndcy, sscx, sscy;
  Ray ray;

  // For given image resolution {resx, resy}
  // Loop over pixel raster coordinates [0, res-1]
  for(prcx = 0; prcx < resx; prcx++){
    for(prcy = 0; prcy < resy; prcy++){
        // Normalized device coordinates [0, 1]
        ndcx = (prcx + 0.5f) / resx;
        ndcy = (prcy + 0.5f) / resy;
        // Screen space coordinates [-1, 1]
        sscx = ndcx * 2.0f - 1;
        sscy = ndcy * 2.0f - 1;
        ray = this->cam->getPrimaryRay(sscx, -sscy);
        img(prcx, prcy) = a2computeColor(ray);
      }
  }
}

}
