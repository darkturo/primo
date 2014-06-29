#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers. 
# 
# darkturo 2014.
use strict;
use POSIX;
use threads;
use Thread::Queue;
use sort '_quicksort'

# Tweak some details. These are for my current machine
my $CPU = 4
my $numOfPrimeExplorers = $CPU * 4;
my $numOfPrimeTesters = $CPU * 8;
my $PrimesToFind = 2000000;

# Queues
my $primeExplorersQueue = Thread::Queue->new();
my $primeTestersQueue = Thread::Queue->new();
my $printerQueue = Thread::Queue->new();

# Workers
my @primeExplorerWorkers; 
my @primeTestWorkers; 
for (my $i; $i < $numOfPrimeExplorers; $i++) 
{
   push @primeExplorerWorkers, threads->create( \&primeExplorer );
#   my $thr = threads->create( $printPrime );
}

for (my $i; $i < $numOfPrimeTesters; $i++) 
{
   push @primeTestWorkers, threads->create( \&primeTester);
}

# Assign some work (starting with number 2)
$primeExplorersQueue->enque(2);

# The printing work, will be done by this main thread.
my $primesFound = 0;
my @buffer = ();
my @printJobs = ();
open FILE, ">primesEveryWhere.txt";
while (defined(my $n = $printerQueue->dequeue())) 
{
   $primesFound ++;
   if ($primesFound <= $PrimesToFind)
   {
      if (@buffer < 500)
      {
         push @buffer, $n;
      }
      else
      {
         @buffer = sort @buffer;
         push @printJobs, async
            {
               for (my $i = 0; $i < @buffer - $numOfPrimeExplorers; $i++)
               {
                  print FILE "$buffer[$i]\n";
               }
            };
      }

      if ($primesFound == $PrimesToFind)
      {
         $printerQueue->end(); 
      }
   }
   else
   {
      #Stop the train
      $printerQueue->end(); 
   }
}

# ShutDown
$primeExplorersQueue->end();
$primeTestersQueue->end() ;

map { $_->join() } @primeExplorerWorkers; 
map { $_->join() } @primeTestWorkers; 

close(FILE);

###################################
## Subroutines
###################################
sub primeExplorer 
{
   my %switchTable = {2 => 3, 3 => 5, 5 => 7, 7 => 11};
   while (defined(my $n = $primeExplorersQueue->dequeue())) 
   {
      # Going to use the conjecture of Firoozbakht to jump between primes. The
      # conjecture does not apply for the first 4 prime numbers, so I'm
      # skipping them.
      if ($n <= 7)
      {
         $primeExplorersQueue->enque($switchTable{$n});
         $printerQueue->enque($n)
      }

      # Then, I find the Firoozbakht number that ensures to be greater than the
      # gap between the current number and the next one.
      my $ln = log($n) ;
      my $gapBoundary = floor($ln**2 - $ln);
      
      for (my $gap = 2; $gap < $gapBoundary; $gap += 2)
      {
         $primeTestersQueue->enque($n + $gap);
      }
   }
}

sub primeTester
{
   while (defined(my $n = $primeTestersQueue->dequeue())) 
   {
      my $isPrime = 1;
      my $maxFactor = floor( sqrt($n) );
      for ($factor = 2; $factor <= $maxFactor; $factor += 2)
      {
         if ($n % $factor == 0)
         {
            $isPrime = 0;
            break;
         }

         # special case to put in 3.
         $pivot-- if ($pivot == 2)
      }

      if ( $isPrime )
      {
         # The number is prime!
         $primeExplorersQueue->enque($n);        
         $printerQueue->enque($n)
      }
   }
}
