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

#ifdef __Linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h> 
#define FILESIZE 17245905
#endif

#define TIMEDIFF(start, stop) 1000.0 * (stop - start)/CLOCKS_PER_SEC
#define MAXNUMBER 32452843
#define BUFFER_SIZE 8l * MAXNUMBER 

template <int MaxNumber>
class ErasthostenesSieve
{
   std::bitset<MaxNumber> listOfNaturals;
   std::ofstream output;
   int counter; 
#ifdef __Darwin__
   char * buffer;
   char * p_input;
#else
   char * p_map;
#endif

   public:
   ErasthostenesSieve() : 
#ifdef __Darwin__
           output("primesEveryWhere.txt", std::ios::out | std::ios::trunc),
#endif
           counter(0)
   {
      listOfNaturals.set();
      listOfNaturals.set(0, false); // 1 is not prime

#ifdef __Darwin__
      buffer = new char[BUFFER_SIZE];
      p_input = buffer;
#else
      output_fd = open("primesEveryWhere.txt", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0664);
      lseek(output_fd, FILESIZE-1, SEEK_SET);
      write(output_fd, "", 1);
      p_map = (char*)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, output_fd, 0);
      p_input = p_map;
#endif
   }

   ~ErasthostenesSieve()
   {
#ifdef __Darwin__
      if (p_input != buffer)
         output.write(buffer, p_input - buffer);  // flush
      output.close();
#else
      munmap(p_map, p_input - p_map);
      close(output_fd);
#endif
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
#ifdef __Darwin__
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
#else
   inline void print(int number)
   {
      boost::spirit::karma::generate(p_input, boost::spirit::int_, number);
      *p_input++ = '\n';
      counter ++;
   }
#endif
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
