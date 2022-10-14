#include "light.h"

Light::Light(QVector3D n_origin, QVector3D n_destination, QRgb n_color, double b)
{
    this->origin = n_origin;
    this->destination = n_destination;
    this->color = n_color;
    this->bright = b;

    this->view = this->origin - this->destination;
}

Light::Light(Light &copy)
{
    this->origin = copy.GetOrigin();
    this->destination = copy.GetDestination();
    this->bright = copy.bright;

    this->view = this->origin - this->destination;
}
