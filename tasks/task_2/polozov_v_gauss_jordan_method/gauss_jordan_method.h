// Copyright 2023 Polozov Vladislav




#ifndef TASKS_TASK_2_POLOZOV_V_GAUSS_JORDAN_METHOD_GAUSS_JORDAN_METHOD_H_
#define TASKS_TASK_2_POLOZOV_V_GAUSS_JORDAN_METHOD_GAUSS_JORDAN_METHOD_H_

#include <mpi.h>
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>

std::vector<double> getParallelGaussJordan(std::vector<double> A, int n);

std::vector<double> getSequentialGaussJordan(std::vector<double> A, int n);

std::vector<double> getRandomMatrix(int n, int m);

std::vector<double> generateMatrix(int n);

int CalcRank(std::vector<double> A, int n);

#endif  // TASKS_TASK_2_POLOZOV_V_GAUSS_JORDAN_METHOD_GAUSS_JORDAN_METHOD_H_
