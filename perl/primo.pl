#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers. 
# To test the primality I'm using Eratosthenes Sieve.
# 
# darkturo 2014.
use strict;
use POSIX;

# The gap between two consecutive prime numbers p and q, is always a
# multiple of 2, except for the case when p is 2, and q 3. 
# In the following table, I have the collection of gaps that will appear in
# the first 2M sequence. In principle, it is not more than count al the
# pairs, starting from 2; but in the end, the closer we are to 2M, some gaps
# are not present (at least in the first 2M numbers). So, with this list the
# idea is to avoid some calculations.
my @primeGapTable = ( 1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28,
                     30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56,
                     58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84,
                     86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 
                     110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 
                     132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 
                     154, 156, 164, 170, 180, 210, 220 );

my @primes = (2);

# Program
my $number = $primes[0]; 
open FILE, ">primesEveryWhere.txt";
for (my $i = 0; $i < 2000000; $i++)
{
   print FILE "$number\n";
   $number = findNextPrime($number);
}
close(FILE);

###################################
sub isPrime
{
   my $n = shift;
   
   my $factor = floor( sqrt($n) );
   for (; $factor > 1; $factor = previousFactor($factor))
   {
      if ($n % $factor == 0)
      {
         return 0;
      }
   }

   push @primes, $n;
   return 1;
}

sub previousFactor 
{
   my $currentFactor = shift;

   # Special cases
   return 0 if ( $currentFactor == 2 );
   return 2 if ( $currentFactor == 3 );

   my $factor = $currentFactor;
   if ($currentFactor % 2 == 0)
   {
      $factor --;
   }
   else
   {
      $factor -= 2;
   }
   
   return $factor;
}

sub findNextPrime
{
   my $currPrime = shift;

   # Special case.
   return 3 if ( $currPrime <= 2);

   # Calculate a number N (using the cojecture of Firoozbakht) so that is
   # greater than the gap betwen the prime (currPrime) and its subsequent
   my $ln = log($currPrime) ;
   my $gapBoundary = $ln**2 - $ln;

   # The conjecture only works for the primes greater than the 4th prime (7)
   $gapBoundary = 5 if ( $currPrime <= 7 );


   my $index = 0;
   my $candidate = 0;
   # Select the list applicable gaps that are lower tan Firoozbakht number. 
   do {
      if ($primeGapTable[$index] < $gapBoundary) 
      {
         if ($index < @primeGapTable)
         {
            $candidate = $currPrime + $primeGapTable[$index++];
         }
         else 
         {
            $candidate += 2;
         }
      }
   } while ( not isPrime($candidate) ); 

   return $candidate;
}
