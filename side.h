#ifndef SIDE_H
#define SIDE_H
#include "row.h"

class Side {
private:
    Row* front_row;
    Row* mid_row;
    Row* back_row;

public:
    Side(QVector<Cube*> cubes = QVector<Cube*>(9, 0));
    QVector<Cube*> getCubes();
    QVector<int> sideAsIds();

    Row* getFront_row() const;
    void setFront_row(Row* value);
    Row* getMid_row() const;
    void setMid_row(Row* value);
    Row* getBack_row() const;
    void setBack_row(Row* value);
};

#endif // SIDE_H
