// Copyright 2023 Kozyreva K
#include <gtest/gtest.h>
#include <mpi.h>
#include <vector>
#include <string>
#include "../tasks/task_1/Kozyreva_K_word_count/words_count.h"


TEST(Words_Count_MPI, Just_Count) {
    std::string str = "This is a test string for MPI programm.";
    int res = SimpleCount(str);
    ASSERT_EQ(res, 8);
}

TEST(Words_Count_MPI, Empty_String_Words_Count_no_throw) {
    std::string str = "";
    ASSERT_NO_THROW(SimpleCount(str));
}

TEST(Words_Count_MPI, Parallel_Count) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string testStr = "This is a test string for MPI programm.";
    int res = ParallelCount(testStr);
    if (rank == 0) {
        ASSERT_EQ(res, 8);
    }
}
TEST(Words_Count_MPI, Parallel_Count_Complicated_String) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string testStr = "Test  this . . . ... strange string with 11 words";
    int res = ParallelCount(testStr);
    if (rank == 0) {
        ASSERT_EQ(res, 11);
    }
}
TEST(Words_Count_MPI, Parallel_Count_Generated_String) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string testStr = getLongString(100);
    int res = ParallelCount(testStr);
    if (rank == 0) {
        ASSERT_EQ(res, 100);
    }
}

TEST(Words_Count_MPI, Parallel_Count_Generated_Long_String) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string testStr = getLongString(1000);
    int res = ParallelCount(testStr);
    if (rank == 0) {
        ASSERT_EQ(res, 1000);
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

    int result = RUN_ALL_TESTS();
    MPI_Finalize();
    return result;
}
