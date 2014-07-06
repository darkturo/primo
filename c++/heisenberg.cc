/*
 * Using Erasthostenes' sieve, print the first 2,000,000 numbers
 * darkturo 2014
 */
#include <iostream>
#include <fstream>
#include <bitset>
#include <ctime>
#include <limits>
#include <boost/spirit/include/karma.hpp>

#define TIMEDIFF(start, stop) 1000.0 * (stop - start)/CLOCKS_PER_SEC
#define BUFFER_SIZE 512 

template <int MaxNumber>
class ErasthostenesSieve
{
   std::bitset<MaxNumber> listOfNaturals;
   std::ofstream output;
   int counter; 
   char buffer[BUFFER_SIZE];
   char * p_input;

   public:
   ErasthostenesSieve() : 
           output("primesEveryWhere.txt", std::ios::out | std::ios::trunc),
           counter(0),
           p_input(buffer)
   {
      listOfNaturals.set();
      listOfNaturals.set(0, false); // 1 is not prime
   }

   ~ErasthostenesSieve()
   {
      if (p_input != buffer)
         output.write(buffer, p_input - buffer);  // flush
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
   inline void print(int number)
   {
      doPrint(number);
      counter ++;
   }

   inline void doPrint(int number)
   {
      boost::spirit::karma::generate(p_input, boost::spirit::int_, number);
      *p_input++ = '\n';
      if (p_input - buffer > BUFFER_SIZE - 8)
      {
         output.write(buffer, p_input - buffer); 
         p_input = buffer;
         memset(buffer, 0u, BUFFER_SIZE);
      }
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
