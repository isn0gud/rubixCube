#include "cube.h"
#include <QDebug>
#include <QMatrix4x4>
#include <QColor>

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

    for (int i = 0; i < 6; ++i) {
        frontColors << QVector3D(0.6, 0, 0);
    }
    for (int i = 0; i < 6; ++i) {
        backColors << QVector3D(0.9, 0.4, 0);
    }
    for (int i = 0; i < 6; ++i) {
        leftColors << QVector3D(0, 0.4, 0);
    }
    for (int i = 0; i < 6; ++i) {
        rightColors << QVector3D(0, 0, 0.4);
    }
    for (int i = 0; i < 6; ++i) {
        topColors << QVector3D(0.9, 0.9, 0.9);
    }
    for (int i = 0; i < 6; ++i) {
        bottomColors << QVector3D(0.8, 0.8, 0);
    }
    setToStdColor();
    //    qDebug() << (id & 0x000000FF) / 255.0f << endl;
    for (int i = 0; i < 36; ++i) {
        colorsById << QVector3D(id / 255.0f, id / 255.0f, id / 255.0f);
    }

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
    //    xAngle += angle;
    //    xAngle = xAngle % 360;
    //    if (xAngle % 360 == 0 && angle >) {

    //      } else {
    //      }

    //    QMatrix4x4 rotMatrix;
    //    rotMatrix.rotate(angle, currentXVec);
    //    currentXVec = rotMatrix.map(QVector3D(1, 0, 0));

    rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), angle) * rotation;
}

void Cube::rotateY(int angle)
{
    //    QMatrix4x4 rotMatrix;
    //    rotMatrix.rotate(angle, currentYVec);
    //    currentYVec = rotMatrix.map(QVector3D(0, 1, 0));
    rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), angle) * rotation;
}

void Cube::rotateZ(int angle)
{
    //    QMatrix4x4 rotMatrix;
    //    rotMatrix.rotate(angle, currentZVec);
    //    currentZVec = rotMatrix.map(QVector3D(0, 0, 1));
    rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), angle) * rotation;
}
