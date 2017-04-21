// Subject: https://code.google.com/codejam/contest/3264486/dashboard#s=p2

#define TEST 0

#if TEST
#define CATCH_CONFIG_MAIN 
#include <catch/catch.hpp>
#endif

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace {

   class Solution {
   public:
      typedef std::size_t T_MaxDistance;
      typedef std::size_t T_MinDistance;
      typedef std::pair<T_MaxDistance, T_MinDistance> T_Result;
      typedef std::pair<std::size_t, std::size_t> T_Input;
      class InputKey
      {
      public:
         InputKey(std::size_t N, std::size_t K) : m_N(N), m_K(K) {}
         std::size_t m_N, m_K;
         bool operator<(const InputKey& o) const
         {
            if (m_N != o.m_N)
               return m_N < o.m_N;
            return m_K < o.m_K;
         }
      };
      std::map<InputKey, T_Result> m_cache;

      T_Result solve(std::size_t N, std::size_t K) {
         T_Result result;
         if (K < N) {
            m_cache.clear();
            result = solveImpl(N, K);
         }
         return result;
      }
   private:
      T_Result solveImpl(std::size_t N, std::size_t K) {
         auto c = m_cache.find(InputKey(N, K));
         if (c != m_cache.end())
            return c->second;

         if (K == 1) {
            // Two cases:
            // * N is odd -> min and max are equals
            // * N is even -> min is one below max
            auto n = N / 2;
            return T_Result({ n, n - (~(N & 0x1) & 0x1) });
         }
         else {
            // divide the problem in 2 parts: left hand side,
            // right hand side; if not equal part, lhs is the smaller one.
            
            // remove the current step
            --K;
            --N;
            // compute the two sub problems input
            auto n_lhs = N / 2;
            auto n_rhs = N - n_lhs;
            auto k_lhs = K / 2;
            auto k_rhs = K - k_lhs;
            // solve rhs part
            auto res = solveImpl(n_rhs, k_rhs);
            // solve lhs part only if there is something remaining k
            if (k_lhs != 0) {
               // choose the less good solution (which will be the choice of the last k).
               res = lower(solveImpl(n_lhs, k_lhs), res);
            }
            m_cache.insert(std::make_pair(InputKey(N+1, K+1), res));
            return res;
         }
      }
      T_Result lower(const T_Result& lhs, const T_Result& rhs) const {
         if (lhs.first != rhs.first)
            return lhs.first < rhs.first ? lhs : rhs;
         return lhs.second < rhs.second ? lhs : rhs;
      }
   };
}      

#if TEST

TEST_CASE("Bathroom Stalls", "[test]") {
   typedef Solution::T_Result T_Result;
   Solution s;

   CHECK(T_Result({ 1, 1 }) == s.solve(6, 2));


   CHECK(T_Result({1, 0}) == s.solve(4, 2));
   CHECK(T_Result({2, 2}) == s.solve(5, 1));
   CHECK(T_Result({1, 0}) == s.solve(5, 2));
   CHECK(T_Result({3, 2}) == s.solve(6, 1));
   CHECK(T_Result({1, 1}) == s.solve(6, 2));
   CHECK(T_Result({2, 1}) == s.solve(8, 2));
   CHECK(T_Result({0, 0}) == s.solve(1000, 1000));
   CHECK(T_Result({500, 499}) == s.solve(1000, 1));
   CHECK(T_Result({4, 4}) == s.solve(9, 1));
   CHECK(T_Result({49, 49}) == s.solve(99, 1));
   CHECK(T_Result({499, 499}) == s.solve(999, 1));
   CHECK(T_Result({249, 249}) == s.solve(999, 2));
   CHECK(T_Result({4, 4}) == s.solve(19, 3));

   CHECK(T_Result({5, 4}) == s.solve(10, 1));
   CHECK(T_Result({2, 2}) == s.solve(10, 2));
   CHECK(T_Result({2, 1}) == s.solve(10, 3));
   CHECK(T_Result({1, 0}) == s.solve(10, 4));
   CHECK(T_Result({1, 0}) == s.solve(10, 5));
   CHECK(T_Result({1, 0}) == s.solve(10, 6));
   CHECK(T_Result({0, 0}) == s.solve(10, 7));
   CHECK(T_Result({0, 0}) == s.solve(10, 8));
   CHECK(T_Result({0, 0}) == s.solve(10, 9));
   CHECK(T_Result({0, 0}) == s.solve(10, 10));

   CHECK(T_Result({5, 5}) == s.solve(11, 1));
   CHECK(T_Result({2, 2}) == s.solve(11, 2));
   CHECK(T_Result({2, 2}) == s.solve(11, 3));
   CHECK(T_Result({1, 0}) == s.solve(11, 4));
   CHECK(T_Result({1, 0}) == s.solve(11, 5));
   CHECK(T_Result({1, 0}) == s.solve(11, 6));
   CHECK(T_Result({1, 0}) == s.solve(11, 7));
   CHECK(T_Result({0, 0}) == s.solve(11, 8));
   CHECK(T_Result({0, 0}) == s.solve(11, 9));
   CHECK(T_Result({0, 0}) == s.solve(11, 10));

   CHECK(T_Result({6, 5}) == s.solve(12, 1));
   CHECK(T_Result({3, 2}) == s.solve(12, 2));
   CHECK(T_Result({2, 2}) == s.solve(12, 3));
   CHECK(T_Result({1, 1}) == s.solve(12, 4));
   CHECK(T_Result({1, 0}) == s.solve(12, 5));
   CHECK(T_Result({1, 0}) == s.solve(12, 6));
   CHECK(T_Result({1, 0}) == s.solve(12, 7));
   CHECK(T_Result({0, 0}) == s.solve(12, 8));
   CHECK(T_Result({0, 0}) == s.solve(12, 9));
   CHECK(T_Result({0, 0}) == s.solve(12, 10));
   CHECK(T_Result({0, 0}) == s.solve(12, 11));
   CHECK(T_Result({0, 0}) == s.solve(12, 12));

   CHECK(T_Result({8, 7}) == s.solve(16, 1));
   CHECK(T_Result({4, 3}) == s.solve(16, 2));
   CHECK(T_Result({3, 3}) == s.solve(16, 3));
   CHECK(T_Result({2, 1}) == s.solve(16, 4));
   CHECK(T_Result({1, 1}) == s.solve(16, 5));
   CHECK(T_Result({1, 1}) == s.solve(16, 6));
   CHECK(T_Result({1, 1}) == s.solve(16, 7));
   CHECK(T_Result({1, 0}) == s.solve(16, 8));
   CHECK(T_Result({0, 0}) == s.solve(16, 9));
   CHECK(T_Result({0, 0}) == s.solve(16, 10));
}

#else
//"E:\Mes documents\Downloads\C-large.in" "E:\Mes documents\Downloads\C-large.out"
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
      std::size_t N, K;
      in >> N >> K;
      Solution::T_Result result = Solution().solve(N, K);
      std::cerr << "Case #" << i << ": " << result.first << " " << result.second << std::endl;
      out       << "Case #" << i << ": " << result.first << " " << result.second << std::endl;
   }
   return 0;
}

#endif