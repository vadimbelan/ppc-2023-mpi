// Copyright 2023 Pivovarov Alexey

#ifndef TASKS_TASK_2_PIVOVAROV_A_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_
#define TASKS_TASK_2_PIVOVAROV_A_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_
#include <iostream>
#include <mpi.h>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;

void producer_consumer_seq(int num_producers, int num_consumers, std::vector<int> results);
void producer_consumer_par(int num_producers, int num_consumers, std::vector<int> results);

#endif  // TASKS_TASK_2_PIVOVAROV_A_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_
