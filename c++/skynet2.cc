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
   char biggerbuffer[512000 * 8];

   public:
   ErasthostenesSieve()
   {
      listOfNaturals.set();
      listOfNaturals.set(0, false); // 1 is not prime
      output.open("primesEveryWhere.txt", std::fstream::out);
      output.rdbuf()->pubsetbuf(biggerbuffer, 512000);
   }

   ~ErasthostenesSieve()
   {
      output.close();
   }

   void applyTheSieve()
   {
      for (int index = 3; index <= MaxNumber; index += 2 )
      {
         // Mark all even numbers greater than 2 as multiples of 2.
         // NOTE: listOfNaturals[3] represents 4.
         listOfNaturals.set(index, false);
      }

      for (int base = 3; base * base <= MaxNumber; base += 2 )
      {
         int jump = 2 * base;
         for (int pivot = base + jump; pivot <= MaxNumber; pivot += jump)
         {
            listOfNaturals.set(pivot - 1, false);
         }
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
