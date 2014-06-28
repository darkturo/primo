#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers. 
# To test the primality I'm using Eratosthenes Sieve.
# 
# darkturo 2014.
use strict;
use POSIX;

my @primes = (2, 3, 5, 7, 11);
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
      $factor = $primes[$index];
      if ($n % $factor == 0)
      {
         return 0;
      }
      $index ++;
   }
   push @primes, $n;
   return 1;
}

sub nextFactor
{
   my $n = shift;
   return $n + 2;
}

sub findNextPrime
{
   my $currPrime = shift;
   my @primeGapTable = (1, 2, 4, 6, 8, 14, 18, 20, 22, 34, 36, 44, 52, 
                        72, 86, 96, 112, 114, 118, 132, 148, 154, 180, 
                        210, 220);
   my $index = 0;

   my $candidate = 0;
   do {
      $candidate = $currPrime + $primeGapTable[$index];
   } while ( not isPrime($candidate) );

   return $candidate;
}
