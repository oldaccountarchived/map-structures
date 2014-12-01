#include "hashmap_enhanced.hpp"
#include <cstddef>
#include <iostream>
#include <cmath>

// Hashing functions for different types:
inline int int_hash( int key, size_t size ) {
    return ( key % size );
}

inline int double_hash( double key, size_t size ) {
    return ( int ) ( fmod(key, 1) * size );
}

inline int cstring_hash( char const* key, size_t size ) {
    int i = 0;
    while ( *key )
        i ^= *key++;
    return i % size;
}

inline int string_hash( std::string key, size_t size ) {
    int i = 0;
    for (int j = 0; j < key.length(); j++) {
        i ^= key.at(i);
    }
    return i % size;
}

// Comparison functions for different types:
inline bool string_compare( std::string s1, std::string s2 ) {
    return s1 == s2;
}

inline bool cstring_compare( char const* c1, char const* c2 ) {
    // for(; *c1 == *c2; ++c1, ++c2)
    //     if(*c1 == 0)
    //         return true;
    if ( std::string(c1) == std::string(c2) ) {
        return true;
    } else {
        return false;
    }
}

inline bool int_compare(int i1, int i2) {
    return i1 == i2;
}

inline bool double_compare(int d1, int d2) {
    return d1 == d2;
}

// Probing functions:
template <typename KEY, typename VAL>
inline int linear_probe( KEY key, VAL index ) {
    return index;
}

template <typename KEY, typename VAL>
inline int quadratic_probe( KEY key, VAL index ) {
    return (index * index);
}

// Rehashing for different types:
template <typename KEY, typename VAL>
inline int rehash( KEY key, VAL index ) {
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
