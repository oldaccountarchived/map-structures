#include <cstdlib>
#include <cstddef>
#include <ostream>

class BucketMap {

public:
    BucketMap(unsigned int max_size);
    ~BucketMap();

    bool insert( char key, int value );
    bool remove( char key, int &value );
    bool search( char key, int &value );
    void clear();
    bool isEmpty();
    std::size_t capacity();
    std::ostream& print( std::ostream& out );

private:
    struct pair {
        int value;
        char key;
        pair* next;
        
        pair( char key, int value ) {
            this->value = value;
            this->key = key;
            this->next = nullptr;
        }

        pair( char key, int value, pair* next ) {
            this->value = value;
            this->key = key;
            this->next = next;
        }
    };
    pair** backing_array;
    unsigned int size;
    unsigned int max_size;
    int hash( char key );
};
