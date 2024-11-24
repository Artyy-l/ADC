#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

struct Point {
    double x;
    double y;

    Point(double x_, double y_) : x(x_), y(y_) {}
};

struct Circle {
    Point centre = Point(0, 0);
    double r;

    Circle(double x0, double y0, double radius) {
        centre = Point(x0, y0);
        r = radius;
    }

    Circle(Point centre_, double radius) {
        centre = centre_;
        r = radius;
    }
};

double squareDist(const Point &p1, const Point &p2) {
    return std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2);
}

bool isInsideCircle(const Circle &circle, const Point &point) {
    return squareDist(circle.centre, point) <= (circle.r * circle.r);
}

bool isInsideIntersection(const Circle &c1, const Circle &c2, const Circle &c3, const Point &p) {
    return isInsideCircle(c1, p) && isInsideCircle(c2, p) && isInsideCircle(c3, p);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double x1, y1, r1, x2, y2, r2, x3, y3, r3;
    std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 >> x3 >> y3 >> r3;

    Circle c1(x1, y1, r1);
    Circle c2(x2, y2, r2);
    Circle c3(x3, y3, r3);

    double minX = std::min({x1 - r1, x2 - r2, x3 - r3});
    double maxX = std::max({x1 + r1, x2 + r2, x3 + r3});
    double minY = std::min({y1 - r1, y2 - r2, y3 - r3});
    double maxY = std::max({y1 + r1, y2 + r2, y3 + r3});

    std::random_device rd;
    std::mt19937 gen(rd());
    // все точки выпадают с одинаковой вероятностью
    std::uniform_real_distribution<> disX(minX, maxX);
    std::uniform_real_distribution<> disY(minY, maxY);

    const int pointsNumber = 1000000;
    int countInIntersection = 0;

    for (int i = 0; i < pointsNumber; ++i) {
        Point point(disX(gen), disY(gen));

        if (isInsideIntersection(c1, c2, c3, point)) {
            ++countInIntersection;
        }
    }

    double RectangleArea = (maxX - minX) * (maxY - minY);
    double intersectionArea = (static_cast<double>(countInIntersection) / pointsNumber) * RectangleArea;
    std::cout << intersectionArea << '\n';

    return 0;
}
