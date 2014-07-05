#include <math.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>

template <int MaxNumber>
class ErasthostenesSieve
{
   std::bitset<MaxNumber> listOfNaturals;
   std::fstream output;

   public:
   ErasthostenesSieve()
   {
      listOfNaturals.set();
      listOfNaturals.set(0, false); // 1 is not prime
      output.open("primesEveryWhere.txt", std::fstream::out);
   }

   ~ErasthostenesSieve()
   {
      output.close();
   }

   void applyTheSieve()
   {
      for (int base = 2; base * base < MaxNumber; base += 2 )
      {
         int jump = (base == 2)? base : 2 * base;
         for (int pivot = base + jump; pivot <= MaxNumber; pivot += jump)
         {
            listOfNaturals.set(pivot - 1, false);
         }
         base = (base == 2)? 1 : base;
      }
   }

   int printPrimes()
   {
      int counter = 0;
      for (int i = 0; i < MaxNumber; i++)
      {
         if (listOfNaturals[i])
         {
            output << i << std::endl;
            counter ++;
         }
      }
      return counter;
   }
};

int main(int argc, char ** argv)
{
   const int MaxNumber = 32288611;
   time_t t1, t2;


   time(&t1);

   ErasthostenesSieve<MaxNumber> siever;
   siever.applyTheSieve();
   int printedPrimes = siever.printPrimes();

   time(&t2);

   // Summary
   std::cout.precision(std::numeric_limits<double>::digits10);
   std::cerr << "Used " << std::fixed << difftime(t2, t1) 
             << " seconds to calculate " << printedPrimes
             << " primes." << std::endl;
}
