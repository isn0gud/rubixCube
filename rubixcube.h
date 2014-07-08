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
class RubixCube
{
private:
 QVector<Cube*> cubes;
 QVector<Side*> sides;
public:
  RubixCube();
  void rotateX(int block, int degree);
  void rotateY(int block, int degree);
  void rotateZ(int block, int degree);
  QVector<Cube *> getCubes() const;

private:
  QVector<Side*> getSides(Cube* cube);

};

#endif // RUBIXCUBE_H
