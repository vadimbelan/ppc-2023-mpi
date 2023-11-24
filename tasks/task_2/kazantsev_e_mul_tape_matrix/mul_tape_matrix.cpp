// Copyright 2023 Kazantsev Evgeny
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
#include "../tasks/task_2/kazantsev_e_mul_tape_matrix/mul_tape_matrix.h"

std::vector<int> GetMatrixRand(int n) {
  std::vector<int> matrix(n * n);
  std::random_device d;
  std::mt19937 gen(d());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i * n + j] = gen() % 5;
    }
  }
return matrix;
}
std::vector<int> SequentialMulMatrix(const std::vector<int>& a,
const std::vector<int>& b, int n) {
  std::vector<int> c(n * n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        c[i * n + j] += a[i * n + k] * b[k * n + j];
      }
    }
  }
  return c;
}
std::vector<int> parallelMatrixMul(std::vector<int>* c,
std::vector<int>* d, int sz) {
  std::vector<int>& a = *c;
  std::vector<int>& b = *d;
  int comSize;
  int comRank;
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD, &comSize);
  MPI_Comm_rank(MPI_COMM_WORLD, &comRank);
  if (sz < comSize || comSize == 1) {
    if (comRank == 0) {
      return SequentialMulMatrix(a, b, sz);
      }
  }
  int n = sz / comSize;
  int ost = sz % comSize;
  std::vector<int> sendcounts(comSize);
  std::vector<int> displs(comSize);

  for (int i = 0; i < comSize; ++i) {
    sendcounts[i] = (i < ost) ? (n + 1) * sz : n * sz;
    displs[i] = (i == 0) ? 0 : (displs[i - 1] + (sendcounts[i - 1]));
  }
  MPI_Bcast(b.data(), sz * sz, MPI_INT, 0, MPI_COMM_WORLD);

  if (comRank == 0) {
    if (n > 0) {
      for (int i = 1; i < comSize; ++i) {
        MPI_Send(a.data() + displs[i], sendcounts[i], MPI_INT, i, 0, MPI_COMM_WORLD);
      }
    }
  }
  std::vector<int> loc_buf;
  if (comRank == 0) {
      loc_buf = std::vector<int>(a.begin(), a.begin() + sendcounts[0]);
  } else {
      if (n > 0) {
          loc_buf.resize(sendcounts[comRank]);
          MPI_Recv(loc_buf.data(), sendcounts[comRank],
              MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      }
    }

  std::vector<int> loc_mul(sendcounts[comRank]);
  int tmpSize = sendcounts[comRank] / sz;

  for (int i = 0; i < tmpSize; ++i) {
    for (int j = 0; j < sz; ++j) {
      for (int k = 0; k < sz; ++k) {
        loc_mul[i * sz + j] += loc_buf[i * sz + k] * b[k * sz + j];
      }
    }
  }
  int resultSize = std::accumulate(sendcounts.begin(), sendcounts.end(), 0);
  std::vector<int> result;
  if (comRank == 0) {
    result.resize(resultSize);
  }
  MPI_Gatherv(loc_mul.data(), sendcounts[comRank],
  MPI_INT, result.data(), sendcounts.data(), displs.data(),
  MPI_INT, 0, MPI_COMM_WORLD);
  return result;
}
