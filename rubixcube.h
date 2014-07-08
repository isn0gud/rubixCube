#ifndef RUBIXCUBE_H
#define RUBIXCUBE_H

#include "cube.h"

class RubixCube
{
private:
    Cube *rCube[3][3][3];

    double rotationX;
    double rotationY;
    double rotationZ;
    double rotx[3];
    double roty[3];
    double rotz[3];
public:
  RubixCube();
  void rotateX(int block, int degree);
  void rotateY(int block, int degree);
  void rotateZ(int block, int degree);


};

#endif // RUBIXCUBE_H
