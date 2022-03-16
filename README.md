## CG-RayTracer

[CG-RayTracer](https://github.com/besteekmen/CG-RayTracer "raytracer") is a ray tracing engine developed with C++. This project was created as a part of the practical exercises  for the [Introduction to Computer Graphics](https://graphics.cg.uni-saarland.de/courses/cg1-2021/index.html "class") 2021 class of Saarland University. This release includes the implementations for CG class requested in the Assignment 7.

### Build:
CMakeLists.txt is provided to allow using any build system. The respective assignment-xx.cmake lists 
all ﬁles that were added with a particular assignment. On Linux libpng-dev is required for the 
build and should be automatically detected.

By invoking: 
* mkdir build debug && cd build debug — create and enter a build directory for CMake
* cmake -DCMAKE BUILD TYPE=Debug .. — conﬁgure the project in debug mode
* cmake --build . —  compile the project, producing executable cgray

For release mode use cmake -DCMAKE BUILD TYPE=Release .. in a diﬀerent build release directory 
respectively. 
On Windows using Visual Studio you can generate a single multi-conﬁguration build directory.

### Development Platform:
* OS: Ubuntu 16.04 LTS
* Processor: Intel® Core™ i7-6700HQ CPU @ 2.60GHz × 3
* C++ version: C++ 17
* IDE: Atom

### Sample Images:
The rendered images are located in the images folder on this release as well as main directory of each release.

<table width="500" cellpadding="5">
   <tr>
    <td align="center" valign="center" width="25%">
      <img src="/images/a1.png" alt="" />
      <br />
      Image with julia set pattern
    </td>
    <td align="center" valign="center" width="25%">
      <img src="/images/a1-2.png" alt="" />
      <br />
      Perspective camera
    </td>
    <td align="center" valign="center" width="25%">
      <img src="/images/a1-3.png" alt=""/>
      <br />
      Perspective camera
    </td>
    <td align="center" valign="center" width="25%">
      <img src="/images/a1-4.png" alt=""/>
      <br />
      Orthographic camera
    </td>
  </tr>
  
  <tr>
    <td align="center" valign="center">
      <img src="/images/a2-2.png" alt="" />
      <br />
      Ray solid intersection
    </td>
    <td align="center" valign="center">
      <img src="/images/a2-2_quadric.png" alt="" />
      <br />
      Intersection for quadric
    </td>
    <td align="center" valign="center">
      <img src="/images/a3-sitting.png" alt="" />
      <br />
      BVH rendering
    </td>
    <td align="center" valign="center">
      <img src="/images/a4-1.png" alt="" />
      <br />
      Instancing with transformations 
    </td>
  </tr>

  <tr>
    <td align="center" valign="center">
      <img src="/images/a5-1.png" alt="" />
      <br />
      Colored point light
    </td>
    <td align="center" valign="center">
      <img src="/images/a5-3.png" alt="" />
      <br />
      Spot and directional lights
    </td>
    <td align="center" valign="center">
      <img src="/images/a5-1-proj.png" alt="" />
      <br />
      Projective light
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-1a.png" alt="" />
      <br />
      Lambertian materials
    </td>
  </tr>

  <tr>
    <td align="center" valign="center">
      <img src="/images/a6-1b.png" alt="" />
      <br />
      Phong material and mirror 
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-1d.png" alt="" />
      <br />
      Cook-torrance material
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-1c.png" alt="" />
      <br />
      Combined material
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-1e.png" alt="" />
      <br />
      Motion blur
    </td>
  </tr>

  <tr>
    <td align="center" valign="center">
      <img src="/images/a6-4c.png" alt="" />
      <br />
      Triangle texture mapping
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-4d.png" alt="" />
      <br />
      Cylindrical texture mapping
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-4e.png" alt="" />
      <br />
      Spherical texture mapping
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-8b.png" alt="" />
      <br />
      Smooth edges
    </td>
  </tr>

  <tr>
    <td align="center" valign="center">
      <img src="/images/a6-5.png" alt="" />
      <br />
      Area light source
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-6.png" alt="" />
      <br />
      Glass and fuzzy mirror material
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-7a.png" alt="" />
      <br />
      Depth of field
    </td>
    <td align="center" valign="center">
      <img src="/images/a6-7b.png" alt="" />
      <br />
      Supersampling 
    </td>
  </tr>

  <tr>
    <td align="center" valign="center">
      <img src="/images/abump-1a.png" alt="" />
      <br />
      Bump mapping nn
    </td>
    <td align="center" valign="center">
      <img src="/images/abump-1b.png" alt="" />
      <br />
      Bump mapping bilinear
    </td>
    <td align="center" valign="center">
      <img src="/images/abump-2.png" alt="" />
      <br />
      Bump mapping bilinear
    </td>
  </tr>
</table>

