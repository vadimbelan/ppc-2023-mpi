// Copyright 2023 Durandin Vladimir
#ifndef __STRONGIN_GLOBAL_SEARCH_H__
#define __STRONGIN_GLOBAL_SEARCH_H__

#include <cstring>
#include <iostream>
#include <mpi.h>
#include <random>
#include <vector>


namespace global_search {
double seq_Strongin_alghorithm(double x0, double x1, double eps);
double paral_Strongin_algorithm(double x0, double x1, double eps);
} // namespace global_search

#endif // __STRONGIN_GLOBAL_SEARCH_H__
