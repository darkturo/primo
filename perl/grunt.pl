#!/usr/bin/perl
# First 2,000,000 using Erasthostenes Sieve, and some regexp.
# 
# darkturo 2014
my $SearchSpaceSize = 32452843;

# Discard 1, and all the numbers that in principle are not primes.
my $N = "0110101" . "000101000101000100000101000001" x ($SearchSpaceSize/30 + 2);

# Sieve
for (my $i = 7; $i < sqrt($SearchSpaceSize); $i += 2)
{
   next if (substr($N, $i - 1, 1) eq 0);
   my $j = $i - 1;
   pos($N) = $i;
   $N =~ s/\G.{$j}\K./0/g;
}

# print yeah
$N =~ s/\G(?{$n++})(.)(?:(?<=1(?{$prim="$n\n"}))|(?<=0(?{undef $prim})))/$prim/g;
open OUTPUT, ">primesEveryWhere.txt";
print OUTPUT $N;
close OUTPUT;
