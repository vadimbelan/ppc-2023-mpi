// Copyright 2023 Sharapov Georgiy
#ifndef TASKS_TASK_3_SHARAPOV_G_CONV_HULL_CONN_COMP_CONVEX_HULL_H_
#define TASKS_TASK_3_SHARAPOV_G_CONV_HULL_CONN_COMP_CONVEX_HULL_H_

#include <vector>

struct point {
  int x;
  int y;

  void print() { std::cout << "(" << x << ", " << y << ")"; }
};

std::vector<point> convex_hull(int* matrix, size_t n);

#endif  // TASKS_TASK_3_SHARAPOV_G_CONV_HULL_CONN_COMP_CONVEX_HULL_H_
