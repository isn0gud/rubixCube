#ifndef CUBE_H
#define CUBE_H

#include <QVector>
#include <QVector3D>

class Cube {
private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;

    QVector<QVector3D> frontColors;
    QVector<QVector3D> backColors;
    QVector<QVector3D> leftColors;
    QVector<QVector3D> rightColors;
    QVector<QVector3D> topColors;
    QVector<QVector3D> bottomColors;

    QVector<QVector3D> colorsById;
    int id;
    int xAngle = 0;
    int yAngle = 0;
    int zAngle = 0;
    QVector3D position;

public:
    enum axis { X, Y, Z};
    Cube(int _id = 1, int x = 0, int y = 0, int z = 0);
    QVector<QVector3D> getVertices() const;
    QVector<QVector3D> getColorVectorById() const;
    QVector<QVector3D> getColors() const;
    void setToStdColor();
    void setColorHighlight();

    int getId() const;

    QVector3D getPosition() const;

    int getXAngle() const;

    int getYAngle() const;
    int getZAngle() const;



    QVector<QVector3D> getFrontColors() const;
    void setFrontColors(const QVector<QVector3D> &value);

    QVector<QVector3D> getBackColors() const;
    void setBackColors(const QVector<QVector3D> &value);

    QVector<QVector3D> getLeftColors() const;
    void setLeftColors(const QVector<QVector3D> &value);

    QVector<QVector3D> getRightColors() const;
    void setRightColors(const QVector<QVector3D> &value);

    QVector<QVector3D> getTopColors() const;
    void setTopColors(const QVector<QVector3D> &value);

    QVector<QVector3D> getBottomColors() const;
    void setBottomColors(const QVector<QVector3D> &value);

private:
};

#endif // CUBE_H
