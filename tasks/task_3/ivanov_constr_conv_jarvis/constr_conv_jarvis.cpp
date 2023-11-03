// Copyright 2023 Ivanov Nikita
#include <vector>
#include "task_3/ivanov_constr_conv_jarvis/constr_conv_jarvis.h"

bool operator==(P a, P b) { return a.x == b.x && b.y == a.y; }

int distance(P a, P b, P c) {
    int y1 = a.y - b.y;
    int y2 = a.y - c.y;
    int x1 = a.x - b.x;
    int x2 = a.x - c.x;
    int item1 = (y1*y1 + x1*x1);
    int item2 = (y2*y2 + x2*x2);
    if(item1 == item2)
        return 0; //when b and c are in same distance from a
    else if(item1 < item2)
        return -1; //when b is closer to a
    return 1; //when c is closer to a
}

int crossProduct(P a, P b, P c) {
    int y1 = a.y - b.y;
    int y2 = a.y - c.y;
    int x1 = a.x - b.x;
    int x2 = a.x - c.x;
    return y2*x1 - y1*x2;
}

std::vector<P> get_points_from_image(std::vector<std::vector<int>> &image){
    std::vector<P> points;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[i].size(); j++){
            if (image[i][j] > 178){
                points.emplace_back(j, i);
            }
        }
    }
    return points;
}

std::vector<P> Jarvis(std::vector<P> points){
    P start_point = points[0];
    for (P p: points)
        if (p.y < start_point.y || (p.y == start_point.y && p.x < start_point.x))
            start_point = p;

    std::vector<P> result;
    P current = start_point;
    P next_point = points[0];
    while (true) {
        for (P p: points) {
            if(p == current)
                continue;
            int val = crossProduct(current, next_point, p);
            if(val > 0) {
                next_point = p;
            }else if(val == 0) {
                if(distance(current, next_point, p) < 0) {
                    next_point = p;
                }
            }
        }

        result.emplace_back(next_point);
        current = next_point;

        if (next_point == start_point)
            break;
    }
    return result;
}
