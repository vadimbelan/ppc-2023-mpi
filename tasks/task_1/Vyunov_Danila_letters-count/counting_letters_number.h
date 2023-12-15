// Copyright 2023 Vyunov Danila
#ifndef TASKS_TASK_1_VYUNOV_DANILA_LETTERS_COUNT_COUNTING_LETTERS_NUMBER_H_
#define TASKS_TASK_1_VYUNOV_DANILA_LETTERS_COUNT_COUNTING_LETTERS_NUMBER_H_

#include <mpi.h>
#include <string>
#include <random>
#include <iostream>

std::string CreateRandomStr(size_t size);
std::string CreateOnlyLettersStr(size_t size);
int CountingLettersParallel(const std::string& str);
int CountingLettersSequential(const std::string& str);

#endif  // TASKS_TASK_1_VYUNOV_DANILA_LETTERS_COUNT_COUNTING_LETTERS_NUMBER_H_
