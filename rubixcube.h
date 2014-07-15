#ifndef RUBIXCUBE_H
#define RUBIXCUBE_H

#include "cube.h"
#include "side.h"
#include <QObject>

/**
 * @brief RubixCube::RubixCube
 *
 *              5
 *              |
 *         _____V___
 *        /        /|
 *       /   2    / |
 *      /________/3 |
 *  0-> |       |  /
 *      |   1   | /
 *      |_______|/
 *          /\
 *           |
 *          4
 */
class RubixCube : public QObject {
    Q_OBJECT
private:
    QVector<Cube*> cubes;
    QVector<Side*> sides;
    QVector<int> initialSideIds;
    const int rotationSpeed = 10;

public:
    enum SIDENAMES {
        TOP = 2,
        BACK = 5,
        FRONT = 1,
        LEFT = 0,
        DOWN = 4,
        RIGHT = 3
    };
    RubixCube();
    void rotateX(int block, int degree, bool rotPositiv);
    void rotateY(int block, int degree, bool rotPositiv);
    void rotateZ(int block, int degree, bool rotPositiv);
    QVector<Cube*> getCubes() const;
    QVector<Side*> getSides() const;

signals:
    void updateGL();
    void correctCube();
    void incorrectCube();

private:
    bool equalSides(QVector<Side*> _sides) const;
    QVector<Side*> getSides(Cube* cube);
    void rotateSide(RubixCube::SIDENAMES side);
    void rotateSingleSide(RubixCube::SIDENAMES sidename);
//    void outputState();
};

#endif // RUBIXCUBE_H
