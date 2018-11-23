#include <gtest/gtest.h>
#include <map>
#include <unordered_set>
#include <iostream>
#include <CNelder_mead_method.h>
#include <Coordinate_system.h>


class start_points_generation_test : public ::testing::Test {
public:

    Point point0, point1;
    size_t limit = 0;

    virtual void SetUp() {
        point0.emplace("x", -10);
        point0.emplace("y", -20);
        limit = 100;

        point1.emplace("x", -5.7);
        point1.emplace("y", 3.9);
    }

};

TEST_F(start_points_generation_test, class_test) {
    CNelder_mead_method result{1, 0.5, 2, limit, point0, 2};
    std::cout << result.nelder_mead_method()["profit"] << std::endl;
}

TEST_F(start_points_generation_test, coordinate_test) {
    Coordinate_system result;
    result.round(point1);
}