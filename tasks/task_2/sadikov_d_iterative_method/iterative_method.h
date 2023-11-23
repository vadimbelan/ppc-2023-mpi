// Copyright 2023 Sadikov Damir
#ifndef TASKS_TASK_2_SADIKOV_D_ITERATIVE_METHOD_ITERATIVE_METHOD_H_
#define TASKS_TASK_2_SADIKOV_D_ITERATIVE_METHOD_ITERATIVE_METHOD_H_

#include <vector>

std::vector<double> getRandomVector(int n);
std::vector<double> getRandomMatrix(int n);
double getNormOfDifference(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> getSequentialIter(const std::vector<double>& A, const std::vector<double> b, int n);
std::vector<double> getParallelIter(const std::vector<double>& A, const std::vector<double> b, int n);
int getSequentialDotProduct(const std::vector<int>& A, const std::vector<int>& B);
int getParallelDotProduct(const std::vector<int>& A,
                          const std::vector<int>& B, int vector_size);

#endif  // TASKS_TASK_2_SADIKOV_D_ITERATIVE_METHOD_ITERATIVE_METHOD_H_
