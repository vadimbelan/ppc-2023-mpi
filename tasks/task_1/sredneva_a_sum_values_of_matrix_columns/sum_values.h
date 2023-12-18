// Copyright 2023 Sredneva Anastasiya
#ifndef TASKS_TASK_1_SREDNEVA_A_SUM_VALUES_OF_MATRIX_COLUMNS_SUM_VALUES_H_
#define TASKS_TASK_1_SREDNEVA_A_SUM_VALUES_OF_MATRIX_COLUMNS_SUM_VALUES_H_

#include <mpi.h>

#include <vector>

std::vector<int> getRandomMatrix(int columns, int lines, int l, int r);
std::vector<int> getParallelSum(const std::vector<int>& vec, int columns, int lines);
std::vector<int> getSequentialSum(const std::vector<int>& vec, int columns);
std::vector<int> transposeMatr(const std::vector<int>& M, int columns, int lines);


#endif  // TASKS_TASK_1_SREDNEVA_A_SUM_VALUES_OF_MATRIX_COLUMNS_SUM_VALUES_H_
