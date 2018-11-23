#ifndef NELDER_MEAD_CNELDER_MEAD_METHOD_H
#define NELDER_MEAD_CNELDER_MEAD_METHOD_H

#include <map>
#include <vector>
#include <Coordinate_system.h>
#include <Point.h>

class CNelder_mead_method : public Coordinate_system{
private:
    Point _middle;
    std::vector<Point> _points;
    const double _alpha;
    const double _beta;
    const double _gamma;
    const size_t _limit;
    const size_t _dimensions;
    size_t _attempts = 0;
    double _avg_profit;
    double _eps = 0.1;
    std::vector<std::string> _param = {"x", "y"};

    void start_points_generation();

    void middle();

    bool reflection();

    bool expansion(Point &old_point);

    void compress();

    void sort();

    double profit(Point point);

    void sum();

public:

    CNelder_mead_method(double alpha, double beta, double gamma, size_t limit, Point start_point, size_t dimensions);

    Point nelder_mead_method();

    void debug(std::vector<Point> &points, Point middle, size_t);
};


#endif //NELDER_MEAD_CNELDER_MEAD_METHOD_H
