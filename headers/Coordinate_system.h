#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

#include "CNelder_mead_method.h"
#include "Point.h"

class Coordinate_system {
private:
    const std::vector<double> _x_coordinate{-7, -6.5, -6, -5.5, -5, -4, -3.5, -3, -2, -1,
                                            0, 1, 2, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7};
    const std::vector<double> _y_coordinate{-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10};
public:
    Coordinate_system(){};
    void round(Point &point);
};


#endif //COORDINATE_SYSTEM_H
