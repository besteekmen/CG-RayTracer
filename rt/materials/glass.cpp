#include <rt/materials/glass.h>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
{
    this->eta = eta;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return(RGBColor::rep(0.0f));
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return(RGBColor::rep(0.0f));
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return(SampleReflectance(Vector::rep(0.0f), RGBColor::rep(0.0f)));
}

Material::Sampling GlassMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}