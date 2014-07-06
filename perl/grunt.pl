#!/usr/bin/perl
# First 2,000,000 using Erasthostenes Sieve, and some regexp.
# 
# darkturo 2014

my $MaxPrimes = 2000000;
my $PrimeDensity = 0.0619413; # Is not really a true density, just the division 
                              # of 2000000 by the last digit in the prime sequence 
#my $SearchSpaceSize = $MaxPrimes * (1/$PrimeDensity);
my $SearchSpaceSize = 32452843;

# Premark 1, and all the even numbers
my $N = "01" . "10" x ($SearchSpaceSize/2);

# Sieve
for (my $i = 3; $i < sqrt($SearchSpaceSize); $i += 2)
{
   for (my $j = 2 * $i - 1; $j < $SearchSpaceSize; $j += $i)
   {
      $N =~ s/^(.{$j})\K./0/
   }
}

my ($number, $counter) = (0, 0);
open OUTPUT, ">primesEveryWhere.txt";
while ($N =~ m/(.)/g and $counter < $MaxPrimes)
{
   $number ++;
   print OUTPUT $number,"\n" and $counter++ if ($1 eq '1');
}
close OUTPUT;
