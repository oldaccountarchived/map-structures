#include "rbst.hpp"

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::RBST( std::size_t max_size,
                                          COMP_FUNC comp, LT_FUNC lt ) {
    this->backing_array = new pair*[max_size];
    this->max_size = max_size;
    this->size = 0;
    this->comp = comp;
    this->lt = lt;
    for ( int i = 0; i != max_size; ++i ) {
        if ( i != max_size - 1 ) {
            backing_array[i] = new pair();
            // Set left to next free node;
            backing_array[i]->left = i + 1;
        } else {
            backing_array[i] = new pair();
        }
    }
    this->free = 0;
    this->root = -1;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::insert( KEY key, VAL value ) {
    int current = root;
    if ( current == -1 ) {
        int new_free = backing_array[free]->left;
        delete backing_array[free];
        backing_array[free] = new pair( key, value );
        free = new_free;
        return 0;
    }
    
    int counter = 1;
    while ( current != -1 ) {
        if ( lt( key, backing_array[current]->key ) ) {
            if ( backing_array[current]->left == -1 ) {
                backing_array[current]->left = free;
                int new_free = backing_array[free]->left;
                delete backing_array[free];
                backing_array[free] = new pair( key, value );
                free = new_free;
                return counter;
            } else {
                current = backing_array[current]->left;
            }
        } else {
            if ( lt( key, backing_array[current]->key ) ) {
                if ( backing_array[current]->right == -1 ) {
                    backing_array[current]->right = free;
                    int new_free = backing_array[free]->left;
                    delete backing_array[free];
                    backing_array[free] = new pair( key, value );
                    free = new_free;
                    return counter;
                } else {
                    current = backing_array[current]->right;
                }
            }
        }
    }
    return counter * -1;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::search( KEY key, VAL &value ) {
    int current = root;
    if ( comp( backing_array[current]->key, key ) ) {
        value = backing_array[current]->value;
        return 0;
    }
    int counter = 0;
    while ( current != -1 ) {
        if ( comp( key, backing_array[current]->key) ) {
            value = backing_array[current]->value;
            return counter;
        } else if ( lt( key, backing_array[current]->key ) ) {
            counter++;
            current = backing_array[current]->left;
        } else {
            counter++;
            current = backing_array[current]->right;
        }
    }
    return counter * -1;
}
