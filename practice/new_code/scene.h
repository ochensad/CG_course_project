#ifndef SCENE_H
#define SCENE_H

#include "model.h"

class Scene
{
public:
    Scene(Drawer* canv);
    Scene(int w, int h, int mode);
    QImage draw_scene_1(void);
    QImage draw_scene_2(void);
    QImage draw_scene_3(void);
private:
    Model* model;
    Drawer* canvas;
    int width;
    int height;
    int mode = 0;
};

#endif // SCENE_H
