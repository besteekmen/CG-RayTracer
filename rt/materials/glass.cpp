#include <rt/materials/glass.h>
#include <core/random.h>

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
    float cos_theta_t = dot(normal, outDir);
    float eta_ratio = eta;
    Vector normal_hit = normal;
    if (cos_theta_t > 0) {
        eta_ratio = 1 / eta;
    }
    else {
        cos_theta_t = -cos_theta_t;
        normal_hit = -normal;
    }
    float sin_theta_i = eta_ratio * sqrt(1 - pow(cos_theta_t, 2));
    //Total internal reflection
    Vector refl_dir = (-outDir + 2 * dot(outDir, normal_hit) * normal_hit).normalize();
    if (sin_theta_i > 1) {
        return(Material::SampleReflectance(refl_dir, RGBColor::rep(1.0f)));
    }
    float cos_theta_i = sqrt(1 - pow(eta_ratio, 2) * (1 - pow(cos_theta_t, 2)));
    float r_pll = (eta_ratio * cos_theta_i - cos_theta_t) / (eta_ratio * cos_theta_i + cos_theta_t);
    float r_ppdlr = (cos_theta_i - eta_ratio * cos_theta_t) / (cos_theta_i + eta_ratio * cos_theta_t);
    float fr = (r_pll * r_pll + r_ppdlr * r_ppdlr) / 2;
    //reflection is sampled
    if (random() < fr) {
        return(Material::SampleReflectance(refl_dir, RGBColor::rep(1.0f)));
    }
    //refraction is sampled
    else {
        Vector refr_dir = (eta_ratio * cos_theta_t - cos_theta_i) * normal_hit - eta_ratio * outDir;
        return(Material::SampleReflectance(refr_dir.normalize(), RGBColor::rep(1.0f)));
    }
}

Material::Sampling GlassMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}