#include <rt/textures/checkerboard.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
{
    /* TODO */
    this->white = white;
    this->black = black;
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
    /* TODO */
    int lu = floor(coord.x / 0.5);
    int lv = floor(coord.y / 0.5);
    int lw = floor(coord.z / 0.5);
    int parity = lu + lv + lw;
    if (parity % 2 == 0) {
        return(white);
    }
    return black;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}