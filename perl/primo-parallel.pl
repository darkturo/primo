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
use Time::HiRes;
use List::Util qw(first);

no strict 'subs';
my $primesFound :shared;

# Tweak some details. These are for my current machine
my $CPU = 4;
my $numOfPrimeTesters = $CPU * 128;
my $numOfSorters = $CPU; 
my $PrimesToFind = 2000000;
my $MaxCandidate = 32500000;

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

# Sorter
my @sortGuys;
for (my $i = 0; $i < $numOfSorters; $i++) 
{
   push @sortGuys, threads->create( \&sorter );
}

# Printer
my $printerGuy = threads->create( \&printer );

# Dispatcher
my $dispatcher = threads->create( \&dispatchJobs );

# loop 
my $elapsedTime = 0;
my $sleepTime = 1;
while ( $primesFound < $PrimesToFind )
{
   sleep($sleepTime);
   $elapsedTime += $sleepTime;
   print "Prime Numbers Found: $primesFound (", sprintf("%.2f", $primesFound/$elapsedTime) , " pps)\n";
}

# ShutDown
$primeTestersQueue->end() ;

map { $_->join() } @primeTestWorkers; 
$dispatcher->join();
map { $_->join() } @sortGuys;
$printerGuy->join();

close(FILE);

###################################
## SubroutdispatchJobs 
sub dispatchJobs 
{
   my @preCachedPrimes = (2, 3, 5, 7, 11, 13, 17, 19); 

   map { $sortQueue->enqueue($_) } @preCachedPrimes;

   my $jumpSize = 8092;
   my $candidate = $preCachedPrimes[-1];
   while ( $primesFound < $PrimesToFind )
   {
      if ( $candidate >= $MaxCandidate )
      {
         threads->exit();
      }
      async {
         $primeTestersQueue->enqueue( map { $candidate += 2 } 1..$jumpSize );
      }->detach();
      $candidate += ($jumpSize * 2);
      Time::HiRes::usleep(250000);
   }
}

sub primeTester
{
   while (my @listToTest = $primeTestersQueue->dequeue(100)) 
   {
      my @primes = ();
      for my $n (@listToTest) 
      {
         my $isPrime = 1;
         
         if ( substr($n, -1) eq "5" )
         {
            $isPrime = 0;
            next;
         }

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
            lock($primesFound);
            $primesFound++;
            push @primes, $n;
         }
      }
      $sortQueue->enqueue(@primes);
   }
}

sub sorter
{
   my $bufferSize = 1000;

   while (my @numbers = $sortQueue->dequeue($bufferSize)) 
   {
      $printerQueue->enqueue( sort { $a > $b } @numbers);
   }
}

sub printer
{
   while (defined(my $n = $printerQueue->dequeue(1000))) 
   {
      print FILE "$n\n";
   };
}
