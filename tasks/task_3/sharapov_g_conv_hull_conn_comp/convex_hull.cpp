// Copyright 2023 Sharapov Georgiy
#include <mpi.h>
#include <cmath>
#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include "task_3/sharapov_g_conv_hull_conn_comp/convex_hull.h"

bool ccw(point start, point a, point b) {
    int x1 = a.x - start.x;
    int y1 = a.y - start.y;
    int x2 = b.x - start.x;
    int y2 = b.y - start.y;
    if ((x1 * y2 - x2 * y1) > 0) {
        return true;
    } else {
        return false;
    }
}

bool cw(point start, point a, point b) {
    int x1 = a.x - start.x;
    int y1 = a.y - start.y;
    int x2 = b.x - start.x;
    int y2 = b.y - start.y;
    if ((x1 * y2 - x2 * y1) < 0) {
        return true;
    } else {
        return false;
    }
}

double angle(point start, point a) {
    double x = a.x - start.x;
    double y = a.y - start.y;
    if (y == 0 && x == 0) return -2;
    return std::atan2(y, x);
}

int distance(point start, point a) {
    double x = a.x - start.x;
    double y = a.y - start.y;
    return abs(x) + abs(y);
}

bool pnt_comp(point start, point a, point b) {
    double angle_a = angle(start, a);
    double angle_b = angle(start, b);
    if (angle_a != angle_b) {
        return angle_a < angle_b;
    }
    return distance(start, a) < distance(start, b);
}

bool pnt_less_by_x(point a, point b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool pnt_less_by_y(point a, point b) {
    if (a.y != b.y) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

point* find_left() {
    return nullptr;
}

point* find_right() {
    return nullptr;
}

std::vector<point> connect_hulls(std::vector<point> lower_hull, std::vector<point> upper_hull) {
    std::vector<point> ans;
    return ans;
}

int* vec_to_arr(std::vector<point> pnts_v) {
    int* res = new int[pnts_v.size() * 2];
    for (int i = 0; i < pnts_v.size(); i++) {
        res[i * 2] = pnts_v[i].x;
        res[(i * 2) + 1] = pnts_v[i].y;
    }
    return res;
}

std::vector<point> arr_to_vec(int* pnts_arr, int size) {
    std::vector<point> res;
    for (int i = 0; i < size; i += 2) {
        res.push_back(point{ pnts_arr[i], pnts_arr[i + 1] });
    }
    return res;
}

std::vector<point> graham_scan(int* matrix, int rows, int columns, int rows_disp) {
    std::vector<point> pnts;

    for (int row = 0; row < rows; row++) {
        for (int elem = 0; elem < columns; elem++) {
            if (matrix[(row * (columns)) + elem] == 1) {
            pnts.push_back(point{elem, columns - (rows_disp + row) - 1});
            }
        }
    }

    std::vector<point> answer;

    if (pnts.size() != 0) {
        point min_pnt = *std::min_element(pnts.begin(), pnts.end(), pnt_less_by_x);

        std::sort(pnts.begin(), pnts.end(), [&](const point& a, const point& b) {
            return pnt_comp(min_pnt, a, b);
        });

        answer.push_back(min_pnt);

        for (int i = 1; i < pnts.size(); i++) {
            while (answer.size() > 1 && (!ccw(answer[answer.size() - 2],
                                        answer[answer.size() - 1], pnts[i])))
            answer.pop_back();
            answer.push_back(pnts[i]);
        }
    }

    return answer;
}

std::vector<point> convex_hull(int* matrix, size_t n) {
    //  DEBUG ----------------------------------

    int test = 1;

    //  DEBUG ----------------------------------

    int ProcRank, ProcNum;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    //  declaration of variables
    int *ProcSizes = new int[ProcNum]();
    int *ProcDisp = new int[ProcNum]();
    for (int i = 0; i < ProcNum; i++) {
        ProcSizes[i] = n / ProcNum + (i < n % ProcNum ? 1 : 0);
        ProcDisp[i] = i * (n / ProcNum) + std::min<int>(i, n % ProcNum);
    }
    int *ProcElem = new int[ProcNum]();
    int *ProcElemDisp = new int[ProcNum]();
    for (int i = 0; i < ProcNum; i++) {
        ProcElem[i] = ProcSizes[i] * n;
        ProcElemDisp[i] = ProcDisp[i] * n;
    }

    int rows_amount = ProcSizes[ProcRank];
    int* rows = new int[rows_amount * n];

    //  sending parts of image to corresponding processors
    if (ProcRank == 0) {
        MPI_Scatterv(matrix, ProcElem, ProcElemDisp, MPI_INT, rows,
                    rows_amount * n, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatterv(nullptr, nullptr, nullptr, MPI_INT, rows, rows_amount * n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    //  DEBUG ----------------------------------
    // if (ProcRank == test) {
    //     for (int i = 0; i < rows_amount; i++) {
    //         for (int j = 0; j < n; j++) {
    //             std::cout << rows[(i * n) + j] << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    // }
    //  DEBUG ----------------------------------

    //  find convex hull for this part of image
    std::vector<point> local_hull = graham_scan(rows, rows_amount, n, ProcDisp[ProcRank]);

    //  DEBUG ----------------------------------
    // if (ProcRank == test) {
    //     for (int i = 0; i < local_hull.size(); i++) {
    //         local_hull[i].print(); std::cout << " ";
    //     }
    //     std::cout << std::endl;
    // }
    //  DEBUG ----------------------------------

    //  connectiong parts to one hull
    int tree_level = 1;
    int rank = ProcRank + 1;
    int hull_size = 0;
    int *points_data;
    std::vector<point> other_hull;
    MPI_Status status;
    while (ProcNum >= pow(2, tree_level)) {
        if ((rank % static_cast<int>(pow(2, tree_level))) == 0) {
            int senderRank = rank - static_cast<int>(pow(2, tree_level - 1)) - 1;

            //  get other_hull
            MPI_Recv(&hull_size, 1, MPI_INT, senderRank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            points_data = new int[hull_size];
            MPI_Recv(points_data, hull_size, MPI_INT, senderRank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            other_hull = arr_to_vec(points_data, hull_size);
            delete[] points_data;

            //  DEBUG ----------------------------------

            if (ProcRank == test) {
                for (int i = 0; i < other_hull.size(); i++) {
                    other_hull[i].print();
                }
            }
            std::cout << std::endl;

            if (ProcRank == test) {
                for (int i = 0; i < local_hull.size(); i++) {
                    local_hull[i].print();
                }
            }
            std::cout << std::endl;

            //  DEBUG ----------------------------------

            local_hull = connect_hulls(local_hull, other_hull);
        } else if (((rank +
                    static_cast<int>(pow(2, tree_level - 1))) % static_cast<int>(pow(2, tree_level))) == 0) {
            int receiverRank = rank + static_cast<int>(pow(2, tree_level - 1)) - 1;
            //  send local_hull
            hull_size = local_hull.size() * 2;
            MPI_Send(&hull_size, 1, MPI_INT, receiverRank, 1, MPI_COMM_WORLD);
            points_data = vec_to_arr(local_hull);
            MPI_Send(points_data, hull_size, MPI_INT, receiverRank, 1, MPI_COMM_WORLD);
            delete[] points_data;
        }
        tree_level++;
    }

    return local_hull;
}
