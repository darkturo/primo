#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers using Eratosthenes Sieve, and the
# conjecture of Firoozbakht to find subsequent numbers (instead of just adding
# one to each candidate).
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
   my @p_n = (1, 2, 3, 5, 7, 11);

   # The conjecture works for p_n where n is greater than 4
   if ( $currPrime <= $p_n[4] )
   {
      my( $index )= grep { $p_n[$_] eq $currPrime } 0..$#p_n;
      return $p_n[$index + 1];
   }

   # Use the conjecture of Firoozbakht to find the gap boundary, between the
   # current prime and the next prime.
   my $lnCurrPrime = log($currPrime) ;
   my $gapBoundary = floor($lnCurrPrime**2 - $lnCurrPrime);
   
   my $candidate = $currPrime + $gapBoundary;
   while ( not isPrime($candidate) )
   {
      $candidate--;
   }
   return $candidate;
}
