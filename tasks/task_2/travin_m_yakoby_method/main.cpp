// Copyright 2023 Travin Maksim
#include <gtest/gtest.h>
#include <mpi.h>
#include <iostream>
#include "./yakoby_method.h"


TEST(Parallel_yakobi_method, Cant_Create_Zero_Element) {
    int rankProc = 0;
    int numProc = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    std::vector<std::vector<double>> mat{
        {1, 2, 3},
        {4, 0, 5},
        {6, 7, 8}
    };
    std::vector<double> vec{ 1, 2, 3 };
    std::vector<double> res(vec.size());

    if (rankProc == 0) {
        ASSERT_ANY_THROW(Yakobi(mat, vec, res));
    }
}

TEST(Parallel_yakobi_method, Cant_Create_b_vec_not_equal_amount_of_solutions) {
    int rankProc = 0;
    int numProc = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    std::vector<std::vector<double>> mat{
        {1, 2, 3},
        {4, 1, 5},
        {6, 7, 8}
    };
    std::vector<double> vec{ 1, 2, 3, 4 };
    std::vector<double> res(vec.size());

    if (rankProc == 0) {
        ASSERT_ANY_THROW(Yakobi(mat, vec, res));
    }
}

TEST(Parallel_yakobi_method, Can_create_matrix_witout_zero_elements) {
    int rankProc = 0;
    int numProc = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    std::vector<std::vector<double>> mat = get_rand_matrix(10, -1, 1);
    std::vector<double> vec = get_rand_vector(10, -10, 10);
    std::vector<double> res(vec.size());

    if (rankProc == 0) {
        ASSERT_NO_THROW(Yakobi(mat, vec, res));
    }
}

TEST(Parallel_yakobi_method, Can_solve_task) {
    int rankProc = 0;
    int numProc = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    std::vector<std::vector<double>> mat{
        {4, -1, 0},
        {-1, 4, -1},
        {0, -1, 3}
    };
    std::vector<double> vec{ 15, 10, 5 };
    std::vector<double> res(vec.size(), 0.0);
    std::vector<double> solve{ 3.75, 2.5, 1.6666666666666667 };

    if (rankProc == 0) {
        res = Yakobi(mat, vec, res, 1);
        for (int i = 0; i < solve.size(); i++) {
            ASSERT_EQ(res[i], solve[i]);
        }
    }
}

TEST(Parallel_yakobi_method, Only_1) {
    int rankProc = 0;
    int numProc = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    std::vector<std::vector<double>> mat{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    std::vector<double> vec{ 1, 1, 1 };
    std::vector<double> res(vec.size(), 0.0);
    std::vector<double> solve{ -1, -1, -1 };

    if (rankProc == 0) {
        res = Yakobi(mat, vec, res, 2);
        for (int i = 0; i < solve.size(); i++) {
            ASSERT_EQ(res[i], solve[i]);
        }
    }
}


int main(int argc, char** argv) {
    int result_code = 0;

    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, -1);
    result_code = RUN_ALL_TESTS();
    MPI_Finalize();

    return result_code;
}
