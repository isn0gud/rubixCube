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
    int xAngle = 0;
    int yAngle = 0;
    QVector3D position;

public:
    Cube(int _id = 1, int x = 0, int y = 0, int z = 0);
    QVector<QVector3D> getVertices() const;
    QVector<QVector3D> getColorVectorById() const;
    QVector<QVector3D> getColors() const;
    void setToStdColor();
    void setColorHighlight();

    int getId() const;

    QVector3D getPosition() const;

    int getXAngle() const;
    void setXAngle(int value);
    int getYAngle() const;
    void setYAngle(int value);

private:
};

#endif // CUBE_H
