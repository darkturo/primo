#include <math.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <ctime>
#include <limits>

#define TIMEDIFF(start, stop) 1000.0 * (stop - start)/CLOCKS_PER_SEC

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
         
         for (int pivot = base + base ; pivot <= MaxNumber; pivot += base)
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
      output << number << "\n"; 
      counter ++;
   }
};

int main(int argc, char ** argv)
{
   const int MaxNumber = 32452843;
   clock_t t1, t2;

   t1 = std::clock();

   ErasthostenesSieve<MaxNumber> siever;
   int printedPrimes = siever.applyTheSieve();

   t2 = std::clock();

   // Summary
   std::cout.precision(std::numeric_limits<double>::digits10);
   std::cerr << "Used " << std::fixed << TIMEDIFF(t1, t2)
             << " msecs to calculate " << printedPrimes
             << " primes." << std::endl;
}
