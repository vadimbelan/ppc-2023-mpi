// Copyright 2023 Ivanov Nikita
#include <gtest/gtest.h>
#include <vector>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/collectives.hpp>
#include "task_3/ivanov_constr_conv_jarvis/constr_conv_jarvis.h"

//TEST(Jarvis, test_1) {
//    boost::mpi::communicator world;
//    std::vector<std::vector<int>> image{
//            {0,   0,   0,  0,   0, 0,   0,  0,   0,   0, 0},  // 0
//            {0,   0, 100,  0,   0, 0, 245,  0,   0,   0, 0},  // 1
//            {0,   0, 200,  0,   0, 0,   0,  0,   0,   0, 0},  // 2
//            {0,   0,   0,  0, 241, 0,   0,  0, 251,   0, 0},  // 3
//            {0,   0,   0, 45,   0, 0, 199,  0,   0,   0, 0},  // 4
//            {0, 196,   0,  0,   0, 0,  52,  0,   0,   0, 0},  // 5
//            {0,   0,   0,  0, 203, 0,   0,  0,   0, 211, 0},  // 6
//            {0,   0,   0,  0,   0, 0,   0, 12,   0,   0, 0},  // 7
//            {0,   0, 145,  0,   0, 0,   0,  0,  77,   0, 0}   // 8
//    };
//
//    std::vector<std::pair<int, int>> points = get_points_from_image(image);
//
//    std::vector<P> points_J = Jarvis(points);
//
//    for (int i = 0; i < points_J.size(); i++) {
//        std::cout << " " << points_J[i].x << " " << points_J[i].y << std::endl;
//    }
//    bool all_inside_flag = inside_conv(points_J, points);
//    ASSERT_EQ(all_inside_flag, true);
////    boost::mpi::communicator world;
//}

TEST(Jarvis, test_2) {
    boost::mpi::communicator world;
    int n = 4;
    int m = 4;
    std::vector<std::vector<int>> image(n, std::vector<int> (m));
    if (world.rank() == 0){
        image = create_image(n, m);
        for (int i = 0; i < n; i++)
            boost::mpi::broadcast(world, image.data()[i].data(), m, 0);
    } else {
        for (int i = 0; i < n; i++)
            boost::mpi::broadcast(world, image.data()[i].data(), m, 0);
    }

//    for (int i = 0; i < world.size(); i++) {
//        if (i == world.rank()){
//            world.barrier();
//            std::cout << "Proc id =  " << i << std::endl;
//            for (int j = 0; j < n; j++) {
//                for (int k = 0; k < m; k++) {
//                    std::cout << " " << image[j][k];
//                }
//            }
//            std::cout << std::endl;
//        }
//    }


    std::vector<std::pair<int, int>> points = get_points_from_image(image);

    std::vector<P> points_J = Jarvis(points);

    for (int i = 0; i < points_J.size(); i++) {
        std::cout << " " << points_J[i].x << " " << points_J[i].y << std::endl;
    }
    bool all_inside_flag = inside_conv(points_J, points);
    ASSERT_EQ(all_inside_flag, true);
}
//
//TEST(Jarvis, test_3) {
////    boost::mpi::communicator world;
//    int n = 4;
//    int m = 5;
//    std::vector<std::vector<int>> image = create_image(n, m);
//
//    std::vector<P> points = get_points_from_image(image);
//
//    std::vector<P> points_J = Jarvis(points);
//
//    for (int i = 0; i < points_J.size(); i++) {
//        std::cout << " " << points_J[i].x << " " << points_J[i].y << std::endl;
//    }
//    bool all_inside_flag = inside_conv(points_J, points);
//    ASSERT_EQ(all_inside_flag, true);
//}
//
//TEST(Jarvis, test_4) {
//    int n = 4;
//    int m = 4;
//    std::vector<std::vector<int>> image{
//            {197,   69,   140,  106},
//            {37,   224,   168,  196},
//            {91,   105,   110,  186},
//            {123,   155,   194,  79}
//    };
//
//    std::vector<P> points = get_points_from_image(image);
//
//    std::vector<P> points_J = Jarvis(points);
//
//    for (int i = 0; i < points_J.size(); i++) {
//        std::cout << " " << points_J[i].x << " " << points_J[i].y << std::endl;
//    }
//    bool all_inside_flag = inside_conv(points_J, points);
//    ASSERT_EQ(all_inside_flag, true);
//}
//
//TEST(Jarvis, test_5) {
////    boost::mpi::communicator world;
//    int n = 5;
//    int m = 4;
//    std::vector<std::vector<int>> image = create_image(n, m);
//
//    std::vector<P> points = get_points_from_image(image);
//
//    std::vector<P> points_J = Jarvis(points);
//
//    for (int i = 0; i < points_J.size(); i++) {
//        std::cout << " " << points_J[i].x << " " << points_J[i].y << std::endl;
//    }
//    bool all_inside_flag = inside_conv(points_J, points);
//    ASSERT_EQ(all_inside_flag, true);
//}

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