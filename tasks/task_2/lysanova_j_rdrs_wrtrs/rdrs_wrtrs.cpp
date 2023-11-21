// Copyright 2023 Lysanova Julia
#include <utility>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include "task_2/lysanova_j_rdrs_wrtrs/rdrs_wrtrs.h"



std::pair<std::queue<std::pair<int, int>>, std::vector<int>> rdrs_wrtrs_boost() {
    boost::mpi::communicator world;
    int shared_data = 0;
    int role;

    if (world.rank() == 0) {
        std::queue<std::pair<int, int>> q;
        for (int i = 0; i < world.size() - 1; i++) {
            auto status = world.recv(MPI_ANY_SOURCE, 0, role);
            q.push({status.source(), role});
            if (role == 1) {
                world.recv(status.source(), 1, shared_data);
            } else {
                world.send(status.source(), 1, shared_data);
            }
        }
        std::vector<int> datas(world.size());
        boost::mpi::gather(world, shared_data, datas, 0);
        datas[0] = shared_data;
        world.barrier();
        return {q, datas};
    } else {
        role = world.rank() % 2;
        world.send(0, 0, role);
        if (role == 1) {
            shared_data = world.rank() * 10;
            world.send(0, 1, shared_data);
        } else {
            world.recv(0, 1, shared_data);
        }
        boost::mpi::gather(world, shared_data, 0);
        world.barrier();
        return {{}, {}};
    }
}
