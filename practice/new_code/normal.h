#ifndef NORMAL_H
#define NORMAL_H

#include <QVector3D>
#include <QMatrix4x4>

class Normal
{
public:
    Normal();
    Normal(const Normal& n) {n_vec = n.n_vec;};
    Normal(QVector3D n) {n_vec = n;};
    QVector3D operator *(QMatrix4x4 matrix) { return this->n_vec*matrix; }
    Normal operator+(const Normal &n1) {return QVector3D(this->n_vec.x() + n1.n_vec.x(), this->n_vec.y() + n1.n_vec.y(), this->n_vec.z() + n1.n_vec.z());}
    void operator=(Normal n) {this->n_vec = n.n_vec;}
    double GetLength();
    QVector3D getNorm() { return n_vec; }
    void setNorm(QVector3D n) { n_vec = n; }

private:
    QVector3D n_vec;
};

#endif // NORMAL_H
