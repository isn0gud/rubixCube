#include "side.h"

Side::Side(QVector<Cube*> cubes)
{
    QVector<Cube*> newCubes;
    for (int i = 0; i < 9; ++i) {
        if (i < 3) {
            newCubes.append(cubes.at(i));
            if (i == 2) {
                front_row = Row(newCubes);
                newCubes.clear();
            }
        } else if(i < 6){
            newCubes.append(cubes.at(i));
            if (i == 5) {
                mid_row = Row(newCubes);
                newCubes.clear();
            }
        } else{
            newCubes.append(cubes.at(i));
            if (i == 8) {
                back_row = Row(newCubes);
                newCubes.clear();
            }
        }
    }
}

QVector<Cube *> Side::getCubes()
{
 QVector<Cube*> cubes;
    cubes << front_row.getFront_cube() << front_row.getMid_cube() << front_row.getBack_cube()
             << mid_row.getFront_cube() << mid_row.getMid_cube() << mid_row.getBack_cube()
                << back_row.getFront_cube() << back_row.getMid_cube() << back_row.getBack_cube();
    return cubes;
}
