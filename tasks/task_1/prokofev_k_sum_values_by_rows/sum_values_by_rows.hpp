// Copyright 2023 Prokofev Kirill
#ifndef TASKS_TASK_1_PROKOFEV_K_SUM_VALUES_BY_ROWS_H_
#define TASKS_TASK_1_PROKOFEV_K_SUM_VALUES_BY_ROWS_H_

#include <mpi.h>
#include <random>
#include <vector>
// n - rows, m - cols

int Random(int low, int high);
std::vector<int>GenerateRandomMatrix(int n, int m);
std::vector<int>ParallSumValuesByRows(std::vector<int>& matrix,int n,int m);
std::vector<int>SeqSumValuesByRows(std::vector<int>& matrix, int n, int m);
#endif  //TASKS_TASK_1_PROKOFEV_K_SUM_VALUES_BY_ROWS_H_