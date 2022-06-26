# include "doctest.h"
# include "math.hpp"

int i;

TEST_CASE("multiplication") {
    unsigned long long a[16], b[16], c[16];
    for (i=0; i<16; ++i) {
        a[i]=0, b[i]=0, c[i]=0;
    }
    a[15] = 12;
    b[15] = 20;
    math::multiply(a,b,c,16);
    REQUIRE(c[15] == 240);
    a[14] = 1;
    b[15] = 2;
    c[15] = 0;
    math::multiply(a,b,c,16);
    REQUIRE(c[15] == 24);
    REQUIRE(c[14] == 2);
}

TEST_CASE("division") {
    unsigned long long a[16], b[16], c[16], d[16];
    for (i=0; i<16; ++i) {
        a[i]=0, b[i]=0, c[i]=0, d[i]=0;
    }
    a[15] = 15;
    b[15] = 7;
    math::divide(a,b,c,d,16);
    REQUIRE(c[15] == 2);
    REQUIRE(d[15] == 1);
}

TEST_CASE("comparison") {
    unsigned long long a[16], b[16];
    for (i=0; i<16; ++i) {
        a[i]=0, b[i]=0;
    }
    a[15] = 15;
    b[15] = 7;
    REQUIRE(math::is_bigger(a,b,16) == true);
    REQUIRE(math::is_bigger(b,a,16) == false);
    a[14] = 1;
    b[14] = 7;
    REQUIRE(math::is_bigger(a,b,16) == false);
}

TEST_CASE("addition"){
    unsigned long long a[16], b[16], c[16];
    for (i=0; i<16; ++i) {
        a[i]=0, b[i]=0, c[i]=0;
    }
    a[15] = 15;
    b[15] = 7;
    math::sum(a,b,c,16);
    REQUIRE(c[15] == 22);
    a[14] = 120;
    b[14] = 21;
    math::sum(a,b,c,16);
    REQUIRE(c[14] == 141);
}

TEST_CASE("substraction"){
    unsigned long long a[16], b[16], c[16];
    for (i=0; i<16; ++i) {
        a[i]=0, b[i]=0, c[i]=0;
    }
    a[15] = 15;
    b[15] = 7;
    math::sub(a,b,c,16);
    REQUIRE(c[15] == 8);
    a[14] = 1;
    b[15] = 16;
    math::sub(a,b,c,16);
    REQUIRE(c[15] == 4294967295);
    REQUIRE(c[14] == 0);
}

TEST_CASE("bezout"){
    unsigned long long a[16], b[16], c[17],d[17];
    for (i=0; i<16; ++i) {
        a[i]=0, b[i]=0, c[i]=0,d[i]=0;
    }
    a[15] = 15;
    b[15] = 7;
    math::bezout(a,b,c,d,16);       // НОД(15,7) = 1 = 15*1 + 7*(-2)
    REQUIRE(c[16] == 1);
    REQUIRE(c[0] == 0);
    REQUIRE(d[16] == 2);
    REQUIRE(d[0] == 1);
}

TEST_CASE("mod_power") {
    unsigned long long a[16], b[16], c[16],d[16];
    for (i=0; i<16; ++i) {
        a[i]=0, b[i]=0, c[i]=0,d[i]=0;
    }
    a[15] = 121;
    b[15] = 65537;
    c[15] = 111222;
    math::mod_pow(a,b,c,d,16);
    REQUIRE(d[15] == 8647);    // 121^65537 % 111222 = 8647
}