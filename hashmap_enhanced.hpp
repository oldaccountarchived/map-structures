#include <ostream>
#include <cstdlib>

class EnhHashMap {

public:
    EnhHashMap(unsigned int max_size);
    ~EnhHashMap();

    int insert( char key, int value );
    int remove( char key, int &value );
    int search( char key, int &value );
    void clear();
    bool isEmpty();
    std::size_t capacity();
    std::ostream& print( std::ostream& out );
    void cluster_distribution(); // Change this return type.
    // Change this return type. (Should be the type of the key)
    void remove_random(); 
    
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
