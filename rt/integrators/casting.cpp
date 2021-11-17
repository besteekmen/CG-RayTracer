#include <rt/integrators/casting.h>
#include <rt/world.h>
#include<cmath>

namespace rt {

    RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
        /* TODO */
        Intersection intersect = this->world->scene->intersect(ray, FLT_MAX);
        if (intersect) {
            float grey_color = -dot(intersect.normal(), ray.d) / (intersect.normal().length() * ray.d.length());
            return(RGBColor(grey_color, grey_color, grey_color));
        }
        return(RGBColor(0.0f, 0.0f, 0.0f));
    }
}