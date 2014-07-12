#!/usr/bin/perl
#
# Erasthostenes sieve in perl to calculate 2000000
# darkturo 2014
my $LASTPRIME = 32452843;
my @N = ((0, 0, 1, 1, 0, 1, 0, 1), 
         (0, 0, 0, 1, 0, 1, 0, 0, 
          0, 1, 0, 1, 0, 0, 0, 1, 
          0, 0, 0, 0, 0, 1, 0, 1, 
          0, 0, 0, 0, 0, 1) x ($LASTPRIME/30 + 2));

my $i;
open FILE, ">primesEveryWhere.txt";
print FILE "2\n3\n5\n";
for ($i = 7; $i < sqrt($LASTPRIME); $i += 2)
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
