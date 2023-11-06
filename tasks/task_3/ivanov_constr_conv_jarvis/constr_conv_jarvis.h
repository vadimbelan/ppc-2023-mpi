// Copyright 2023 Ivanov Nikita
#ifndef PPC_2023_MPI_CONSTR_CONV_JARVIS_H
#define PPC_2023_MPI_CONSTR_CONV_JARVIS_H

struct P{
    double x;
    double y;
    P(): x(0), y(0){}
    P(double _x, double _y): x(_x), y(_y) {}
    P(std::pair<int, int> pair): x(pair.first), y(pair.second) {}
    bool operator==(P p) const { return x == p.x && y == p.y; }
};

std::vector<std::pair<int, int>> get_points_from_image(std::vector<std::vector<int>> &image, int n);

std::vector<P> Jarvis(std::vector<std::pair<int, int>> points);
std::vector<P> JarvisParallel(std::vector<std::vector<int>> &image, int n);
bool inside_conv(std::vector<P> pol, std::vector<std::pair<int, int>> points);

std::vector<std::vector<int>> create_image(int n, int m);

#endif //PPC_2023_MPI_CONSTR_CONV_JARVIS_H
