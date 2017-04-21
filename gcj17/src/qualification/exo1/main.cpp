// Subject: https://code.google.com/codejam/contest/3264486/dashboard#s=p0

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
         std::string current(number);
         auto res = solveImpl(current, n);
         auto end = current.rbegin() + n;
         if (end == std::find(current.rbegin(), end, '-'))
            return std::to_string(res);
         return "IMPOSSIBLE";
      }

   private:
      int solveImpl(std::string& number, std::size_t n) {
         auto nbFlip = 0;
         for (auto i = 0; i <= number.size() - n; ++i) {
            if (number[i] == '-') {
               ++nbFlip;
               turn(number, i, i + n);
            }
         }
         return nbFlip;
      }
      void turn(std::string& number, std::size_t first, std::size_t last) {
         for (auto i = first; i < last; ++i)
            number[i] = number[i] == '+' ? '-' : '+';
      }
   };
}

#if TEST

TEST_CASE("Oversize Pancake Flipper", "[test]") {
   Solution s;

   CHECK("IMPOSSIBLE" == s.solve("-+++", 2));
   CHECK("2" == s.solve("-+-+", 2));
   CHECK("0" == s.solve("+++++", 4));
   CHECK("3" == s.solve("-+-+-", 3));
   CHECK("3" == s.solve("---+-++-", 3));
   CHECK("2" == s.solve("----", 2));
   CHECK("0" == s.solve("++++", 2));
   CHECK("IMPOSSIBLE" == s.solve("-+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--", 2));

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
      out       << "Case #" << i << ": " << result << std::endl;
   }
   return 0;
}

#endif