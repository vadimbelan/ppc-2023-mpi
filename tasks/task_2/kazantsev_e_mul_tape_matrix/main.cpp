// Copyright 2023 Kazantsev Evgeny
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "../tasks/task_2/kazantsev_e_mul_tape_matrix/mul_tape_matrix.h"

TEST(Parallel_Operations_MPI, Test_free_size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_m1;
  std::vector<int> global_m2;
  const int count_size_matrix = 10;
  if (rank == 0) {
    global_m1 = GetMatrixRand(count_size_matrix);
    global_m2 = GetMatrixRand(count_size_matrix);
  }
  std::vector<int> glob_res = parallelMatrixMul(&global_m1, &global_m2, count_size_matrix);
  if (rank == 0) {
    std::vector<int> SeqRes = SequentialMulMatrix(global_m1, global_m2, count_size_matrix);
    ASSERT_EQ(glob_res, SeqRes);
  }
}

TEST(Parallel_Operations_MPI, big_size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_m1;
  std::vector<int> global_m2;
  const int count_size_matrix = 5;
  if (rank == 0) {
    global_m1 = GetMatrixRand(count_size_matrix);
    global_m2 = GetMatrixRand(count_size_matrix);
  }
  std::vector<int> glob_res = parallelMatrixMul(&global_m1, &global_m2, count_size_matrix);
  if (rank == 0) {
    std::vector<int> SeqRes = SequentialMulMatrix(global_m1, global_m2, count_size_matrix);
    ASSERT_EQ(glob_res, SeqRes);
  }
}

TEST(Parallel_Operations_MPI, Test_odd_size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_m1;
  std::vector<int> global_m2;
  const int count_size_matrix = 5;
  if (rank == 0) {
    global_m1 = GetMatrixRand(count_size_matrix);
    global_m2 = GetMatrixRand(count_size_matrix);
  }
  std::vector<int> glob_res = parallelMatrixMul(&global_m1, &global_m2, count_size_matrix);
  if (rank == 0) {
    std::vector<int> SeqRes = SequentialMulMatrix(global_m1, global_m2, count_size_matrix);
    ASSERT_EQ(glob_res, SeqRes);
  }
}

TEST(Parallel_Operations_MPI, Test_small_size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_m1;
  std::vector<int> global_m2;
  const int count_size_matrix = 2;
  if (rank == 0) {
    global_m1 = GetMatrixRand(count_size_matrix);
    global_m2 = GetMatrixRand(count_size_matrix);
  }
  std::vector<int> glob_res = parallelMatrixMul(&global_m1, &global_m2, count_size_matrix);
  if (rank == 0) {
    std::vector<int> SeqRes = SequentialMulMatrix(global_m1, global_m2, count_size_matrix);
    ASSERT_EQ(glob_res, SeqRes);
  }
}

TEST(Parallel_Operations_MPI, Test_min_size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_m1;
  std::vector<int> global_m2;
  const int count_size_matrix = 1;
  if (rank == 0) {
    global_m1 = GetMatrixRand(count_size_matrix);
    global_m2 = GetMatrixRand(count_size_matrix);
  }
  std::vector<int> glob_res = parallelMatrixMul(&global_m1, &global_m2, count_size_matrix);
  if (rank == 0) {
    std::vector<int> SeqRes = SequentialMulMatrix(global_m1, global_m2, count_size_matrix);
    ASSERT_EQ(glob_res, SeqRes);
  }
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()
  ->listeners();
  if (rank != 0) {
    delete listeners.Release(listeners.default_result_printer());
  }
  int result = RUN_ALL_TESTS();
  if (rank == 0) {
  MPI_Finalize();
}
  return result;
}
