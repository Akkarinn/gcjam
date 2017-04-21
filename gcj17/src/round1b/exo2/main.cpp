// Subject: 

#define TEST 0

#if TEST
#define CATCH_CONFIG_MAIN 
#include <catch/catch.hpp>
#endif

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace {

   class Solution {
   public:
      std::string solve(const std::string& number, std::size_t n) {
         return "";
      }
   };
}

#if TEST

TEST_CASE("TITLE", "[test]") {
   Solution s;

   CHECK("" == s.solve("", 2));
}

#else
//"E:\Mes documents\Downloads\A-large.in" "E:\Mes documents\Downloads\A-large.out"
int main(int argc, char * argv[]) {
   if (argc != 3) {
      std::cerr << "Usage: ./exe <input_file> <output_file>" << std::endl;
      return 1;
   }
   std::cout << "Read from '" << argv[1] << "', write to '" << argv[2] << "'" << std::endl;

   std::ifstream in(argv[1]);
   std::ofstream out(argv[2], std::ios_base::trunc);

   int nbInput = 0;
   in >> nbInput;
   for (auto i = 1; i <= nbInput; ++i) {
      std::string input;
      int size;
      in >> input;
      in >> size;
      auto result = Solution().solve(input, size);
      std::cerr << "Case #" << i << ": " << result << std::endl;
      out << "Case #" << i << ": " << result << std::endl;
   }
   return 0;
}

#endif