#ifndef SURFACE_H
#define SURFACE_H

#include <memory>
#include "polygon.h"
#include "normal.h"

class Surface
{
public:
    Surface() {};
    Surface(Polygon polygon);

    void SetPolygon(Polygon polygon);
    Polygon GetPolygon(void) {return this->polygon; };

    void SetNormal(Normal norm) {n_vect = norm; };
    void SetAutoNormal(void);
    Normal GetNormal(void) {return n_vect;};

    double Get_A_coef(void) {return A_coef; };
    double Get_B_coef(void) {return B_coef; };
    double Get_C_coef(void) {return C_coef; };
    double Get_D_coef(void) {return D_coef; };
private:
    Polygon polygon;
    double A_coef;
    double B_coef;
    double C_coef;
    double D_coef;
    Normal n_vect;
};

#endif // SURFACE_H
