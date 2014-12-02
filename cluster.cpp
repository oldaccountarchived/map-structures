#include "cluster.hpp"
#include <cstdlib>

#ifndef CLUSTER_CPP
#define CLUSTER_CPP

cluster::cluster( int index, int size ) {
    this->index = index;
    this->size = size;
    this->next = nullptr;
}

#endif
