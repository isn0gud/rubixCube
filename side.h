#ifndef SIDE_H
#define SIDE_H
#include "row.h"

class Side
{
private:
    Row front_row;
    Row mid_row;
    Row back_row;
public:
    Side(QVector<Cube* > cubes = QVector<Cube*>(9,0));
    QVector<Cube *> getCubes();
};

#endif // SIDE_H
