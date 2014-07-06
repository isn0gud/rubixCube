#include "cube.h"
#include <QDebug>


int Cube::getXAngle() const
{
  return xAngle;
}

void Cube::setXAngle(int value)
{
  xAngle = value;
}

int Cube::getYAngle() const
{
  return yAngle;
}

void Cube::setYAngle(int value)
{
  yAngle = value;
}
Cube::Cube(int _id, int x, int y, int z)
  : id(_id)
  , position(x, y, z)
{
  vertices << QVector3D(-0.5, -0.5, 0.5) << QVector3D(0.5, -0.5, 0.5) << QVector3D(0.5, 0.5, 0.5) // Front
             << QVector3D(0.5, 0.5, 0.5) << QVector3D(-0.5, 0.5, 0.5) << QVector3D(-0.5, -0.5, 0.5)
             << QVector3D(0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, 0.5, -0.5) // Back
             << QVector3D(-0.5, 0.5, -0.5) << QVector3D(0.5, 0.5, -0.5) << QVector3D(0.5, -0.5, -0.5)
             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, 0.5) << QVector3D(-0.5, 0.5, 0.5) // Left
             << QVector3D(-0.5, 0.5, 0.5) << QVector3D(-0.5, 0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
             << QVector3D(0.5, -0.5, 0.5) << QVector3D(0.5, -0.5, -0.5) << QVector3D(0.5, 0.5, -0.5) // Right
             << QVector3D(0.5, 0.5, -0.5) << QVector3D(0.5, 0.5, 0.5) << QVector3D(0.5, -0.5, 0.5)
             << QVector3D(-0.5, 0.5, 0.5) << QVector3D(0.5, 0.5, 0.5) << QVector3D(0.5, 0.5, -0.5) // Top
             << QVector3D(0.5, 0.5, -0.5) << QVector3D(-0.5, 0.5, -0.5) << QVector3D(-0.5, 0.5, 0.5)
             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(0.5, -0.5, -0.5) << QVector3D(0.5, -0.5, 0.5) // Bottom
             << QVector3D(0.5, -0.5, 0.5) << QVector3D(-0.5, -0.5, 0.5) << QVector3D(-0.5, -0.5, -0.5);
    setToStdColor();
    //    qDebug() << (id & 0x000000FF) / 255.0f << endl;
    for (int i = 0; i < 36; ++i) {
        colorsById << QVector3D(id / 255.0f, id / 255.0f, id / 255.0f);
    }
}

QVector<QVector3D> Cube::getVertices() const
{
    return vertices;
}

QVector<QVector3D> Cube::getColorVectorById() const
{

    return colorsById;
}

QVector<QVector3D> Cube::getColors() const
{
    return colors;
}

void Cube::setToStdColor()
{
    colors.clear();
    colors << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) // Front
           << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) << QVector3D(0, 0, 0)
           << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) // Back
           << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1)
           << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) // Left
           << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0)
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
           << QVector3D(0.5, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) // Top
           << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5)
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);
}

void Cube::setColorHighlight()
{
    QVector<QVector3D> highlightedColors;
    for (int i = 0; i < colors.size(); ++i) {
        //      colors.at(i) *= QVector3D(1,0,0);
        highlightedColors << colors.at(i) * QVector3D(1, 0.5, 0.5);
    }
    colors = highlightedColors;
}

QVector3D Cube::getPosition() const
{
    return position;
}
