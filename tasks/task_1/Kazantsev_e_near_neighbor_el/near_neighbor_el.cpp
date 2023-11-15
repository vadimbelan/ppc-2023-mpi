// Copyright 2023 Nesterov Alexander
#include <vector>
#include <cmath>
#include <limits>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>
#include <functional>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include "examples/test_mpi/ops_mpi.h"
#include "/home/evgenius/ppc-2023/ppc-2023-mpi/tasks/task_1/Kazantsev_e_near_neighbor_el/near_neighbor_el.h"

std::vector<int> getRandVec(int size) {
  std::vector<int> vec(size);
  std::random_device d;
  std::mt19937 gen(d());
  for (int i = 0; i < size; ++i) {
    vec[i] = gen() % 100;
  }
  return vec;
}
int SecquentialCount(const std::vector<int>& vec) {
  if (vec.size() == 0 || vec.size() == 1) {
    return 0;
  }
  int lenght = vec.size();
  int min = abs(vec[1] - vec[0]);
  for (int i = 2; i < lenght; ++i) {
    if (min > abs(vec[i] - vec[i - 1])) {
      min = abs(vec[i] - vec[i - 1]);
    }
  }
  return min;
}
int parallelCount(const std::vector<int>& vec) {
  int size;
  int rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = vec.size() / size;
  int remainder = vec.size() % size;
  std::vector<int> loc_vec;
  if (rank == 0) {
    if (n > 0) {
      for (int process = 1; process < size; ++process) {
        int send_index = remainder + process * n - 1;
        MPI_Send(vec.data() + send_index, n + 1, MPI_INT, process, 0, MPI_COMM_WORLD);
       }
    }
  }
  if (rank == 0) {
    loc_vec = std::vector<int>(vec.begin(), vec.begin() + n + remainder);
  } else {
    if (n > 0) {
      loc_vec.resize(n + 1);
      MPI_Status status;
      MPI_Recv(loc_vec.data(), n + 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
  }
  int loc_res = SecquentialCount(loc_vec);
  int glob_res;
  MPI_Reduce(&loc_res, &glob_res, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
  return glob_res;
}
