#include "bucketmap.hpp"

BucketMap::BucketMap(std::size_t max_size) {
    this->backing_array = new pair*[1024];
    this->size = 0;
    this->max_size = max_size;
    for ( int i = 0; i != max_size; ++i )
        backing_array[i] = nullptr;
}

BucketMap::~BucketMap() {
    delete[] backing_array;
}

int BucketMap::hash( int key ) {
    return ( (int) key % max_size );
}

bool BucketMap::insert( int key, char value ) {
    if ( size == max_size ) {
        return false;
    }
    pair* item = new pair( key, value );
    int index = hash(key);
    if ( this->backing_array[index] == nullptr ) {
        this->backing_array[index] = item;
        ++size;
        return true;
    } else {
        pair* temp = backing_array[index];
        while ( temp->next != nullptr ) {
            temp = temp->next;
        }
        temp->next = item;
        return true;
    }
}

bool BucketMap::remove( int key, char &value ) {
    int index = hash(key);
    if ( backing_array[index]->key == key ) {
        value = backing_array[index]->value;
        // This may leak memory
        backing_array[index] = backing_array[index]->next;
        --size;
        return true;
    } else {
        pair* temp = backing_array[index];
        while ( temp->next != nullptr ) {
            if ( temp->next->key == key ) {
                value = temp->next->value;
                temp->next = temp->next->next;
                --size;
                return true;
            }
            temp = temp->next;
        }
        // We found nothing so...
        return false;
    }
}

bool BucketMap::search( int key, char &value ) {
    int index = hash(key);
    if ( backing_array[index]->key == key ) {
        value = backing_array[index]->value;
        return true;
    } else {
        pair* temp = backing_array[index];
        while ( temp->next != nullptr ) {
            if ( temp->next->key == key ) {
                value = temp->next->value;
                return true;
            }
            temp = temp->next;
        }
        // We found nothing so...
        return false;
    }
}

void BucketMap::clear() {
    for ( int i = 0; i != max_size; ++i ) {
        backing_array[i] = nullptr;
    }
    this->size = 0;
}

bool BucketMap::isEmpty() {
    if ( size == 0 ) {
        return true;
    } else {
        return false; 
    }
}

std::size_t BucketMap::capacity() {
    return size;
}

std::ostream& BucketMap::print( std::ostream& out ) {
    out << "[ ";
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            out << backing_array[i]->key;
            pair* temp = backing_array[i];
            while ( temp->next != nullptr ) {
                temp = temp->next;
                out << ", " << temp->key;
            }
        } else {
            out << "-";
        }

        if ( i != max_size - 1 ) {
            out << " | ";
        }
    }
    out << " ]";
    return out;
}
