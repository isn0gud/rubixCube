#ifndef RUBIXCUBE_H
#define RUBIXCUBE_H

#include "cube.h"
#include "side.h"

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
class RubixCube {
private:
    QVector<Cube*> cubes;
    QVector<Side*> sides;

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
    void rotateX(int block, int degree);
    void rotateY(int block, int degree);
    void rotateZ(int block, int degree);
    QVector<Cube*> getCubes() const;

private:
    QVector<Side*> getSides(Cube* cube);
    void rotateSide(RubixCube::SIDENAMES side);
    void rotateSingleSide(RubixCube::SIDENAMES sidename);
    void outputState();
};

#endif // RUBIXCUBE_H
