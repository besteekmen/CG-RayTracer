#include <rt/integrators/castingdist.h>
#include <rt/world.h>
#include <cmath>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    /* TODO */
    this->world = world;
    this->nearColor = nearColor;
    this->farColor = farColor;
    this->nearDist = nearDist;
    this->farDist = farDist;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    Intersection intersect = this->world->scene->intersect(ray, FLT_MAX);
    if (intersect) {
        float cosine_value = -dot(intersect.normal(), ray.d)/(intersect.normal().length()*ray.d.length());
        RGBColor final_color = this->nearColor + ((intersect.distance - nearDist) / (this->farDist - this->nearDist))*(this->farColor - this->nearColor);
        return(final_color*cosine_value);
    }
    return(RGBColor(0.0f, 0.0f, 0.0f));
}

}
