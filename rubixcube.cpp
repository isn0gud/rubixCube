#include "rubixcube.h"
//#include <QDebug>

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

QVector<Cube*> RubixCube::getCubes() const
{
    return cubes;
}

QVector<Side*> RubixCube::getSides(Cube* cube)
{
    QVector<Side*> _sides;
    foreach(Side * side, sides)
    {
        if (side->getCubes().contains(cube)) {
            _sides.append(side);
        }
    }
    return _sides;
}

RubixCube::RubixCube()
{
    int id = 0;
    QVector<QVector<Cube*> > vSides = QVector<QVector<Cube*> >(6, QVector<Cube*>(0));
    for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
            for (int z = -1; z < 2; ++z) {
                cubes << new Cube(id, x, y, z);
                id++;
                if (x == -1) {
                    Cube* cube = cubes.back();
                    vSides[RubixCube::LEFT].append(cube);
                }
                if (y == -1) {
                    vSides[RubixCube::DOWN].append(cubes.back());
                }
                if (z == -1) {
                    vSides[RubixCube::BACK].append(cubes.back());
                }
                if (x == 1) {
                    vSides[RubixCube::RIGHT].append(cubes.back());
                }
                if (y == 1) {
                    vSides[RubixCube::TOP].append(cubes.back());
                }
                if (z == 1) {
                    vSides[RubixCube::FRONT].append(cubes.back());
                }
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        sides.append(new Side(vSides[i]));
    }
//    outputState();
}

void RubixCube::rotateX(int block, int degree)
{
    QVector<Side*> _sides = getSides(cubes[block]);

    if (_sides.contains(sides[RubixCube::RIGHT])) {
        foreach(Cube * cube, sides[RubixCube::RIGHT]->getCubes())
        {
            cube->rotateX(degree);
        }
        rotateSide(RubixCube::RIGHT);

    } else if (_sides.contains(sides[RubixCube::LEFT])) {
        degree *= -1;
        foreach(Cube * cube, sides[RubixCube::LEFT]->getCubes())
        {
            cube->rotateX(degree);
        }
        rotateSide(RubixCube::LEFT);
    }
}

void RubixCube::rotateY(int block, int degree)
{
    //    cubes[block]->rotateY(degree);
    QVector<Side*> _sides = getSides(cubes[block]);

    if (_sides.contains(sides[RubixCube::TOP])) {
        foreach(Cube * cube, sides[RubixCube::TOP]->getCubes())
        {
            cube->rotateY(degree);
        }
        rotateSide(RubixCube::TOP);

    } else if (_sides.contains(sides[RubixCube::DOWN])) {
        degree *= -1;
        foreach(Cube * cube, sides[RubixCube::DOWN]->getCubes())
        {
            cube->rotateY(degree);
        }
        //        foreach(Cube * cube, sides[DOWN]->getCubes())
        //        {
        //            qDebug() << cube->getId();
        //        }
        //        qDebug() << "+++++";
        rotateSide(RubixCube::DOWN);
        //        foreach(Cube * cube, sides[DOWN]->getCubes())
        //        {
        //            qDebug() << cube->getId();
        //        }
        //        qDebug() << "+++++";
    }
}

void RubixCube::rotateZ(int block, int degree)
{
    QVector<Side*> _sides = getSides(cubes[block]);

    if (_sides.contains(sides[RubixCube::FRONT])) {

        foreach(Cube * cube, sides[RubixCube::FRONT]->getCubes())
        {
            cube->rotateZ(degree);
        }
        rotateSide(RubixCube::FRONT);

    } else if (_sides.contains(sides[RubixCube::BACK])) {
        degree *= -1;
        foreach(Cube * cube, sides[RubixCube::BACK]->getCubes())
        {
            cube->rotateZ(degree);
        }
        rotateSide(RubixCube::BACK);
    }
}

void RubixCube::rotateSide(RubixCube::SIDENAMES side)
{
    rotateSingleSide(side);

    switch (side) {
    case FRONT:
        sides[TOP]->getFront_row()->setBack_cube(sides[side]->getFront_row()->getBack_cube());
        sides[TOP]->getMid_row()->setBack_cube(sides[side]->getMid_row()->getBack_cube());
        sides[TOP]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[RIGHT]->getFront_row()->setBack_cube(sides[side]->getBack_row()->getFront_cube());
        sides[RIGHT]->getMid_row()->setBack_cube(sides[side]->getBack_row()->getMid_cube());
        sides[RIGHT]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[LEFT]->getFront_row()->setBack_cube(sides[side]->getFront_row()->getFront_cube());
        sides[LEFT]->getMid_row()->setBack_cube(sides[side]->getFront_row()->getMid_cube());
        sides[LEFT]->getBack_row()->setBack_cube(sides[side]->getFront_row()->getBack_cube());

        sides[DOWN]->getFront_row()->setBack_cube(sides[side]->getFront_row()->getFront_cube());
        sides[DOWN]->getMid_row()->setBack_cube(sides[side]->getMid_row()->getFront_cube());
        sides[DOWN]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getFront_cube());

        break;
    case BACK:
        sides[TOP]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getBack_cube());
        sides[TOP]->getMid_row()->setFront_cube(sides[side]->getMid_row()->getBack_cube());
        sides[TOP]->getBack_row()->setFront_cube(sides[side]->getBack_row()->getBack_cube());

        sides[RIGHT]->getFront_row()->setFront_cube(sides[side]->getBack_row()->getFront_cube());
        sides[RIGHT]->getMid_row()->setFront_cube(sides[side]->getBack_row()->getMid_cube());
        sides[RIGHT]->getBack_row()->setFront_cube(sides[side]->getBack_row()->getBack_cube());

        sides[LEFT]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[LEFT]->getMid_row()->setFront_cube(sides[side]->getFront_row()->getMid_cube());
        sides[LEFT]->getBack_row()->setFront_cube(sides[side]->getFront_row()->getBack_cube());

        sides[DOWN]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[DOWN]->getMid_row()->setFront_cube(sides[side]->getMid_row()->getFront_cube());
        sides[DOWN]->getBack_row()->setFront_cube(sides[side]->getBack_row()->getFront_cube());

        break;
    case LEFT:

        sides[TOP]->getFront_row()->setFront_cube(sides[side]->getBack_row()->getFront_cube());
        sides[TOP]->getFront_row()->setMid_cube(sides[side]->getBack_row()->getMid_cube());
        sides[TOP]->getFront_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[FRONT]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getBack_cube());
        sides[FRONT]->getFront_row()->setMid_cube(sides[side]->getMid_row()->getBack_cube());
        sides[FRONT]->getFront_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[BACK]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[BACK]->getFront_row()->setMid_cube(sides[side]->getMid_row()->getFront_cube());
        sides[BACK]->getFront_row()->setBack_cube(sides[side]->getBack_row()->getFront_cube());

        sides[DOWN]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[DOWN]->getFront_row()->setMid_cube(sides[side]->getFront_row()->getMid_cube());
        sides[DOWN]->getFront_row()->setBack_cube(sides[side]->getFront_row()->getBack_cube());

        break;
    case RIGHT:

        sides[TOP]->getBack_row()->setFront_cube(sides[side]->getBack_row()->getFront_cube());
        sides[TOP]->getBack_row()->setMid_cube(sides[side]->getBack_row()->getMid_cube());
        sides[TOP]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[FRONT]->getBack_row()->setFront_cube(sides[side]->getFront_row()->getBack_cube());
        sides[FRONT]->getBack_row()->setMid_cube(sides[side]->getMid_row()->getBack_cube());
        sides[FRONT]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[BACK]->getBack_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[BACK]->getBack_row()->setMid_cube(sides[side]->getMid_row()->getFront_cube());
        sides[BACK]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getFront_cube());

        sides[DOWN]->getBack_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[DOWN]->getBack_row()->setMid_cube(sides[side]->getFront_row()->getMid_cube());
        sides[DOWN]->getBack_row()->setBack_cube(sides[side]->getFront_row()->getBack_cube());

        break;
    case TOP:

        sides[RIGHT]->getBack_row()->setFront_cube(sides[side]->getBack_row()->getFront_cube());
        sides[RIGHT]->getBack_row()->setMid_cube(sides[side]->getBack_row()->getMid_cube());
        sides[RIGHT]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[FRONT]->getFront_row()->setBack_cube(sides[side]->getFront_row()->getBack_cube());
        sides[FRONT]->getMid_row()->setBack_cube(sides[side]->getMid_row()->getBack_cube());
        sides[FRONT]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[BACK]->getFront_row()->setBack_cube(sides[side]->getFront_row()->getFront_cube());
        sides[BACK]->getMid_row()->setBack_cube(sides[side]->getMid_row()->getFront_cube());
        sides[BACK]->getBack_row()->setBack_cube(sides[side]->getBack_row()->getFront_cube());

        sides[LEFT]->getBack_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[LEFT]->getBack_row()->setMid_cube(sides[side]->getFront_row()->getMid_cube());
        sides[LEFT]->getBack_row()->setBack_cube(sides[side]->getFront_row()->getBack_cube());

        break;
    case DOWN:

        sides[RIGHT]->getFront_row()->setFront_cube(sides[side]->getBack_row()->getFront_cube());
        sides[RIGHT]->getFront_row()->setMid_cube(sides[side]->getBack_row()->getMid_cube());
        sides[RIGHT]->getFront_row()->setBack_cube(sides[side]->getBack_row()->getBack_cube());

        sides[FRONT]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getBack_cube());
        sides[FRONT]->getMid_row()->setFront_cube(sides[side]->getMid_row()->getBack_cube());
        sides[FRONT]->getBack_row()->setFront_cube(sides[side]->getBack_row()->getBack_cube());

        sides[BACK]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[BACK]->getMid_row()->setFront_cube(sides[side]->getMid_row()->getFront_cube());
        sides[BACK]->getBack_row()->setFront_cube(sides[side]->getBack_row()->getFront_cube());

        sides[LEFT]->getFront_row()->setFront_cube(sides[side]->getFront_row()->getFront_cube());
        sides[LEFT]->getFront_row()->setMid_cube(sides[side]->getFront_row()->getMid_cube());
        sides[LEFT]->getFront_row()->setBack_cube(sides[side]->getFront_row()->getBack_cube());

        break;
    }
//    outputState();
}

void RubixCube::rotateSingleSide(RubixCube::SIDENAMES sidename)
{
    Side* side = sides[sidename];
    if (sidename == DOWN || sidename == FRONT || sidename == RIGHT) {
        Cube* tmpFrontFront = side->getFront_row()->getFront_cube();
        Cube* tmpFrontMid = side->getFront_row()->getMid_cube();

        side->getFront_row()->setFront_cube(side->getFront_row()->getBack_cube());
        side->getFront_row()->setMid_cube(side->getMid_row()->getBack_cube());
        side->getFront_row()->setBack_cube(side->getBack_row()->getBack_cube());
        side->getMid_row()->setBack_cube(side->getBack_row()->getMid_cube());
        side->getBack_row()->setBack_cube(side->getBack_row()->getFront_cube());
        side->getBack_row()->setMid_cube(side->getMid_row()->getFront_cube());
        side->getBack_row()->setFront_cube(tmpFrontFront);
        side->getMid_row()->setFront_cube(tmpFrontMid);
    } else {

        Cube* tmpFrontFront = side->getFront_row()->getFront_cube();
        Cube* tmpFrontMid = side->getFront_row()->getMid_cube();

        side->getFront_row()->setFront_cube(side->getBack_row()->getFront_cube());
        side->getFront_row()->setMid_cube(side->getMid_row()->getFront_cube());
        side->getMid_row()->setFront_cube(side->getBack_row()->getMid_cube());
        side->getBack_row()->setFront_cube(side->getBack_row()->getBack_cube());
        side->getBack_row()->setMid_cube(side->getMid_row()->getBack_cube());
        side->getBack_row()->setBack_cube(side->getFront_row()->getBack_cube());
        side->getMid_row()->setBack_cube(tmpFrontMid);
        side->getFront_row()->setBack_cube(tmpFrontFront);

        //        side->getFront_row()->setBack_cube(side->getFront_row()->getFront_cube());
        //        side->getFront_row()->setMid_cube(side->getMid_row()->getFront_cube());
        //        side->getFront_row()->setFront_cube(side->getBack_row()->getFront_cube());
        //        side->getMid_row()->setFront_cube(side->getBack_row()->getMid_cube());
        //        side->getBack_row()->setFront_cube(side->getBack_row()->getBack_cube());
        //        side->getBack_row()->setMid_cube(side->getMid_row()->getBack_cube());
        //        side->getBack_row()->setBack_cube(tmpFrontFront);
        //        side->getMid_row()->setBack_cube(tmpFrontMid);
    }
}

//void RubixCube::outputState()
//{

//    qDebug() << "++++++++++++++++++++" << endl
//             << "\t" << sides[BACK]->getFront_row()->getFront_cube()->getId() << sides[BACK]->getMid_row()->getFront_cube()->getId() << sides[BACK]->getBack_row()->getFront_cube()->getId() << endl //BACK
//             << "\t" << sides[BACK]->getFront_row()->getMid_cube()->getId() << sides[BACK]->getMid_row()->getMid_cube()->getId() << sides[BACK]->getBack_row()->getMid_cube()->getId() << endl
//             << "\t" << sides[BACK]->getFront_row()->getBack_cube()->getId() << sides[BACK]->getMid_row()->getBack_cube()->getId() << sides[BACK]->getBack_row()->getBack_cube()->getId() << endl << endl
//             << "\t" << sides[TOP]->getFront_row()->getFront_cube()->getId() << sides[TOP]->getMid_row()->getFront_cube()->getId() << sides[TOP]->getBack_row()->getFront_cube()->getId() << endl //BACK
//             << "\t" << sides[TOP]->getFront_row()->getMid_cube()->getId() << sides[TOP]->getMid_row()->getMid_cube()->getId() << sides[TOP]->getBack_row()->getMid_cube()->getId() << endl
//             << "\t" << sides[TOP]->getFront_row()->getBack_cube()->getId() << sides[TOP]->getMid_row()->getBack_cube()->getId() << sides[TOP]->getBack_row()->getBack_cube()->getId() << endl << endl
//             << sides[LEFT]->getBack_row()->getFront_cube()->getId() << sides[LEFT]->getBack_row()->getMid_cube()->getId() << sides[LEFT]->getBack_row()->getBack_cube()->getId() << /*LEFT*/ "\t" << sides[FRONT]->getFront_row()->getBack_cube()->getId() << sides[FRONT]->getMid_row()->getBack_cube()->getId() << sides[FRONT]->getBack_row()->getBack_cube()->getId() << "\t" << sides[RIGHT]->getBack_row()->getBack_cube()->getId() << sides[RIGHT]->getBack_row()->getMid_cube()->getId() << sides[RIGHT]->getBack_row()->getFront_cube()->getId() << endl
//             << sides[LEFT]->getMid_row()->getFront_cube()->getId() << sides[LEFT]->getMid_row()->getMid_cube()->getId() << sides[LEFT]->getMid_row()->getBack_cube()->getId() << /*LEFT*/ "\t" << sides[FRONT]->getFront_row()->getMid_cube()->getId() << sides[FRONT]->getMid_row()->getMid_cube()->getId() << sides[FRONT]->getBack_row()->getMid_cube()->getId() << "\t" << sides[RIGHT]->getMid_row()->getBack_cube()->getId() << sides[RIGHT]->getMid_row()->getMid_cube()->getId() << sides[RIGHT]->getMid_row()->getFront_cube()->getId() << endl
//             << sides[LEFT]->getFront_row()->getFront_cube()->getId() << sides[LEFT]->getFront_row()->getMid_cube()->getId() << sides[LEFT]->getFront_row()->getBack_cube()->getId() << /*LEFT*/ "\t" << sides[FRONT]->getFront_row()->getFront_cube()->getId() << sides[FRONT]->getMid_row()->getFront_cube()->getId() << sides[FRONT]->getBack_row()->getFront_cube()->getId() << "\t" << sides[RIGHT]->getFront_row()->getBack_cube()->getId() << sides[RIGHT]->getFront_row()->getMid_cube()->getId() << sides[RIGHT]->getFront_row()->getFront_cube()->getId() << endl << endl
//             << "\t" << sides[DOWN]->getFront_row()->getBack_cube()->getId() << sides[DOWN]->getMid_row()->getBack_cube()->getId() << sides[DOWN]->getBack_row()->getBack_cube()->getId() << endl
//             << "\t" << sides[DOWN]->getFront_row()->getMid_cube()->getId() << sides[DOWN]->getMid_row()->getMid_cube()->getId() << sides[DOWN]->getBack_row()->getMid_cube()->getId() << endl
//             << "\t" << sides[DOWN]->getFront_row()->getFront_cube()->getId() << sides[DOWN]->getMid_row()->getFront_cube()->getId() << sides[DOWN]->getBack_row()->getFront_cube()->getId() << endl;
//}
