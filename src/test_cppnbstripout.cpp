#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <fstream>

#include "cppnbstripoutlib.hpp"

using nlohmann::json;

 
TEST(CleanTest, TestCleanWorks) {
  std::ifstream ifs{"../Test.ipynb"};
  json raw = json::parse(ifs);

  ifs = std::ifstream{"../TestClean.ipynb"};
  json exp = json::parse(ifs);

  json proc = raw;
  clean(proc);

  ASSERT_EQ(proc, exp);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
