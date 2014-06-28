#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers. 
# To test the primality I'm using Eratosthenes Sieve.
# 
# darkturo 2014.
use strict;
use POSIX;

my $number = 2; 
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

   if ( ( $n % 2 == 0 ) or ( $n % 3 == 0 ) or ( $n % 5 == 0 ) )
   {
      return 0 unless ( $n == 2 or $n == 3 or $n == 5 );
   }

   my $squareOfN = sqrt($n);
   for (my $factor = floor($squareOfN); $factor > 1; $factor--)
   {
      if ($n % $factor == 0)
      {
         return 0;
      }
   }
   return 1;
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
