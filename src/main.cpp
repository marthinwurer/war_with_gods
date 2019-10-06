#include <cstdio>

#define TEST_BUILD

#ifdef TEST_BUILD
    #define CATCH_CONFIG_MAIN
    #include <Catch2/catch.hpp>
#else

int main() {
    printf("FUCK ME DADDY\n");
    
    return 0;
}

#endif