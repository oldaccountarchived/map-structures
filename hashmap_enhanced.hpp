#include <ostream>
#include <cstdlib>

template <typename KEY, typename VAL, typename HASH_FUNC,
          typename PROBE_FUNC, typename COMP_FUNC>

class EnhHashMap {

public:
    EnhHashMap(std::size_t max_size, HASH_FUNC hash, PROBE_FUNC probe,
               COMP_FUNC comp);
    
    ~EnhHashMap();

    int insert( KEY key, VAL value );
    int remove( KEY key, VAL &value );
    int search( KEY key, VAL &value );
    void clear();
    bool isEmpty();
    std::size_t capacity();
    std::ostream& print( std::ostream& out );
    void cluster_distribution(); // Change this return type.
    // Change this return type. (Should be the type of the key)
    void remove_random(); 
    
private:
    struct pair {
        VAL value;
        KEY key;

        pair( KEY key, VAL value ) {
            this->value = value;
            this->key = key;
        }
    };
    pair** backing_array;
    std::size_t size;
    std::size_t max_size;
    HASH_FUNC hash;
    COMP_FUNC comp;
    PROBE_FUNC probe;
};
