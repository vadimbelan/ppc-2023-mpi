// Copyright 2023 Kruglov Alexey
#ifndef TASKS_TASK_2_KRUGLOV_A_ALLREDUCE_ALLREDUCE_H_
#define TASKS_TASK_2_KRUGLOV_A_ALLREDUCE_ALLREDUCE_H_

#include <mpi.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <climits>
#include <functional>

std::vector<int> getRandomVector(int sz);

std::vector<float> getRandomFloatVector(int sz);

std::vector<double> getRandomDoubleVector(int sz);

int myAllreduce(const void* send_buf, void* recv_buf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);

#endif  // TASKS_TASK_2_KRUGLOV_A_ALLREDUCE_ALLREDUCE_H_
