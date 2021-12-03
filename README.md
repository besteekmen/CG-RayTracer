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

***Note:*** *The showcase images for mandatory and bonus features are uploaded in the main diretory and to release. Current version renders the same scene requested in the assignment. To get the scenes in the other images, the commented out parts should be used in a_indexing.cpp and cmake file with adding object files to models folder. We have explained the additional images and rendering durations below in 'Tests' section.

#### Theoretical:
We have submitted the theoretical part on MS Teams, we solved all the theoretical questions.

#### Tests:

We have generated 2 additional images with various low poly and high poly objects and compared the rendering times of both techniques. The images are rendered in the machine described above. The last one on the tale shows the duration for the original scene.

* a3-sitting.pgm - This picture has a high poly object which is the obj output from blender file with two objects, a woman and a couch. 
* a3-lowpoly.pgm - This picture has three low poly objects separately exported from blender and added to scene, a plant, a deer and a cat.

| File | Faces | Middle-split | SAH |
| -------- | -------- | -------- | -------- |
| a3-sitting | 2097211 | 1.21 min | 2.30 min |
| a3-lowpoly | 4187 | 15 sn | 14 sn |
| a1-cow | 34824 | 7 sn | 10 sn |