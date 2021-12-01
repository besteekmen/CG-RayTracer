#include <rt/groups/bvh.h>
#include <tuple>

namespace rt {

BVH::BVH()
{
  root = new BVHNode();
}

void BVH::rebuildIndex() {
  root->primitives = primitives;
  buildRecursive(root);
  return;
}

float BVH::splitMiddle(int axisIndex, BVHNode* node) {
  // find the middle of the longest axis with axisIndex
  return node->bbox.centroid().getAxis(axisIndex);
}

float BVH::splitSAH(int axisIndex, BVHNode* node) {
  // find the middle of the longest axis with axisIndex
  return node->bbox.centroid().getAxis(axisIndex);
}

void BVH::buildRecursive(BVHNode* node) {
  Primitive* primitive;
  float axisLength;
  int axisIndex;

  int size = node->primitives.size();

  if (size <= 0)
    return;

  else {
    node->bbox = BBox::empty();

    for (int i=0; i<size; i++)
      node->bbox.extend(node->primitives[i]->getBounds());

    if (size < 3) {
      node->isLeaf = true;
      return;
    }

    if (size >= 3) {
      node->isLeaf = false;
      node->left = new BVHNode();
      node->right = new BVHNode();

      axisIndex = node->bbox.largestAxis();
      axisLength = node->bbox.centroid().getAxis(axisIndex);
      // also for SAH

      for (int i=0; i<size; i++) {
        primitive = node->primitives[i];

        if (primitive->getBounds().centroid().getAxis(axisIndex) <= axisLength)
          node->left->primitives.push_back(primitive);
        else
          node->right->primitives.push_back(primitive);
      }

      if (node->left->primitives.size() == 0) {
        node->left->primitives.push_back(node->right->primitives[0]);
        node->right->primitives.erase(node->right->primitives.begin());
      }

      else if (node->right->primitives.size() == 0) {
        node->right->primitives.push_back(node->left->primitives[0]);
        node->left->primitives.erase(node->left->primitives.begin());
      }

      buildRecursive(node->left);
      buildRecursive(node->right);
      return;
    }
  }
}

BBox BVH::getBounds() const {
  BBox bbox = BBox::empty();
  for(std::vector<Primitive *>::size_type i = 0; i != primitives.size(); i++) {
    bbox.extend(primitives[i]->getBounds());
  }
  return bbox;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
  BVHNode* node = new BVHNode();
  Intersection nearest = Intersection::failure();
  Intersection current;
  std::vector<BVHNode*> nodes;
  float t0left, t1left, t0right, t1right;

  nodes.push_back(this->root);

  while (!nodes.empty()) {
      node = nodes.back();
      nodes.pop_back();

      if (node->isLeaf) {
          for (auto prim : node->primitives) {
              current = prim->intersect(ray, previousBestDistance);
              if (current) {
                  previousBestDistance = current.distance;
                  nearest = current;
              }
          }
      }
      else
      {
          BBox left = node->left->bbox;
          auto tleft = left.intersect(ray);
          if(tleft.first < tleft.second)
              nodes.push_back(node->left);

          BBox right = node->right->bbox;
          auto tright = right.intersect(ray);
          if(tright.first < tright.second)
              nodes.push_back(node->right);
      }
  }
  return nearest;
}

void BVH::add(Primitive* p) {
  primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::serialize(BVH::Output& output) {
    // To implement this function:
    // - Call output.setNodeCount() with the number of nodes in the BVH
    /* TODO */
    // - Set the root node index using output.setRootId()
    /* TODO */
    // - Write each and every one of the BVH nodes to the output using output.writeNode()
    /* TODO */ NOT_IMPLEMENTED;
}
void BVH::deserialize(BVH::Input& input) {
    // To implement this function:
    // - Allocate and initialize input.getNodeCount() nodes
    /* TODO */
    // - Fill your nodes with input.readNode(index)
    /* TODO */
    // - Use the node at index input.getRootId() as the root node
    /* TODO */ NOT_IMPLEMENTED;
}

}
