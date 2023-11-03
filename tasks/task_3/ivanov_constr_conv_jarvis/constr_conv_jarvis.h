// Copyright 2023 Ivanov Nikita
#ifndef PPC_2023_MPI_CONSTR_CONV_JARVIS_H
#define PPC_2023_MPI_CONSTR_CONV_JARVIS_H

struct P{
    int x;
    int y;
    P(int _x, int _y): x(_x), y(_y) {}
};

std::vector<P> get_points_from_image(std::vector<std::vector<int>> &image);

std::vector<P> Jarvis(std::vector<P> points);

#endif //PPC_2023_MPI_CONSTR_CONV_JARVIS_H
