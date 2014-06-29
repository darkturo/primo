#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers. 
# To test the primality I'm using Eratosthenes Sieve.
# 
# darkturo 2014.
use strict;
use POSIX;

# Program
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

   return 1 if ( $n == 2 or $n == 3 or $n == 5 ); 
   return 0 if ( $n % 2 == 0 or $n % 3 == 0 or $n % 5 == 0);
   
   my $pivot = floor( sqrt($n) );
   $pivot-- if ($pivot > 2 and $pivot % 2 == 0);

   for (; $pivot > 5; $pivot -= 2)
   {
      if ($n % $pivot == 0)
      {
         return 0;
      }
   }

   return 1;
}

sub findNextPrime
{
   my $currPrime = shift;

   # Special case.
   return 3 if ( $currPrime == 2);

   my $nextPrime = $currPrime;
   do
   {
      $nextPrime += 2;
   } while ( not isPrime($nextPrime) ); 
   
   return $nextPrime;
}
