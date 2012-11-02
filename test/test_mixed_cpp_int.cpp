///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_

//
// Compare arithmetic results using fixed_int to GMP results.
//

#ifdef _MSC_VER
#  define _SCL_SECURE_NO_WARNINGS
#endif

#include <boost/multiprecision/cpp_int.hpp>
#include "test.hpp"

template <class Number, class BigNumber>
void test()
{
   using namespace boost::multiprecision;
   typedef Number test_type;

   test_type h = (std::numeric_limits<test_type>::max)();
   test_type l = (std::numeric_limits<test_type>::max)();
   BigNumber r;

   add(r, h, h);
   BOOST_CHECK_EQUAL(r, cpp_int(h) + cpp_int(h));

   multiply(r, h, h);
   BOOST_CHECK_EQUAL(r, cpp_int(h) * cpp_int(h));

   if(std::numeric_limits<test_type>::is_signed)
   {
      subtract(r, l, h);
      BOOST_CHECK_EQUAL(r, cpp_int(l) - cpp_int(h));
      subtract(r, h, l);
      BOOST_CHECK_EQUAL(r, cpp_int(h) - cpp_int(l));
      multiply(r, l, l);
      BOOST_CHECK_EQUAL(r, cpp_int(l) * cpp_int(l));
   }

   //
   // Try again with integer types as the source:
   //
   static const unsigned max_digits = std::numeric_limits<test_type>::is_signed ? std::numeric_limits<long long>::digits : std::numeric_limits<unsigned long long>::digits;
   static const unsigned require_digits = std::numeric_limits<test_type>::digits <= 2 * max_digits ? std::numeric_limits<test_type>::digits / 2 : max_digits;
   typedef typename boost::mpl::if_c<std::numeric_limits<test_type>::is_signed, typename boost::int_t<require_digits>::least, typename boost::uint_t<require_digits>::least>::type i_type;

   i_type ih = (std::numeric_limits<i_type>::max)();
   i_type il = (std::numeric_limits<i_type>::max)();

   add(r, ih, ih);
   BOOST_CHECK_EQUAL(r, cpp_int(ih) + cpp_int(ih));

   multiply(r, ih, ih);
   BOOST_CHECK_EQUAL(r, cpp_int(ih) * cpp_int(ih));

   if(std::numeric_limits<test_type>::is_signed)
   {
      subtract(r, il, ih);
      BOOST_CHECK_EQUAL(r, cpp_int(il) - cpp_int(ih));
      subtract(r, ih, il);
      BOOST_CHECK_EQUAL(r, cpp_int(ih) - cpp_int(il));
      multiply(r, il, il);
      BOOST_CHECK_EQUAL(r, cpp_int(il) * cpp_int(il));
   }
}

int main()
{
   using namespace boost::multiprecision;

   test<checked_int512_t, checked_int1024_t>();
   test<checked_int256_t, checked_int512_t>();
   test<number<cpp_int_backend<64, 64, signed_magnitude, checked, void>, et_off>, checked_int512_t>();

   test<checked_uint512_t, checked_uint1024_t>();
   test<checked_uint256_t, checked_uint512_t>();
   test<number<cpp_int_backend<64, 64, unsigned_magnitude, checked, void>, et_off>, checked_uint512_t>();
   return boost::report_errors();
}


