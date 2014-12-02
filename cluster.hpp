#ifndef CLUSTER_HPP
#define CLUSTER_HPP

struct cluster {
    int index;
    int size;
    cluster* next;
        
    cluster( int index, int size );
};

#endif
