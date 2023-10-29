// Copyright 2023 Ivanov Nikita
#include <gtest/gtest.h>
#include <vector>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/collectives.hpp>
#include "gauss_lent_horiz.h"

TEST(Parallel_Gauss, test_1) {
    boost::mpi::communicator world;
    std::vector<double> a{
        2, -2,  1, -3,
        1,  3, -2,  1,
        3, -1, -1,  2
    };

    std::vector<double> res;
    res = Gauss(a, 3);
    for (auto it = res.begin(); it != res.end(); it++)
        std::cout << *it << " ";
}

TEST(Parallel_Gauss, test_2) {
//    boost::mpi::communicator world;
//    int row = 0;
//    int size = 3;
//    std::vector<double> a{1, 2, 3, 4};
//    std::vector<double> tmp(size);
//    if (world.rank() == 0) {
//        a[0] = 0;
//        a[1] = -1;
//        row++;
////        for (int j = 0; j < size; j++) {
////            tmp[j] = a[row + j];
////        }
//        boost::mpi::broadcast(world, &a.data()[row], 2, 0);
//    } else {
//        boost::mpi::broadcast(world, tmp.data(), 2, 0);
//    }
//
////    boost::mpi::broadcast(world , &(a.data()[row]), 2, 0);
////    boost::mpi::broadcast(world, &a.data()[row], 2, 0);
//
//    std::cout << "Process #" << world.rank() << " says " << tmp[0] << ", " << tmp[1] << ", " << tmp[2] << " addr = " << &a[0]
//              << std::endl;
//    boost::mpi::communicator world;
//    std::vector<double> a{
//            2, -2,  1, -3, 1,
//            1,  3, -2,  1, 2,
//            3, -1, -1,  2, 3,
//            4,  0, -5,  1, 0
//    };
//
//    std::vector<double> res;
//    res = Gauss(a, 4);
}

TEST(Parallel_Gauss, test_3) {
//    boost::mpi::communicator world;
//    std::vector<double> a{
//            2, -2,  1, -3, 1, 0,
//            1,  3, -2,  1, 2, 4,
//            3, -1, -1,  2, 3, 5,
//            4,  0, -5,  1, 0, 6,
//            1,  1,  1,  1, 1, 1
//    };
//
//    std::vector<double> res;
//    res = Gauss(a, 5);
}

TEST(Parallel_Gauss, test_4) {
}

TEST(Parallel_Gauss, test_5) {
}

int main(int argc, char** argv) {
    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator world;
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    if (world.rank() != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }
    return RUN_ALL_TESTS();
}
