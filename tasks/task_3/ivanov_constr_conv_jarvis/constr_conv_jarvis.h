// Copyright 2023 Ivanov Nikita
#ifndef PPC_2023_MPI_CONSTR_CONV_JARVIS_H
#define PPC_2023_MPI_CONSTR_CONV_JARVIS_H

struct P{
    double x;
    double y;
    P(double _x, double _y): x(_x), y(_y) {}
    bool operator==(P p) const { return x == p.x && y == p.y; }
};

std::vector<P> get_points_from_image(std::vector<std::vector<int>> &image);

std::vector<P> Jarvis(std::vector<P> points);
bool inside_conv(std::vector<P> pol, std::vector<P> points);

std::vector<std::vector<int>> create_image(int n, int m);

#endif //PPC_2023_MPI_CONSTR_CONV_JARVIS_H
