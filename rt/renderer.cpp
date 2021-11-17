#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <rt/integrators/integrator.h>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
    /* TODO */
    uint width, height;
    width = img.width();
    height = img.height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < height; j++) {
            float pix_x = (2 * (i + 0.5) / width) - 1;
            float pix_y = (2 * (j + 0.5) / height) - 1;
            img(i,j) = this->integrator->getRadiance(cam->getPrimaryRay(pix_x, -pix_y));
        }
    }
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
    /* TODO NOT_IMPLEMENTED;*/
    uint width, height;
    width = img.width();
    height = img.height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < height; j++) {
            img(i, j) = a1computeColor(i, j, width, height);
        }
    }
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
    /* TODO NOT_IMPLEMENTED;*/
    uint width, height;
    width = img.width();
    height = img.height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < height; j++) {
            float pix_x = (2 * (i + 0.5) / width) - 1;
            float pix_y = (2 * (j + 0.5) / height) - 1;
            img(i, j) = a2computeColor(cam->getPrimaryRay(pix_x, -pix_y));
        }
    }
}

}
