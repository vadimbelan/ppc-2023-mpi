// Copyright 2023 Sharapov Georgiy
#ifndef TASKS_TASK_2_SHARAPOV_G_SEIDEL_METHOD_SEIDEL_METHOD_H_
#define TASKS_TASK_2_SHARAPOV_G_SEIDEL_METHOD_SEIDEL_METHOD_H_

double* generateMatrix(size_t size);
void printMatrix(double* matrix, size_t size);
bool seidelMethod(size_t n, double eps);

#endif  // TASKS_TASK_2_SHARAPOV_G_SEIDEL_METHOD_SEIDEL_METHOD_H_
