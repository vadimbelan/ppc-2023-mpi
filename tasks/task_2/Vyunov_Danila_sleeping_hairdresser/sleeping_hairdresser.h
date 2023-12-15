// Copyright 2023 Vyunov Danila
#ifndef TASKS_TASK_2_VYUNOV_DANILA_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_
#define TASKS_TASK_2_VYUNOV_DANILA_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_

void barber(int myrank, int chairs_count, int ccount);
void customer(int myrank);
void line(int chairs_count, int runs);
#define CHAIR_REQUEST  1
#define CHAIR_RESPONSE  2
#define HAIR_CUT_REQUEST 3
#define HAIR_CUT 4
#endif  // TASKS_TASK_2_VYUNOV_DANILA_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_
