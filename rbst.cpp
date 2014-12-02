#include "rbst.hpp"
#include <iostream>

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::RBST( std::size_t max_size,
                                          COMP_FUNC comp, LT_FUNC lt ) {
    this->backing_array = new pair*[max_size];
    this->max_size = max_size;
    this->current_size = 0;
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
RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::~RBST() {
    delete[] backing_array;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::insert( KEY key, VAL value ) {
    if ( current_size == max_size ) {
        return -1;
    }
    if ( nrand( current_size ) == current_size / 2 ) {
        return insert_at_root( key, value );
    } else {
        int current = root;
        if ( current == -1 ) {
            int new_free = backing_array[free]->left;
            delete backing_array[free];
            backing_array[free] = new pair( key, value );
            root = free;
            free = new_free;
            ++current_size;
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
                    ++current_size;
                    return counter;
                } else {
                    current = backing_array[current]->left;
                }
            } else {
                if ( backing_array[current]->right == -1 ) {
                    backing_array[current]->right = free;
                    int new_free = backing_array[free]->left;
                    delete backing_array[free];
                    backing_array[free] = new pair( key, value );
                    free = new_free;
                    ++current_size;
                    return counter;
                } else {
                    current = backing_array[current]->right;
                }
            }
        }
        return counter * -1;
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::insert_at_root( int root_n, int prev,
                                                        KEY key, VAL value,
                                                        int count ) {
    if ( root_n == -1 ) {
        if ( prev == -1 ) {
            int new_free = backing_array[free]->left;
            delete backing_array[free];
            root = free;
            backing_array[root] = new pair(key, value);
            free = new_free;
            ++current_size;
            return count;
        } else if ( lt( key, backing_array[prev]->key ) ) {
            int new_free = backing_array[free]->left;
            backing_array[prev]->left = free;
            delete backing_array[free];
            backing_array[free] = new pair(key, value);
            free = new_free;
            ++current_size;
            return count;
        } else {
            int new_free = backing_array[free]->left;
            backing_array[prev]->right = free;
            delete backing_array[free];
            backing_array[free] = new pair(key, value);
            free = new_free;
            ++current_size;
            return count;
        }
    } else if ( lt( key, backing_array[root_n]->key ) ) {
        insert_at_root( backing_array[root_n]->left, root_n, key,
                        value, count + 1 );
        rot_right(root_n);
    } else {
        insert_at_root( backing_array[root_n]->right, root_n, key,
                        value, count + 1 );
        rot_left(root_n);
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
void RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::rot_left( int root_n ) {
    pair* temp = backing_array[root_n];
    int old_root = root_n;
    int right = backing_array[root_n]->right;
    backing_array[root_n] = backing_array[right];
    temp->right = backing_array[root_n]->left;
    backing_array[root_n]->left = old_root;
    backing_array[old_root] = temp;
    if ( root == old_root ) {
        root = right;
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
void RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::rot_right( int root_n ) {
    pair* temp = backing_array[root_n];
    int old_root = root_n;
    int left = backing_array[root_n]->left;
    backing_array[root_n] = backing_array[left];
    temp->left = backing_array[root_n]->right;
    backing_array[root_n]->right = old_root;
    backing_array[old_root] = temp;
    if ( root == old_root ) {
        root = left;
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::insert_at_root( KEY key, VAL value) {
    insert_at_root( root, -1, key, value, 0 );
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::remove( KEY key, VAL &value ) {
    int current = root;
    int prev = -1;
    int counter = 0;
    while ( current != -1 ) {
        if ( comp( backing_array[current]->key, key ) ) {
            value = backing_array[current]->value;
            if (backing_array[current]->left == -1) {
                if ( current == root ) {
                    root = backing_array[current]->right;
                } else {
                    if ( backing_array[prev]->left == current ) {
                        backing_array[prev]->left = backing_array[current]->right;
                    } else {
                        backing_array[prev]->right = backing_array[current]->right;
                    }
                }
                backing_array[current] = new pair();
                backing_array[current]->left = free;
                free = current;
                --current_size;
                return counter;
            } else if ( backing_array[current]->right == -1 ) {
                if ( current == root ) {
                    root = backing_array[current]->left;
                } else {
                    if ( backing_array[prev]->left == current ) {
                        backing_array[prev]->left = backing_array[current]->left;
                    } else {
                        backing_array[prev]->right = backing_array[current]->left;
                    }
                }
                backing_array[current] = new pair();
                backing_array[current]->left = free;
                free = current;
                --current_size;
                return counter;
            } else {
                int min_index = find_min( backing_array[current]->right );
                if ( min_index != backing_array[current]->right ) {
                    backing_array[min_index]->right = backing_array[current]->right;
                }
                backing_array[min_index]->left = backing_array[current]->left;
                if ( current == root ) {
                    root = min_index;
                } else {
                    if ( backing_array[prev]->left == current ) {
                        backing_array[prev]->left = min_index;
                    } else {
                        backing_array[prev]->right = min_index;
                    }
                }
                backing_array[current] = new pair();
                backing_array[current]->left = free;
                free = current;
                --current_size;
                return counter;
            }
        } else {
            ++counter;
            if ( lt( key, backing_array[current]->key ) ) {
                prev = current;
                current = backing_array[current]->left;
            } else {
                prev = current;
                current = backing_array[current]->right;
            }
        }
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::search( KEY key, VAL &value ) {
    int current = root;
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
    if ( counter == 0 )
        return -1;
    return counter * -1;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
int RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::find_min( int root_n ) {
    while (backing_array[root_n]->left != -1) {
        root_n = backing_array[root_n]->left;
    }
    return root_n;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
void RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::clear() {
    delete[] backing_array;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
bool RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::isEmpty() {
    return current_size == 0;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
std::size_t RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::size() {
    return current_size;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
std::size_t RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::capacity() {
    return max_size;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
double RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::load() {
    return ((double) current_size) / ((double) max_size);
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>
std::ostream& RBST<KEY, VAL, COMP_FUNC, LT_FUNC>::print( std::ostream& out ) {
    out << "[ ";
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i]->right != -2 ) {
            out << backing_array[i]->key;
            out << ", " << backing_array[i]->left;
            out << ", " << backing_array[i]->right;
        } else {
            out << "-";
        }

        if ( i != max_size - 1 ) {
            out << " | ";
        }
    }
    out << " ]";
    return out;
}
