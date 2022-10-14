#ifndef LIGHT_H
#define LIGHT_H

#include <QRgb>
#include <QMatrix4x4>

class Light
{
public:
    Light(QVector3D n_origin, QVector3D n_destination, QRgb n_color, double b);
    Light(Light &copy);
    void operator=(const Light& l) {this->origin = l.origin; this->destination = l.destination; this->color = l.color; this->view = l.view;}

    QVector3D GetView() {return view;};

    QVector3D GetOrigin() {return origin;};
    void SetOrigin(QVector3D n_origin) {this->origin = n_origin;};

    QVector3D GetDestination() {return destination;};
    QRgb GetColor() {return color;};
private:
    QVector3D view;
    QVector3D origin;
    QVector3D destination;
    QRgb color;
    double bright;
};

#endif // LIGHT_H

