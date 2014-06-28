#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers using Eratosthenes Sieve, and the
# conjecture of Firoozbakht to find subsequent numbers (instead of just adding
# one to each candidate).
# 
# darkturo 2014.
use strict;
use POSIX;

my $number = 2; 
open FILE, ">primesEveryWhere.txt";
for (my $i = 0; $i < 2000000; $i++)
{
   print FILE "$number\n";
   $number = findNextPrime($candidate);
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

my @preCached = (2, 3, 5, 7, 11)
sub findNextPrime
{
   my $currPrime = shift;

   if (@preCached)
   {
      # The conjecture works for p_n where n is greater than 4, that's why I'll
      # start with 11. 
      return shift @preCached;
   }

   # Use the conjecture of Firoozbakht to find the gap boundary, between the
   # current prime and the next prime.
   my $lnCurrCand = log($currCandidate) ;
   my $gapBoundary = $lnCurrCand**2 - $lnCurrCand;
   
   my $candidate = $currPrime + $gapBoundary;
   while ( not isPrime($candidate) )
   {
      $candidate--;
   }
   return $candidate;
}
