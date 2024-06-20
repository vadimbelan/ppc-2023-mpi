// Copyright 2023 Benduyzhko Tatiana
#include <gtest/gtest.h>
#include "./moors_algoritm.h"


TEST(Moors_Algorithm_MPI, Cant_Find_If_Incorrect_Source_Seq) {
    int rank;
    int n = 3;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> g(n * n);
    if (rank == 0)
        g = getRandomGraph(n);
    std::vector<int> ans(n);
    if (rank == 0) {
        ASSERT_ANY_THROW(Moors_algorithm(g, (-1)));
    }
}

TEST(Moors_Algorithm_MPI, Can_Find_If_Correct_Source_Seq) {
    int rank;
    int n = 3;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> g(n * n);
    if (rank == 0)
        g = getRandomGraph(n);
    std::vector<int> ans(n);
    if (rank == 0) {
        ASSERT_NO_THROW(Moors_algorithm(g, (1)));
    }
}

TEST(Moors_Algorithm_MPI, Test_On_Size_5) {
    int rank;
    int n = 5;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> g(n * n);
    if (rank == 0)
        g = getRandomGraph(n);
    std::vector<int> ans1(n);
    std::vector<int> ans2(n);
    ans1 = ParallelMoor(g, 0);
    if (rank == 0) {
        ans2 = Moors_algorithm(g, 0);
        for (int i = 0; i < n; ++i) {
            ASSERT_EQ(ans2[i], ans1[i]);
        }
    }
}

TEST(Moors_Algorithm_MPI, Test_On_Size_10) {
    int rank;
    int n = 10;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> g(n * n);
    if (rank == 0)
        g = getRandomGraph(n);
    std::vector<int> ans1(n);
    std::vector<int> ans2(n);
    ans1 = ParallelMoor(g, 0);
    if (rank == 0) {
        ans2 = Moors_algorithm(g, 0);
        for (int i = 0; i < n; ++i) {
            ASSERT_EQ(ans2[i], ans1[i]);
        }
    }
}

TEST(Moors_Algorithm_MPI, Test_On_Size_15) {
    int rank;
    int n = 15;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> g(n * n);
    if (rank == 0)
        g = getRandomGraph(n);
    std::vector<int> ans1(n);
    std::vector<int> ans2(n);
    ans1 = ParallelMoor(g, 0);
    if (rank == 0) {
        ans2 = Moors_algorithm(g, 0);
        for (int i = 0; i < n; ++i) {
            ASSERT_EQ(ans2[i], ans1[i]);
        }
    }
}

int main(int argc, char** argv) {
    int result_code = 0;
    int rank = 0;

    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) MPI_Abort(MPI_COMM_WORLD, -1);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }

    result_code = RUN_ALL_TESTS();
    MPI_Finalize();

    return result_code;
}
