// Copyright 2023 Ivanov Nikita
#include <vector>
#include <iostream>
#include <random>
#include "task_3/ivanov_constr_conv_jarvis/constr_conv_jarvis.h"

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

std::vector<P> Jarvis(const std::vector<P> points){
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

bool inside_conv(const std::vector<P> pol, const std::vector<P> points){
    int pol_size = pol.size();
    for (P point: points){
        int j = pol_size - 1;
        bool res = false;
        for (int i = 0; i < pol_size; i++) {
            if (pol[i] == point || pol[j] == point) {
                res = true;
                break;
            }
            if (pol[i].y == pol[j].y && pol[i].y == point.y){
                res = true;
                break;
            }
            if (pol[i].x == pol[j].x && pol[i].x == point.x){
                res = true;
                break;
            }
            if ((pol[i].y < point.y && pol[j].y >= point.y || pol[j].y < point.y && pol[i].y >= point.y) &&
                (pol[i].x + (point.y - pol[i].y) / (pol[j].y - pol[i].y) * (pol[j].x - pol[i].x) == point.x)) {
                res = true;
                break;
            }
            if ((pol[i].y < point.y && pol[j].y >= point.y || pol[j].y < point.y && pol[i].y >= point.y) &&
                (pol[i].x + (point.y - pol[i].y) * (pol[j].x - pol[i].x) / (pol[j].y - pol[i].y) > point.x))
                res = !res;
            j = i;
        }
        if (!res)
            return false;
    }
    return true;
}

std::vector<std::vector<int>> create_image(int n, int m){
    std::random_device rd;
    std::uniform_int_distribution<int> unif(0, 255);
    std::vector<std::vector<int>> image(n, std::vector<int> (m));
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            image[i][j] = unif(rd);
    image[0][0] = 255;

    return image;
}