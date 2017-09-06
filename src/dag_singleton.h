// Copyright (c) 2017 Energi Development Team
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ENERGI_DAG_SINGLETON_H
#define ENERGI_DAG_SINGLETON_H

#include "crypto/egihash.h"

#include <memory>

/** The currently active DAG */
std::unique_ptr<egihash::dag_t> const & ActiveDAG(std::unique_ptr<egihash::dag_t> next_dag = std::unique_ptr<egihash::dag_t>());

#endif
