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
#define BUFFER_SIZE 512 

template <int MaxNumber>
class ErasthostenesSieve
{
   std::bitset<MaxNumber> listOfNaturals;
   std::ofstream output;
   int counter; 
#ifdef __Darwin__
   char buffer[BUFFER_SIZE];
#else
   char * p_map;
   int output_fd;
#endif
   char * p_input;

   public:
   ErasthostenesSieve() : 
#ifdef __Darwin__
           output("primesEveryWhere.txt", std::ios::out | std::ios::trunc),
           counter(0),
           p_input(buffer)
#else
           counter(0)
#endif
   {
      listOfNaturals.set();
      listOfNaturals.set(0, false); // 1 is not prime

#ifdef __Linux__
      output_fd = open("primesEveryWhere.txt", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0664);
      lseek(output_fd, FILESIZE-1, SEEK_SET);
      write(output_fd, "", 1);
      p_map = (char*)mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, output_fd, 0);
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
      msync(p_map, FILESIZE, MS_ASYNC);
      munmap(p_map, FILESIZE);
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

      if (p_input - buffer > BUFFER_SIZE - 8)
      {
         output.write(buffer, p_input - buffer); 
         p_input = buffer;
         memset(buffer, 0u, BUFFER_SIZE);
      }
   }
#else
   inline void print(int number)
   {
      boost::spirit::karma::generate(p_input, boost::spirit::int_, number);
      p_input += strlen(p_input);
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
