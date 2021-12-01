#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
  Intersection Nearest_Intersection;
  bool found = false;
  //for (int i = 0; i < this->Primitives.size(); i++)
  for(std::vector<Primitive *>::size_type i = 0; i != this->primitives.size(); i++) {
      Intersection intersection = primitives[i]->intersect(ray, previousBestDistance);
      float distance = intersection.distance;

      if (intersection && (distance < previousBestDistance) && (distance>epsilon)){
          previousBestDistance = distance;
          Nearest_Intersection = intersection;
          found = true;
      }
  }
  if (found)
      return Nearest_Intersection;
  else
      return Intersection::failure();
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
  this->primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
