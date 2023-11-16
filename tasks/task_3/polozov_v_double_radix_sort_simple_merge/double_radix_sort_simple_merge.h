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

void RadixSortDouble(double* inp , int n);
void getRandomInput(double* inp, int n, );
void CountingSort(double* inp, double* tmp, int byteNum, int n);
double fRand(double fMin, double fMax);

#endif  // TASKS_TASK_2_POLOZOV_V_GAUSS_JORDAN_METHOD_GAUSS_JORDAN_METHOD_H_
