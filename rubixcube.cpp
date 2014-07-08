#include "rubixcube.h"
#include <QDebug>

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


QVector<Cube *> RubixCube::getCubes() const
{
    return cubes;
}

QVector<Side*> RubixCube::getSides(Cube* cube)
{
    QVector<Side*> _sides;
    foreach (Side* side, sides) {
        if (side->getCubes().contains(cube)) {
            _sides.append(side);
        }
    }
    return _sides;
}

RubixCube::RubixCube()
{
    int id = 0;
    QVector<QVector<Cube*> > vSides = QVector<QVector<Cube*> >(6,QVector<Cube*>(0));
    for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
            for (int z = -1; z < 2; ++z) {
                cubes << new Cube(id, x, y, z);
                id++;
                if (x == -1) {
                    Cube* cube = cubes.back();
                    vSides[0].append(cube);
                }
                if (y == -1) {
                    vSides[4].append(cubes.back());
                }
                if (z == -1) {
                    vSides[5].append(cubes.back());
                }
                if (x == 1) {
                    vSides[3].append(cubes.back());
                }
                if (y == 1) {
                    vSides[2].append(cubes.back());
                }
                if (z == 1) {
                    vSides[1].append(cubes.back());
                }

            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        sides.append(new Side(vSides[i]));
    }

}

void RubixCube::rotateX(int block, int degree)
{
    QVector<Side*> _sides = getSides(cubes[block]);

    if (_sides.contains(sides[3])) {
        foreach (Cube* cube, sides[3]->getCubes()) {
            cube->rotateX(degree);
        }
    }else if (_sides.contains(sides[0])) {
        foreach (Cube* cube, sides[0]->getCubes()) {
            cube->rotateX(degree);
        }
    }
}

void RubixCube::rotateY(int block, int degree)
{
    QVector<Side*> _sides = getSides(cubes[block]);

    if (_sides.contains(sides[2])) {
        foreach (Cube* cube, sides[2]->getCubes()) {
            cube->rotateY(degree);
        }
    }else if (_sides.contains(sides[4])) {
        foreach (Cube* cube, sides[4]->getCubes()) {
            cube->rotateY(degree);
        }
    }
}

void RubixCube::rotateZ(int block, int degree)
{
    foreach (Cube* cube, sides[2]->getCubes()) {
        cube->rotateZ(degree);
    }
}
//void RubixCube::rotateX(int block, int degree){
//  for (int i = 0;i<3;i++){
//    if (roty[i]!=0) return;
//    if (rotz[i]!=0) return;
//  }
//  rotx[block] += degree;

//  if ((degree<0)&&(rotx[block]==-90)){
//    rotx[block]=0;

//    Cube *tmp = rCube[block][0][0];
//    rCube[block][0][0] = rCube[block][2][0];
//    rCube[block][2][0] = rCube[block][2][2];
//    rCube[block][2][2] = rCube[block][0][2];
//    rCube[block][0][2] = tmp;

//    tmp = rCube[block][1][0];
//    rCube[block][1][0] = rCube[block][2][1];
//    rCube[block][2][1] = rCube[block][1][2];
//    rCube[block][1][2] = rCube[block][0][1];
//    rCube[block][0][1] = tmp;

//    for (int j = 0; j<3; j++)
//      for (int k = 0; k<3; k++)
//    rCube[block][j][k]->rotate(Cube::Xaxis, false);

//  }

//  if ((degree>0)&&(rotx[block] == 90)){
//    rotx[block] = 0;
//    Cube *tmp = rCube[block][0][2];
//    rCube[block][0][2] = rCube[block][2][2];
//    rCube[block][2][2] = rCube[block][2][0];
//    rCube[block][2][0] = rCube[block][0][0];
//    rCube[block][0][0] = tmp;

//    tmp = rCube[block][0][1];
//    rCube[block][0][1] = rCube[block][1][2];
//    rCube[block][1][2] = rCube[block][2][1];
//    rCube[block][2][1] = rCube[block][1][0];
//    rCube[block][1][0] = tmp;

//    for (int j = 0; j<3; j++)
//      for (int k = 0; k<3; k++)
//    rCube[block][j][k]->rotate(Cube::Xaxis, true);
//  }

//  if ((rotx[0]==rotx[1] || rotx[0]==rotx[1]-90 || rotx[0]==rotx[1]+90)
//      &&(rotx[1]== rotx[2] || rotx[1]==rotx[2]-90 || rotx[1]==rotx[2]+90))
//    {
//      rotationX +=rotx[0];
//      rotx[0]=rotx[1]=rotx[2]=0;
//    }
//}


//void RubixCube::rotateY(int block, int degree){
//  for (int i = 0;i<3;i++){
//    if (rotx[i]!=0) return;
//    if (rotz[i]!=0) return;
//  }
//  roty[block] += degree;

//  if ((degree<0)&&(roty[block]==-90)){
//    roty[block]=0;
//    Cube *tmp  = rCube[0][block][2];
//    rCube[0][block][2] = rCube[2][block][2];
//    rCube[2][block][2] = rCube[2][block][0];
//    rCube[2][block][0] = rCube[0][block][0];
//    rCube[0][block][0] = tmp;

//    tmp = rCube[0][block][1];
//    rCube[0][block][1] = rCube[1][block][2];
//    rCube[1][block][2] = rCube[2][block][1];
//    rCube[2][block][1] = rCube[1][block][0];
//    rCube[1][block][0] = tmp;

//    for (int i = 0; i<3; i++)
//      for (int k = 0; k<3; k++)
//    rCube[i][block][k]->rotate(Cube::Yaxis, false);

//  }

//  if ((degree>0)&&(roty[block] == 90)){
//    roty[block] = 0;
//    Cube *tmp = rCube[0][block][0];
//    rCube[0][block][0] = rCube[2][block][0];
//    rCube[2][block][0] = rCube[2][block][2];
//    rCube[2][block][2] = rCube[0][block][2];
//    rCube[0][block][2] = tmp;

//    tmp = rCube[1][block][0];
//    rCube[1][block][0] = rCube[2][block][1];
//    rCube[2][block][1] = rCube[1][block][2];
//    rCube[1][block][2] = rCube[0][block][1];
//    rCube[0][block][1] = tmp;

//    for (int i = 0; i<3; i++)
//      for (int k = 0; k<3; k++)
//    rCube[i][block][k]->rotate(Cube::Yaxis, true);
//  }

//  if ((roty[0]==roty[1] || roty[0]==roty[1]-90 || roty[0]==roty[1]+90)
//      &&(roty[1]== roty[2] || roty[1]==roty[2]-90 || roty[1]==roty[2]+90))
//    {
//      rotationY +=roty[0];
//      roty[0]=roty[1]=roty[2]=0;
//    }
//}

//void RubixCube::rotateZ(int block, int degree){
//  for (int i = 0;i<3;i++){
//    if (roty[i]!=0) return;
//    if (rotx[i]!=0) return;
//  }
//  rotz[block] += degree;

//  if ((degree<0)&&(rotz[block]==-90)){
//    rotz[block]=0;

//    Cube *tmp = rCube[0][0][block];
//    rCube[0][0][block]   = rCube[2][0][block];
//    rCube[2][0][block]   = rCube[2][2][block];
//    rCube[2][2][block]   = rCube[0][2][block];
//    rCube[0][2][block]   = tmp;

//    tmp            = rCube[1][0][block];
//    rCube[1][0][block] = rCube[2][1][block];
//    rCube[2][1][block] = rCube[1][2][block];
//    rCube[1][2][block] = rCube[0][1][block];
//    rCube[0][1][block] = tmp;

//    for (int i = 0; i<3; i++)
//      for (int j = 0; j<3; j++)
//    rCube[i][j][block]->rotate(Cube::Zaxis, false);

//  }

//  if ((degree>0)&&(rotz[block] == 90)){
//    rotz[block] = 0;

//    Cube *tmp = rCube[0][2][block];
//    rCube[0][2][block] = rCube[2][2][block];
//    rCube[2][2][block] = rCube[2][0][block];
//    rCube[2][0][block] = rCube[0][0][block];
//    rCube[0][0][block] = tmp;

//    tmp = rCube[0][1][block];
//    rCube[0][1][block] = rCube[1][2][block];
//    rCube[1][2][block] = rCube[2][1][block];
//    rCube[2][1][block] = rCube[1][0][block];
//    rCube[1][0][block] = tmp;

//    for (int i = 0; i<3; i++)
//      for (int j = 0; j<3; j++)
//    rCube[i][j][block]->rotate(Cube::Zaxis, true);
//  }

//  if ((rotz[0]==rotz[1] || rotz[0]==rotz[1]-90 || rotz[0]==rotz[1]+90)
//      &&(rotz[1]== rotz[2] || rotz[1]==rotz[2]-90 || rotz[1]==rotz[2]+90))
//    {
//      rotationZ +=rotz[0];
//      rotz[0]=rotz[1]=rotz[2]=0;
//    }
//}
