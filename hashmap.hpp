#include <ostream>
#include <cstdlib>
#include <cstddef>

class HashMap {

public:
    HashMap( std::size_t max_size );
    ~HashMap();

    bool insert( int key, char value );
    bool remove( int key, char &value );
    bool search( int key, char &value );
    void clear();
    bool isEmpty();
    std::size_t capacity();
    std::ostream& print( std::ostream& out );

private:
    struct pair {
        int key;
        char value;

        pair( int key, char value ) {
            this->value = value;
            this->key = key;
        }
    };
    
    pair** backing_array;
    std::size_t size;
    std::size_t max_size;
    int hash( int key );
};
