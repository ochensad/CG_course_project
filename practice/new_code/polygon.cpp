#include "polygon.h"

Polygon::Polygon(QVector3D t1, QVector3D t2, QVector3D t3, QRgb cl)
{
    side_t1.setX(t1.x());
    side_t1.setY(t1.y());
    side_t1.setZ(t1.z());

    side_t2.setX(t2.x());
    side_t2.setY(t2.y());
    side_t2.setZ(t2.z());

    side_t3.setX(t3.x());
    side_t3.setY(t3.y());
    side_t3.setZ(t3.z());

    color = cl;
}

Polygon::Polygon()
{
    side_t1.setX(0);
    side_t1.setY(0);
    side_t1.setZ(0);

    side_t2.setX(0);
    side_t2.setY(0);
    side_t2.setZ(0);

    side_t3.setX(0);
    side_t3.setY(0);
    side_t3.setZ(0);
}
