#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material): Solid(texMapper, material)
{
    /* TODO */
    this->corners[0] = corner1;
    this->corners[1] = corner2;
    this->normals[0] = Vector(1, 0, 0);
    this->normals[1] = Vector(-1, 0, 0);
    this->normals[2] = Vector(0, 1, 0);
    this->normals[3] = Vector(0, -1, 0);
    this->normals[4] = Vector(0, 0, 1);
    this->normals[5] = Vector(0, 0, -1);
    if (corners[0].x < corners[1].x) {
        this->normal_associated_point_index[0] = 1;
        this->normal_associated_point_index[1] = 0;
        max[0] = corners[1].x;
        min[0] = corners[0].x;
    }
    else {
        this->normal_associated_point_index[0] = 0;
        this->normal_associated_point_index[1] = 1;
        max[0] = corners[0].x;
        min[0] = corners[1].x;
    }
    if (corners[0].y < corners[1].y) {
        this->normal_associated_point_index[2] = 1;
        this->normal_associated_point_index[3] = 0;
        max[1] = corners[1].y;
        min[1] = corners[0].y;
    }
    else {
        this->normal_associated_point_index[2] = 0;
        this->normal_associated_point_index[3] = 1;
        max[1] = corners[0].y;
        min[1] = corners[1].y;
    }
    if (corners[0].z < corners[1].z) {
        this->normal_associated_point_index[4] = 1;
        this->normal_associated_point_index[5] = 0;
        max[2] = corners[1].z;
        min[2] = corners[0].z;
    }
    else {
        this->normal_associated_point_index[4] = 0;
        this->normal_associated_point_index[5] = 1;
        max[2] = corners[0].z;
        min[2] = corners[1].z;
    }
}

BBox AABox::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */
    Vector v = (corners[0] - corners[1]);
    return(2*(abs(v.x*v.y)+abs(v.y*v.z)+abs(v.z*v.x)));
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    float distance = 1000;
    int least_distance_index = -1;
    for (int i = 0; i < 6; i++) {
        float denominator = dot(ray.d, this->normals[i]);
        if (abs(denominator) <= std::numeric_limits<float>::epsilon()) {
            continue;
        }
        float dist = dot(corners[this->normal_associated_point_index[i]] - ray.o, this->normals[i])/denominator;
        if (dist>0 && dist < distance && dist<previousBestDistance) {
            Point pt_of_intersection = ray.getPoint(dist);
            bool flag = true;
            if (this->normals[i].x ==0) {
                if (pt_of_intersection.x > max[0] || pt_of_intersection.x < min[0]) {
                    flag = false;
                }
            }
            if (this->normals[i].y ==0) {
                if (pt_of_intersection.y > max[1] || pt_of_intersection.y < min[1]) {
                    flag = false;
                }
            }
            if (this->normals[i].z ==0) {
                if (pt_of_intersection.z > max[2] || pt_of_intersection.z < min[2]) {
                    flag = false;
                }
            }
            if (flag) {
                distance = dist;
                least_distance_index = i;
            }
        }
    }
    if (least_distance_index != -1 && distance > 0) {
        return(Intersection(distance, ray, this, this->normals[least_distance_index], ray.getPoint(distance)));
    }
    return(Intersection::failure());
}
}
