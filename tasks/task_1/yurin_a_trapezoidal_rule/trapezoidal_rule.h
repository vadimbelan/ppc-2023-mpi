// Copyright 2023 Nesterov Alexander
#ifndef TASKS_EXAMPLES_TEST_MPI_OPS_MPI_H_
#define TASKS_EXAMPLES_TEST_MPI_OPS_MPI_H_

#include <functional>

double IntegrateWithTrapezoidRuleSequential(
        const std::function<double(const double argument)>& function,
        double leftBound,
        double rightBound,
        double step
        );

double IntegrateWithTrapezoidRuleParallel(
        const std::function<double(const double argument)>& function,
        double leftBound,
        double rightBound,
        double step
        );


#endif  // TASKS_EXAMPLES_TEST_MPI_OPS_MPI_H_
