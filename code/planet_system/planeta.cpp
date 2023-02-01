#include "planeta.h"
#include <iostream>
#include <cmath>

PlanetA::PlanetA(int radius_a, int radius_b, int net_nodes_num, std::vector<Point> lights,
               QColor surface_color, int type) : Sphere(Point(0.0, 0.0, 0.0), radius_a, radius_b, net_nodes_num, type)
{
    this->surface_color = surface_color;
    this->lights = lights;
    CalcIntensities(lights);
}

void PlanetA::CalcIntensities(std::vector<Point> lights)
{
    Edge* edges = GetEdges();
    Point* points = GetPoints();
    int n = GetNetNodesParam();

    Vector *normals = new Vector[GetEdgesNum()];
    Point a, b, c;
    Vector ab, ac, ra;
    int I_0 = 1, I;
    double cos_lamb, cos_r;
    double len_n, len_a, len_r;
    double sn, sr;

    Point center = GetCenter();

    for (int i = 0; i < GetEdgesNum(); i++)
    {
        intensities[i] = 0;
        for (int j = 0; j < GetEdgesNum(); j++)
        {
            a = points[edges[i].GetP1()];
            b = points[edges[i].GetP2()];
            c = points[edges[i].GetP3()];

            ab.Set(a, b);
            ac.Set(a, c);
            normals[i] = ab.VectProd(ac);

            ra.Set(a, center);
            len_r = ra.GetLen();
            sr = normals[i].ScalarProd(ra);
            len_n = normals[i].GetLen();
            len_a = a.GetDistance(lights[j]);

            cos_r = sr / len_r / len_n;
            if (cos_r > 0)
                normals[i].Neg();

            sn = normals[i].ScalarProd(Vector(a, lights[j]));
            cos_lamb = sn / len_n / len_a;

            intensities[i] += I_0 * cos_lamb;
        }
    }
    delete [] normals;
}

void PlanetA::RotateX(int degree, Point c)
{
    Point* points = GetPoints();
    int n = GetNetNodesParam();
    Point center = GetCenter();
    for (int i = 0; i < GetPointsNum(); i++)
    {
        points[i].RotateX(degree, c);
    }
    SetCenter(center.RotateX(degree, c));
}

void PlanetA::RotateY(int degree, Point c)
{
    Point* points = GetPoints();
    int n = GetNetNodesParam();
    Point center = GetCenter();
    for (int i = 0; i < GetPointsNum(); i++)
    {
        points[i].RotateY(degree, c);
    }
    SetCenter(center.RotateY(degree, c));
}

void PlanetA::RotateZ(int degree, Point c)
{
    Point* points = GetPoints();
    int n = GetNetNodesParam();
    Point center = GetCenter();
    for (int i = 0; i < GetPointsNum(); i++)
    {
        points[i].RotateZ(degree, c);
    }
    SetCenter(center.RotateZ(degree, c));
}

void PlanetA::Scale(double kx, double ky, double kz, Point c)
{
    Point* points = GetPoints();
    int n = GetNetNodesParam();
    Point center = GetCenter();
    for (int i = 0; i < GetPointsNum(); i++)
    {
        points[i].Scale(kx, ky, kz, c);
    }

    SetCenter(center.Scale(kx, ky, kz, c));
}

void PlanetA::Scale(double k, Point c)
{
    Point* points = GetPoints();
    int n = GetNetNodesParam();
    Point center = GetCenter();
    for (int i = 0; i < GetPointsNum(); i++)
    {
        points[i].Scale(k, c);
    }

    SetCenter(center.Scale(k, c));
}

void PlanetA::Move(double dx, double dy, double dz)
{
    Point* points = GetPoints();
    int n = GetNetNodesParam();
    Point center = GetCenter();
    for (int i = 0; i < GetPointsNum(); i++)
    {
        points[i].Move(dx, dy, dz);
    }

    SetCenter(center.Move(dx, dy, dz));
    CalcIntensities(this->lights);
}

double *PlanetA::GetIntensities()
{
    return intensities;
}

void PlanetA::AddOrbitPoint(Point p)
{
    if (orbits_v.size() > 1000)
        orbits_v.clear();
    orbits_v.push_back(Point(p.GetX(), p.GetY(), p.GetZ()));
}

std::vector<Point> PlanetA::GetOrbitNum(void)
{
    std::vector tmp = orbits_v;
    return tmp;
}

void PlanetA::MashOrbit(double k)
{
    this->orbits_v.clear();
}

