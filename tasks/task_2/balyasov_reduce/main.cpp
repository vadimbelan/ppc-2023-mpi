// Copyright 2023 Balyasov Ivan
#include <gtest/gtest.h>

#include "./my_reduce.h"

TEST(MPI_TESTS, Test_1) { ASSERT_EQ(1, 1); }

int main(int argc, char** argv) {
  int code = 0;
  int rank = 0;

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank != 0) {
    delete listeners.Release(listeners.default_result_printer());
  }

  code = RUN_ALL_TESTS();
  MPI_Finalize();

  return code;
}
