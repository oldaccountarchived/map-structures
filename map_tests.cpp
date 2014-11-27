#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hashmap.hpp"
#include "bucketmap.hpp"

TEST_CASE ( "Testing hashmap", "[HashMap]" ) {
    HashMap map(5);
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( 'a', 5 );
        map.insert( 'f', 9 );
        map.insert( 'k', 12);
        map.insert( 'b', 8 );
        int val;
        map.print();
        REQUIRE( map.search('a', val) == true );
        REQUIRE( val == 5 );
        REQUIRE( map.search('b', val) == true );
        REQUIRE( val == 8 );
        std::cout << std::endl;
        map.remove('f', val);
        map.print();
        std::cout << std::endl;
    }
}

TEST_CASE ( "Testing bucketmap", "[BucketMap]" ) {
    BucketMap map(5);
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( 'a', 5 );
        map.insert( 'f', 9 );
        map.insert( 'k', 12);
        map.insert( 'b', 8 );
        int val;
        map.print();
        REQUIRE( map.search('a', val) == true );
        REQUIRE( val == 5 );
        REQUIRE( map.search('b', val) == true );
        REQUIRE( val == 8 );
        std::cout << std::endl;
        map.remove('f', val);
        map.print();
        std::cout << std::endl;
    }
}
