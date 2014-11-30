#include "hashmap_enhanced.hpp"
#include <cstddef>
#include <iostream>
#include <cmath>

// Hashing functions for different types:
int int_hash( int key, size_t size ) {
    return ( key % size );
}

int double_hash( double key, size_t size ) {
    return ( int ) ( fmod(key, 1) * size );
}

int cstring_hash( const char* key, size_t size ) {
    int i = 0;
    while ( *key )
        i ^= *key++;
    return i % size;
}

int string_hash( std::string key, size_t size ) {
    int i = 0;
    for (int j = 0; j < key.length(); j++) {
        i ^= key.at(i);
    }
    return i % size;
}

// Comparison functions for different types:
bool string_compare( std::string s1, std::string s2 ) {
    return !s1.compare(s2);
}

bool cstring_compare( const char* c1, const char* c2 ) {
    for(; *c1 == *c2; ++c1, ++c2)
        if(*c1 == 0)
            return true;
    return false;
}

bool int_compare(int i1, int i2) {
    return i1 == i2;
}

bool double_compare(int d1, int d2) {
    return d1 == d2;
}

// Probing functions:
template <typename KEY, typename VAL>
int linear_probe( KEY key, VAL index, size_t size ) {
    return ( (index + 1) % size );
}

template <typename KEY, typename VAL>
int quadratic_probe( KEY key, VAL index, size_t size ) {
    return ( (index * index) % size );
}

// Rehashing for different types:
template <typename KEY, typename VAL>
int rehash( KEY key, VAL index, size_t size ) {
    return 0;
}

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
    int index = hash(key);
    if ( this->backing_array[index] == nullptr ) {
        this->backing_array[index] = item;
        ++size;
        return 0;
    } else {
        int counter = 0;
        int i = index;
        do {
            i = probe(key, i, max_size);
            ++counter;
            if ( this->backing_array[i] == nullptr ) {
                this->backing_array[i] = item;
                ++size;
                return counter;
            }
        } while ( i != index );
        
        // There's no spot to insert this value.
        return -1;
    }
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
int EnhHashMap<KEY, VAL, HASH_FUNC,
               PROBE_FUNC, COMP_FUNC>::remove( KEY key, VAL &value ) {
    int index = hash(key);
    if ( backing_array[index]->key.comp( key ) ) {
        value = backing_array[index]->value;
        backing_array[index] = nullptr;
        --size;
        int i = index;
        do {
            i = probe(key, i, max_size);
            if ( backing_array[i] == nullptr ) {
                break;
            }
            pair* temp = backing_array[i];
            backing_array[i] = nullptr;
            insert( temp->key, temp->value );
        } while ( i != index );
        return 0;
    } else {
        int counter = 0;
        int i = index;
        do {
            i = probe(key, i, max_size);
            ++counter;
            if ( this->backing_array[i].comp( key ) ) {
                 value = backing_array[index]->value;
                 backing_array[index] = nullptr;
                 --size;
                 int j = i;
                 do {
                     j = probe(key, j, max_size);
                     if ( backing_array[i] == nullptr ) {
                         break;
                     }
                     pair* temp = backing_array[j];
                     backing_array[j] = nullptr;
                     insert( temp->key, temp->value );
                 } while ( j != i );
                 return counter;
            }
        } while ( i != index ); 
        return -1;
        
         for ( int i = index + 1; i != index; ++i ) {
            if ( i == max_size ) { // Wrap around
                i = 0;
            }
            if ( backing_array[i]->key == key ) {
                 value = backing_array[i]->value;
                 backing_array[i] = nullptr;
                 --size;
                 for ( int j = i + 1; j != i; ++j ) {
                     if ( j == max_size ) {
                         j = 0;
                     }
                     if ( backing_array[j] == nullptr ) {
                         break;
                     }
                     pair* temp = backing_array[j];
                     backing_array[j] = nullptr;
                     insert( temp->key, temp->value );
                 }
                 return true;
            }
         }
         return false;
    }
}

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>
int EnhHashMap<KEY, VAL, HASH_FUNC,
               PROBE_FUNC, COMP_FUNC>::search( KEY key, VAL &value ) {
    int index = hash(key);
    if ( backing_array[index]->key == key ) {
        value = backing_array[index]->value;
        return 0;
    } else {
        int counter = 0;
        int i = index;
        do {
            i = probe(key, i, max_size);
            ++counter;
            // Change this to use compare function...
            if ( this->backing_array[i]->key.comp(key) ) {
                value = this->backing_array[i]->value;
                return counter;
            }
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
std::ostream& EnhHashMap<KEY, VAL, HASH_FUNC,
                         PROBE_FUNC, COMP_FUNC>::print( std::ostream& out ) {
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            out << "position: " << i
                << ", key: " << backing_array[i]->key
                << ", val: " << backing_array[i]->value << std::endl;
        }
    }
    return out;
}
