#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QRgb>
#include <QPixmap>

class Drawer: public QWidget
{
    Q_OBJECT
public:
    explicit Drawer(QWidget *parent = 0);
    void SetBuff(QRgb* buffer)
    {
        buf = buffer;
    }
    int GetHeight() {return wind->height();};
    int GetWidth() {return wind->width();};

    void SetColor(int n_r, int n_g, int n_b) {r = n_r; g = n_g; b = n_b;};
    int GetR() {return r;};
    int GetG() {return g;};
    int GetB() {return b;};
private:
    QRgb* buf;
    QWidget* wind;
    QPixmap pixmap;
    int r = 0;
    int b = 0;
    int g = 0;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // DRAWER_H
