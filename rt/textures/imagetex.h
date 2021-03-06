#ifndef CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER
#define CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER

#include <core/image.h>
#include <rt/textures/texture.h>
#include <core/point.h>

namespace rt {

class ImageTexture : public Texture {
public:
    Image texture_img;
    enum BorderHandlingType {
        CLAMP,
        MIRROR,
        REPEAT
    };

    enum InterpolationType {
        NEAREST,
        BILINEAR
    };
    BorderHandlingType bht;
    InterpolationType it;
    int img_width, img_height;
    ImageTexture();
    ImageTexture(const Image& image, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR);
    ImageTexture(const std::string& filename, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR);
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord);
    virtual RGBColor getColorDY(const Point& coord);
};

}

#endif