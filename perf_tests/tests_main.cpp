//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER //used for our custom main

#include <iostream>

#include "catch.hpp"

int main(int argc, char *argv[]) {
   
   std::cout << "Welcome to the YAGL test suite!\n";

   int result = Catch::Session().run(argc, argv);
   
   return result;
}

