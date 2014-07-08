#ifndef ROW_H
#define ROW_H
#include "cube.h"

class Row
{
private:
    Cube* front_cube;
    Cube* mid_cube;
    Cube* back_cube;

public:
    Row(QVector<Cube*> cubes = QVector<Cube*>(3,0));

    Cube *getFront_cube() const;
    void setFront_cube(Cube *value);
    Cube *getMid_cube() const;
    void setMid_cube(Cube *value);
    Cube *getBack_cube() const;
    void setBack_cube(Cube *value);
};

#endif // ROW_H
