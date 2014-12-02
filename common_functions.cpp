#include <cstdlib>
#include <cstddef>
#include <string>
#include <cmath>
#include <exception>

#ifndef COMMON_FUNCTIONS_CPP
#define COMMON_FUNCTIONS_CPP

// Hashing functions for different types:
inline int int_hash( int key, std::size_t size ) {
    return ( key % size );
}

inline int nrand( int n ) {
    if (n <= 0 || n > RAND_MAX )
        return -1;

    const int bucket_size = RAND_MAX / n;
    int r = 0;

    do {
        r = rand() / bucket_size;
    } while (r >= n);

    return r;
}

inline int double_hash( double key, std::size_t size ) {
    return ( int ) ( fmod(key, 1) * size );
}

inline int cstring_hash( char const* key, std::size_t size ) {
    int i = 0;
    while ( *key )
        i ^= *key++;
    return i % size;
}

inline int string_hash( std::string key, std::size_t size ) {
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
    return std::string(c1) == std::string(c2);
}

inline bool int_compare(int i1, int i2) {
    return i1 == i2;
}

inline bool double_compare(int d1, int d2) {
    return d1 == d2;
}

inline bool string_lt( std::string s1, std::string s2 ) {
    return s1 < s2;
}

inline bool cstring_lt( char const* c1, char const* c2 ) {
    // for(; *c1 == *c2; ++c1, ++c2)
    //     if(*c1 == 0)
    //         return true;
    return std::string(c1) < std::string(c2);
}

inline bool int_lt(int i1, int i2) {
    return i1 < i2;
}

inline bool double_lt(int d1, int d2) {
    return d1 < d2;
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
inline int int_rehash( KEY key, VAL index ) {
    return 0;
}

template <typename KEY, typename VAL>
inline int double_rehash( KEY key, VAL index ) {
    return 0;
}

template <typename KEY, typename VAL>
inline int string_rehash( KEY key, VAL index ) {
    return 0;
}

template <typename KEY, typename VAL>
inline int cstring_rehash( KEY key, VAL index ) {
    return 0;
}

#endif
