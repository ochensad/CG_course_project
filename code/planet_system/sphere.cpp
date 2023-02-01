#include "sphere.h"
#include <iostream>

Sphere::Sphere(Point center, int radius_a, int radius_b, int net_nodes_num, int type)
{
    this->center = center;
    this->radius_a = radius_a;
    this->radius_b = radius_b;
    this->m_radius_a = radius_a;
    this->m_radius_b = radius_b;
    this->net_nodes_param = net_nodes_num;
    this->type = type;
    CreateNet();
}

Sphere Sphere::operator=(Sphere p)
{
    this->center = p.center;
    this->radius_a = p.radius_a;
    this->radius_b = p.radius_b;
    this->net_nodes_param = p.net_nodes_param;
    this->type = p.type;
    this->edges = p.edges;
    this->points = p.points;
    return *this;
}

Sphere::~Sphere()
{
}

void Sphere::CreateNet()
{
    CreatePoints();
    CreateEdges();
}

void Sphere::CreatePoints()
{
    points = new Point [GetPointsNum()];
    int k = 0;
    int r = radius_a;
    int cx = center.GetX(); int cy = center.GetY(); int cz = center.GetZ();

    points[k++] = Point(cx - r, cy, cz);

    int step_degree = 90 / (net_nodes_param + 1);
    double radians, a, b, c;
    for (int i = 1; i <= net_nodes_param; i++)
    {
        radians = (90 - step_degree * i) * M_PI / 180;
        if (type == 0)
        {
            a = sqrt(2 * r * r * (1 - cos(radians)));
            b = sin(radians) * r;
            c = sqrt(a * a - b * b);
            points[k++] = Point(cx - b, cy + r - c, cz);
        }
        else if (type == 1)
        {
            int r_tmp = round(sqrt((radius_a*radius_a*radius_b*radius_b) / (cos(radians)*cos(radians)*radius_a*radius_a+sin(radians)*sin(radians)*radius_b*radius_b)));
            a = sqrt(2 * r_tmp * r_tmp * (1 - cos(radians)));
            b = sin(radians) * r_tmp;
            c = sqrt(a * a - b * b);
            points[k++] = Point(cx - b, cy + radius_a - c, cz);
        }
        //points[k++] = Point(cx - b, cy + r - c, cz);
    }
    points[k++] = Point(cx, cy + r, cz);

    for (int i = 0; i <= net_nodes_param; i++)
    {
        points[k++] = Point(2 * cx - points[net_nodes_param - i].GetX(),
                          points[net_nodes_param - i].GetY(),
                          points[net_nodes_param - i].GetZ());
    }
}

int Sphere::GetPointsNum()
{
    int n = net_nodes_param;
    return (3 + n * 2) + (n * 2 + 1) * 2 * (360 / 90 * (n + 1));
}

void Sphere::CreateEdges()
{
    int n = 3 + net_nodes_param * 2;
    int m = 2 + net_nodes_param * 2 * 2;

    Edge cur_edges[m];
    edges = new Edge[GetEdgesNum()];

    int j = 0;
    int top_set[n];
    int bottom_set[n];
    double step_degree = 90 / (net_nodes_param + 1);
    int k = n;
    int cur, right, left;

    for (int i = 0; i < n; i++)
    {
        top_set[i] = i;
    }

    int s = n;

    for (double degree = step_degree; degree <= 360; degree += step_degree)
    {
        for (int i = 1; i < n - 1; i++)
        {
            Point temp = points[i];
            points[s++] = temp.RotateX(degree, center);
        }
        for (int i = 0; i < n - 2; i++)
        {
            bottom_set[i] = k + i;
        }
        for (int i = 0; i < m; i++)
        {
            cur_edges[i] = Edge();
        }

        cur_edges[0].Append(top_set[0]);
        cur_edges[n - 2].Append(top_set[n - 1]);

        for (int i = 1; i < n - 1; i++)
        {
            cur_edges[i - 1].Append(top_set[i]);
            cur_edges[i].Append(top_set[i]);
        }

        for (int i = 2; i < n - 1; i++)
        {
            cur_edges[n - 1 + i - 2].Append(top_set[i]);
        }
        for (int i = 0; i < n - 2; i++)
        {
            cur = (n + i) % (n - 1);
            right = (n - 1) + i;
            left = right - 1;
            if (cur == 1)
            {
                left = 0;
            }
            cur_edges[cur].Append(bottom_set[i]);
            cur_edges[left].Append(bottom_set[i]);
            if (cur != n - 2)
            {
                cur_edges[right].Append(bottom_set[i]);
            }
        }
        for (int i = j; i < j + m; i++)
        {
            edges[i] = cur_edges[i % m];
        }
        j += m;
        top_set[0] = 0;
        top_set[n - 1] = n - 1;
        for (int i = 0; i < n - 2; i++)
        {
            top_set[i + 1] = bottom_set[i];
        }
        k += n - 2;
    }

    for (int i = 0; i < n - 2; i++)
    {
        bottom_set[i] = top_set[i + 1];
    }
    for (int i = 0; i < n; i++)
    {
        top_set[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        cur_edges[i] = Edge();
    }

    cur_edges[0].Append(top_set[0]);
    cur_edges[n - 2].Append(top_set[n - 1]);

    for (int i = 1; i < n - 1; i++)
    {
        cur_edges[i - 1].Append(top_set[i]);
        cur_edges[i].Append(top_set[i]);
    }

    for (int i = 2; i < n - 1; i++)
    {
        cur_edges[n - 1 + i - 2].Append(top_set[i]);
    }
    for (int i = 0; i < n - 2; i++)
    {
        cur = (n + i) % (n - 1);
        right = (n - 1) + i;
        left = right - 1;
        if (cur == 1)
        {
            left = 0;
        }
        cur_edges[cur].Append(bottom_set[i]);
        cur_edges[left].Append(bottom_set[i]);
        if (cur != n - 2)
        {
            cur_edges[right].Append(bottom_set[i]);
        }
    }
    for (int i = j; i < j + m; i++)
    {
        edges[i] = cur_edges[i % m];
    }

}

int Sphere::GetEdgesNum()
{
    int n = net_nodes_param;
    return (n * 2 * 2 + 2) * (360 / 90 * (n + 1) + 2) + (n * 2 * 2 + 2);
}

void Sphere::RotateX(int degree, Point c)
{
    int n = GetPointsNum();
    for (int i = 0; i < n; i++)
    {
        points[i].RotateX(degree, c);
    }
    center.RotateX(degree, c);
}

void Sphere::RotateY(int degree, Point c)
{
    int n = GetPointsNum();
    for (int i = 0; i < n; i++)
    {
        points[i].RotateY(degree, c);
    }
    center.RotateY(degree, c);
}

void Sphere::RotateZ(int degree, Point c)
{
    int n = GetPointsNum();
    for (int i = 0; i < n; i++)
    {
        points[i].RotateZ(degree, c);
    }
    center.RotateZ(degree, c);
}

void Sphere::Scale(double kx, double ky, double kz, Point c)
{
    int n = GetPointsNum();
    for (int i = 0; i < n; i++)
    {
        points[i].Scale(kx, ky, kz, c.GetX(), c.GetY(), c.GetZ());
    }
    center.Scale(kx, ky, kz, c.GetX(), c.GetY(), c.GetZ());
}

void Sphere::Move(double dx, double dy, double dz)
{
    int n = GetPointsNum();
    for (int i = 0; i < n; i++)
    {
        points[i].Move(dx, dy, dz);
    }
    center.Move(dx, dy, dz);
}

void Sphere::ChangeR(double k)
{
    this->radius_a = this->m_radius_a * k;
    this->radius_b = this->m_radius_b * k;
    delete []edges;
    delete []points;
    CreateNet();
}

void Sphere::ChangeR(int r_1, int r_2)
{
    this->radius_a = r_1;
    this->radius_b = r_2;
    delete []edges;
    delete []points;
    CreateNet();
}
