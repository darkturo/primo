#include <math.h>
#include <iostream>
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

class end_of_sieve
{
   public:
   bool isComposite(int n)
   {
      return false;
   }

   void print()
   {
      std::cerr << "Hasta la vista, baby" << std::endl;
   }
};

template <int base, int max, typename listOfNaturals>
class sieve_iterate_rest
{
   enum { value = base };
   
   public:
   void print()
   {
      if_ < (base + 2) <= max,
            sieve_iterate_rest<base + 2, max>, 
            end_of_sieve> sieve;

      if ( not sieve.isComposite(base) )
         std::cout << value << endl;
      sieve.print();
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
   
   if_ < (base + 2 * base) < max,
        sieve_mark_multiples_iter<base + 2 * base, max>, 
        end_of_list > multiplesOfBase;

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
      if_ < (base + 2 * base) <= max,
            sieve_mark_multiples_iter<base + 2 * base, max>, 
            end_of_list > multiplesOfBase;

      if ( n == value )
         return false;
      else 
         if ( multiplesOfBase.has(n) )
            return true;
         else
            return listOfNaturals.isComposite(n);
   }
};

template <int max, typename listOfNaturals>
class sieve_mark_multiples<2>
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
   if_< base <= sqrt, 
        sieve_explore<base + 2, sqrt, max, sieve_mark_multiples<base, max, listOfNaturals> >
        sieve_iterate_rest<base + 2, max, listOfNaturals> > sieve;

   public:
   void print()
   {
      if ( not sieve.isComposite(base) )
         std::cout << value << endl;
      sieve.print();
   }
};

template <int sqrt, int max, typename listOfNaturals>
class sieve_explore<2>
{
   enum { value = 2 };
   sieve_explore<3, sqrt, max, sieve_mark_multiples<2, max, listOfNaturals> > sieve;
   public:
   void print()
   {
      std::cout << 2 << endl;
      sieve.print();
   }
};

template <int n>
class erasthostenes {
public:
   void sieve() 
   {
      sieve_explore<2, SQRT(n), n, end_of_sieve> sieve;
      sieve.print();
   }
};

int main(int argc, char ** argv)
{
   const int max_number = 32288611;

   erasthostenes<max_number> Erasthostenes;
   Erasthostenes::sieve();
}
