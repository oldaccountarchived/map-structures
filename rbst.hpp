#include <ostream>
#include <cstdlib>
#include "common_functions.cpp"

template <typename KEY, typename VAL, typename COMP_FUNC, typename LT_FUNC>

class RBST {

public:
    RBST( std::size_t max_size, COMP_FUNC comp, LT_FUNC lt );
    ~RBST();

    int insert( KEY key, VAL value );
    int remove( KEY key, VAL &value );
    int search( KEY key, VAL &value );
    void clear();
    bool isEmpty();
    double load();
    std::size_t capacity();
    std::size_t size();
    std::ostream& print( std::ostream& out );
    void cluster_distribution(); // Change this return type.
    // Change this return type. (Should be the type of the key)
    void remove_random();
    
private:
    struct pair {
        VAL value;
        KEY key;
        int left;
        int right;
        
        pair( KEY key, VAL value ) {
            this->value = value;
            this->key = key;
            this->left = -1;
            this->right = -1;
        }

        pair() {
            this->left = -1;
            this->right = -2;
        }
    };
    int insert_at_root( int root_n, int prev, KEY key, VAL value, int count );
    int insert_at_root( KEY key, VAL value);
    void rot_left( int root_n );
    void rot_right( int root_n );
    int find_min( int root_n );
    pair** backing_array;
    int free;
    int root;
    std::size_t current_size;
    std::size_t max_size;
    COMP_FUNC comp;
    LT_FUNC lt;
};
