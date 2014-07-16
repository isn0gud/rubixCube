#include "rubixcube.h"
#include "windows.h"

/**
 * Values of the sides
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

RubixCube::RubixCube()
{
    int id = 0;
    QVector<QVector<Cube*> > vSides = QVector<QVector<Cube*> >(6, QVector<Cube*>(0));
    for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
            for (int z = -1; z < 2; ++z) {
                cubes << new Cube(id, x, y, z);
                id++;
                //assign cubes to sides
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
        initialSideIds << sides[i]->sideAsIds();
    }
}

QVector<Cube*> RubixCube::getCubes() const
{
    return cubes;
}

QVector<Side*> RubixCube::getSides() const
{
    return sides;
}
//tests if the current side status is equal to the inital sides
bool RubixCube::equalSides(QVector<Side*> _sides) const
{
    QVector<int> currentSideIds;
    foreach(Side * side, _sides)
    {
        currentSideIds << side->sideAsIds();
    }
    bool equal = true;
    for (int i = 0; i < initialSideIds.size(); ++i) {
        if (!(initialSideIds.at(i) == currentSideIds.at(i))) {
            equal = false;
        }
    }
    return equal;
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

//rotates the LEFT and RIGHT side around the x axis
void RubixCube::rotateX(int block, int degree, bool rotPositiv)
{
    QVector<Side*> _sides = getSides(cubes[block]);
    if (_sides.contains(sides[RubixCube::RIGHT])) {

        for (int i = 1; i <= degree; i = i + rotationSpeed) {
            foreach(Cube * cube, sides[RubixCube::RIGHT]->getCubes())
            {
                if (rotPositiv) {
                    cube->rotateX(rotationSpeed);
                } else {
                    cube->rotateX(-rotationSpeed);
                }
            }
            Sleep(sleepTime);
            emit updateGL();
        }
        rotateSide(RubixCube::RIGHT);
        if (!rotPositiv) {
            rotateSide(RubixCube::RIGHT);
            rotateSide(RubixCube::RIGHT);
        }
    } else if (_sides.contains(sides[RubixCube::LEFT])) {
        for (int i = 1; i <= degree; i = i + rotationSpeed) {
            foreach(Cube * cube, sides[RubixCube::LEFT]->getCubes())
            {
                if (rotPositiv) {
                    cube->rotateX(-rotationSpeed);
                } else {
                    cube->rotateX(rotationSpeed);
                }
            }
            Sleep(sleepTime);
            emit updateGL();
        }
        rotateSide(RubixCube::LEFT);
        if (!rotPositiv) {
            rotateSide(RubixCube::LEFT);
            rotateSide(RubixCube::LEFT);
        }
    }
}

void RubixCube::rotateY(int block, int degree, bool rotPositiv)
{
    QVector<Side*> _sides = getSides(cubes[block]);
    if (_sides.contains(sides[RubixCube::TOP])) {
        for (int i = 1; i <= degree; i = i + rotationSpeed) {
            foreach(Cube * cube, sides[RubixCube::TOP]->getCubes())
            {
                if (rotPositiv) {
                    cube->rotateY(rotationSpeed);
                } else {
                    cube->rotateY(-rotationSpeed);
                }
            }
            Sleep(sleepTime);
            emit updateGL();
        }
        rotateSide(RubixCube::TOP);
        if (!rotPositiv) {
            rotateSide(RubixCube::TOP);
            rotateSide(RubixCube::TOP);
        }

    } else if (_sides.contains(sides[RubixCube::DOWN])) {
        for (int i = 1; i <= degree; i = i + rotationSpeed) {
            foreach(Cube * cube, sides[RubixCube::DOWN]->getCubes())
            {
                if (rotPositiv) {
                    cube->rotateY(-rotationSpeed);
                } else {
                    cube->rotateY(rotationSpeed);
                }
            }
            Sleep(sleepTime);
            emit updateGL();
        }
        rotateSide(RubixCube::DOWN);
        if (!rotPositiv) {
            rotateSide(RubixCube::DOWN);
            rotateSide(RubixCube::DOWN);
        }
    }
}

void RubixCube::rotateZ(int block, int degree, bool rotPositiv)
{
    QVector<Side*> _sides = getSides(cubes[block]);

    if (_sides.contains(sides[RubixCube::FRONT])) {
        for (int i = 1; i <= degree; i = i + rotationSpeed) {
            foreach(Cube * cube, sides[RubixCube::FRONT]->getCubes())
            {
                if (rotPositiv) {
                    cube->rotateZ(rotationSpeed);
                } else {
                    cube->rotateZ(-rotationSpeed);
                }
            }
            Sleep(sleepTime);
            emit updateGL();
        }
        rotateSide(RubixCube::FRONT);
        if (!rotPositiv) {
            rotateSide(RubixCube::FRONT);
            rotateSide(RubixCube::FRONT);
        }

    } else if (_sides.contains(sides[RubixCube::BACK])) {

        for (int i = 1; i <= degree; i = i + rotationSpeed) {
            foreach(Cube * cube, sides[RubixCube::BACK]->getCubes())
            {
                if (rotPositiv) {
                    cube->rotateZ(-rotationSpeed);
                } else {
                    cube->rotateZ(rotationSpeed);
                }
            }
            Sleep(sleepTime);
            emit updateGL();
        }
        rotateSide(RubixCube::BACK);
        if (!rotPositiv) {
            rotateSide(RubixCube::BACK);
            rotateSide(RubixCube::BACK);
        }
    }
}
//set cube pinters in adjacent sides after rotation of the singe side
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
    if (equalSides(sides)) {
        emit correctCube();
    } else {
        emit incorrectCube();
    }
}
//rotated cube pointers in a singe side
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
    }
}
