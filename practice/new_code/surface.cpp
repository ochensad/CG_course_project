#include "surface.h"

Surface::Surface(Polygon polygon)
{
    this->polygon = polygon;
    double y1 = polygon.Get_t1().y();
    double y2 = polygon.Get_t2().y();
    double y3 = polygon.Get_t3().y();

    double z1 = polygon.Get_t1().z();
    double z2 = polygon.Get_t2().z();
    double z3 = polygon.Get_t3().z();

    double x1 = polygon.Get_t1().x();
    double x2 = polygon.Get_t2().x();
    double x3 = polygon.Get_t3().x();

    A_coef = (y2-y1)*(z3-z1)-(y3-y1)*(z2-z1);
    B_coef = (z2-z1)*(x3-x1)-(z3-z1)*(x2-x1);
    C_coef = (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);

    D_coef = -x1 * Get_A_coef() - y1 * Get_B_coef() - z1 * Get_C_coef();
}

void Surface::SetPolygon(Polygon polygon)
{
    this->polygon = polygon;
    double y1 = polygon.Get_t1().y();
    double y2 = polygon.Get_t2().y();
    double y3 = polygon.Get_t3().y();

    double z1 = polygon.Get_t1().z();
    double z2 = polygon.Get_t2().z();
    double z3 = polygon.Get_t3().z();

    double x1 = polygon.Get_t1().x();
    double x2 = polygon.Get_t2().x();
    double x3 = polygon.Get_t3().x();

    A_coef = (y2-y1)*(z3-z1)-(y3-y1)*(z2-z1);
    B_coef = (z2-z1)*(x3-x1)-(z3-z1)*(x2-x1);
    C_coef = (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);

    D_coef = -x1 * Get_A_coef() - y1 * Get_B_coef() - z1 * Get_C_coef();
}

void Surface::SetAutoNormal()
{
    QVector3D v0 = QVector3D(this->GetPolygon().Get_t2().x() - this->GetPolygon().Get_t1().x(),
                                this->GetPolygon().Get_t2().y() - this->GetPolygon().Get_t1().y(),
                                 this->GetPolygon().Get_t2().z() - this->GetPolygon().Get_t1().z());
    QVector3D v1 = QVector3D(this->GetPolygon().Get_t3().x() - this->GetPolygon().Get_t2().x(),
                                this->GetPolygon().Get_t3().y() - this->GetPolygon().Get_t2().y(),
                                 this->GetPolygon().Get_t3().z() - this->GetPolygon().Get_t2().z());
    QVector3D res = QVector3D(v0.y()*v1.z() - v0.z()*v1.y(), v0.z()*v1.x() - v0.x()*v1.z(), v0.x()*v1.y() - v0.y()*v1.x());
    n_vect.setNorm(res);
}
