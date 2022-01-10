#include <rt/materials/combine.h>

namespace rt {

CombineMaterial::CombineMaterial()
{
    /* TODO */
}

void CombineMaterial::add(Material* m, float w) {
    /* TODO */
    materials.push_back(m);
    weights.push_back(w);
    Material::Sampling s = m->useSampling();
    if (s != Material::Sampling::SAMPLING_NOT_NEEDED) {
        sample_index = weights.size() - 1;
    }
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    RGBColor reflectance = RGBColor::rep(0.0f);
    for (int i = 0; i < weights.size(); i++) {
        if (i == sample_index) {
            continue;
        }
        reflectance = reflectance + weights[i] * materials[i]->getReflectance(texPoint, normal, outDir, inDir);
    }
    return reflectance;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    RGBColor emission = RGBColor::rep(0.0f);
    for (int i = 0; i < weights.size(); i++) {
        emission = emission + weights[i] * materials[i]->getEmission(texPoint, normal, outDir);
    }
    return emission;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    if (sample_index == -1) {
        UNREACHABLE;
    }
    Material::SampleReflectance s;
    s.direction = (-outDir + 2 * dot(outDir, normal) * normal).normalize();
    s.reflectance = weights[sample_index] * materials[sample_index]->getReflectance(texPoint, normal, outDir, s.direction);
    return(s);
}

Material::Sampling CombineMaterial::useSampling() const {
    /* TODO */
    // When all materials don't need sampling
    if (sample_index == -1) {
        return(Material::Sampling::SAMPLING_NOT_NEEDED);
    }
    //When there is only one material and it needs sampling
    else if (weights.size() == 1) {
        return(Material::Sampling::SAMPLING_ALL);
    }
    //Otherwise, the hybrid case
    return(Material::Sampling::SAMPLING_SECONDARY);
}

}