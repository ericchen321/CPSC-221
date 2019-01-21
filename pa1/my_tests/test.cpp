#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "chain.h"
#include "block.h"
#include <iostream>
#include "../cs221util/PNG.h"
#include "catch.hpp"
using namespace cs221util;
using namespace std;

TEST_CASE("test insert_back",""){
  Block b1(1);
  Block b2(2);
  Block b3(3);

	Chain c;
  c.insertBack(b1);
  c.insertBack(b2);
  c.insertBack(b3);
  REQUIRE(c.size() == 3);
}