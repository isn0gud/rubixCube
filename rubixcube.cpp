#include "rubixcube.h"

RubixCube::RubixCube()
{
    for (int i = 0; i<3; i++)
      for (int j = 0; j<3; j++)
        for (int k = 0; k<3; k++)
          rCube[i][j][k] = new Cube();
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
