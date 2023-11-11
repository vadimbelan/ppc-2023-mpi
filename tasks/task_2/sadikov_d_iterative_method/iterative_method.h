// Copyright 2023 Sadikov Damir
#ifndef TASKS_TASK_2_SADIKOV_D_ITERATIVE_METHOD_ITERATIVE_METHOD_H_
#define TASKS_TASK_2_SADIKOV_D_ITERATIVE_METHOD_ITERATIVE_METHOD_H_

#include <vector>

std::vector<int> getRandomVector(int sz);
int getSequentialDotProduct(const std::vector<int>& A, const std::vector<int>& B);
int getParallelDotProduct(const std::vector<int>& A,
                          const std::vector<int>& B, int vector_size);

#endif  // TASKS_TASK_2_SADIKOV_D_ITERATIVE_METHOD_ITERATIVE_METHOD_H_
