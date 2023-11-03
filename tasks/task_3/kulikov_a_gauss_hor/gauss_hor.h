// Copyright 2023 Kulikov Artem
#ifndef TASKS_TASK_2_KULIKOV_A_GAUSS_HOR_GAUSS_HOR_H_
#define TASKS_TASK_2_KULIKOV_A_MIN_IN_MATR_MIN_IN_MATR_H_

#include <vector>
#include <boost/serialization/vector.hpp>

std::vector<double> get3x3GaussKernel(double sd);
uint32_t getPxSum(std::vector<uint8_t>& pic, int n);
std::vector<uint8_t> getExtPicture(int n);
std::vector<uint8_t> getParallelGauss(std::vector<uint8_t>& orig, std::vector<double>& kernel, int n);
std::vector<uint8_t> getSequentialGauss(std::vector<uint8_t>& orig, std::vector<double>& kernel, int n);

#endif  // TASKS_TASK_2_KULIKOV_A_MIN_IN_MATR_MIN_IN_MATR_H_
