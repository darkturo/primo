#!/usr/bin/perl
#
# Simplistic implementation, using Eratosthenes Sieve
# 
# darkturo 2014.
use strict;
use POSIX;

my $candidate = 2; 
my $numbersFound = 0;
open FILE, ">primesEveryWhere.txt";
while ($numbersFound != 2000000) 
{
   if ( isPrime( $candidate ) )
   {
      print FILE "$candidate\n";
      $numbersFound++;
   }
   $candidate++;
}
close(FILE);

sub isPrime
{
   my $n = shift;

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
