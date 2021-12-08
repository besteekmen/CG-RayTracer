### Introduction to Computer Graphics - Assignment 3 Release

This release includes the implementations for CG class requested in the Assignment 3.

#### Students:

* Rahul Nittala (7015773)
* Beste Ekmen   (2572855)
           
#### Development Platform:

* OS: Ubuntu 16.04 LTS
* Processor: Intel® Core™ i7-6700HQ CPU @ 2.60GHz × 3
* C++ version: C++ 17 
* IDE: Atom

#### Features:
We have implemented all mandatory and bonus features requested in this assignment.
Mandatory Features: All
BONUS features: SAH (The implementation is in bvh.cpp and bvh.h, can be activated with setting the 'isSAH' in bvh.h true. It is binning SAH) (All)

***Note:*** The showcase images for mandatory and bonus features are uploaded in the main directory and to the release. Current version renders the same scene requested in the assignment. To get the scenes in the other images, the commented out parts should be used in a_indexing.cpp and cmake file with new models. However, due to the size, we were not able to upload the object file for 'sitting' image. We have explained the additional images and rendering durations below in 'Tests' section.

#### Theoretical:
We have submitted the theoretical part on MS Teams, we solved all the theoretical questions.

#### Tests:

We have generated 2 additional images with various low poly and high poly objects and compared the rendering times of both techniques. The images are rendered in the machine described above. The last one on the table (a3-1) shows the duration for the original scene with the cow and spheres.

* a3-sitting.pgm - This picture has a high poly object which is the obj output from blender file with two objects, a woman and a couch. 
* a3-lowpoly.pgm - This picture has three low poly objects separately exported from blender and added to scene, a plant, a deer and a cat.

| File | Faces | Middle-split | SAH |
| -------- | -------- | -------- | -------- |
| a3-sitting | 2097211 | 1.21 min | 2.30 min |
| a3-lowpoly | 4187 | 15 sn | 14 sn |
| a3-1 | 34824 | 7 sn | 10 sn |

#### References:
* a3-sitting: woman - https://free3d.com/tr/3d-model/091_aya-3dsmax-2020-189298.html
* a3-sitting: couch - https://free3d.com/tr/3d-model/couch-sofa-742041.html
* a3-lowpoly: cat - https://free3d.com/tr/3d-model/low-poly-cat-46138.html
* a3-lowpoly: deer - https://free3d.com/tr/3d-model/low-poly-deer-72513.html
* a3-lowpoly: plant - https://free3d.com/tr/3d-model/house-plant-01-60848.html