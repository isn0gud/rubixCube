#include "cube.h"
#include <QDebug>

Cube::Cube(int _id, float x, float y, float z)
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

    frontColors << QVector3D(0.1, 0.2, 0.3) << QVector3D(0.1, 0.2, 0.3) << QVector3D(0.1, 0.2, 0.3) // Front
                << QVector3D(0.1, 0.2, 0.3) << QVector3D(0.1, 0.2, 0.3) << QVector3D(0.1, 0.2, 0.3);
    backColors << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) // Back
               << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1);
    leftColors << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) // Left
               << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0);
    rightColors << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right
                << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0);
    topColors << QVector3D(0.5, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) // Top
              << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5);
    bottomColors << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom
                 << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);
    setToStdColor();
    //    qDebug() << (id & 0x000000FF) / 255.0f << endl;
    for (int i = 0; i < 36; ++i) {
        colorsById << QVector3D(id / 255.0f, id / 255.0f, id / 255.0f);
    }
    currentXVec = QVector3D(1, 0, 0);
    currentYVec = QVector3D(0, 1, 0);
    currentZVec = QVector3D(0, 0, 1);
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

    return colorsById;
}

QVector<QVector3D> Cube::getColors() const
{
    return colors;
}

void Cube::setToStdColor()
{
    colors.clear();
    colors << frontColors << backColors << leftColors << rightColors << topColors << bottomColors;
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

void Cube::rotateX(int angle)
{
    currentYVec = currentZVec * -1;
    rotation *= QQuaternion::fromAxisAndAngle(currentXVec, angle);
}

void Cube::rotateY(int angle)
{
    rotation *= QQuaternion::fromAxisAndAngle(currentYVec, angle);
}

void Cube::rotateZ(int angle)
{
    rotation *= QQuaternion::fromAxisAndAngle(currentZVec, angle);
}
