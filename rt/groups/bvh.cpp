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

float BVH::split(int axisIndex, BVHNode* node, bool isSAH) {
  // find the middle of the longest axis with axisIndex
  if (isSAH) {
    return findSAHSplit(axisIndex, node, 16);
  } else {
    return node->getBounds().centroid().getAxis(axisIndex);
  }
}

float BVH::findSAHSplit(int axisIndex, BVHNode* parent, int binNum) {
  float bins[binNum], bins_n[binNum];

  for (int i = 0; i < binNum; i++) {
    bins[i] = 0; bins_n[i] = 0;
	}
	float mid, primMid; int num;
  float axisLength = parent->bbox.max.getAxis(axisIndex) - parent->bbox.min.getAxis(axisIndex);

  // implement binning SAH since it is faster then sweep SAH
  for (int i = 0; i < parent->primitives.size(); i++) {
    BBox pbox = parent->primitives[i]->getBounds();
    mid = pbox.centroid().getAxis(axisIndex);
    primMid = parent->bbox.min.getAxis(axisIndex);
    num = roundf((mid - primMid) / axisLength * (binNum - 1));

		bins[num] += parent->primitives[i]->getBounds().area();
		bins_n[num] ++;
	}

  // compute cost for SAH
	float SA_L = 0, N_L = 0, cbest = FLT_MAX, cleft, cright, sah_split;
	for (int i = 1; i <= binNum; i++) {
		SA_L = 0;
		N_L = 0;
		for (int j = 0; j < i; j++) {
      SA_L = SA_L + bins[j];
      N_L = N_L + bins_n[j];
    }

		cleft = SA_L / parent->area * N_L;
		cright = (parent->area - SA_L) / parent->area * (parent->primitives.size() - N_L);
		if ((cleft + cright) < cbest) {
      sah_split = i; cbest = cleft + cright;
    }
	}

  return parent->bbox.min.getAxis(axisIndex) + ((sah_split/binNum) * axisLength);
}

void BVH::buildRecursive(BVHNode* node) {
  Primitive* primitive;
  float splitLength, primSplitLength;
  int axisIndex;
  bool isSAH = false;

  int size = node->primitives.size();

  if (size <= 0)
    return;

  else {
    //node->bbox = BBox::empty();

    //for (int i=0; i<size; i++)
    //  node->bbox.extend(node->primitives[i]->getBounds());

    if (size < 3) {
      node->isLeaf = true;
      return;
    }

    if (size >= 3) {
      node->isLeaf = false;
      node->left = new BVHNode();
      node->right = new BVHNode();

      axisIndex = node->bbox.largestAxis();
      splitLength = split(axisIndex, node, isSAH);

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
