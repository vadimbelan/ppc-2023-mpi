// Copyright 2023 Sredneva Anastasiya
#include <gtest/gtest.h>
#include <vector>
#include "./sum_values.h"

TEST(TEST_MPI, Test_rand) {
    int ProcRank;
    int columns = 4;
    int lines = 5;
    int l = -10;
    int r = 10;
    std::vector<int> M(columns * lines);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        M = getRandomMatrix(columns, lines, l, r);
    }
    std::vector<int> ParallelSum = getParallelSum(M, columns, lines);
    if (ProcRank == 0) {
        std::vector<int> SequentialSum = getSequentialSum(M, columns);
        ASSERT_EQ(SequentialSum, ParallelSum);
    }
}

TEST(TEST_MPI, Test_rand_all_neg) {
    int ProcRank;
    int columns = 5;
    int lines = 5;
    int l = -10;
    int r = -1;
    std::vector<int> M(columns * lines);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        M = getRandomMatrix(columns, lines, l, r);
    }
    std::vector<int> ParallelSum = getParallelSum(M, columns, lines);
    if (ProcRank == 0) {
        std::vector<int> SequentialSum = getSequentialSum(M, columns);
        ASSERT_EQ(SequentialSum, ParallelSum);
    }
}

TEST(TEST_MPI, Test_all_pos) {
    int ProcRank;
    int columns = 3;
    int lines = 5;
    int l = 1;
    int r = 10;
    std::vector<int> M(columns * lines);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        M = getRandomMatrix(columns, lines, l, r);
    }
    std::vector<int> ParallelSum = getParallelSum(M, columns, lines);
    if (ProcRank == 0) {
        std::vector<int> SequentialSum = getSequentialSum(M, columns);
        ASSERT_EQ(SequentialSum, ParallelSum);
    }
}

TEST(TEST_MPI, Test_all_null) {
    int ProcRank, ProcNum;
    int columns = 3;
    int lines = 3;
    std::vector<int> M(columns * lines);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        M = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    }
    std::vector<int> ParallelSum = getParallelSum(M, columns, lines);
    if (ProcRank == 0) {
        std::vector<int> SequentialSum = getSequentialSum(M, columns);
        ASSERT_EQ(SequentialSum, ParallelSum);
    }
}

TEST(TEST_MPI, Test_rand2) {
    int ProcRank;
    int columns = 6;
    int lines = 6;
    int l = -10;
    int r = 10;
    std::vector<int> M(columns * lines);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        M = getRandomMatrix(columns, lines, l, r);
    }
    std::vector<int> ParallelSum = getParallelSum(M, columns, lines);
    if (ProcRank == 0) {
        std::vector<int> SequentialSum = getSequentialSum(M, columns);
        ASSERT_EQ(SequentialSum, ParallelSum);
    }
}


int main(int argc, char** argv) {
    int result = 0;

    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    MPI_Init(&argc, &argv);
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }

    result = RUN_ALL_TESTS();

	MPI_Finalize();
	return result;
}
