#include <ostream>
#include <cstdlib>

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
    int insert_at_root( KEY key, VAL value );
    pair** backing_array;
    int free;
    int root;
    std::size_t current_size;
    std::size_t max_size;
    COMP_FUNC comp;
    LT_FUNC lt;
};
