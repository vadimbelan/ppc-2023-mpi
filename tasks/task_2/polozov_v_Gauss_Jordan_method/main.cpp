// Copyright 2023 Polozov Vladislav

#include <gtest/gtest.h>
#include <mpi.h>
#include "./Gauss_Jordan_method.h"

TEST(MPI_TESTS, Test1) {
    int n = 3;
    std::vector<double>matr = {3,-2,4,12,3,4,-2,6,2,-1,-1,-9};
    std::vector<double>ans = getSequentialGaussJordan(matr,n);
    std::cout<<"ANSWER:";
    for(auto x : ans){
        std::cout<<x<<' ';
    }
    std::cout<<"\n";
}


TEST(MPI_TESTS, Test2) {

}


TEST(MPI_TESTS, Test3) {

}

TEST(MPI_TESTS, Test4) {

}

TEST(MPI_TESTS, Test5) {

}

int main(int argc, char** argv) {
    int result = 0;
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, -1);
    int rankProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    if (rankProc != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }
    result = RUN_ALL_TESTS();
    MPI_Finalize();
    return result;
}

