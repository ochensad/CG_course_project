#include "model.h"
#include "zbuffer.h"
#include <iostream>
#include "math.h"
#include <algorithm>

Model::Model()
{
    QColor lt(0, 0, 255);
    QRgb h = lt.rgb();
    this->light = new Light(QVector3D(-200, 250, 250), QVector3D(0, 0, 0), h, 0.8);
}

Model::~Model()
{
    if (this->color_buf)
    {
        delete []color_buf;
    }
}

void Model::addSurface(Surface s)
{
    this->model_components.push_back(s);
}

float MulVecLenght(float x1, float x2, float y1, float y2)
{
    float first;
    float second;
    first = sqrt(x1*x1 + x2*x2);
    second = sqrt(y1*y1 + y2*y2);

    return first*second;
}

void Model::angleShadowSearch(QVector3D v, QVector3D l, QMatrix4x4 &m)
{
    float angle_X, angle_Y;
    float v_length, l_length;

    int angle_x_int, angle_y_int;
    v_length = MulVecLenght(v.y(), v.z(), l.y(), l.z());
    l_length = MulVecLenght(v.x(), v.z(), l.x(), l.z());

    angle_X = (v.y() * l.y() + v.z() * l.z()) / v_length;
    angle_Y = (v.x() * l.x() + v.z() * l.z()) /l_length ;

    angle_x_int = int((acos(angle_X) * 180 / M_PI));
    angle_y_int = int((acos(angle_Y) * 180 / M_PI));

    if (l_length != 0)
    {
        if (l.x() < 0)
        {
            m.rotate(360 - angle_y_int, 0, 1, 0);
        }
        else
        {
            m.rotate(angle_y_int, 0, 1, 0);
        }

    }
    if (v_length != 0)
    {
        if (l.z() < 0)
        {
            m.rotate(180 - angle_x_int - 1, 1, 0, 0);
        }

        else
        {
            m.rotate((angle_x_int - 1), 1, 0, 0);
        }
    }
}

bool cmp(const Surface &a, const Surface &b)
{
    Surface tmp = a;
    float z_a_1 = tmp.GetPolygon().Get_t1().z();
    float z_a_2 = tmp.GetPolygon().Get_t2().z();
    float z_a_3 = tmp.GetPolygon().Get_t3().z();
    float z_a_max = std::max(std::max(z_a_1, z_a_2), z_a_3);

    tmp = b;
    float z_b_1 = tmp.GetPolygon().Get_t1().z();
    float z_b_2 = tmp.GetPolygon().Get_t2().z();
    float z_b_3 = tmp.GetPolygon().Get_t3().z();
    float z_b_max = std::max(std::max(z_b_1, z_b_2), z_b_3);

    if (z_a_max < z_b_max)
        return true;
    return false;
}

void Model::sort(void)
{
    std::sort(model_components.begin(), model_components.end(),cmp);
}

void Model::Normalise()
{
    Surface c, tmp;
    Normal n, n1, n2;
    std::vector<Surface> new_v;
    Polygon t;
    for(unsigned int i = 0; i < this->model_components.size(); i++)
    {
        c = this->model_components.at(i);
        c.SetAutoNormal();
        n = c.GetNormal();
        for(unsigned int j = i; j < this->model_components.size(); j++)
        {
            tmp = this->model_components.at(j);
            tmp.SetAutoNormal();
            if (tmp.GetPolygon().Get_t1().x() == c.GetPolygon().Get_t1().x() && tmp.GetPolygon().Get_t1().y() == c.GetPolygon().Get_t1().y()
                    && tmp.GetPolygon().Get_t1().z() == c.GetPolygon().Get_t1().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
            else if (tmp.GetPolygon().Get_t2().x() == c.GetPolygon().Get_t1().x() && tmp.GetPolygon().Get_t2().y() == c.GetPolygon().Get_t1().y()
                    && tmp.GetPolygon().Get_t2().z() == c.GetPolygon().Get_t1().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
            else if (tmp.GetPolygon().Get_t3().x() == c.GetPolygon().Get_t1().x() && tmp.GetPolygon().Get_t3().y() == c.GetPolygon().Get_t1().y()
                    && tmp.GetPolygon().Get_t3().z() == c.GetPolygon().Get_t1().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
        }
        t = c.GetPolygon();
        t.SetNorm_t1(n.getNorm());
        n = c.GetNormal();
        for(unsigned int j = i + 1; j < this->model_components.size(); j++)
        {
            tmp = this->model_components.at(j);
            tmp.SetAutoNormal();
            if (tmp.GetPolygon().Get_t1().x() == c.GetPolygon().Get_t2().x() && tmp.GetPolygon().Get_t1().y() == c.GetPolygon().Get_t2().y()
                    && tmp.GetPolygon().Get_t1().z() == c.GetPolygon().Get_t2().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
            else if (tmp.GetPolygon().Get_t2().x() == c.GetPolygon().Get_t2().x() && tmp.GetPolygon().Get_t2().y() == c.GetPolygon().Get_t2().y()
                    && tmp.GetPolygon().Get_t2().z() == c.GetPolygon().Get_t2().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
            else if (tmp.GetPolygon().Get_t3().x() == c.GetPolygon().Get_t2().x() && tmp.GetPolygon().Get_t3().y() == c.GetPolygon().Get_t2().y()
                    && tmp.GetPolygon().Get_t3().z() == c.GetPolygon().Get_t2().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
        }
        t.SetNorm_t2(n.getNorm());
        n = c.GetNormal();
        for(unsigned int j = i + 1; j < this->model_components.size(); j++)
        {
            tmp = this->model_components.at(j);
            tmp.SetAutoNormal();
            if (tmp.GetPolygon().Get_t1().x() == c.GetPolygon().Get_t3().x() && tmp.GetPolygon().Get_t1().y() == c.GetPolygon().Get_t3().y()
                    && tmp.GetPolygon().Get_t1().z() == c.GetPolygon().Get_t3().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
            else if (tmp.GetPolygon().Get_t2().x() == c.GetPolygon().Get_t3().x() && tmp.GetPolygon().Get_t2().y() == c.GetPolygon().Get_t3().y()
                    && tmp.GetPolygon().Get_t2().z() == c.GetPolygon().Get_t3().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
            else if (tmp.GetPolygon().Get_t3().x() == c.GetPolygon().Get_t3().x() && tmp.GetPolygon().Get_t3().y() == c.GetPolygon().Get_t3().y()
                    && tmp.GetPolygon().Get_t3().z() == c.GetPolygon().Get_t3().z())
            {
                n1 = tmp.GetNormal();
                n = n + n1;
            }
        }
        t.SetNorm_t3(n.getNorm());
        new_v.push_back(Surface(t));
    }
    model_components = new_v;
}


QImage Model::draw(Drawer *canv)
{
    this->sort();
    this->Normalise();

    int lenght = canv->GetHeight() * canv->GetWidth();
    color_buf = new QRgb[lenght];

    QColor c (0,0,0);

    for(int i = 0; i < lenght; i++)
        color_buf[i] = c.rgb();

    QRgb *keeper_color_buf = color_buf;
    color_buf += lenght/2 + canv->GetWidth()/2;


    QVector3D view = QVector3D(0, 0, 600);
    QVector3D light_vector = light->GetOrigin();

    Surface tempSurface, tmp;
    Polygon t, tmp_pol;

    std::vector<Surface> new_triangles;
    std::vector<Surface> orig_triangles;

    QMatrix4x4 rotate_m = QMatrix4x4();
    rotate_m.rotate(100, 1, 0, 0);
    rotate_m.rotate(-30, 0, 1, 0);

    this->sort();

    ZBuffer buffer(canv->GetWidth(), canv->GetHeight());
    buffer.setLight(light);
    buffer.setPixmap(color_buf);

    ZBuffer buffer_shadow(canv->GetWidth(), canv->GetHeight());

    QMatrix4x4 m = QMatrix4x4();

    angleShadowSearch(view, light_vector, m);

    this->sort();

    for (unsigned int i = 0; i < model_components.size(); ++i)
    {
        tempSurface = model_components.at(i);
        t = tempSurface.GetPolygon();
        tmp_pol = Polygon(t.Get_t1()*rotate_m*m, t.Get_t2() * rotate_m*m, t.Get_t3() * rotate_m*m, t.Get_color());
        tmp_pol.SetNorm_t1(t.GetNorm_t1().getNorm() *rotate_m*m);
        tmp_pol.SetNorm_t2(t.GetNorm_t2().getNorm() *rotate_m*m);
        tmp_pol.SetNorm_t3(t.GetNorm_t3().getNorm() *rotate_m*m);
        tmp.SetPolygon(tmp_pol);
        new_triangles.push_back(tmp);
    }

    float * buf = buffer_shadow.getShadows(&new_triangles);
    buffer.setShadowBuffer(buf);

    for (unsigned int i = 0; i < model_components.size(); ++i)
    {
        tempSurface = model_components.at(i);
        t = tempSurface.GetPolygon();
        tmp.SetNormal(Normal(tempSurface.GetNormal()*rotate_m));
        tmp_pol = Polygon(t.Get_t1()*rotate_m, t.Get_t2() * rotate_m, t.Get_t3() * rotate_m, t.Get_color());
        tmp_pol.SetNorm_t1(t.GetNorm_t1().getNorm() *rotate_m);
        tmp_pol.SetNorm_t2(t.GetNorm_t2().getNorm() *rotate_m);
        tmp_pol.SetNorm_t3(t.GetNorm_t3().getNorm() *rotate_m);
        tmp.SetPolygon(tmp_pol);
        orig_triangles.push_back(tmp);
    }

    buffer.fillBufferWithShadows(&orig_triangles, m);

    color_buf = keeper_color_buf;
    canv->setGeometry(0, 0, canv->GetWidth(), canv->GetHeight());
    canv->SetBuff(color_buf);
    QImage cur = QImage((uchar*)color_buf, canv->width(), canv->height(), QImage::Format_ARGB32);
    canv->update();
    return cur;
}

QImage Model::get_image(int w, int h)
{
    this->sort();
    this->Normalise();

    int lenght = h * w;
    color_buf = new QRgb[lenght];

    QColor c (0,0,0);

    for(int i = 0; i < lenght; i++)
        color_buf[i] = c.rgb();

    QRgb *keeper_color_buf = color_buf;
    color_buf += lenght/2 + w/2;


    QVector3D view = QVector3D(0, 0, 600);
    QVector3D light_vector = light->GetOrigin();

    Surface tempSurface, tmp;
    Polygon t, tmp_pol;

    std::vector<Surface> new_triangles;
    std::vector<Surface> orig_triangles;

    QMatrix4x4 rotate_m = QMatrix4x4();
    rotate_m.rotate(100, 1, 0, 0);
    rotate_m.rotate(-30, 0, 1, 0);

    this->sort();

    ZBuffer buffer(w, h);
    buffer.setLight(light);
    buffer.setPixmap(color_buf);

    ZBuffer buffer_shadow(w, h);

    QMatrix4x4 m = QMatrix4x4();

    angleShadowSearch(view, light_vector, m);

    this->sort();

    for (unsigned int i = 0; i < model_components.size(); ++i)
    {
        tempSurface = model_components.at(i);
        t = tempSurface.GetPolygon();
        tmp_pol = Polygon(t.Get_t1()*rotate_m*m, t.Get_t2() * rotate_m*m, t.Get_t3() * rotate_m*m, t.Get_color());
        tmp_pol.SetNorm_t1(t.GetNorm_t1().getNorm() *rotate_m*m);
        tmp_pol.SetNorm_t2(t.GetNorm_t2().getNorm() *rotate_m*m);
        tmp_pol.SetNorm_t3(t.GetNorm_t3().getNorm() *rotate_m*m);
        tmp.SetPolygon(tmp_pol);
        new_triangles.push_back(tmp);
    }

    float * buf = buffer_shadow.getShadows(&new_triangles);
    buffer.setShadowBuffer(buf);

    for (unsigned int i = 0; i < model_components.size(); ++i)
    {
        tempSurface = model_components.at(i);
        t = tempSurface.GetPolygon();
        tmp.SetNormal(Normal(tempSurface.GetNormal()*rotate_m));
        tmp_pol = Polygon(t.Get_t1()*rotate_m, t.Get_t2() * rotate_m, t.Get_t3() * rotate_m, t.Get_color());
        tmp_pol.SetNorm_t1(t.GetNorm_t1().getNorm() *rotate_m);
        tmp_pol.SetNorm_t2(t.GetNorm_t2().getNorm() *rotate_m);
        tmp_pol.SetNorm_t3(t.GetNorm_t3().getNorm() *rotate_m);
        tmp.SetPolygon(tmp_pol);
        orig_triangles.push_back(tmp);
    }

    buffer.fillBufferWithShadows(&orig_triangles, m);

    color_buf = keeper_color_buf;
    QImage cur = QImage((uchar*)color_buf, w, h, QImage::Format_ARGB32);
    return cur;
}
