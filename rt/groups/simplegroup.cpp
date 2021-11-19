#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
  Intersection intersection = Intersection::failure();

  for(auto iter = primitives.begin(); iter != primitives.end(); ++iter) {
      if((*iter)->intersect(ray, previousBestDistance)){
          intersection = (*iter)->intersect(ray, previousBestDistance);
          previousBestDistance = intersection.distance;
      }
  }
  return intersection;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
