#include <rt/groups/bvh.h>
#include <tuple>
#include <string.h>

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

float BVH::split(int axisIndex, BVHNode* node) {
  // find the middle of the longest axis with axisIndex
  if (isSAH) {
    return findSAHSplit(axisIndex, node);
  } else {
    return node->getBounds().centroid().getAxis(axisIndex);
  }
}

float BVH::findSAHSplit(int axisIndex, BVHNode* node) {
  // set elements of arrays to 0 for new node
  memset(bins, 0, sizeof(bins));
  memset(binsNum, 0, sizeof(binsNum));

	float mid, primMid; int num;
  float axisLength = node->bbox.max.getAxis(axisIndex) - node->bbox.min.getAxis(axisIndex);

  // implement binning SAH since it is faster then sweep SAH
  for(std::vector<Primitive *>::size_type i = 0; i != node->primitives.size(); i++) {
    BBox primBBox = node->primitives[i]->getBounds();
    primMid = primBBox.centroid().getAxis(axisIndex);
    mid = node->bbox.min.getAxis(axisIndex);
    num = roundf((primMid - mid) / axisLength * (binNum - 1));

		bins[num] += node->primitives[i]->getBounds().area();
		binsNum[num] ++;
	}

  // compute cost for SAH
	float leftSA = 0, leftNum = 0, cBest = FLT_MAX, cLeft, cRight, splitIndex;
	for (int i = 1; i <= binNum; i++) {
		leftSA = 0;
		leftNum = 0;
		for (int j = 0; j < i; j++) {
      leftSA = leftSA + bins[j];
      leftNum = leftNum + binsNum[j];
    }

		cLeft = leftSA / node->area * leftNum;
		cRight = (node->area - leftSA) / node->area * (node->primitives.size() - leftNum);
		if ((cLeft + cRight) < cBest) {
      splitIndex = i; cBest = cLeft + cRight;
    }
	}

  return node->bbox.min.getAxis(axisIndex) + ((splitIndex/binNum) * axisLength);
}

void BVH::buildRecursive(BVHNode* node) {
  Primitive* primitive;
  float splitLength;
  int axisIndex;

  int size = node->primitives.size();

  if (size <= 0)
    return;

  else {
    if (size < 3) {
      node->isLeaf = true;
      return;
    }

    if (size >= 3) {
      node->isLeaf = false;
      node->left = new BVHNode();
      node->right = new BVHNode();

      axisIndex = node->bbox.largestAxis();
      splitLength = split(axisIndex, node);

      for (int i=0; i<size; i++) {
        primitive = node->primitives[i];

        if (primitive->getBounds().centroid().getAxis(axisIndex) <= splitLength)
          node->left->add(primitive);
        else
          node->right->add(primitive);
      }

      if (node->left->primitives.size() == 0) {
        node->left->add(node->right->primitives[0]);
        // need to update area as well
        node->right->primitives.erase(node->right->primitives.begin());
      }

      else if (node->right->primitives.size() == 0) {
        node->right->add(node->left->primitives[0]);
        // need to update area as well
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
