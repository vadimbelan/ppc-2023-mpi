// Copyright 2023 Kuznetsov Artem
#include <gtest/gtest.h>
#include <mpi.h>

#include <iostream>

#include "./contrast_enhancement.h"

TEST(MPI_TESTS, Test_1) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ASSERT_EQ(1, 1);
}

TEST(MPI_TESTS, Test_2) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ASSERT_EQ(1, 1);
}

TEST(MPI_TESTS, Test_3) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ASSERT_EQ(1, 1);
}

TEST(MPI_TESTS, Test_4) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ASSERT_EQ(1, 1);
}

TEST(MPI_TESTS, Test_5) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ASSERT_EQ(1, 1);
}

int main(int argc, char** argv) {
  int result_code = 0;

  std::cout << "RESULT: " << sum(10, 20) << '\n';

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  if (MPI_Init(&argc, &argv) != MPI_SUCCESS) MPI_Abort(MPI_COMM_WORLD, -1);
  result_code = RUN_ALL_TESTS();
  MPI_Finalize();

  return result_code;
}
