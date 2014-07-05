#include <math.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>
#include <pthread.h>

template <int MaxNumber>
class ErasthostenesSieve
{
   std::bitset<MaxNumber> listOfNaturals;
   std::fstream output;
   int counter; 

   public:
   ErasthostenesSieve() : counter(0)
   {
      listOfNaturals.set();
      listOfNaturals.set(0, false); // 1 is not prime
      output.open("primesEveryWhere.txt", std::fstream::out);
   }

   ~ErasthostenesSieve()
   {
      output.close();
   }

   int applyTheSieve()
   {
      int base = 2;
      print( base );

      for (base = 3; base * base < MaxNumber; base += 2 )
      {
         if (not listOfNaturals[base - 1]) 
            continue;

         print( base );
         
         for (int pivot = 2 * base ; pivot <= MaxNumber; pivot += base)
         {
            listOfNaturals.set(pivot - 1, false);
         }
      }

      for (; base <= MaxNumber; base += 2)
      {
         if (listOfNaturals[base - 1])
            print( base );
      }
      return counter;
   }

   private:
   void print(int number)
   {
//      output << number << std::endl;
      counter ++;
   }
};

int main(int argc, char ** argv)
{
   const int MaxNumber = 32452843;
   time_t t1, t2;


   time(&t1);

   ErasthostenesSieve<MaxNumber> siever;
   int printedPrimes = siever.applyTheSieve();

   time(&t2);

   // Summary
   std::cout.precision(std::numeric_limits<double>::digits10);
   std::cerr << "Used " << std::fixed << difftime(t2, t1) 
             << " seconds to calculate " << printedPrimes
             << " primes." << std::endl;
}
