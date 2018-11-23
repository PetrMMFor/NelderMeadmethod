#include "CNelder_mead_method.h"
#include <iostream>
#include <cmath>
#include <utility>

CNelder_mead_method::CNelder_mead_method(double alpha, double beta, double gamma, size_t limit, Point start_point,
                                         size_t dimensions)
        : _alpha(alpha), _beta(beta), _gamma(gamma), _limit(limit), _dimensions(dimensions) {
    start_point.emplace("profit", profit(start_point));
    _points.push_back(start_point);
};

void CNelder_mead_method::debug(std::vector<Point> &points, Point middle, size_t cnt) {

    auto it_begin = _points.begin();

    std::cout << "cnt = " << cnt << std::endl;

    std::cout << "best:\n" << "\t\"x\":" << (*it_begin)["x"] << std::endl;
    std::cout << "\t\"y\":" << (*it_begin)["y"] << std::endl;
    std::cout << "\t\"profit\":" << (*it_begin++)["profit"] << std::endl;

    std::cout << "good:\n" << "\t\"x\":" << (*it_begin)["x"] << std::endl;
    std::cout << "\t\"y\":" << (*it_begin)["y"] << std::endl;
    std::cout << "\t\"profit\":" << (*it_begin++)["profit"] << std::endl;

    std::cout << "worst:\n" << "\t\"x\":" << (*it_begin)["x"] << std::endl;
    std::cout << "\t\"y\":" << (*it_begin)["y"] << std::endl;
    std::cout << "\t\"profit\":" << (*it_begin)["profit"] << std::endl;

    std::cout << "middle:\n" << "\t\"x\":" << middle["x"] << std::endl;
    std::cout << "\t\"y\":" << middle["y"] << std::endl;
};

Point CNelder_mead_method::nelder_mead_method() {
    start_points_generation();
    size_t cnt = 1;

    while (cnt < _limit && _attempts < 5) {
        debug(_points, _middle, cnt);
        if (!reflection()) {
            compress();
        }
        ++cnt;
    }
    debug(_points, _middle, cnt);
    return *_points.begin();
};

double CNelder_mead_method::profit(Point point) {
    double res = 0;
    res = -((point["x"] * point["x"]) + (point["y"] * point["y"]));
    return res;
};

void CNelder_mead_method::sort() {
    auto it_begin = _points.begin();
    auto it_end = _points.end();

    while (it_begin != (it_end - 1)) {
        if ((*it_begin)["profit"] < (*(it_begin + 1))["profit"]) {
            auto tmp = *it_begin;
            *it_begin = *(it_begin + 1);
            *(it_begin + 1) = tmp;
            it_begin = _points.begin();
        } else {
            ++it_begin;
        }
    }
    sum();
    middle();
};

void CNelder_mead_method::compress() {

    Point new_point;

    for (auto &param_name : _points.back()) {
        if (param_name.first == "profit") { continue; }
        new_point[param_name.first] =
                _middle[param_name.first] + _beta * (_points.back()[param_name.first] - _middle[param_name.first]);
    }
    //    round(new_point);
    new_point["profit"] = profit(new_point);

    if (pow((new_point["profit"] - _avg_profit), 2) / _dimensions < _eps) {
        _attempts++;
    } else {
        _attempts = 0;
    }

    _points.back().swap(new_point);
    sort();
};

bool CNelder_mead_method::expansion(Point &old_point) {

    Point new_point;

    for (auto &param_name : _points.back()) {
        if (param_name.first == "profit") { continue; }
        new_point[param_name.first] =
                _middle[param_name.first] + _gamma * (_middle[param_name.first] - _points.back()[param_name.first]);
    }
    //    round(new_point);
    new_point["profit"] = profit(new_point);

    if (old_point["profit"] <= new_point["profit"]) {
        _points.back().swap(new_point);
    } else {
        _points.back().swap(old_point);
    }
    sort();
    return true;
};

bool CNelder_mead_method::reflection() {

    Point new_point;

    for (auto &param_name : _points.back()) {
        if (param_name.first == "profit") { continue; }
        new_point[param_name.first] =
                _middle[param_name.first] + _alpha * (_middle[param_name.first] - _points.back()[param_name.first]);
    }
    //    round(new_point);
    new_point["profit"] = profit(new_point);

    if (pow((new_point["profit"] - _avg_profit), 2) / _dimensions < _eps) {
        _attempts++;
    } else {
        _attempts = 0;
    }

    if (new_point["profit"] > _points.back()["profit"]) {
        return expansion(new_point);
    }
    return false;
};

void CNelder_mead_method::middle() {
    _middle.clear();
    for (auto &param_name : _param) {
        if (param_name == "profit") { continue; }
        for (auto &point : _points) {
            if (point != _points.back()) {
                _middle[param_name] += point[param_name];
            }
        }
        _middle[param_name] /= _dimensions;
    }
}

void CNelder_mead_method::start_points_generation() {

    Point point;

    for (size_t i = 0; i < _dimensions; ++i, point.clear()) {
        point.emplace("x", rand() % 20);
        point.emplace("y", rand() % 30);
        point["profit"] = profit(point);
        _points.push_back(point);
    }
    sort();
}

void CNelder_mead_method::sum() {
    _avg_profit = 0;
    for (auto &map_it : _points) {
        _avg_profit += map_it["profit"];
    }
    _avg_profit /= _dimensions + 1;
}