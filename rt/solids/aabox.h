#ifndef CG1RAYTRACER_SOLIDS_BOX_HEADER
#define CG1RAYTRACER_SOLIDS_BOX_HEADER

#include <rt/solids/solid.h>

namespace rt {

class AABox : public Solid {
public:
    Point corners[2];
    uint normal_associated_point_index[6];
    float max[3], min[3];
    Vector normals[6];
    AABox() {}
    AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
};

}

#endif