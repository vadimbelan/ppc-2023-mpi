// Copyright 2023 Shmelev Ivan
#ifndef TASKS_TASK_1_SHMELEV_I_MAX_OF_MATRIX_ELEMENTS_MAX_OF_MATRIX_ELEMENTS_H_
#define TASKS_TASK_1_SHMELEV_I_MAX_OF_MATRIX_ELEMENTS_MAX_OF_MATRIX_ELEMENTS_H_

#include <mpi.h>
#include <vector>
#include <ctime>
#include <climits>

int MaxInMatrixSeq(const std::vector<int>& matrix);
int MaxInMatrixPar(const std::vector<int>& matrix);

#endif  // TASKS_TASK_1_SHMELEV_I_MAX_OF_MATRIX_ELEMENTS_MAX_OF_MATRIX_ELEMENTS_H_
