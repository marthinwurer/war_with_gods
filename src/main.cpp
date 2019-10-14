#include <cstdio>

#ifdef TEST
    #define CATCH_CONFIG_MAIN
    #include <Catch2/catch.hpp>
#else

int main() {
    printf("FUCK ME\n");
    
    return 0;
}

#endif