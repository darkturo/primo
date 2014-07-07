#!/usr/bin/perl
#
# Erasthostenes sieve in perl to calculate 2000000
# darkturo 2014
my $LASTPRIME = 32452843;
my @N = (1) x ($LASTPRIME + 1);
$N[0] = 0;
$N[1] = 0;

open FILE, ">primesEveryWhere.txt";

my $i;
for ($i = 2; $i < sqrt($LASTPRIME); $i += ($i == 2? 1 : 2))
{
   if ( $N[$i] ) 
   {
      print FILE "$i\n";
      for (my $j = $i + $i; $j <= $LASTPRIME; $j += $i )
      {
         $N[$j] = 0;
      }
   }
}

for (; $i <= $LASTPRIME; $i += 2)
{
   if ( $N[$i] ) 
   {
      print FILE "$i\n";
   }
}

close(FILE);
