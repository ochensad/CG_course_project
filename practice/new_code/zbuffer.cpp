#include "zbuffer.h"
#include "math.h"
#define EXP 1e-4

ZBuffer::ZBuffer(int n_width, int n_height)
{
    this->width = n_width;
    this->height = n_height;
    buffer = new float[width*height];
    for(int i = 0; i < width*height; i++)
        buffer[i] = -1*std::numeric_limits<float>::max();
}

ZBuffer::~ZBuffer()
{
    if (buffer)
    {
        delete []buffer;
        buffer = nullptr;
    }
}

void ZBuffer::setPixmap(QRgb *n_pixmap)
{
    pixmap = n_pixmap;
}

int checkColor(int color)
{
    if (color < 0)
        return 0;
    if (color > 255)
        return 255;
    return color;
}

QRgb ShdwUndo(int i1, int i2, float tc)
{
    return qRgba(checkColor((int)(tc * qRed(i2) + (1.0 - tc) * qRed(i1))),
                 checkColor((int)(tc * qGreen(i2) + (1.0 - tc) * qGreen(i1))),
                 checkColor((int)(tc * qBlue(i2) + (1.0 - tc) * qBlue(i1))), 255);
}

int ShdwDo(int i1, int i2, float tc)
{
    return qRgba(checkColor((int)(0.6* tc * qRed(i2) + 0.3 *(1.0 - tc) * qRed(i1))),
                 checkColor((int)(0.6* tc * qGreen(i2) + 0.3 *(1.0 - tc) * qGreen(i1))),
                 checkColor((int)(0.6* tc * qBlue(i2) + 0.3 *(1.0 - tc) * qBlue(i1))), 255);
}

float VectorLength(QVector3D vector)
{
    return sqrt(vector.x()*vector.x() + vector.y()*vector.y() + vector.z()*vector.z());
}


void ZBuffer::fillBufferWithShadows(std::vector<Surface> *new_triangles, QMatrix4x4 orig_proj)
{
    Polygon temp;
    float xScanLine1, xScanLine2;
    bool bordersFound;
    float x1 = 0, x2 = 0, tc;
    float z1 = 0, z2 = 0, z = 0;
    int ymax, ymin, yScanLine, e1;
    float x[3], y[3];
    float z_a[3];
    int halfHeight = (getHeight()>>1);
    Surface tempSurface;
    Normal normal;
    QVector3D d;
    int new_index = 0;
    for(unsigned int j = 0; j < new_triangles->size(); ++j)
    {
        tempSurface = new_triangles->at(j);
        temp = tempSurface.GetPolygon();
        normal = tempSurface.GetNormal();
        x[0] = round(temp.Get_t1().x()); y[0] = round(temp.Get_t1().y()); z_a[0] = temp.Get_t1().z();
        x[1] = round(temp.Get_t2().x()); y[1] = round(temp.Get_t2().y()); z_a[1] = temp.Get_t2().z();
        x[2] = round(temp.Get_t3().x()); y[2] = round(temp.Get_t3().y()); z_a[2] = temp.Get_t3().z();
        ymin = std::min(std::min(y[0], y[1]),y[2]);
        ymax = std::max(std::max(y[0], y[1]),y[2]);


        QVector3D l = (light->GetOrigin());
        QVector3D norm_1 = temp.GetNorm_t1().getNorm();
        QVector3D norm_2 = temp.GetNorm_t2().getNorm();
        QVector3D norm_3 = temp.GetNorm_t3().getNorm();

        float cosinus[3];
        int rc[3], bc[3], gc[3];

        for (int i = 0; i < 3; ++i)
        {
            QVector3D lt(l.x()- x[i], l.y() - y[i], l.z() - z_a[i]);

            if (i == 0)
            {
                cosinus[i] = (norm_1.x()*lt.x() + norm_1.y()*lt.y() + norm_1.z()*lt.z()) / (VectorLength(norm_1) * VectorLength(lt));
            }
            else if (i == 1)
            {

                cosinus[i] = (norm_2.x()*lt.x() + norm_2.y()*lt.y() + norm_2.z()*lt.z()) / (VectorLength(norm_2) * VectorLength(lt));
            }
            else if (i == 2)
            {

                cosinus[i] = (norm_3.x()*lt.x() + norm_3.y()*lt.y() + norm_3.z()*lt.z()) / (VectorLength(norm_3) * VectorLength(lt));
            }
            rc[i] = checkColor((int)(180*cosinus[i] + qRed(temp.Get_color())));
            gc[i] = checkColor((int)(180*cosinus[i] + qGreen(temp.Get_color())));
            bc[i] = checkColor((int)(180*cosinus[i] + qBlue(temp.Get_color())));
        }

        int i1 = 0, i2 = 0;
        for (yScanLine = round(ymin); yScanLine < round(ymax); yScanLine++)
        {
            bordersFound = false;
            for (int e = 0; e < 3; e++)
            {
                e1 = e + 1;
                if (e1 == 3)
                    e1 = 0;

                if (y[e] < y[e1] && (y[e1] <= yScanLine || yScanLine < y[e]))
                    continue;
                else if (y[e] > y[e1] && (y[e1] > yScanLine || yScanLine >= y[e]))
                    continue;
                else if (y[e] == y[e1])
                    continue;

                tc = (y[e] - yScanLine) / (y[e] - y[e1]);
                if (bordersFound)
                {
                    x2 = x[e] + ( tc * (x[e1] - x[e]));
                    z2 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                    i2 = qRgba(checkColor((int)(rc[e] + tc*(rc[e1] - rc[e]))),
                               checkColor((int)(gc[e] + tc*(gc[e1] - gc[e]))),
                               checkColor((int)(bc[e] + tc*(bc[e1] - bc[e]))),
                                255);
                }
                else
                {
                    x1 = x[e] +  (tc * (x[e1] - x[e]));
                    z1 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                    i1 = qRgba(checkColor((int)(rc[e] + tc*(rc[e1] - rc[e]))),
                               checkColor((int)(gc[e] + tc*(gc[e1] - gc[e]))),
                               checkColor((int)(bc[e] + tc*(bc[e1] - bc[e]))),
                                255);
                    bordersFound = true;
                }
            }

            if (x2 < x1)
            {
                std::swap(x2, x1);
                std::swap(z2, z1);
                std::swap(i2, i1);
            }

            xScanLine1 = (x1 < -1*std::numeric_limits<float>::max()) ? -1*std::numeric_limits<float>::max() : x1;
            xScanLine2 = (x2 < getWidth()) ? x2 : getWidth();
            for (int xScanLine = round(xScanLine1); xScanLine < round(xScanLine2); xScanLine++)
            {
                float tc = (x1 - xScanLine) / (x1 - x2);
                z = z1 + tc * (z2 - z1);
                int index = 0;
                index = (int)round(xScanLine+(yScanLine+halfHeight)*getWidth());
                if (index < getWidth()*getHeight() && index > 0)
                {
                    if(z > buffer[index])
                    {
                        d = QVector3D((xScanLine), (yScanLine), (z))*(orig_proj);
                        new_index = (int)round(round(d.x()) + (round(d.y())+float(halfHeight))*float(getWidth()));

                        int clr = ShdwUndo(i1, i2, (xScanLine - x1)/VectorLength(QVector3D(x2 - x1, 0,0)));

                        if (new_index <= getWidth()*getHeight())
                        {
                            if (j < 2 && d.z() - 5 < shadowBuffer[abs(new_index)])
                                clr = ShdwUndo(i1, i2, (xScanLine - x1)/VectorLength(QVector3D(x2 - x1, 0,0)));
                            else if (d.z() + 15 < shadowBuffer[abs(new_index)])
                            {
                                clr = ShdwDo(i1, i2, (xScanLine - x1)/VectorLength(QVector3D(x2 - x1, 0,0)));
                            }
                        }
                        QRgb color = qRgba(qRed(clr)*0.75 + 0.25*qRed(light->GetColor())*qAlpha(light->GetColor())/255,
                                       qGreen(clr)*0.75 + 0.25*qGreen(light->GetColor())*qAlpha(light->GetColor())/255,
                                       qBlue(clr)*0.75 + 0.25*qBlue(light->GetColor())*qAlpha(light->GetColor())/255, 255);



                        buffer[index] = z;
                        int ind = (int)round(xScanLine+yScanLine*getWidth());
                        if (ind < getWidth()*getHeight())
                            pixmap[ind] = color;
                    }
                }
            }
        }
    }
}

float * ZBuffer::getShadows(std::vector<Surface> *model)
{
    Surface tmp, tempSurface;
    Normal normal;
    Polygon temp;
    float xScanLine1, xScanLine2;
    bool bordersFound;
    float x1 = 0, x2 = 0, tc;
    float z1 = 0, z2 = 0, z = 0;
    int ymax, ymin, yScanLine, e1;
    float x[3], y[3];
    float z_a[3];
    int halfHeight = (getHeight()>>1);

    for(unsigned int j = 0; j < model->size(); ++j)
    {
        tempSurface = model->at(j);
        temp = tempSurface.GetPolygon();

        x[0] = round((temp.Get_t1()).x()); y[0] = round((temp.Get_t1()).y()); z_a[0] = (temp.Get_t1()).z();
        x[1] = round((temp.Get_t2()).x()); y[1] = round((temp.Get_t2()).y()); z_a[1] = (temp.Get_t2()).z();
        x[2] = round((temp.Get_t3()).x()); y[2] = round((temp.Get_t3()).y()); z_a[2] = (temp.Get_t3()).z();
        ymin = std::min(std::min(y[0], y[1]),y[2]);
        ymax = std::max(std::max(y[0], y[1]),y[2]);
        for (yScanLine = round(ymin); yScanLine < round(ymax); yScanLine++)
        {
            bordersFound = false;
            for (int e = 0; e < 3; e++)
            {
                e1 = e + 1;
                if (e1 == 3)
                    e1 = 0;

                if (y[e] < y[e1] && (y[e1] <= yScanLine || yScanLine < y[e]))
                    continue;
                else if (y[e] > y[e1] && (y[e1] > yScanLine || yScanLine >= y[e]))
                    continue;
                else if (y[e] == y[e1])
                    continue;

                tc = (y[e] - yScanLine) / (y[e] - y[e1]);
                if (bordersFound)
                {
                    x2 = x[e] + ( tc * (x[e1] - x[e]));
                    z2 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                }
                else
                {
                    x1 = x[e] +  (tc * (x[e1] - x[e]));
                    z1 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                    bordersFound = true;
                }
            }

            if (x2 < x1)
            {
                std::swap(x2, x1);
                std::swap(z2, z1);
            }

            xScanLine1 = (x1 < -1*std::numeric_limits<float>::max()) ? -1*std::numeric_limits<float>::max() : x1;
            xScanLine2 = (x2 < getWidth()) ? x2 : getWidth();

            for (int xScanLine = round(xScanLine1); xScanLine < round(xScanLine2); xScanLine++)
            {
                z = z1 + (x1 - xScanLine) / (x1 - x2) * (z2 - z1);
                int index = (int)round(xScanLine+(yScanLine+halfHeight)*getWidth());
                if(z > buffer[abs(index)])
                {
                    buffer[index] = z;
                }
            }
        }
    }
    return buffer;
}




