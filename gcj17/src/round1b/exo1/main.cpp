// Subject: 

#define TEST 0

#if TEST
#define CATCH_CONFIG_MAIN 
#include <catch/catch.hpp>
#endif

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {

   static const double maxSpeed = 10000.;

   class Solution {
   public:
      typedef unsigned                       T_Position;
      typedef double                         T_Speed;
      typedef std::pair<T_Position, T_Speed> T_Horse;
      typedef std::vector<T_Horse>           T_Horses;


      double solve(T_Horses horses, T_Position target) {
         horses.push_back(T_Horse{ 0, std::numeric_limits<double>::max() });
         std::sort(horses.begin(), horses.end(), [](auto& h1, auto& h2) { return h1.first < h2.first; });

         return solveImpl(horses, target);
      }
      private:
         double solveImpl(T_Horses horses, T_Position target) {
            while (horses.size() > 1) {
               auto& last = horses.back();
               auto& prevLast = horses[horses.size()-2];
               prevLast.second = computeMeanSpeed(prevLast, last, target);
               horses.pop_back();
            }
            return horses.front().second;
         }

         double computeMeanSpeed(const T_Horse& prevLast, const T_Horse& last, T_Position target) {
            if (prevLast.second <= last.second)
               return prevLast.second;
            auto distance_last_to_target = static_cast<double>(target - last.first);

            auto time_last_to_target = distance_last_to_target / last.second;
            auto time_prevLast_to_last = static_cast<double>(last.first - prevLast.first) / (prevLast.second - last.second);
            if (time_last_to_target <= time_prevLast_to_last)
               return prevLast.second;

            return std::min(
               static_cast<double>(prevLast.second),
               static_cast<double>(target - prevLast.first) / time_last_to_target);
         }
   };

}

#if TEST

TEST_CASE("Steed 2: Cruise Control", "[test]") {
   Solution s;
   {
      Solution::T_Horses horses{ { 999999997, 2 },{ 999999996, 3 } };
      CHECK(2.0000000040000003 == s.solve(horses, 1000000000));
   }
   {
      Solution::T_Horses horses{ { 1, 3 },{ 2, 2 } };
      CHECK(2.0000000040000003 == s.solve(horses, 1000000000));
   }
   {
      Solution::T_Horses horses{ { 120, 60 },{ 60, 90 } };
      CHECK(100. == s.solve(horses, 300));
   }
   {
      Solution::T_Horses horses{ { 2400, 5 } };
      CHECK(101. == s.solve(horses, 2525));
   }
   {
      Solution::T_Horses horses{ { 80, 100 },{ 70, 10 } };
      CHECK(100. / 3. == s.solve(horses, 100));
   }
}

#else
//"E:\Mes documents\Downloads\A-large (1).in" "E:\Mes documents\Downloads\A-large (1).in.out"
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
      unsigned int targetDistance, nbHorse;
      in >> targetDistance >> nbHorse;
      Solution::T_Horses horses;
      horses.resize(nbHorse);
      for (auto n = 0u; n < nbHorse; ++n) {
         auto& current = horses[n];
         in >> current.first >> current.second;
      }

      auto result = Solution().solve(horses, targetDistance);

      std::cerr << "Case #" << i << ": " << result << std::endl;
      out       << "Case #" << i << ": " << std::fixed << result << std::endl;
   }
   return 0;
}

#endif