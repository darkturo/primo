/*
 * Using Sundaram' sieve, print the first 2,000,000 numbers
 * darkturo 2014
 */
#include <iostream>
#include <fstream>
#include <bitset>
#include <ctime>
#include <limits>
#include <boost/spirit/include/karma.hpp>

#define TIMEDIFF(start, stop) 1000.0 * (stop - start)/CLOCKS_PER_SEC
#define MAX 32452843
#define MAXPRIMES 2000000
#define BUFFER_SIZE 8l * MAX

class SundaramSieve
{
   std::bitset<MAX> N;
   std::ofstream output;
   int counter; 
   char * buffer;
   char * p_input;

   public:
   SundaramSieve() : 
           output("primesEveryWhere.txt", std::ios::out | std::ios::trunc),
           counter(0)
   {
      buffer = new char[BUFFER_SIZE];
      p_input = buffer;
      N.set();
   }

   ~SundaramSieve()
   {
      if (p_input != buffer)
         output.write(buffer, p_input - buffer);  // flush
      output.close();
   }

   void sieve()
   {
      print( 2 );
      for (long i = 1; (2*i + 2*(i^2)) <= 2*sqrt(MAX) - 1000; i++)
      {
         for (long j = i; (i + j + 2*i*j) <= (MAX - 2)/2; j++)
         {
            N.set((i + j + 2*i*j) - 1, false);
         }
      }

      for (int i = 1; counter < MAXPRIMES; i++)
      {
         if (N[i-1]) 
         {
            print( 2*i + 1 );
         }
      }
   }

   int printedPrimes()
   {
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
   }
};

int main(int argc, char ** argv)
{
   clock_t t1, t2;

   t1 = std::clock();

   SundaramSieve siever;
   siever.sieve();

   t2 = std::clock();

   // Summary
   std::cout.precision(std::numeric_limits<double>::digits10);
   std::cerr << "Used " << std::fixed << TIMEDIFF(t1, t2)
             << " msecs to calculate " << siever.printedPrimes()
             << " primes." << std::endl;
}
