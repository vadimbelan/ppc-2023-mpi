// Copyright 2023 Pozdnyakov Vasya
#ifndef TASKS_TASK_2_POZDNYAKOV_A_ALLREDUCE_MY_ALLREDUCE_H_
#define TASKS_TASK_2_POZDNYAKOV_A_ALLREDUCE_MY_ALLREDUCE_H_

#include <mpi.h>
#include <cstdlib>
#include <cstring>

int local_reduce(const void *sendbuf, void *recvbuf, int count,
    MPI_Datatype datatype, MPI_Op op);

int allreduce(const void *sendbuf, void *recvbuf, int cout,
    MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);

template <typename T>
int operation_int(const void* inbuf, void* accbuf, int count, MPI_Op op) {
    int ret_status = operation<T>(inbuf, accbuf, count, op);
    const T *inbuf_cast = reinterpret_cast<const T*>(inbuf);
    T *accbuf_cast = reinterpret_cast<T*>(accbuf);
    if (ret_status != MPI_SUCCESS) {
        switch (op) {
            case MPI_BAND: {
                for (int i = 0; i < count; i++)
                    accbuf_cast[i] &= inbuf_cast[i];
                break;
            }
            case MPI_BOR: {
                for (int i = 0; i < count; i++)
                    accbuf_cast[i] |= inbuf_cast[i];
                break;
            }
            case MPI_BXOR: {
                for (int i = 0; i < count; i++)
                    accbuf_cast[i] ^= inbuf_cast[i];
                break;
            }
            default: {
                ret_status = MPI_ERR_OP;
            }
        }
    }
    return ret_status;
}

template <typename T>
int operation(const void* inbuf, void* accbuf, int count, MPI_Op op) {
    const T *inbuf_cast = reinterpret_cast<const T*>(inbuf);
    T *accbuf_cast = reinterpret_cast<T*>(accbuf);
    int ret_status = MPI_SUCCESS;
    switch (op) {
        case MPI_MAX: {
            for (int i = 0; i < count; i++)
                if (inbuf_cast[i] > accbuf_cast[i])
                    accbuf_cast[i] = inbuf_cast[i];
            break;
        }
        case MPI_MIN: {
            for (int i = 0; i < count; i++)
                if (inbuf_cast[i] < accbuf_cast[i])
                    accbuf_cast[i] = inbuf_cast[i];
            break;
        }
        case MPI_SUM: {
            for (int i = 0; i < count; i++)
                accbuf_cast[i] += inbuf_cast[i];
            break;
        }
        case MPI_PROD: {
            for (int i = 0; i < count; i++)
                accbuf_cast[i] *= inbuf_cast[i];
            break;
        }
        case MPI_LAND: {
            for (int i = 0; i < count; i++)
                accbuf_cast[i] = static_cast<bool>(accbuf_cast[i])
                    && static_cast<bool>(inbuf_cast[i]);
            break;
        }
        case MPI_LOR: {
            for (int i = 0; i < count; i++)
                accbuf_cast[i] = static_cast<bool>(accbuf_cast[i])
                    || static_cast<bool>(inbuf_cast[i]);
            break;
        }
        case MPI_LXOR: {
            for (int i = 0; i < count; i++)
                accbuf_cast[i] = !static_cast<bool>(accbuf_cast[i])
                    != !static_cast<bool>(inbuf_cast[i]);
            break;
        }
        default: {
            ret_status = MPI_ERR_OP;
        }
    }
    return ret_status;
}

#endif  // TASKS_TASK_2_POZDNYAKOV_A_ALLREDUCE_MY_ALLREDUCE_H_
