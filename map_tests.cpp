#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hashmap.hpp"
#include "bucketmap.hpp"
#include "hashmap_enhanced.cpp"
#include "bucketmap_enhanced.cpp"

TEST_CASE ( "Testing hashmap", "[HashMap]" ) {
    HashMap map(5);
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( 1,  'a' );
        map.insert( 6,  'f' );
        map.insert( 11, 'k' );
        map.insert( 2,  'b' );
        char val;
        map.print(std::cout);
        REQUIRE( map.search(1, val) == true );
        REQUIRE( val == 'a' );
        REQUIRE( map.search(2, val) == true );
        REQUIRE( val == 'b' );
        std::cout << std::endl;
        map.remove(6 , val);
        REQUIRE( val == 'f' );
        map.print(std::cout);
        std::cout << std::endl;
        REQUIRE( map.isEmpty() == false );
        map.clear();
        REQUIRE( map.isEmpty() == true );
    }
}

TEST_CASE ( "Testing bucketmap", "[BucketMap]" ) {
    BucketMap map(5);
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( 1,  'a' );
        map.insert( 6,  'f' );
        map.insert( 11, 'k' );
        map.insert( 2,  'b' );
        char val;
        map.print(std::cout);
        REQUIRE( map.search(1, val) == true );
        REQUIRE( val == 'a' );
        REQUIRE( map.search(2, val) == true );
        REQUIRE( val == 'b' );
        std::cout << std::endl;
        map.remove(6 , val);
        REQUIRE( val == 'f' );
        map.print(std::cout);
        std::cout << std::endl;
        REQUIRE( map.isEmpty() == false );
        map.clear();
        REQUIRE( map.isEmpty() == true );
    }
}

TEST_CASE ( "Testing enhanced hash_map", "[ENH]" ) {
    EnhHashMap<int, int, int(*)(int, size_t), 
               int(*)(int, int), 
               bool(*)(int, int)> map(5, int_hash, 
                                      linear_probe<int, int>,
                                      int_compare);
    
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( 'a', 5 );
        map.insert( 'f', 9 );
        map.insert( 'k', 12);
        map.insert( 'b', 8 );
        int val;
        map.print(std::cout);
        REQUIRE( map.search('a', val) != -1 );
        REQUIRE( val == 5 );
        REQUIRE( map.search('b', val) != -1 );
        REQUIRE( val == 8 );
        std::cout << std::endl;
        map.remove( 'f', val );
        map.print(std::cout);
        std::cout << std::endl;
        REQUIRE( map.isEmpty() == false );
        map.clear();
        REQUIRE( map.isEmpty() == true );
    }
}

TEST_CASE ( "Testing enhanced hash_map2", "[ENH2]" ) {
    EnhHashMap<char*, int, int(*)(char const*, size_t), 
               int(*)(char const*, int), 
               bool(*)(char const*, char const*)> map(5, cstring_hash, 
                                      linear_probe<char const*, int>,
                                      cstring_compare);
    
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( "a", 5 );
        map.insert( "f", 9 );
        map.insert( "k", 12);
        map.insert( "b", 8 );
        int val;
        map.print(std::cout);
        REQUIRE( map.search("a", val) != -1 );
        REQUIRE( val == 5 );
        REQUIRE( map.search("b", val) != -1 );
        REQUIRE( val == 8 );
        std::cout << std::endl;
        map.remove( "f", val );
        map.print(std::cout);
        std::cout << std::endl;
        REQUIRE( map.isEmpty() == false );
        map.clear();
        REQUIRE( map.isEmpty() == true );
    }
}

TEST_CASE ( "Testing enhanced hash_map3", "[ENH3]" ) {
    EnhHashMap<char*, int, int(*)(std::string, size_t), 
               int(*)(std::string, int), 
               bool(*)(std::string, std::string)> map(5, string_hash, 
                                      linear_probe<std::string, int>,
                                      string_compare);
    
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( "a", 5 );
        map.insert( "f", 9 );
        map.insert( "k", 12);
        map.insert( "b", 8 );
        int val;
        map.print(std::cout);
        REQUIRE( map.search("a", val) != -1 );
        REQUIRE( val == 5 );
        REQUIRE( map.search("b", val) != -1 );
        REQUIRE( val == 8 );
        std::cout << std::endl;
        map.remove( "f", val );
        map.print(std::cout);
        std::cout << std::endl;
        REQUIRE( map.isEmpty() == false );
        map.clear();
        REQUIRE( map.isEmpty() == true );
    }
}

TEST_CASE ( "Testing enhanced bucket map", "[ENBM]" ) {
    EnhBucketMap<char*, int, bool(*)(std::string, std::string), 
                 int(*)(std::string, size_t)> map(5, string_compare,
                                                  string_hash);
    
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( "a", 5 );
        map.insert( "f", 9 );
        map.insert( "k", 12);
        map.insert( "b", 8 );
        int val;
        map.print(std::cout);
        REQUIRE( map.search("a", val) != -1 );
        REQUIRE( val == 5 );
        REQUIRE( map.search("b", val) != -1 );
        REQUIRE( val == 8 );
        std::cout << std::endl;
        map.remove( "f", val );
        map.print(std::cout);
        std::cout << std::endl;
        REQUIRE( map.isEmpty() == false );
        map.clear();
        REQUIRE( map.isEmpty() == true );
    }
}
