#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tritset.h"


TEST_CASE(){

    trit a = trit::True, b = trit::False, c = trit::Unknown;

    REQUIRE( (a & a) == trit::True );
    REQUIRE( (b & b) == trit::False );
    REQUIRE( (c & c) == trit::Unknown );
    REQUIRE( (a & b) == trit::False );
    REQUIRE( (a & c) == trit::Unknown );
    REQUIRE( (b & c) == trit::False );

    REQUIRE( (a | a) == trit::True );
    REQUIRE( (b | b) == trit::False );
    REQUIRE( (c | c) == trit::Unknown );
    REQUIRE( (a | b) == trit::True );
    REQUIRE( (a | c) == trit::True );
    REQUIRE( (b | c) == trit::Unknown );

    REQUIRE( ~a == trit::False );
    REQUIRE( ~b == trit::True );
    REQUIRE( ~c == trit::Unknown );

    tritset unita(20);
    tritset unitb(40);
    REQUIRE( unita.getSize() == 20);
    REQUIRE( unitb.getSize() == 40);

    for(size_t i = 0; i < unita.getSize(); i++)
        REQUIRE( unita[i]  == trit::Unknown);

    unita[1] = trit::True;
    unitb[2] = trit::False;
    REQUIRE( unita[1] == trit::True );
    REQUIRE( unitb[2] == trit::False );
    
    tritset unitc = unita & unitb;
    REQUIRE( unitc.getSize() == 40);
    for(size_t i = 0; i < unitc.getSize(); i++)
        REQUIRE( unitc[i]  == (unita[i] & unitb[i]));

    unitc = unita | unitb;
    REQUIRE( unitc.getSize() == 40);
    for(size_t i = 0; i < unitc.getSize(); i++)
        REQUIRE( unitc[i]  == (unita[i] | unitb[i]));  

    unitc = ~unita;
    REQUIRE( unitc.getSize() == 20);
    for(size_t i = 0; i < unitc.getSize(); i++)
        REQUIRE( unitc[i]  == ~unita[i]); 

    unita[4] = trit::True;
    REQUIRE( unita.length() == 5 );
    unita.shrink();
    REQUIRE( unita.getSize() == 5 );

    for(size_t i = 0; i < 10; i++)
        unitb[i] = trit::True;
    unitb.trim(10);
    for(size_t i = 10; i < unitb.getSize(); i++)
        REQUIRE( unitb[i] == trit::Unknown );
    
    
    for(size_t i = 0; i < 10; i++)
        unita[i] = trit::True;
    for(size_t i = 10; i < 30; i++)
        unita[i] = trit::Unknown;
    for(size_t i = 30; i < 100; i++)
        unita[i] = trit::False;
        unitc[99] = trit::True;
    REQUIRE( unita.getSize() == 100 );
    REQUIRE( unita.cardinality(trit::False) == 70 );
    REQUIRE( unita.cardinality(trit::True) == 10 );
    REQUIRE( unita.cardinality(trit::Unknown) == 20 );

    std::map<trit, int> test = unita.cardinality();
    REQUIRE( test[trit::False] == 70 );
    REQUIRE( test[trit::True] == 10 );
    REQUIRE( test[trit::Unknown] == 20 );

    REQUIRE( unita[1000] == trit::Unknown );
    unita[200] = unita[3000];
    REQUIRE( unita.getSize() == 100 );

}