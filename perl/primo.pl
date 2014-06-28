#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers. 
# To test the primality I'm using Eratosthenes Sieve.
# 
# darkturo 2014.
use strict;
use POSIX;

my @primes = (2, 3);
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

   my $index = 0;
   my $factor = 1;
   my $factorLimit = floor( sqrt($n) );
   while ($factor <= $factorLimit)
   {
      $factor = $primes[$index++];
      if ($n % $factor == 0)
      {
         return 0;
      }
   }
   push @primes, $n;
   return 1;
}

sub findNextPrime
{
   my $currPrime = shift;
   my $index = 0;

   # A list of gap jumps in according of their frequency. This list is accurate
   # for the first 2M numbers. 
   my @primeGapTable = ( 6, 12, 2, 4, 10, 18, 8, 14, 24, 16, 30, 20, 22, 28, 26,
                         36, 42, 34, 32, 40, 38, 48, 44, 54, 46, 50, 60, 52, 56,
                         66, 58, 64, 62, 70, 72, 78, 68, 84, 74, 76, 90, 80, 82,
                         88, 86, 96, 92, 94, 100, 102, 98, 108, 104, 114, 110,
                         120, 112, 106, 126, 116, 118, 132, 122, 124, 138, 130,
                         140, 136, 144, 134, 128, 148, 150, 142, 156, 154, 146,
                         152, 210, 180, 170, 164, 1 );

   my $candidate = 0;
   do {
      if ($index < @primeGapTable) 
      {
         # jump using the more frequent gaps between numbers
         $candidate = $currPrime + $primeGapTable[$index++];
      }
      else
      {
         # The number is out of reach, of the greedy strategy.
         # Icrement steps of 2. 
         $candidate += 2;
      }
   } while ( not isPrime($candidate) ); 

   return $candidate;
}
