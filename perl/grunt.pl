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
my $N = "011" . "010100" x ($SearchSpaceSize/6);

# Sieve
for (my $i = 5; $i < sqrt($SearchSpaceSize); $i += 2)
{
   my $j = $i - 1;
   pos($N) = $i;
   $N =~ s/\G.{$j}\K./0/g;
}

# print yeah
$N =~ s/\G(?{$n++})(.)(?:(?<=1(?{$prim="$n\n"}))|(?<=0(?{undef $prim})))/$prim/g;
open OUTPUT, ">primesEveryWhere.txt";
print OUTPUT substr($N, 0, $MaxPrimes), "\n";
close OUTPUT;
