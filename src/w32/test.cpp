#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include "com.hpp"

int main(int argc, char* argv[]) {
  w32::com::com init;

  int result = Catch::Session().run(argc, argv);

  return result;
}
