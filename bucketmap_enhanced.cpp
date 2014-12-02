#include "bucketmap_enhanced.hpp"

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::EnhBucketMap(std::size_t max_size,
                                                           COMP_FUNC comp,
                                                           HASH_FUNC hash) {
    this->backing_array = new pair*[max_size];
    this->comp = comp;
    this->hash = hash;
    this->size = 0;
    this->max_size = max_size;
    for ( int i = 0; i != max_size; ++i )
        backing_array[i] = nullptr;
}


template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::~EnhBucketMap() {
    delete[] backing_array;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
int EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::insert( KEY key, VAL value ) {
    if ( size == max_size ) {
        return false;
    }
    pair* item = new pair( key, value );
    int index = hash(key, max_size);
    if ( this->backing_array[index] == nullptr ) {
        this->backing_array[index] = item;
        ++size;
        return true;
    } else {
        pair* temp = backing_array[index];
        while ( temp->next != nullptr ) { 
            temp = temp->next;
        }
        temp->next = item;
        return true;
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
int EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::remove( KEY key, VAL &value ) {
    int index = hash(key, max_size);
    if ( comp( backing_array[index]->key, key ) ) {
        value = backing_array[index]->value;
        // This may leak memory
        backing_array[index] = backing_array[index]->next;
        --size;
        return true;
    } else {
        pair* temp = backing_array[index];
        while ( temp->next != nullptr ) {
            if ( temp->next->key == key ) {
                value = temp->next->value;
                temp->next = temp->next->next;
                --size;
                return true;
            }
            temp = temp->next;
        }
        // We found nothing so...
        return false;
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
int EnhBucketMap<KEY, VAL,
                 COMP_FUNC, HASH_FUNC>::search( KEY key, VAL &value ) {
    int index = hash(key, max_size);
    if ( comp( backing_array[index]->key, key ) ) {
        value = backing_array[index]->value;
        return true;
    } else {
        pair* temp = backing_array[index];
        while ( temp->next != nullptr ) {
            if ( temp->next->key == key ) {
                value = temp->next->value;
                return true;
            }
            temp = temp->next;
        }
        // We found nothing so...
        return false;
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
void EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::clear() {
    for ( int i = 0; i != max_size; ++i ) {
        backing_array[i] = nullptr;
    }
    this->size = 0;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
bool EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::isEmpty() {
    if ( size == 0 ) {
        return true;
    } else {
        return false; 
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
std::size_t EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::capacity() {
    return size;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
KEY EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::remove_random() {
    int counter = nrand( size );
    int j = 0;
    
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            pair* current = backing_array[i];
            do {
                ++j;
                if ( j == counter ) {
                    KEY key = current->key;
                    int garbage_val = 0;
                    remove(key, garbage_val);
                    return key;
                }
                current = current->next;
            } while( current != nullptr );
        }
    }
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
cluster* EnhBucketMap<KEY, VAL, COMP_FUNC, HASH_FUNC>::cluster_distribution() {
    cluster* head = new cluster( 0, 0 );
    cluster* current = head;
    int cluster_size = 1;
    for ( int i = 0; i < max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            pair* curr_pair = backing_array[i]->next;
            while ( curr_pair != nullptr ) {
                ++cluster_size;
                curr_pair = curr_pair->next;
            }
            if ( cluster_size > 1 ) {
                current->next = new cluster(i, cluster_size);
                current = current->next;
                cluster_size = 1;
            }
        }
    }
    current = head;
    head = head->next;
    delete current;
    return head;
}

template <typename KEY, typename VAL, typename COMP_FUNC, typename HASH_FUNC>
std::ostream& EnhBucketMap<KEY, VAL,
                           COMP_FUNC, HASH_FUNC>::print( std::ostream& out ) {
    out << "[ ";
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            out << backing_array[i]->key;
            pair* temp = backing_array[i];
            while ( temp->next != nullptr ) {
                temp = temp->next;
                out << ", " << temp->key;
            }
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
