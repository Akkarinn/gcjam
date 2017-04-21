// Subject: https://code.google.com/codejam/contest/3264486/dashboard#s=p1

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
      std::string solve(const std::string& number) {
         std::string result;

         for (auto i = 0; i < number.size(); ++i) {
            auto digit = number[number.size() - i - 1] - '0';
            if (! result.empty() && digit > result.back() - '0') {
               digit -= 1;
               std::fill(result.begin(), result.end(), '9');
            }
            result.push_back(digit + '0');
         }

         // Remove trailing 0
         result.resize(result.size() -
            std::distance(result.rbegin(),
               std::find_if(result.rbegin(), result.rend(), [](char c) { return c != '0'; })));
         // Reverse string
         std::reverse(result.begin(), result.end());
         return result;
      }
   private:
   };
}      

#if TEST

TEST_CASE("Tidy Numbers", "[test]") {
   Solution s;

   CHECK("113" == s.solve("113"));

   CHECK("" == s.solve(""));
   CHECK("7" == s.solve("7"));
   CHECK("9" == s.solve("10"));
   CHECK("13" == s.solve("13"));
   CHECK("17" == s.solve("17"));
   CHECK("129" == s.solve("132"));
   CHECK("134" == s.solve("134"));
   CHECK("599" == s.solve("624"));
   CHECK("999" == s.solve("1000"));
   CHECK("99999999999999999"  == s.solve("111111111111111110"));
   CHECK("999999999999999999" == s.solve("1000000000000000000"));
   CHECK("799999999999999999" == s.solve("880012345556666679"));
}

#else
//"E:\Mes documents\Downloads\B-large.in" "E:\Mes documents\Downloads\B-large.out"
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
      in >> input;
      std::string result = Solution().solve(input);
      std::cerr << "Case #" << i << ": " << result << std::endl;
      out       << "Case #" << i << ": " << result << std::endl;
   }
   return 0;
}

#endif