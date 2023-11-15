// Copyright 2023 Nesterov Alexander
#ifndef TASKS_TASK_1_KAZANTSEV_E_MATRIX_SUM_MATRIX_SUM_H_
#define TASKS_TASK_1_KAZANTSEV_E_MATRIX_SUM_MATRIX_SUM_H_

#include <vector>
#include <string>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>

std::vector<int> getRandVec(int size);
int SecquentialCount(const std::vector<int>& vec);
int parallelCount(const std::vector<int>& vec);
#endif  // TASKS_TASK_1_KAZANTSEV_E_MATRIX_SUM_MATRIX_SUM_H_
