// Subject: https://code.google.com/codejam/contest/8294486/dashboard#s=p1

#define TEST 1

#if TEST
#define CATCH_CONFIG_MAIN 
#include <catch/catch.hpp>
#endif

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace {
   static const char base[] = "ROYGBV";

   class Solution {
   public:
      typedef std::pair<char, std::size_t>    T_Color;
      typedef std::vector<T_Color>            T_Colors;
      typedef T_Colors::iterator             IT_Colors;

      typedef std::map<char, std::size_t>     T_Occurences;

      std::string solve(T_Colors colors) const {
         if (colors.size() != 6)
            return "";
         // 1- Treat composite colors
         std::string left_result;
         try {
            left_result = mergeCompositeColor(colors);
         } catch (...) {
            return "IMPOSSIBLE";
         }
         // 2- Treat remaining primary colors
         auto right_result = solvePrimatyColors(colors);
         // 3- Perform some check on the possibility to concatenate 2 solutions.
         if ((!left_result.empty() && !right_result.empty()) &&
              (left_result.back() == right_result.front() ||
               left_result.front() == right_result.back())) {
            if (right_result.size() == 1)
                return "IMPOSSIBLE";
            std::swap(*right_result.rbegin(), *(right_result.rbegin()+1));
         }
         if (left_result.empty() && right_result.size() > 1 && right_result.front() == right_result.back())
            return "IMPOSSIBLE";
         return left_result + right_result;
      }
   private:
      std::string mergeCompositeColor(T_Colors& colors) const {
         std::string result;
         std::map<char, std::size_t> occurences;
         for (auto c : colors) {
            occurences[c.first] = c.second;
         }
         // Consume mixed color
         auto b_result = consumeCompositeColor(occurences, { 'O', 'B' });
         auto r_result = consumeCompositeColor(occurences, { 'G', 'R' });
         auto y_result = consumeCompositeColor(occurences, { 'V', 'Y' });
         // Update colors count
         for (auto& c : colors)
            c.second = occurences[c.first];
         // Order mixed color according to number of remaining primary color
         std::vector<T_Color> orderedMixed;
         for (auto& c : colors) {
            if (c.first == 'B' || c.first == 'R' || c.first == 'Y')
               orderedMixed.push_back(c);
         }
         std::sort(orderedMixed.begin(), orderedMixed.end(), [](const auto& a, const auto& b) {
            return a.second != b.second ? (a.second > b.second) : (a.first > b.first);
         });
         for (auto& c : orderedMixed) {
            if (c.first == 'B')
               result += b_result;
            else if (c.first == 'R')
               result += r_result;
            else if (c.first == 'Y')
               result += y_result;
         }
         return result;
      }
      std::string consumeCompositeColor(T_Occurences& occurences, const std::pair<char /*mixed*/, char/*allowed*/>& colors) const {
         std::string result;
         if (occurences[colors.second] < occurences[colors.first])
            throw std::runtime_error("IMPOSSIBLE");
         else if (occurences[colors.first]) {
            // Consume character mixed and allow two by two, starting by primary.
            do {
               auto& first = occurences[colors.first];
               auto& second = occurences[colors.second];
               if (first == 0 || second == 0)
                  throw std::runtime_error("IMPOSSIBLE");
               --first;
               --second;
               result += colors.second;
               result += colors.first;
            } while (occurences[colors.first] != 0);
            // Consume extra primary if there is other mixed color.
            for (auto c : "OGV") {
               auto& occ = occurences[c];
               if (occ) {
                  if (occurences[colors.second] == 0)
                     throw std::runtime_error("IMPOSSIBLE"); // no character available -> impossible to continue
                  occurences[colors.second]--;
                  result += colors.second;
                  break;
               }
            }
         }
         return result;
      }

      std::string solvePrimatyColors(T_Colors& colors) const {
         std::string result;
         // Sort by descending frequence
         std::sort(colors.begin(), colors.end(), [](const auto& a, const auto& b) {
            return a.second != b.second ? (a.second > b.second) : (a.first > b.first);
         });
         // Early exit
         if (colors.front().second == 0)
            return result;
         IT_Colors initialLastRange = --findEndRange(colors);
         // Consume letters by range of frequence
         if (colors.front().second > 1) {
            while (colors.front().second > 1) {
               auto end = findEndRange(colors);
               do {
                  --end;
                  --end->second;
                  result.push_back(end->first);
               } while (end != colors.begin());
            }
            if (std::distance(colors.begin(), findEndRange(colors)) < 2)
               return "IMPOSSIBLE";
         }
         // Last iteration: build according to the first consumed letter
         auto end = findEndRange(colors);
         auto dist = std::distance(colors.begin(), end);
         if (dist == 1) {
            result.push_back(initialLastRange->first);
         }
         else if (dist == 2) {
            result.push_back((colors.begin()+1)->first);
            result.push_back(colors.begin()->first);
         }
         else if (dist == 3) {
            if (!result.empty() && result.front() == result.back()) {
               result.push_back((colors.begin() + 1)->first);
               result.push_back(colors.begin()->first);
               result.push_back((colors.begin() + 2)->first);
            }
            else {
               result.push_back(initialLastRange->first);
               for (auto it = colors.begin(); it != end; ++it)
                  if (it != initialLastRange)
                     result.push_back(it->first);
            }
         }
         return result;
      }
      IT_Colors findEndRange(T_Colors& colors) const {
         return std::find_if_not(colors.begin(), colors.end(), [&](const auto& v) {
            return v.second == colors.front().second; });
      }
   };
}

#if TEST

TEST_CASE("Stable Neigh-bors", "[test]") {
   Solution s;

   // Only Primary
   CHECK("Y"            == s.solve({ {'R', 0}, {'O', 0}, {'Y', 1}, {'G', 0}, {'B', 0}, {'V', 0} }));
   CHECK("BY"           == s.solve({ {'R', 0}, {'O', 0}, {'Y', 1}, {'G', 0}, {'B', 1}, {'V', 0} }));
   CHECK("BYR"          == s.solve({ {'R', 1}, {'O', 0}, {'Y', 1}, {'G', 0}, {'B', 1}, {'V', 0} }));
   CHECK("BRYBYR"       == s.solve({ {'R', 2}, {'O', 0}, {'Y', 2}, {'G', 0}, {'B', 2}, {'V', 0} }));
   CHECK("BYBYR"        == s.solve({ {'R', 1}, {'O', 0}, {'Y', 2}, {'G', 0}, {'B', 2}, {'V', 0} }));
   CHECK("BRBR"         == s.solve({ {'R', 2}, {'O', 0}, {'Y', 0}, {'G', 0}, {'B', 2}, {'V', 0} }));
   CHECK("IMPOSSIBLE"   == s.solve({ {'R', 0}, {'O', 0}, {'Y', 2}, {'G', 0}, {'B', 0}, {'V', 0} }));
   CHECK("IMPOSSIBLE"   == s.solve({ {'R', 2}, {'O', 0}, {'Y', 0}, {'G', 0}, {'B', 3}, {'V', 0} }));
   CHECK("IMPOSSIBLE"   == s.solve({ {'R', 2}, {'O', 0}, {'Y', 4}, {'G', 0}, {'B', 1}, {'V', 0} }));
   // Single Composite
   CHECK("IMPOSSIBLE"   == s.solve({ {'R', 0}, {'O', 0}, {'Y', 1}, {'G', 0}, {'B', 0}, {'V', 2} }));
   CHECK("YV"           == s.solve({ {'R', 0}, {'O', 0}, {'Y', 1}, {'G', 0}, {'B', 0}, {'V', 1} }));
   CHECK("IMPOSSIBLE"   == s.solve({ {'R', 0}, {'O', 0}, {'Y', 2}, {'G', 0}, {'B', 0}, {'V', 1} }));
   // Composite and Primary
   CHECK("YVYVB"        == s.solve({ {'R', 0}, {'O', 0}, {'Y', 2}, {'G', 0}, {'B', 1}, {'V', 2} }));
   CHECK("YVBRBRYB"     == s.solve({ {'R', 2}, {'O', 0}, {'Y', 2}, {'G', 0}, {'B', 3}, {'V', 1} }));
   CHECK("YVBRYBYBR"    == s.solve({ {'R', 2}, {'O', 0}, {'Y', 3}, {'G', 0}, {'B', 3}, {'V', 1} }));
   CHECK("BOBYVBRYBYBR" == s.solve({ {'R', 2}, {'O', 1}, {'Y', 3}, {'G', 0}, {'B', 5}, {'V', 1} }));
   CHECK("IMPOSSIBLE"   == s.solve({ {'R', 1}, {'O', 1}, {'Y', 1}, {'G', 0}, {'B', 0}, {'V', 0} }));

}

#else
//"E:\Mes documents\Downloads\B-small-practice (1).in" "E:\Mes documents\Downloads\B-small-practice.out"
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
      int len = 0;
      in >> len;
      Solution::T_Colors colors;
      for (auto j = 0; j < 6; ++j) {
         Solution::T_Color c{base[j], 0};
         in >> c.second;
         colors.push_back(c);
      }
      auto result = Solution().solve(colors);
      std::cerr << "Case #" << i << ": " << result << std::endl;
      out << "Case #" << i << ": " << result << std::endl;
   }
   return 0;
}

#endif