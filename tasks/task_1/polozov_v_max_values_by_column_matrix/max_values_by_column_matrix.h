// Copyright 2023 Polozov Vladislav




#ifndef TASKS_TASK_1_POLOZOV_V_MAX_VALUES_BY_COLUMN_MATRIX_MAX_VALUES_BY_COLUMN_MATRIX_H_
#define TASKS_TASK_1_POLOZOV_V_MAX_VALUES_BY_COLUMN_MATRIX_MAX_VALUES_BY_COLUMN_MATRIX_H_

#include <mpi.h>
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

std::vector<int> getParallelMax(const std::vector<int> &A, int n, int m);

std::vector<int> getSequentialMax(const std::vector<int> &A, int n, int m);

std::vector<int> getRandomMatrix(int n, int m);


#endif  // TASKS_TASK_1_POLOZOV_V_MAX_VALUES_BY_COLUMN_MATRIX_MAX_VALUES_BY_COLUMN_MATRIX_H_
