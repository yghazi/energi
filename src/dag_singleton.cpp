// Copyright (c) 2017 Energi Development Team
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "dag_singleton.h"

#include <mutex>

std::unique_ptr<egihash::dag_t> const & ActiveDAG(std::unique_ptr<egihash::dag_t> next_dag)
{
    using namespace std;

    static mutex m;
    lock_guard<mutex> lock(m);
    static unique_ptr<egihash::dag_t> active; // only keep one DAG in memory at once

    // if we have a next_dag swap it
    if (next_dag)
    {
        active.swap(next_dag);
    }

    // unload the previous dag
    if (next_dag)
    {
        next_dag->unload();
        next_dag.reset();
    }

    return active;
}
