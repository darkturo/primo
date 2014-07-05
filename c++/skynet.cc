#include <math.h>
#include <iostream>
#include <ctime>
#include <limits>

#define MID(a, b) ((a+b)/2)
#define POW(a) (a*a)

template<long long int res, long long int l = 1, long long int r = res>
struct SQRT;

template<long long int res, long long int r>
struct SQRT<res, r, r> {
   static const long long int value = r;
};

template <long long int res, long long int l, long long int r>
struct SQRT {
   static const long long int value = SQRT<res, 
                                (POW(MID(r, l)) >= res ?  l : MID(r, l)+1),
                                (POW(MID(r, l)) >= res ? MID(r, l) : r)>::value;
};

template <bool Condition, typename TrueResult, typename FalseResult>
struct if_;
 
template <typename TrueResult, typename FalseResult>
struct if_<true, TrueResult, FalseResult>
{
   typedef TrueResult result;
};
 
template <typename TrueResult, typename FalseResult>
struct if_<false, TrueResult, FalseResult>
{
   typedef FalseResult result;
};
/////////////////
 
class end_of_sieve
{
   public:
   bool isComposite(int n)
   {
      return false;
   }

   int print()
   {
      /* done! */
      return 0;
   }
};

template <int base, int max, typename listOfNaturals>
class sieve_iterate_rest
{
   enum { value = base };
   
   public:
   bool isComposite(int n)
   {
      listOfNaturals N;
      return N.isComposite(n);
   }

   int print()
   {
      typename if_< ((base + 2) <= max),
                  sieve_iterate_rest<base + 2, max, listOfNaturals>, 
                  end_of_sieve>::result sieve;
      int count = 0;

      if ( not sieve.isComposite(base) ) 
      {
         std::cout << value << std::endl;
         count ++;
      }
      return count + sieve.print();
   }
};

class end_of_list
{
   public:
   bool has(int n)
   {
      return false;
   }
};

template <int base, int max>
class sieve_mark_multiples_iter
{
   enum { value = base };
   
   typename if_< (base + 2 * base) <= max,
              sieve_mark_multiples_iter<base + 2 * base, max>, 
              end_of_list >::result multiplesOfBase;

   public:
   bool has(int n)
   {
      if ( n == value )
         return true;
      else
         return multiplesOfBase.has(n); 
   }
};

template <int base, int max, typename listOfNaturals>
class sieve_mark_multiples 
{
   enum { value = base };
   
   public:
   bool isComposite(int n)
   {
      typename if_< (base + 2 * base) <= max,
                  sieve_mark_multiples_iter<base + 2 * base, max>, 
                  end_of_list >::result multiplesOfBase;
      listOfNaturals naturals;

      if ( n == value )
         return false;
      else 
         if ( multiplesOfBase.has(n) )
            return true;
         else
            return naturals.isComposite(n);
   }
};

template <int max, typename listOfNaturals>
class sieve_mark_multiples<2, max, listOfNaturals>
{
   public:
   bool isComposite(int n)
   {
      return (n % 2 == 0);
   }
};

template <int base, int sqrt, int max, typename listOfNaturals>
class sieve_explore
{
   enum { value = base };
   typename if_< base <= sqrt, 
               sieve_explore<base + 2, sqrt, max, sieve_mark_multiples<base, max, listOfNaturals> >,
               sieve_iterate_rest<base + 2, max, listOfNaturals> >::result sieve;

   public:
   int print()
   {
      listOfNaturals N;
      int count = 0;

      if ( not N.isComposite(base) )
      {
         std::cout << value << std::endl;
         count++;
      }
      return count + sieve.print();
   }
};

template <int sqrt, int max, typename listOfNaturals>
class sieve_explore<2, sqrt, max, listOfNaturals>
{
   enum { value = 2 };
   typename if_< value <= sqrt, 
               sieve_explore<value + 1, sqrt, max, sieve_mark_multiples<2, max, listOfNaturals> >,
               sieve_iterate_rest<value + 1, max, listOfNaturals> >::result sieve;
   public:
   int print()
   {
      std::cout << value << std::endl;
      int count = 1;
      if (max > value) 
         count += sieve.print();
      return count;
   }
};

template <int n>
class erasthostenes_t {
public:
   int sieve() 
   {
      if (n > 1)
      {
         sieve_explore<2, SQRT<n>::value, n, end_of_sieve> sieve;
         return sieve.print();
      }
      return 0;
   }
};

int main(int argc, char ** argv)
{
   //const int max_number = 32288611;
   const int max_number = 20;
   time_t t1, t2;

   time(&t1);

   erasthostenes_t<max_number> Erasthostenes;
   int calculatedPrimes = Erasthostenes.sieve();

   time(&t2);
   std::cout.precision(std::numeric_limits<double>::digits10);
   std::cerr << "Used " << std::fixed << difftime(t2, t1) 
             << " seconds to calculate " << calculatedPrimes
             << " primes." << std::endl;
}
