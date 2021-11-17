#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
    /* TODO */
    Intersection best_intersection;
    for (int i = 0; i < this->primitives.size(); i++) {
        Intersection intersection = primitives[i]->intersect(ray, previousBestDistance);
        float distance = intersection.distance;
        if (intersection && distance<previousBestDistance && distance>0){
            previousBestDistance = distance;
            best_intersection = intersection;
        }
    }
    return(best_intersection);
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    /* TODO NOT_IMPLEMENTED;*/
    this->primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
