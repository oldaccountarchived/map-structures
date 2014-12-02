#include "hashmap_enhanced.hpp"

// EnhHashMap Implementation:
template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
EnhHashMap<KEY, VAL, HASH_FUNC,
           PROBE_FUNC, COMP_FUNC>::EnhHashMap(std::size_t max_size,
                                              HASH_FUNC hash,
                                              PROBE_FUNC probe,
                                              COMP_FUNC comp) {
    this->probe = probe;
    this->hash = hash;
    this->comp = comp;
    this->backing_array = new pair*[max_size];
    this->size = 0;
    this->max_size = max_size;
    for ( int i = 0; i != max_size; ++i )
        backing_array[i] = nullptr;
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
EnhHashMap<KEY, VAL, HASH_FUNC, PROBE_FUNC, COMP_FUNC>::~EnhHashMap() {
    delete[] backing_array;
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
int EnhHashMap<KEY, VAL, HASH_FUNC,
               PROBE_FUNC, COMP_FUNC>::insert( KEY key, VAL value ) {
    if ( size == max_size ) {
        return -1;
    }
    pair* item = new pair( key, value );
    int index = hash(key, max_size);
    if ( this->backing_array[index] == nullptr ) {
        this->backing_array[index] = item;
        ++size;
        return 0;
    } else {
        int counter = 1;
        int i = index;
        do {
            i = ( ( i + probe(key, counter) ) % max_size );
            if ( this->backing_array[i] == nullptr ) {
                this->backing_array[i] = item;
                ++size;
                return counter;
            }
            ++counter;
        } while ( i != index );
        
        // There's no spot to insert this value.
        return -1;
    }
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
int EnhHashMap<KEY, VAL, HASH_FUNC,
               PROBE_FUNC, COMP_FUNC>::remove( KEY key, VAL &value ) {
    int index = hash(key, max_size);
    if ( comp( key, this->backing_array[index]->key ) ) {
        value = backing_array[index]->value;
        backing_array[index] = nullptr;
        --size;
        int i = index;
        int counter = 1;
        do {
            i = ( ( i + probe(key, counter) ) % max_size );
            if ( backing_array[i] == nullptr ) {
                break;
            }
            pair* temp = backing_array[i];
            backing_array[i] = nullptr;
            insert( temp->key, temp->value );
        } while ( i != index );
        return 0;
    } else {
        int counter = 1;
        int i = index;
        do {
            i = ( ( i + probe(key, counter) ) % max_size );
            if ( comp( key, this->backing_array[i]->key ) ) {
                 value = backing_array[i]->value;
                 backing_array[index] = nullptr;
                 --size;
                 int j = i;
                 int counter2 = counter;
                 do {
                     j = ( ( j + probe(key, counter2) ) % max_size );
                     if ( backing_array[j] == nullptr ) {
                         break;
                     }
                     pair* temp = backing_array[j];
                     backing_array[j] = nullptr;
                     insert( temp->key, temp->value );
                 } while ( j != i );
                 return counter;
            }
            ++counter;
        } while ( i != index ); 
        return -1;
    }
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
int EnhHashMap<KEY, VAL, HASH_FUNC,
               PROBE_FUNC, COMP_FUNC>::search( KEY key, VAL &value ) {
    int index = hash(key, max_size);
    if ( backing_array[index]->key == key ) {
        value = backing_array[index]->value;
        return 0;
    } else {
        int counter = 1;
        int i = index;
        do {
            i = ( (i + probe(key, counter)) % max_size );
            // Change this to use compare function...
            if ( comp( key, this->backing_array[i]->key ) ) {
                value = this->backing_array[i]->value;
                return counter;
            }
            ++counter;
        } while ( i != index );
        return -1;
    }
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
void EnhHashMap<KEY, VAL, HASH_FUNC, PROBE_FUNC, COMP_FUNC>::clear() {
    for ( int i = 0; i != max_size; ++i ) {
        backing_array[i] = nullptr;
    }
    this->size = 0;
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
bool EnhHashMap<KEY, VAL, HASH_FUNC, PROBE_FUNC, COMP_FUNC>::isEmpty() {
    if ( size == 0 ) {
        return true;
    } else {
        return false; 
    }
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
std::size_t EnhHashMap<KEY, VAL, HASH_FUNC, PROBE_FUNC, COMP_FUNC>::capacity() {
    return size;
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
KEY EnhHashMap<KEY, VAL, HASH_FUNC, PROBE_FUNC, COMP_FUNC>::remove_random() {
    int counter = nrand( size );
    int j = 0;
    
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            ++j;
            if ( j == counter ) {
                KEY key = backing_array[i]->key;
                int garbage_val = 0;
                remove(key, garbage_val);
                return key;
            }
        }
    }
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
cluster* EnhHashMap<KEY, VAL, HASH_FUNC,
                    PROBE_FUNC, COMP_FUNC>::cluster_distribution() {
    cluster* head = new cluster( 0, 0 );
    cluster* current = head;
    int j = 0;
    int cluster_size = 1;
    for ( int i = 0; i < max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            j = i + 1;
            while ( backing_array[j] != nullptr ) {
                ++cluster_size;
                ++j;
            }
            if ( cluster_size > 1 ) {
                current->next = new cluster(i, cluster_size);
                current = current->next;
                i = j - 1;
                cluster_size = 1;
            }
        }
    }
    current = head;
    head = head->next;
    delete current;
    return head;
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
std::ostream& EnhHashMap<KEY, VAL, HASH_FUNC,
                         PROBE_FUNC, COMP_FUNC>::print( std::ostream& out ) {
    out << "[ ";
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            out << backing_array[i]->key;
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
