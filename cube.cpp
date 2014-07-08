#include "cube.h"
#include <QDebug>


int Cube::getXAngle() const
{
  return xAngle;
}



int Cube::getYAngle() const
{
  return yAngle;
}

int Cube::getZAngle() const
{
    return yAngle;
}


//QVector<QVector3D> Cube::getFrontColors() const
//{
//    return frontColors;
//}

//void Cube::setFrontColors(const QVector<QVector3D> &value)
//{
//    frontColors = value;
//}

//QVector<QVector3D> Cube::getBackColors() const
//{
//    return backColors;
//}

//void Cube::setBackColors(const QVector<QVector3D> &value)
//{
//    backColors = value;
//}

//QVector<QVector3D> Cube::getLeftColors() const
//{
//    return leftColors;
//}

//void Cube::setLeftColors(const QVector<QVector3D> &value)
//{
//    leftColors = value;
//}

//QVector<QVector3D> Cube::getRightColors() const
//{
//    return rightColors;
//}

//void Cube::setRightColors(const QVector<QVector3D> &value)
//{
//    rightColors = value;
//}

//QVector<QVector3D> Cube::getTopColors() const
//{
//    return topColors;
//}

//void Cube::setTopColors(const QVector<QVector3D> &value)
//{
//    topColors = value;
//}

//QVector<QVector3D> Cube::getBottomColors() const
//{
//    return bottomColors;
//}

//void Cube::setBottomColors(const QVector<QVector3D> &value)
//{
//    bottomColors = value;
//}

int Cube::getId() const
{
    return id;
}

Cube::Cube(int _id , float x, float y , float z)
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

  frontColors << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) // Front
         << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) << QVector3D(0, 0, 0);
        backColors << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) // Back
         << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1);
        leftColors << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) // Left
         << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0);
        rightColors << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right
         << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0);
        topColors << QVector3D(0.5, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) // Top
         << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5);
         bottomColors<< QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom
         << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);
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
    xAngle += angle;
    while (xAngle >= 360) {
        xAngle -= 360;
    }

}

void Cube::rotateY(int angle)
{
    yAngle += angle;
    while (yAngle >= 360) {
        yAngle -= 360;
    }
}

void Cube::rotateZ(int angle)
{
    zAngle += angle;
    while (zAngle >= 360) {
        zAngle -= 360;
    }
}
