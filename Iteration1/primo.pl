#!/usr/bin/perl
#
# Simplistic implementation, using Eratosthenes Sieve
# 
# darkturo 2014.
use strict;
use POSIX;

my $candidate = 2; 
my $numbersFound = 0;
while ($numbersFound != 2000000) 
{
   if ( isPrime( $candidate ) )
   {
      print "$candidate\n";
      $numbersFound++;
   }
   $candidate++;
}

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
