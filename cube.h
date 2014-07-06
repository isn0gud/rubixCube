#ifndef CUBE_H
#define CUBE_H

#include <QVector>
#include <QVector3D>

class Cube {
private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
    QVector<QVector3D> colorsById;
    int id;

public:
    Cube(int _id = 1);
    QVector<QVector3D> getVertices() const;
    QVector<QVector3D> getColorVectorById() const;
    QVector<QVector3D> getColors() const;
    void setToStdColor();
    void setColorHighlight();


private:
};

#endif // CUBE_H
