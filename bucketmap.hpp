#include <cstdlib>
#include <ostream>
#include <cstddef>

class BucketMap {

public:
    BucketMap( std::size_t max_size);
    ~BucketMap();

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
        pair* next;
        
        pair( int key, char value ) {
            this->value = value;
            this->key = key;
            this->next = nullptr;
        }

        pair( int key, char value, pair* next ) {
            this->value = value;
            this->key = key;
            this->next = next;
        }
    };
    pair** backing_array;
    std::size_t size;
    std::size_t max_size;
    int hash( int key );
};
