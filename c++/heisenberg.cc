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
#define MAXNUMBER 32452843
#define BUFFER_SIZE 8l * MAXNUMBER 

class ErasthostenesSieve
{
   std::bitset<MAXNUMBER> listOfNaturals;
   std::ofstream output;
   int counter; 
   char * buffer;
   char * p_input;

   public:
   ErasthostenesSieve() : 
           output("primesEveryWhere.txt", std::ios::out | std::ios::trunc),
           counter(0)
   {
      listOfNaturals.set();
      listOfNaturals.set(0, false); // 1 is not prime

      buffer = new char[BUFFER_SIZE];
      p_input = buffer;
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

      for (base = 3; base * base < MAXNUMBER; base += 2 )
      {
         if (not listOfNaturals[base - 1]) 
            continue;

         print( base );
         
         for (int pivot = base + base ; pivot <= MAXNUMBER; pivot += base)
         {
            listOfNaturals.set(pivot - 1, false);
         }
      }

      for (; base <= MAXNUMBER; base += 2)
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
#if BOOST_VERSION > 103600
      *p_input++ = '\n';
#else
      p_input += strlen(p_input);
      *p_input++ = '\n';
#endif
   }
};

int main(int argc, char ** argv)
{
   clock_t t1, t2;

   t1 = std::clock();

   ErasthostenesSieve siever;
   int printedPrimes = siever.applyTheSieve();

   t2 = std::clock();

   // Summary
   std::cout.precision(std::numeric_limits<double>::digits10);
   std::cerr << "Used " << std::fixed << TIMEDIFF(t1, t2)
             << " msecs to calculate " << printedPrimes
             << " primes." << std::endl;
}
