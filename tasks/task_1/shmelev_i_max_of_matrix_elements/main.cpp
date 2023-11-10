// Copyright 2023 Shmelev Ivan
#include <gtest/gtest.h>

#include "./max_of_matrix_elements.h"

TEST(TESTS, Test_1) { ASSERT_EQ(1, 1); }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  int rank = 0;
  int exit_code = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank != 0) {
    delete listeners.Release(listeners.default_result_printer());
  }

  exit_code = RUN_ALL_TESTS();

  if (rank == 0) {
    std::cout << sum(rank, exit_code) << '\n';
  }
  MPI_Finalize();

  return exit_code;
}
