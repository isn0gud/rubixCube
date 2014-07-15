#ifndef CUBE_H
#define CUBE_H

#include <QVector>
#include <QVector3D>
#include <QQuaternion>
#include <QColor>

class Cube {
private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
    int id;
    QQuaternion rotation;
    QVector3D position;

public:
    Cube(int _id = 1, float x = 0, float y = 0, float z = 0);
    QVector<QVector3D> getVertices() const;
    QVector<QVector3D> getColorVectorById() const;
    QVector<QVector3D> getColors() const;
    void setToStdColor();
    void setColorHighlight();
    QVector3D getPosition() const;
    void rotateX(int angle);
    void rotateY(int angle);
    void rotateZ(int angle);
    int getId() const;
    QQuaternion getRotation() const;
//    void setToColor(QColor color);

private:
};

#endif // CUBE_H
