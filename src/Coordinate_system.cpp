#include <CNelder_mead_method.h>
#include "Coordinate_system.h"
#include <algorithm>
#include <iostream>

void Coordinate_system::round(Point &point){
    auto it_b = _x_coordinate.begin();
    auto it_e = _x_coordinate.end();

    while(it_b != it_e){
        if(*it_b >= point["x"]){
            point["x"] = *it_b;
            break;
        }
        it_b++;
        if(it_b == it_e){
            point["x"] = _x_coordinate.back();
            break;
        }
    }

    it_b = _y_coordinate.begin();
    it_e = _y_coordinate.end();

    while(it_b != it_e){
        if(*it_b >= point["y"]){
            point["y"] = *it_b;
            break;
        }
        it_b++;
        if(it_b == it_e){
            point["y"] = _y_coordinate.back();
            break;
        }
    }

//    std::cout << "\nx = " << point["x"] << " y = " << point["y"] << std::endl;
}