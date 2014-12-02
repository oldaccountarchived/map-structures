#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hashmap.hpp"
#include "bucketmap.hpp"
#include "hashmap_enhanced.cpp"
#include "bucketmap_enhanced.cpp"
#include "rbst.cpp"

TEST_CASE ( "Testing hashmap", "[HashMap]" ) {
    HashMap map(5);
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( 1,  'a' );
        map.insert( 6,  'f' );
        map.insert( 11, 'k' );
        map.insert( 2,  'b' );
        map.insert( 45,  'd' );
        bool failed = map.insert( 72,  'r' );
        REQUIRE( failed == false );
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
        map.insert( 45,  'd' );
        map.insert( 72,  'r' );
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
        map.insert( 'd', 45 );
        int failed = map.insert( 'r', 72 );
        REQUIRE( failed == -1 );
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
        map.insert( "d", 45 );
        int failed = map.insert( "r", 72 );
        REQUIRE( failed == -1 );
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
    EnhHashMap<std::string, int, int(*)(std::string, size_t), 
               int(*)(std::string, int), 
               bool(*)(std::string, std::string)> map(5, string_hash, 
                                      linear_probe<std::string, int>,
                                      string_compare);
    
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( "a", 5 );
        map.insert( "f", 9 );
        map.insert( "k", 12);
        map.insert( "b", 8 );
        map.insert( "d", 45 );
        int failed = map.insert( "r", 72 );
        REQUIRE( failed == -1 );
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
    EnhBucketMap<std::string, int, bool(*)(std::string, std::string), 
                 int(*)(std::string, size_t)> map(5, string_compare,
                                                  string_hash);
    
    SECTION ( "Test insert method", "[insert]" ) {
        map.insert( "a", 5 );
        map.insert( "f", 9 );
        map.insert( "k", 12);
        map.insert( "b", 8 );
        map.insert( "d", 45 );
        int passed = map.insert( "r", 72 );
        REQUIRE( passed > -1 );
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

TEST_CASE ( "Testing RBST", "[RBST]" ) {
    RBST<std::string, int, bool(*)(std::string, std::string), 
                 bool(*)(std::string, std::string)> map(5, string_compare,
                                                        string_lt);
    SECTION( "Test insert", "[insert]" ) {
        map.insert( "a", 5 );
        map.insert( "f", 9 );
        map.insert( "k", 12);
        map.insert( "b", 8 );
        map.insert( "d", 45 );
        int failed = map.insert( "r", 72 );
        REQUIRE( failed == -1 );
        int val;
        map.search( "b", val );
        REQUIRE( val == 8 );
        map.search( "f", val );
        REQUIRE( val == 9 );
        map.search( "a", val );
        REQUIRE( val == 5 );
        map.search( "k", val );
        REQUIRE( val == 12 );
        map.print( std::cout );
        std::cout << std::endl;
        map.remove( "a", val );
        REQUIRE( val == 5 );
        map.remove( "f", val );
        REQUIRE( val == 9 );
        REQUIRE( map.size() == 3 );
        REQUIRE( map.capacity() == 5 );
        map.print( std::cout );
        std::cout << std::endl;
    }
}
