#include <rt/integrators/raytrace.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    Intersection intersect = world->scene->intersect(ray);

    Vector outDir = -ray.d.normalize();
    RGBColor color = RGBColor::rep(0.0f);

    if (intersect){
        for(std::vector<Primitive *>::size_type i = 0; i != world->light.size(); i++){
            LightHit hit = world->light[i]->getLightHit(intersect.hitPoint());

            Vector inDir = hit.direction.normalize();
						Ray shadowRay (intersect.hitPoint(), inDir);

						// shadow ray and the primary ray leave the surface on the same side
            float cosIn = dot(inDir, intersect.normal().normalize());
            float cosOut = dot(-ray.d, intersect.normal().normalize());

						if ((cosIn < 0 && cosOut > 0) || (cosIn > 0 && cosOut < 0))
			                continue; // if opposite direction ---> ignore source

						// offset to avoid acne problem
						Intersection obstacleIntersec = world->scene->intersect(shadowRay, hit.distance - epsilon);

						if (obstacleIntersec)
			                continue; // if an obstacle ---> ignore source

            RGBColor intensity = world->light[i]->getIntensity(hit);

            RGBColor reflectance = intersect.solid->material->getReflectance(intersect.local(), intersect.normal(), outDir, -inDir);

            RGBColor irradiance = intensity * reflectance;
						color = color + irradiance;

        }
        RGBColor emitted = Intersec.solid->material->getEmission(intersect.local(), intersect.normal(), outDir);
        return color + emitted;

    }
}

}
