// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "/home/evgenius/ppc-2023/ppc-2023-mpi/tasks/task_1/Kazantsev_e_near_neighbor_el/near_neighbor_el.h"

TEST(Parallel_Operations_MPI, Test_count) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 100;

    if (rank == 0) {
        global_vec = getRandVec(count_size_vector);
    }
    int global_min = parallelCount(global_vec);
    if (rank == 0) {
        int reference_min = SequentialCount(global_vec);
        ASSERT_EQ(global_min, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_count_2) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 150;

  if (rank == 0) {
      global_vec = getRandVec(count_size_vector);
  }
  int global_min = parallelCount(global_vec);
  if (rank == 0) {
      int reference_min = SequentialCount(global_vec);
      ASSERT_EQ(global_min, reference_min);
  }
}

TEST(Parallel_Operations_MPI, Test_odd_numb) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 111;

  if (rank == 0) {
      global_vec = getRandVec(count_size_vector);
  }
  int global_min = parallelCount(global_vec);
  if (rank == 0) {
      int reference_min = SequentialCount(global_vec);
      ASSERT_EQ(global_min, reference_min);
  }
}

TEST(Parallel_Operations_MPI, Test_only_el) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 1;

  if (rank == 0) {
      global_vec = getRandVec(count_size_vector);
  }
  int global_min = parallelCount(global_vec);
  if (rank == 0) {
      int reference_min = SequentialCount(global_vec);
      ASSERT_EQ(global_min, reference_min);
  }
}

TEST(Parallel_Operations_MPI, Test_count_2) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 1000;

  if (rank == 0) {
      global_vec = getRandVec(count_size_vector);
  }
  int global_min = parallelCount(global_vec);
  if (rank == 0) {
      int reference_min = SequentialCount(global_vec);
      ASSERT_EQ(global_min, reference_min);
  }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
     int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    if (rank != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }
    return RUN_ALL_TESTS();
}

