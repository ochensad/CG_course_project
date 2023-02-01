#include "timer.h"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <QPair>
#include "zbuffer.h"

#define RUNS 10

Timer::Timer(int polygons)
{
    this->count = polygons;
}

uint64_t tick(void)
{

    uint64_t ticks = 20;

    return ticks;
}

QPair<long long int, double> get_result(int64_t start, int64_t end)
{
    return {end - start, (double)(end - start)/HZ};
}

void Timer::create_model(int num)
{
    QColor cl(255, 4, 33);
    QRgb r = cl.rgb();

    float x_1 = 0.0;
    float y_1 = 0.0;
    float x_2 = 10.0;
    float y_2 = 0.0;
    float x_3 = 0.0;
    float y_3 = 10.0;

    float z = 400;

    model = new Model();

    QVector3D p1(x_1, y_1, z);
    QVector3D p2(x_2, y_2, z);
    QVector3D p3(x_3, y_3, z);

    for (int i = 0; i < num; i++)
    {
        p1.setZ(z - i);
        p2.setZ(z - i);
        p3.setZ(z - i);
        model->addSurface(Polygon(p1, p2, p3, r));
    }
}

void Timer::func()
{
    model->Normalise();

    int lenght = 1000*800;
    QRgb *color_buf = new QRgb[lenght];

    QColor c (0,0,0);

    for(int i = 0; i < lenght; i++)
        color_buf[i] = c.rgb();

    QRgb *keeper_color_buf = color_buf;
    color_buf += lenght/2 + 1000/2;

    QColor lt(255, 255, 255);
    QRgb h = lt.rgb();
    Light l(QVector3D(200, 100, 500), QVector3D(0,0, -1000), h, 0.8);
    QVector3D view = QVector3D(0, 0, 600);
    QVector3D light_vector = l.GetOrigin();

    Surface tempSurface, tmp;
    Polygon t, tmp_pol;

    std::vector<Surface> new_triangles;
    std::vector<Surface> orig_triangles;


    ZBuffer buffer(1000, 800);
    buffer.setLight(&l);
    buffer.setPixmap(color_buf);

    ZBuffer buffer_shadow(1000, 800);

    QMatrix4x4 m = QMatrix4x4();

    model->angleShadowSearch(view, light_vector, m);

    for (unsigned int i = 0; i < model->getComponents().size(); ++i)
    {
        tempSurface = model->getComponents().at(i);
        t = tempSurface.GetPolygon();
        tmp_pol = Polygon(t.Get_t1()*m, t.Get_t2() *m, t.Get_t3() *m, t.Get_color());
        tmp_pol.SetNorm_t1(t.GetNorm_t1().getNorm() *m);
        tmp_pol.SetNorm_t2(t.GetNorm_t2().getNorm() *m);
        tmp_pol.SetNorm_t3(t.GetNorm_t3().getNorm() *m);
        tmp.SetPolygon(tmp_pol);
        new_triangles.push_back(tmp);
    }

    float * buf = buffer_shadow.getShadows(&new_triangles);
    buffer.setShadowBuffer(buf);

    for (unsigned int i = 0; i < model->getComponents().size(); ++i)
    {
        tempSurface = model->getComponents().at(i);
        t = tempSurface.GetPolygon();
        tmp_pol = Polygon(t.Get_t1(), t.Get_t2() , t.Get_t3() , t.Get_color());
        tmp_pol.SetNorm_t1(t.GetNorm_t1().getNorm() );
        tmp_pol.SetNorm_t2(t.GetNorm_t2().getNorm() );
        tmp_pol.SetNorm_t3(t.GetNorm_t3().getNorm() );
        tmp.SetPolygon(tmp_pol);
        orig_triangles.push_back(tmp);
    }

    buffer.fillBufferWithShadows(&orig_triangles, m);
}

void Timer::calculate_time()
{
    std::ofstream out;
    out.open("test.txt");
    int64_t start = 0, end = 0;

    for (int i = 0; i < this->count; i++)
    {
        create_model(i);
        for(int j = 0; j < RUNS; j++)
        {
            start += tick();
            this->func();
            end += tick();
        }

        QPair<long long int, double> res = get_result(start / RUNS, end / RUNS);
        if (out.is_open())
        {
            out << res.first << " " << res.second << std::endl;
        }
    }
    out.close();

}
