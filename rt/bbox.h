#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>
#include <cmath>

namespace rt {

class Ray;

class BBox {
public:
    Point min, max;

    BBox() {/*this->isEmpty = true;*/}
    BBox(const Point& min, const Point& max)
    {
      this->min = rt::min(min, max);
      this->max = rt::max(min, max);
      this->isEmpty = false;
    }

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const {
      return max-min;
    }

    float area() const {
      float x = fabs(min.x - max.x);
      float y = fabs(min.y - max.y);
      float z = fabs(min.z - max.z);
      return 2 * (x*y + y*z + z*x);
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound() const;
    Point centroid() const;
    int largestAxis() const;
    bool isEmpty;
};

}

#endif
