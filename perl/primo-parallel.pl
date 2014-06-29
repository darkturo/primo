#!/usr/bin/perl
#
# Find the first 2,000,000 prime numbers. 
# 
# darkturo 2014.
use strict;
use POSIX;
use threads;
use threads::shared;
use Thread::Queue;
use sort '_quicksort';
use List::Util qw(first);

no strict 'subs';
my $primesFound :shared;

# Tweak some details. These are for my current machine
my $CPU = 4;
my $numOfPrimeTesters = $CPU * 10;
my $PrimesToFind = 2000000;

# Queues
my $primeTestersQueue = Thread::Queue->new();
my $sortQueue = Thread::Queue->new();
my $printerQueue = Thread::Queue->new();

# Open the output file.
open FILE, ">primesEveryWhere.txt";

# Workers
my @primeTestWorkers; 
for (my $i; $i < $numOfPrimeTesters; $i++) 
{
   push @primeTestWorkers, threads->create( \&primeTester );
}

# Dispatcher
my $dispatcher = threads->create( \&dispatchJobs );

# Sorter
my $sortGuy = threads->create( \&sorter );

# Printer
my $printerGuy = threads->create( \&printer );

# loop 
my $elapsedTime = 0;
while ( $primesFound < $PrimesToFind )
{
   sleep(1);
   $elapsedTime ++;
   print "Prime Numbers Found: $primesFound (", sprintf("%.2f", $primesFound/$elapsedTime) , " pps)\n";
}

# ShutDown
$primeTestersQueue->end() ;

map { $_->join() } @primeTestWorkers; 
$dispatcher->join();
$sortGuy->join();
$printerGuy->join();

close(FILE);

###################################
## Subroutines
###################################
sub dispatchJobs 
{
   my @preCachedPrimes = (2, 3, 5, 7, 11, 13, 17, 19); 

   map { $sortQueue->enqueue($_) } @preCachedPrimes;

   my $candidate = $preCachedPrimes[-1];
   while ( $primesFound < $PrimesToFind )
   {
      $candidate += 2;
      if ( substr($candidate, -1) != "5" and $candidate % 3 != 0 )
      {
         $primeTestersQueue->enqueue( $candidate );
      }
   }
}

sub primeTester
{
   while (defined(my $n = $primeTestersQueue->dequeue(1))) 
   {
      my $isPrime = 1;
      my $maxFactor = floor( sqrt($n) );
      for (my $factor = 2; $factor <= $maxFactor; $factor += 2)
      {
         if ($n % $factor == 0)
         {
            $isPrime = 0;
            break;
         }

         # special case to put in 3.
         $factor-- if ($factor == 2)
      }

      if ( $isPrime )
      {
         # The number is prime!
         $sortQueue->enqueue($n);
         lock($primesFound);
         $primesFound++;
      }
   }
}

sub sorter
{
   my @buffer = ();
   my $bufferSize = 500;

   while (defined(my $n = $sortQueue->dequeue(1))) 
   {
      if (@buffer < $bufferSize)
      {
         push @buffer, $n;
      }
      else
      {
         $printerQueue->enqueue(sort @buffer);
         @buffer = ();
      }
   }
}

sub printer
{
   while (defined(my $n = $printerQueue->dequeue(1))) 
   {
      print FILE "$n\n";
   };
}
