// Copyright 2023 Pivovarov Alexey

#ifndef TASKS_TASK_2_PIVOVAROV_A_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_
#define TASKS_TASK_2_PIVOVAROV_A_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_

#include <mpi.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cstdio>
using namespace std;

void producer_consumer_seq(int num_producers, int num_consumers, vector<int> results);
void producer_consumer_par(int num_producers, int num_consumers, vector<int> results);

#endif  // TASKS_TASK_2_PIVOVAROV_A_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_
