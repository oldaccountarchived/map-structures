#include <cstdlib>

class HashMap {

public:
    HashMap(unsigned int max_size);
    ~HashMap();

    bool insert( char key, int value );
    bool remove( char key, int &value );
    bool search( char key, int &value );
    void clear();
    bool isEmpty();
    std::size_t capacity();
    void print();

private:
    struct pair {
        int value;
        char key;

        pair( char key, int value ) {
            this->value = value;
            this->key = key;
        }
    };
    pair** backing_array;
    unsigned int size;
    unsigned int max_size;
    int hash( char key );
};
