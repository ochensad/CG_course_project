#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "light.h"
#include "surface.h"

class ZBuffer
{
public:
    ZBuffer(int n_width, int n_height);
    ~ZBuffer();
    int getWidth() { return width; }
    int getHeight() { return height; }
    void setPixmap(QRgb* n_pixmap);
    void setLight(Light* n_light) { light = n_light; }
    void setShadowBuffer(float *buf) {shadowBuffer = buf;}
    QRgb* getPixmap() { return pixmap; }

    float *getShadows(std::vector<Surface> *model);
    void fillBufferWithShadows(std::vector<Surface> *model, QMatrix4x4 orig_proj);
private:
    int width;
    int height;
    float* buffer = nullptr;
    float* shadowBuffer = nullptr;
    QRgb* pixmap;
    Light* light;
};

#endif // ZBUFFER_H
