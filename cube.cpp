#include "cube.h"
#include <QMatrix4x4>
#include <QColor>
//#include <QDebug>

Cube::Cube(int _id, float x, float y, float z)
    : id(_id)
    , position(x, y, z)
{
    vertices << QVector3D(-0.48, -0.48, 0.48) << QVector3D(0.48, -0.48, 0.48) << QVector3D(0.48, 0.48, 0.48) // Front
             << QVector3D(0.48, 0.48, 0.48) << QVector3D(-0.48, 0.48, 0.48) << QVector3D(-0.48, -0.48, 0.48)
             << QVector3D(0.48, -0.48, -0.48) << QVector3D(-0.48, -0.48, -0.48) << QVector3D(-0.48, 0.48, -0.48) // Back
             << QVector3D(-0.48, 0.48, -0.48) << QVector3D(0.48, 0.48, -0.48) << QVector3D(0.48, -0.48, -0.48)
             << QVector3D(-0.48, -0.48, -0.48) << QVector3D(-0.48, -0.48, 0.48) << QVector3D(-0.48, 0.48, 0.48) // Left
             << QVector3D(-0.48, 0.48, 0.48) << QVector3D(-0.48, 0.48, -0.48) << QVector3D(-0.48, -0.48, -0.48)
             << QVector3D(0.48, -0.48, 0.48) << QVector3D(0.48, -0.48, -0.48) << QVector3D(0.48, 0.48, -0.48) // Right
             << QVector3D(0.48, 0.48, -0.48) << QVector3D(0.48, 0.48, 0.48) << QVector3D(0.48, -0.48, 0.48)
             << QVector3D(-0.48, 0.48, 0.48) << QVector3D(0.48, 0.48, 0.48) << QVector3D(0.48, 0.48, -0.48) // Top
             << QVector3D(0.48, 0.48, -0.48) << QVector3D(-0.48, 0.48, -0.48) << QVector3D(-0.48, 0.48, 0.48)
             << QVector3D(-0.48, -0.48, -0.48) << QVector3D(0.48, -0.48, -0.48) << QVector3D(0.48, -0.48, 0.48) // Bottom
             << QVector3D(0.48, -0.48, 0.48) << QVector3D(-0.48, -0.48, 0.48) << QVector3D(-0.48, -0.48, -0.48);
    setToStdColor();
    //    qDebug() << (id & 0x000000FF) / 255.0f << endl;

    //    currentXVec = QVector3D(1, 0, 0);
    //    currentYVec = QVector3D(0, 1, 0);
    //    currentZVec = QVector3D(0, 0, 1);
}

//int Cube::getXAngle() const
//{
//    return xAngle;
//}

//int Cube::getYAngle() const
//{
//    return yAngle;
//}

//int Cube::getZAngle() const
//{
//    return zAngle;
//}

QQuaternion Cube::getRotation() const
{
    return rotation;
}

void Cube::setToColor(QColor color)
{
    colors.clear();
    for (int i = 0; i < 36; ++i) {

        colors << QVector3D(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f);
    }
}

int Cube::getId() const
{
    return id;
}

QVector<QVector3D> Cube::getVertices() const
{
    return vertices;
}

QVector<QVector3D> Cube::getColorVectorById() const
{
    QVector<QVector3D> colorsById;
    for (int i = 0; i < 36; ++i) {
        colorsById << QVector3D(id / 255.0f, id / 255.0f, id / 255.0f);
    }
    return colorsById;
}

QVector<QVector3D> Cube::getColors() const
{
    return colors;
}

void Cube::setToStdColor()
{
    colors.clear();

    for (int i = 0; i < 6; ++i) {
        colors << QVector3D(0.6, 0, 0); //FRONT
    }
    for (int i = 0; i < 6; ++i) {
        colors << QVector3D(0.9, 0.4, 0); //BACK
    }
    for (int i = 0; i < 6; ++i) {
        colors << QVector3D(0, 0.4, 0); //LEFT
    }
    for (int i = 0; i < 6; ++i) {
        colors << QVector3D(0, 0, 0.4); //RIGHT
    }
    for (int i = 0; i < 6; ++i) {
        colors << QVector3D(0.9, 0.9, 0.9); //TOP
    }
    for (int i = 0; i < 6; ++i) {
        colors << QVector3D(0.8, 0.8, 0); //BOTTOM
    }
}

void Cube::setColorHighlight()
{
    QVector<QVector3D> highlightedColors;
    for (int i = 0; i < colors.size(); ++i) {
        //      colors.at(i) *= QVector3D(1,0,0);
        highlightedColors << colors.at(i) * QVector3D(0.3, 0.3, 0.3);
    }
    colors = highlightedColors;
}

QVector3D Cube::getPosition() const
{
    return position;
}

void Cube::rotateX(int angle)
{

    rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), angle) * rotation;
}

void Cube::rotateY(int angle)
{

    rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), angle) * rotation;
}

void Cube::rotateZ(int angle)
{

    rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), angle) * rotation;
}
