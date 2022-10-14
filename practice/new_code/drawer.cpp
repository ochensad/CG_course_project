#include "drawer.h"
#include <QPainter>

Drawer::Drawer(QWidget *parent) : QWidget(parent)
{
    wind = parent;
    pixmap = QPixmap(wind->width(), wind->height());
    buf = nullptr;
}

void Drawer::paintEvent(QPaintEvent *)
{
    if(!buf)
        return;
    QPainter painter(this);
    painter.drawImage(0, 0, QImage((uchar*)buf, wind->width(), wind->height(), QImage::Format_ARGB32));
}
