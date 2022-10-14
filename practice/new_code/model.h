#ifndef MODEL_H
#define MODEL_H

#include "surface.h"
#include "light.h"
#include "drawer.h"

class Model
{
public:
    Model();
    ~Model();
    QImage draw(Drawer *canv);
    void addSurface(Surface s);
    void setLight(Light &l) {*light =l;}
    void angleShadowSearch(QVector3D v, QVector3D l, QMatrix4x4 &m);
    void sort(void);
    void Normalise(void);
    std::vector<Surface> getComponents(void) {return model_components;}
    QImage get_image(int w, int h);
private:
    std::vector<Surface> model_components;
    Light *light;
    QRgb *color_buf = nullptr;
};

#endif // MODEL_H
