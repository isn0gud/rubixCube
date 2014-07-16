#include "row.h"

Cube* Row::getFront_cube() const
{
    return front_cube;
}

void Row::setFront_cube(Cube* value)
{
    front_cube = value;
}

Cube* Row::getMid_cube() const
{
    return mid_cube;
}

void Row::setMid_cube(Cube* value)
{
    mid_cube = value;
}

Cube* Row::getBack_cube() const
{
    return back_cube;
}

void Row::setBack_cube(Cube* value)
{
    back_cube = value;
}
Row::Row(QVector<Cube*> cubes)
{
    front_cube = cubes[0];
    mid_cube = cubes[1];
    back_cube = cubes[2];
}
