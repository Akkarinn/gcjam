// Subject: https://codejam.withgoogle.com/2018/challenges/00000000000000cb/dashboard

#define TEST 0

#if TEST
#define CATCH_CONFIG_MAIN 
#include <catch/catch.hpp>
#endif

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

namespace {

   class Solution {
   public:
      std::string solve(unsigned int shield, std::vector<int> bomb_indexes, unsigned int seqLen) {
		auto b_rit = bomb_indexes.rbegin();
		auto score = computeScore(bomb_indexes, seqLen);

		auto nb_swap = 0;
		while (score > shield && b_rit != bomb_indexes.rend()) {
			if (*b_rit == seqLen) {
				++b_rit;
				--seqLen;
			}
			else {
				score -= std::pow(2, std::distance(bomb_indexes.rbegin(), b_rit));
				++(*b_rit);
				++nb_swap;
			}
		}
		if (b_rit == bomb_indexes.rend() || score > shield)
			return "IMPOSSIBLE";
		return std::to_string(nb_swap);
      }
   private:
	   static unsigned int computeScore(const std::vector<int>& bomb_indexes, int seqLen) {
		   if (bomb_indexes.empty())
			   return seqLen;

		   auto score = 0;
		   auto prev_bomb_idx = 0;
		   auto bomb_power = 1;
		   for (auto rank = 0; rank < bomb_indexes.size(); ++rank) {
			   const auto bomb_idx = bomb_indexes[rank];
			   const auto nbShot = bomb_idx - prev_bomb_idx - (rank ? 1 : 0);

			   score += bomb_power * nbShot;
			   prev_bomb_idx = bomb_idx;
			   bomb_power *= 2;
		   }
		   score += bomb_power * (seqLen - 1 - prev_bomb_idx);
		   return score;
	   }
   };
}

#if TEST

TEST_CASE("Saving The Universe Again", "[test]") {
   Solution s;

	CHECK("1" == s.solve(1, { 0 }, std::string("CS").size()));
	CHECK("0" == s.solve(2, { 0 }, std::string("CS").size()));
	CHECK("IMPOSSIBLE" == s.solve(1, {}, std::string("SS").size()));
	CHECK("2" == s.solve(6, { 1, 2, 5 }, std::string("SCCSSC").size()));
	CHECK("0" == s.solve(2, { 0, 1 }, std::string("CC").size()));
	CHECK("5" == s.solve(3, { 0, 2 }, std::string("CSCSS").size()));

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

   for (auto testIdx = 1; testIdx <= nbInput; ++testIdx) {
      unsigned int shield;
	  std::string seq;
	  in >> shield;
	  in >> seq;
	  std::vector<int> bomb_indexes;
	  for (auto i = 0; i < seq.size(); ++i) {
		  if (seq[i] == 'C')
			  bomb_indexes.push_back(i);
	  }
      auto result = Solution().solve(shield, bomb_indexes, seq.size());
      std::cerr << "Case #" << testIdx << ": " << result << std::endl;
      out       << "Case #" << testIdx << ": " << result << std::endl;
   }
   return 0;
}

#endif
