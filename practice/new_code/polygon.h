#ifndef POLYGON_H
#define POLYGON_H

#include <QVector3D>
#include <QRgb>
#include <normal.h>

class Polygon
{
public:
    Polygon();
    Polygon(QVector3D t1, QVector3D t2, QVector3D t3, QRgb cl);
    void Set_t1(QVector3D t1) {side_t1 = t1; };
    void Set_t2(QVector3D t2) {side_t2 = t2; };
    void Set_t3(QVector3D t3) {side_t3 = t3; };
    void Set_color(QRgb cl) {color = cl; };

    QVector3D Get_t1(void) {return side_t1; };
    QVector3D Get_t2(void) {return side_t2; };
    QVector3D Get_t3(void) {return side_t3; };
    QRgb Get_color(void) {return color; };

    Normal GetNorm_t1(void) {return t1_n;}
    Normal GetNorm_t2(void) {return t2_n;}
    Normal GetNorm_t3(void) {return t3_n;}

    void SetNorm_t1(QVector3D n){t1_n = n;}
    void SetNorm_t2(QVector3D n){t2_n = n;}
    void SetNorm_t3(QVector3D n){t3_n = n;}
private:
    QVector3D side_t1;
    QVector3D side_t2;
    QVector3D side_t3;
    QRgb color;
    Normal t1_n;
    Normal t2_n;
    Normal t3_n;
};

#endif // POLYGON_H
