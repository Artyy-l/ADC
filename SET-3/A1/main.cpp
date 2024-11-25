#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>

struct Point {
    double x;
    double y;

    Point(double x_, double y_) : x(x_), y(y_) {}
};

struct Circle {
    Point center = Point(0, 0);
    double r;

    Circle(double x0, double y0, double radius) {
        center = Point(x0, y0);
        r = radius;
    }

    Circle(Point center_, double radius) {
        center = center_;
        r = radius;
    }
};

struct Rectangle {
    double ldx;
    double ldy;
    double rux;
    double ruy;

    Rectangle() : ldx(0), ldy(0), rux(0), ruy(0) {}

    double GetArea() const {
        return (rux - ldx) * (ruy - ldy);
    }
};

std::istream &operator>>(std::istream &is, Circle &circle) {
    is >> circle.center.x >> circle.center.y >> circle.r;
    return is;
}

double squareDist(const Point &p1, const Point &p2) {
    return std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2);
}

bool isInsideCircle(const Circle &circle, const Point &point) {
    return squareDist(circle.center, point) <= (circle.r * circle.r);
}

bool isInsideIntersection(const Circle &c1, const Circle &c2, const Circle &c3, const Point &p) {
    return isInsideCircle(c1, p) && isInsideCircle(c2, p) && isInsideCircle(c3, p);
}

double CalculateArea(const Circle &c1, const Circle &c2, const Circle &c3, const Rectangle &bounds, size_t pointsCount) {
    int countInIntersection = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> disX(bounds.ldx, bounds.rux);
    std::uniform_real_distribution<double> disY(bounds.ldy, bounds.ruy);

    for (size_t i = 0; i < pointsCount; ++i) {
        Point point(disX(gen), disY(gen));

        if (isInsideIntersection(c1, c2, c3, point)) {
            ++countInIntersection;
        }
    }

    return (static_cast<double>(countInIntersection) / static_cast<double>(pointsCount)) * bounds.GetArea();
}

template<typename T>
void PrintArrayIntoFile(std::ofstream &file, const std::vector<T> &array) {
    for (size_t i = 0; i < array.size(); ++i) {
        file << array[i];
        if (i < array.size() - 1) {
            file << ", ";
        }
    }
    file << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Circle c1(1, 1, 1);
    Circle c2(1.5, 2, sqrt(5) / 2);
    Circle c3(2, 1.5, sqrt(5) / 2);

    Rectangle bounds;
    bounds.ldx = std::min({c1.center.x - c1.r, c2.center.x - c2.r, c3.center.x - c3.r});
    bounds.rux = std::max({c1.center.x + c1.r, c2.center.x + c2.r, c3.center.x + c3.r});
    bounds.ldy = std::min({c1.center.y - c1.r, c2.center.y - c2.r, c3.center.y - c3.r});
    bounds.ruy = std::max({c1.center.y + c1.r, c2.center.y + c2.r, c3.center.y + c3.r});

    double answer = 0.25 * M_PI + 1.25 * asin(0.8) - 1;

    std::vector<size_t> pointsCounts;
    std::vector<double> areas;
    std::vector<double> diffs;
    for (size_t pointsCount = 100; pointsCount <= 100000; pointsCount += 500) {
        double area = CalculateArea(c1, c2, c3, bounds, pointsCount);
        areas.push_back(area);
        pointsCounts.push_back(pointsCount);
        diffs.push_back(std::abs(area - answer) / answer * 100);
    }

    std::ofstream outFile("../A1_Different_number_of_points_2.txt");
    PrintArrayIntoFile(outFile, pointsCounts);
    // PrintArrayIntoFile(outFile, areas);
    PrintArrayIntoFile(outFile, diffs);
    outFile.close();

    return 0;
}