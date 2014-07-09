#include "side.h"

Row* Side::getFront_row() const
{
    return front_row;
}

void Side::setFront_row(Row* value)
{
    front_row = value;
}

Row* Side::getMid_row() const
{
    return mid_row;
}

void Side::setMid_row(Row* value)
{
    mid_row = value;
}

Row* Side::getBack_row() const
{
    return back_row;
}

void Side::setBack_row(Row* value)
{
    back_row = value;
}
Side::Side(QVector<Cube*> cubes)
{
    QVector<Cube*> newCubes;
    for (int i = 0; i < 9; ++i) {
        if (i < 3) {
            newCubes.append(cubes.at(i));
            if (i == 2) {
                front_row = new Row(newCubes);
                newCubes.clear();
            }
        } else if (i < 6) {
            newCubes.append(cubes.at(i));
            if (i == 5) {
                mid_row = new Row(newCubes);
                newCubes.clear();
            }
        } else {
            newCubes.append(cubes.at(i));
            if (i == 8) {
                back_row = new Row(newCubes);
                newCubes.clear();
            }
        }
    }
}

QVector<Cube*> Side::getCubes()
{
    QVector<Cube*> cubes;
    cubes << front_row->getFront_cube() << front_row->getMid_cube() << front_row->getBack_cube()
          << mid_row->getFront_cube() << mid_row->getMid_cube() << mid_row->getBack_cube()
          << back_row->getFront_cube() << back_row->getMid_cube() << back_row->getBack_cube();
    return cubes;
}
