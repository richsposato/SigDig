// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#ifdef __CYGWIN__
	#undef _REENT_ONLY
#endif


#include <UnitTest.hpp>

#include <utility.hpp>
#include <defined_value.hpp>
#include <calculated_value.hpp>

#include <iostream>
#include <iomanip>

using namespace ut;
using namespace sigdig;

// ----------------------------------------------------------------------------

void TestDefinedValueBasics()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined Value Basics" );

	// Basic tests with the value zero.
	const defined_value zero;
	UNIT_TEST( u,  zero.get_value() == 0.0L );
	UNIT_TEST( u,  zero.to_string() == "0" );
	UNIT_TEST( u,  zero.get_most_sigdig_exponent() == 0 );

	// Basic tests with the value one.
	const defined_value one( 1.0L );
	UNIT_TEST( u,  one.get_value() == 1.0L );
	UNIT_TEST( u,  one.to_string() == "1" );
	UNIT_TEST( u,  one.get_most_sigdig_exponent() == 0 );

	defined_value d2;
	UNIT_TEST( u, zero == d2 ); // Default constructed value should be equal to another default-constructed value.
	UNIT_TEST( u, zero.equals( d2 ) );

	d2 = 1.0L;
	UNIT_TEST( u, zero != d2 );
	UNIT_TEST( u, !zero.equals( d2 ) );
	UNIT_TEST( u, zero < d2 );
	UNIT_TEST( u, zero.less_than( d2 ) );
	UNIT_TEST( u, zero <= d2 );
	UNIT_TEST( u, zero.less_than_or_equals( d2 ) );

	d2 = 0.0L;
	UNIT_TEST( u, zero == d2 );
	UNIT_TEST( u, zero.equals( d2 ) );
	UNIT_TEST( u, zero >= d2 );
	UNIT_TEST( u, zero.greater_than_or_equals( d2 ) );
	UNIT_TEST( u, zero <= d2 );
	UNIT_TEST( u, zero.less_than_or_equals( d2 ) );

	defined_value d3( one );
	UNIT_TEST( u, d3 == one );
	UNIT_TEST( u, d3.equals( one ) );
	UNIT_TEST( u, d3 != d2 );
	UNIT_TEST( u, !d3.equals( d2 ) );
	UNIT_TEST( u, d3 != zero );
	UNIT_TEST( u, !d3.equals( zero ) );

	d2.swap( d3 );
	UNIT_TEST( u,  d3 != one );
	UNIT_TEST( u, !d3.equals( one ) );
	UNIT_TEST( u,  d3 != d2 );
	UNIT_TEST( u, !d3.equals( d2 ) );
	UNIT_TEST( u,  d3 == zero );
	UNIT_TEST( u,  d3.equals( zero ) );
}

// ----------------------------------------------------------------------------

void TestDefinedStringParsing()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_String_Parsing" );

	defined_value v1( "123" );
	UNIT_TEST( u, v1.get_value() == 123.0L );
	UNIT_TEST( u, v1.get_most_sigdig_exponent() == 2 );

	defined_value v2( "-0.0643" );
	UNIT_TEST( u, utility::are_nearly_equal( v2.get_value(), -0.0643L ) );
	UNIT_TEST( u, v2.get_most_sigdig_exponent() == -2 );

	defined_value v3( "123" );
	UNIT_TEST( u, v3.get_value() == 123.0L );
	UNIT_TEST( u, v3.get_most_sigdig_exponent() == 2 );

	defined_value v4( "9876.54321" );
	UNIT_TEST( u, utility::are_nearly_equal( v4.get_value(), 9876.54321L ) );
	UNIT_TEST( u, v4.get_most_sigdig_exponent() == 3 );

	defined_value v5( "1.54321E+10" );
	UNIT_TEST( u, v5.get_value() == 15432100000.0L );
	UNIT_TEST( u, v5.get_most_sigdig_exponent() == 10 );

	defined_value v6( "-1.54321E-7" );
	UNIT_TEST( u, utility::are_nearly_equal( v6.get_value(), -0.000000154321L ) );
	UNIT_TEST( u, v6.get_most_sigdig_exponent() == -7 );
}

// ----------------------------------------------------------------------------

void TestDefinedStringOutput()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_String_Output" );

	std::string input( "123" );
	defined_value v1( input );
	UNIT_TEST( u, v1.to_string() == input );

	input = "-0.0643";
	defined_value v2( input );
	UNIT_TEST( u, v2.to_string( 3 ) == input );

	input = "123";
	defined_value v3( input );
	UNIT_TEST( u, v3.to_string() == input );
//	std::cout << "v3 [" << v3.to_string() << ']' << std::endl;

	input = "9876.54321";
	defined_value v4( input );
	UNIT_TEST( u, v4.to_string( 9 ) == input );
//	std::cout << "v4 [" << v4.to_string( 9 ) << ']' << std::endl;

	input = "1.54321E+10";
	defined_value v5( input );
	UNIT_TEST( u, v5.to_string() == "15432100000" );
//	std::cout << "v5 [" << v5.to_string() << ']' << std::endl;

	input = "-1.54321E-7";
	defined_value v6( input );
	UNIT_TEST( u, v6.to_string( 6 ) == "-0.000000154321" );
//	std::cout << "v6 [" << v6.to_string( 6 ) << ']' << std::endl;
}

// ----------------------------------------------------------------------------

void TestDefinedNegation()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined Negation" );

	defined_value zero;
	defined_value one( 1UL );
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  one == 1.0L );

	zero = -zero;
	UNIT_TEST( u, zero == 0.0L );

	one = -one;
	UNIT_TEST( u, one == -1.0L );

	defined_value v( -one );
	UNIT_TEST( u, v == 1.0L );
	v = -v;
	UNIT_TEST( u, v == -1.0L );

	defined_value notNegative = zero.absolute();
	UNIT_TEST( u, notNegative == 0.0L );
	UNIT_TEST( u, notNegative.get_most_sigdig_exponent() == zero.get_most_sigdig_exponent() );

	notNegative = v.absolute(); // v is negative.
	UNIT_TEST( u, notNegative == 1.0L );
	UNIT_TEST( u, notNegative.get_most_sigdig_exponent() == zero.get_most_sigdig_exponent() );

	notNegative = one.absolute(); // one is positive
	UNIT_TEST( u, notNegative == 1.0L );
	UNIT_TEST( u, notNegative.get_most_sigdig_exponent() == zero.get_most_sigdig_exponent() );
}

// ----------------------------------------------------------------------------

void TestDefinedEquals()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Equals" );

	const char  zeroChar  = 0;
	const short zeroShort = 0;
	const int   zeroInt   = 0;
	const long  zeroLong  = 0;
	const float zeroFloat = 0.0F;
	const char  oneChar   = 1;
	const short oneShort  = 1;
	const int   oneInt    = 1;
	const long  oneLong   = 1;
	const float oneFloat  = 1.0F;
	const char  minusOneChar  = -1;
	const short minusOneShort = -1;
	const int   minusOneInt   = -1;
	const long  minusOneLong  = -1;

	const float minusOneFloat = -1.0L; 
	const defined_value zero;

	// every test in this section is for operator== or equals.
	UNIT_TEST( u,  zero == 0.0L );
	UNIT_TEST( u,  zero == zeroChar  );
	UNIT_TEST( u,  zero == zeroShort );
	UNIT_TEST( u,  zero == zeroInt   );
	UNIT_TEST( u,  zero == zeroLong  );
	UNIT_TEST( u, !( zero == oneFloat ) );
	UNIT_TEST( u, !( zero == oneChar  ) );
	UNIT_TEST( u, !( zero == oneShort ) );
	UNIT_TEST( u, !( zero == oneInt   ) );
	UNIT_TEST( u, !( zero == oneLong  ) );
	UNIT_TEST( u, !( zero == minusOneFloat ) );
	UNIT_TEST( u, !( zero == minusOneChar  ) );
	UNIT_TEST( u, !( zero == minusOneShort ) );
	UNIT_TEST( u, !( zero == minusOneInt   ) );
	UNIT_TEST( u, !( zero == minusOneLong  ) );
	UNIT_TEST( u,  zero.equals( 0.0L ) );
	UNIT_TEST( u,  zero.equals( 0.0L, 0.000001L ) );
	UNIT_TEST( u,  zero.equals( 0.0L, 1.0L ) );
	UNIT_TEST( u,  zero.equals( zeroChar ) );
	UNIT_TEST( u,  zero.equals( zeroShort ) );
	UNIT_TEST( u,  zero.equals( zeroInt ) );
	UNIT_TEST( u,  zero.equals( zeroLong ) );
	UNIT_TEST( u,  zero.equals( zeroChar,  0.001L ) );
	UNIT_TEST( u,  zero.equals( zeroShort, 0.001L ) );
	UNIT_TEST( u,  zero.equals( zeroInt,   0.001L ) );
	UNIT_TEST( u,  zero.equals( zeroLong,  0.001L ) );
	UNIT_TEST( u, !zero.equals( oneFloat ) );
	UNIT_TEST( u,  zero.equals( 0.0001L, 0.001L   ) );
	UNIT_TEST( u,  zero.equals( 0.0001L, 0.0001L  ) );
	UNIT_TEST( u, !zero.equals( 0.0001L, 0.00009L ) );

	const defined_value one( 1.0L );
	UNIT_TEST( u,  one == oneFloat );
	UNIT_TEST( u,  one.equals( oneFloat ) );
	UNIT_TEST( u,  one.equals( oneFloat, 0.000001L ) );
	UNIT_TEST( u,  one.equals( oneFloat, 1.0L ) );
	UNIT_TEST( u,  one != 0.0L );
	UNIT_TEST( u,  one.equals( oneFloat ) );
	UNIT_TEST( u,  one.equals( 1.01L,      0.1L      ) );
	UNIT_TEST( u,  one.equals( 1.001L,     0.01L     ) );
	UNIT_TEST( u,  one.equals( 1.0001L,    0.001L    ) );
	UNIT_TEST( u,  one.equals( 1.00001L,   0.0001L   ) );
	UNIT_TEST( u,  one.equals( 1.000001L,  0.00001L  ) );
	UNIT_TEST( u,  one.equals( 1.0000001L, 0.000001L ) );
	UNIT_TEST( u, !one.equals( 1.0001L, 0.00009L ) );
	UNIT_TEST( u, !one.equals( 1.001L,  0.0009L  ) );
	UNIT_TEST( u, !one.equals( 1.01L,   0.009L   ) );
	UNIT_TEST( u, !one.equals( 1.1L,    0.09L    ) );
	UNIT_TEST( u,  one.equals( 1.0L,    0.9L     ) );

	UNIT_TEST( u, !one.equals( -1.0001L, 0.001L   ) );
	UNIT_TEST( u, !one.equals( -1.0001L, 0.0001L  ) );
	UNIT_TEST( u, !one.equals( -1.0001L, 0.00009L ) );

	UNIT_TEST( u,  one == one  );
	UNIT_TEST( u,  one != zero );
	UNIT_TEST( u, zero == zero );
	UNIT_TEST( u, zero != one  );

	calculated_value cv0;
	calculated_value cv1( 1.0L );
	UNIT_TEST( u, zero == cv0 );
	UNIT_TEST( u, zero != cv1 );
	UNIT_TEST( u, !( zero != cv0 ) );
	UNIT_TEST( u, !( zero == cv1 ) );
	UNIT_TEST( u, one != cv0 );
	UNIT_TEST( u, one == cv1 );
	UNIT_TEST( u, !( one == cv0 ) );
	UNIT_TEST( u, !( one != cv1 ) );

	UNIT_TEST( u, zero.equals( zeroChar  ) );
	UNIT_TEST( u, zero.equals( zeroShort ) );
	UNIT_TEST( u, zero.equals( zeroInt   ) );
	UNIT_TEST( u, zero.equals( zeroLong  ) );
	UNIT_TEST( u, zero.equals( zeroFloat ) );
	UNIT_TEST( u, one.equals( oneChar  ) );
	UNIT_TEST( u, one.equals( oneShort ) );
	UNIT_TEST( u, one.equals( oneInt   ) );
	UNIT_TEST( u, one.equals( oneLong  ) );
	UNIT_TEST( u, one.equals( oneFloat ) );
	UNIT_TEST( u, !zero.equals( oneChar  ) );
	UNIT_TEST( u, !zero.equals( oneShort ) );
	UNIT_TEST( u, !zero.equals( oneInt   ) );
	UNIT_TEST( u, !zero.equals( oneLong  ) );
	UNIT_TEST( u, !zero.equals( oneFloat ) );
	UNIT_TEST( u, !one.equals( zeroChar  ) );
	UNIT_TEST( u, !one.equals( zeroShort ) );
	UNIT_TEST( u, !one.equals( zeroInt   ) );
	UNIT_TEST( u, !one.equals( zeroLong  ) );
	UNIT_TEST( u, !one.equals( zeroFloat ) );

	UNIT_TEST( u, zero.equals( zeroChar,  0.5L ) );
	UNIT_TEST( u, zero.equals( zeroShort, 0.5L ) );
	UNIT_TEST( u, zero.equals( zeroInt,   0.5L ) );
	UNIT_TEST( u, zero.equals( zeroLong,  0.5L ) );
	UNIT_TEST( u, zero.equals( zeroFloat, 0.5L ) );
	UNIT_TEST( u,  one.equals( oneChar,  0.5L  ) );
	UNIT_TEST( u,  one.equals( oneShort, 0.5L  ) );
	UNIT_TEST( u,  one.equals( oneInt,   0.5L  ) );
	UNIT_TEST( u,  one.equals( oneLong,  0.5L  ) );
	UNIT_TEST( u,  one.equals( oneFloat, 0.5L  ) );
	UNIT_TEST( u, !zero.equals( oneChar,  0.5L ) );
	UNIT_TEST( u, !zero.equals( oneShort, 0.5L ) );
	UNIT_TEST( u, !zero.equals( oneInt,   0.5L ) );
	UNIT_TEST( u, !zero.equals( oneLong,  0.5L ) );
	UNIT_TEST( u, !zero.equals( oneFloat, 0.5L ) );
	UNIT_TEST( u, !one.equals( zeroChar,  0.5L ) );
	UNIT_TEST( u, !one.equals( zeroShort, 0.5L ) );
	UNIT_TEST( u, !one.equals( zeroInt,   0.5L ) );
	UNIT_TEST( u, !one.equals( zeroLong,  0.5L ) );
	UNIT_TEST( u, !one.equals( zeroFloat, 0.5L ) );

	UNIT_TEST( u, !zero.equals(  one, 0.5L ) );
	UNIT_TEST( u,  zero.equals( zero, 0.5L ) );
}

// ----------------------------------------------------------------------------

void TestDefinedLessThan()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Less_Than" );

	const char  oneChar   = 1;
	const short oneShort  = 1;
	const int   oneInt    = 1;
	const long  oneLong   = 1;
	const float oneFloat  = 1.0F;
	const char  minusOneChar  = -1;
	const short minusOneShort = -1;
	const int   minusOneInt   = -1;
	const long  minusOneLong  = -1;
	const float minusOneFloat = -1.0F; 
	const defined_value zero;
	const defined_value one( 1.0L );

	// every test in this section is for operator< or less_than.
	UNIT_TEST( u, !( zero < minusOneFloat ) );
	UNIT_TEST( u, !( zero < minusOneChar  ) );
	UNIT_TEST( u, !( zero < minusOneShort ) );
	UNIT_TEST( u, !( zero < minusOneInt   ) );
	UNIT_TEST( u, !( zero < minusOneLong  ) );
	UNIT_TEST( u,  zero < oneFloat );
	UNIT_TEST( u,  zero < oneChar );
	UNIT_TEST( u,  zero < oneShort );
	UNIT_TEST( u,  zero < oneInt );
	UNIT_TEST( u,  zero < oneLong );
	UNIT_TEST( u,  zero.less_than( oneChar,  0.001L ) );
	UNIT_TEST( u,  zero.less_than( oneShort, 0.001L ) );
	UNIT_TEST( u,  zero.less_than( oneInt,   0.001L ) );
	UNIT_TEST( u,  zero.less_than( oneLong,  0.001L ) );
	UNIT_TEST( u, !zero.less_than( oneChar,  1.0L ) ); // Tolerance is too big, so number cannot be less than value.
	UNIT_TEST( u, !zero.less_than( oneShort, 1.0L ) ); // Tolerance is too big, so number cannot be less than value.
	UNIT_TEST( u, !zero.less_than( oneInt,   1.0L ) ); // Tolerance is too big, so number cannot be less than value.
	UNIT_TEST( u, !zero.less_than( oneLong,  1.0L ) ); // Tolerance is too big, so number cannot be less than value.
	UNIT_TEST( u,  zero.less_than( oneFloat ) );
	UNIT_TEST( u, !zero.less_than( 0.0001L, 0.001L   ) ); // Tolerance is too big, so number cannot be less than value.
	UNIT_TEST( u, !zero.less_than( 0.0001L, 0.0001L  ) ); // Tolerance is too big, so number cannot be less than value.
	UNIT_TEST( u,  zero.less_than( 0.0001L, 0.00009L ) );

	// every test in this section is for operator<= or less_than_or_equals.
	UNIT_TEST( u, !( zero <= minusOneFloat ) );
	UNIT_TEST( u, !( zero <= minusOneChar  ) );
	UNIT_TEST( u, !( zero <= minusOneShort ) );
	UNIT_TEST( u, !( zero <= minusOneInt   ) );
	UNIT_TEST( u, !( zero <= minusOneLong  ) );
	UNIT_TEST( u,  zero <= oneFloat );
	UNIT_TEST( u,  zero <= oneChar );
	UNIT_TEST( u,  zero <= oneShort );
	UNIT_TEST( u,  zero <= oneInt );
	UNIT_TEST( u,  zero <= oneLong );
	UNIT_TEST( u,  zero.less_than_or_equals( oneChar  ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneShort ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneInt   ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneLong  ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneFloat ) );
	UNIT_TEST( u,  zero.less_than_or_equals( 0.0001L ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneFloat ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneChar ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneShort ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneInt ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneLong ) );
	UNIT_TEST( u, !zero.less_than_or_equals( -0.0001L ) );

	UNIT_TEST( u,  zero.less_than_or_equals( oneChar,  0.001L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneShort, 0.001L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneInt,   0.001L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneLong,  0.001L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneChar,  1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneShort, 1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneInt,   1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneLong,  1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneFloat, 1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( 0.0001L, 0.001L   ) );
	UNIT_TEST( u,  zero.less_than_or_equals( 0.0001L, 0.0001L  ) );
	UNIT_TEST( u,  zero.less_than_or_equals( 0.0001L, 0.00009L ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneFloat ) );
	UNIT_TEST( u,  zero.less_than_or_equals( minusOneChar,  1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( minusOneShort, 1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( minusOneInt,   1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( minusOneLong,  1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( -0.0001L, 0.001L   ) );
	UNIT_TEST( u,  zero.less_than_or_equals( -0.0001L, 0.0001L  ) );
	UNIT_TEST( u, !zero.less_than_or_equals( -0.0001L, 0.00009L ) );

	UNIT_TEST( u,  one < 1.1L );
	UNIT_TEST( u,  one.less_than( 1.1L ) );
	UNIT_TEST( u, !one.less_than( 1.0001L, 0.001L   ) );
	UNIT_TEST( u, !one.less_than( 1.0001L, 0.0001L  ) );
	UNIT_TEST( u,  one.less_than( 1.0001L, 0.00009L ) );
	UNIT_TEST( u,  one <= 1.1L );
	UNIT_TEST( u,  one.less_than_or_equals( 1.1L ) );
	UNIT_TEST( u,  one.less_than_or_equals( 1.0001L, 0.001L   ) );
	UNIT_TEST( u,  one.less_than_or_equals( 1.0001L, 0.0001L  ) );
	UNIT_TEST( u,  one.less_than_or_equals( 1.0001L, 0.00009L ) );
	UNIT_TEST( u, zero <= one  );
	UNIT_TEST( u, zero <  one  );
	UNIT_TEST( u,  !one.less_than( zero ) );
	UNIT_TEST( u,  !one.less_than( one  ) );
	UNIT_TEST( u,  !one.less_than_or_equals( zero ) );
	UNIT_TEST( u,   one.less_than_or_equals( one  ) );
	UNIT_TEST( u, !zero.less_than( zero ) );
	UNIT_TEST( u,  zero.less_than( one  ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zero ) );
	UNIT_TEST( u,  zero.less_than_or_equals( one  ) );
	UNIT_TEST( u,  !one.less_than( zero, 0.1L ) );
	UNIT_TEST( u,  !one.less_than( one,  0.1L ) );
	UNIT_TEST( u,  !one.less_than_or_equals( zero, 0.1L ) );
	UNIT_TEST( u,   one.less_than_or_equals( one,  0.1L ) );
	UNIT_TEST( u, !zero.less_than( zero, 0.1L ) );
	UNIT_TEST( u,  zero.less_than( one,  0.1L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zero, 0.1L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( one,  0.1L ) );
	UNIT_TEST( u,  !one.less_than( zero, 1.0L ) );
	UNIT_TEST( u,  !one.less_than( one,  1.0L ) );
	UNIT_TEST( u,   one.less_than_or_equals( zero, 1.0L ) );
	UNIT_TEST( u,   one.less_than_or_equals( one,  1.0L ) );
	UNIT_TEST( u, !zero.less_than( zero, 1.0L ) );
	UNIT_TEST( u, !zero.less_than( one,  1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zero, 1.0L ) );
	UNIT_TEST( u,  zero.less_than_or_equals( one,  1.0L ) );

	calculated_value cv0;
	calculated_value cv1( 1.0L );
	UNIT_TEST( u, zero < cv1 );
	UNIT_TEST( u, zero <= cv0 );
	UNIT_TEST( u, zero <= cv1 );
	UNIT_TEST( u, !( zero < cv0 ) );
	UNIT_TEST( u, !( one < cv0 ) );
	UNIT_TEST( u, !( one <= cv0 ) );
	UNIT_TEST( u, zero.less_than( cv1 ) );
	UNIT_TEST( u, !zero.less_than( cv0 ) );
	UNIT_TEST( u, !one.less_than( cv0 ) );
	UNIT_TEST( u, zero.less_than_or_equals( cv1 ) );
	UNIT_TEST( u, zero.less_than_or_equals( cv0 ) );
	UNIT_TEST( u, !one.less_than_or_equals( cv0 ) );
}

// ----------------------------------------------------------------------------

void TestDefinedGreaterThan()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Greater_Than" );

	const char  zeroChar  = 0;
	const short zeroShort = 0;
	const int   zeroInt   = 0;
	const long  zeroLong  = 0;
	const float zeroFloat = 0.0F;
	const char  oneChar   = 1;
	const short oneShort  = 1;
	const int   oneInt    = 1;
	const long  oneLong   = 1;
	const float oneFloat  = 1.0F;
	const char  minusOneChar  = -1;
	const short minusOneShort = -1;
	const int   minusOneInt   = -1;
	const long  minusOneLong  = -1;
	const float minusOneFloat = -1.0F; 
	const defined_value zero;
	const defined_value one( 1.0L );

	// every test in this section is for operator> or greater_than.
	UNIT_TEST( u,  zero > minusOneFloat );
	UNIT_TEST( u,  zero > minusOneChar );
	UNIT_TEST( u,  zero > minusOneShort );
	UNIT_TEST( u,  zero > minusOneInt );
	UNIT_TEST( u,  zero > minusOneLong );
	UNIT_TEST( u, !( zero > oneFloat  ) );
	UNIT_TEST( u, !( zero > oneChar  ) );
	UNIT_TEST( u, !( zero > oneShort ) );
	UNIT_TEST( u, !( zero > oneInt   ) );
	UNIT_TEST( u, !( zero > oneLong  ) );
	UNIT_TEST( u,  zero.greater_than( minusOneChar,  0.001L ) );
	UNIT_TEST( u,  zero.greater_than( minusOneShort, 0.001L ) );
	UNIT_TEST( u,  zero.greater_than( minusOneInt,   0.001L ) );
	UNIT_TEST( u,  zero.greater_than( minusOneLong,  0.001L ) );
	UNIT_TEST( u, !zero.greater_than( minusOneChar,  1.0L ) );
	UNIT_TEST( u, !zero.greater_than( minusOneShort, 1.0L ) );
	UNIT_TEST( u, !zero.greater_than( minusOneInt,   1.0L ) );
	UNIT_TEST( u, !zero.greater_than( minusOneLong,  1.0L ) );
	UNIT_TEST( u,  zero.greater_than( minusOneFloat ) );
	UNIT_TEST( u, !zero.greater_than( -0.0001L, 0.001L   ) ); // Tolerance is too big, so number cannot be greater than value.
	UNIT_TEST( u, !zero.greater_than( -0.0001L, 0.0001L  ) ); // Tolerance is too big, so number cannot be greater than value.
	UNIT_TEST( u,  zero.greater_than( -0.0001L, 0.00009L ) );

	// every test in this section is for operator>= or greater_than_or_equals.
	UNIT_TEST( u,  zero >= zeroFloat );
	UNIT_TEST( u,  zero >= zeroChar );
	UNIT_TEST( u,  zero >= zeroShort );
	UNIT_TEST( u,  zero >= zeroInt );
	UNIT_TEST( u,  zero >= zeroLong );
	UNIT_TEST( u,  zero >= minusOneFloat );
	UNIT_TEST( u,  zero >= minusOneChar );
	UNIT_TEST( u,  zero >= minusOneShort );
	UNIT_TEST( u,  zero >= minusOneInt );
	UNIT_TEST( u,  zero >= minusOneLong );
	UNIT_TEST( u, !( zero >= oneFloat ) );
	UNIT_TEST( u, !( zero >= oneChar  ) );
	UNIT_TEST( u, !( zero >= oneShort ) );
	UNIT_TEST( u, !( zero >= oneInt   ) );
	UNIT_TEST( u, !( zero >= oneLong  ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneChar,  0.001L ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneShort, 0.001L ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneInt,   0.001L ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneLong,  0.001L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( oneChar,  1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( oneShort, 1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( oneInt,   1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( oneLong,  1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneChar,  0.001L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneShort, 0.001L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneInt,   0.001L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneLong,  0.001L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneChar,  1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneShort, 1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneInt,   1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneLong,  1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneFloat ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.0001L, 0.001L   ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.0001L, 0.0001L  ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.0001L, 0.00009L ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneFloat ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( 0.0001L, 0.001L   ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( 0.0001L, 0.0001L  ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( 0.0001L, 0.00009L ) );

	UNIT_TEST( u,  one >  zero );
	UNIT_TEST( u,  one >= zero );
	UNIT_TEST( u,  one > 0.9L );
	UNIT_TEST( u, !one.greater_than( 1.0L ) );
	UNIT_TEST( u, !one.greater_than( 1.0001L, 0.001L   ) );
	UNIT_TEST( u, !one.greater_than( 1.0001L, 0.0001L  ) );
	UNIT_TEST( u, !one.greater_than( 1.0001L, 0.00009L ) );
	UNIT_TEST( u,  one >= 0.9L );
	UNIT_TEST( u,  one.greater_than_or_equals( 0.9L ) );
	UNIT_TEST( u,  one.greater_than_or_equals( 0.9991L, 0.009L   ) );
	UNIT_TEST( u,  one.greater_than_or_equals( 0.9991L, 0.0009L  ) );
	UNIT_TEST( u,  one.greater_than_or_equals( 0.9991L, 0.00009L ) );
	UNIT_TEST( u,   one.greater_than_or_equals( zero ) );
	UNIT_TEST( u,   one.greater_than_or_equals( one  ) );
	UNIT_TEST( u,   one.greater_than( zero ) );
	UNIT_TEST( u,  !one.greater_than( one  ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zero ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( one  ) );
	UNIT_TEST( u, !zero.greater_than( zero ) );
	UNIT_TEST( u, !zero.greater_than( one  ) );
	UNIT_TEST( u,   one.greater_than_or_equals( zero, 0.1L ) );
	UNIT_TEST( u,   one.greater_than_or_equals( one,  0.1L ) );
	UNIT_TEST( u,   one.greater_than( zero, 0.1L ) );
	UNIT_TEST( u,  !one.greater_than( one,  0.1L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zero, 0.1L ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( one,  0.1L ) );
	UNIT_TEST( u, !zero.greater_than( zero, 0.1L ) );
	UNIT_TEST( u, !zero.greater_than( one,  0.1L ) );
	UNIT_TEST( u,   one.greater_than_or_equals( zero, 1.0L ) );
	UNIT_TEST( u,   one.greater_than_or_equals( one,  1.0L ) );
	UNIT_TEST( u,  !one.greater_than( zero, 1.0L ) );
	UNIT_TEST( u,  !one.greater_than( one,  1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zero, 1.0L ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( one,  1.0L ) );
	UNIT_TEST( u, !zero.greater_than( zero, 1.0L ) );
	UNIT_TEST( u, !zero.greater_than( one,  1.0L ) );

	calculated_value cv0;
	calculated_value cv1( 1.0L );
	UNIT_TEST( u, one > cv0 );
	UNIT_TEST( u, one >= cv0 );
	UNIT_TEST( u, one >= cv1 );
	UNIT_TEST( u, !( zero > cv0 ) );
	UNIT_TEST( u, !( zero > cv1 ) );
	UNIT_TEST( u, !( zero >= cv1 ) );
	UNIT_TEST( u, one.greater_than( cv0 ) );
	UNIT_TEST( u, one.greater_than_or_equals( cv0 ) );
	UNIT_TEST( u, one.greater_than_or_equals( cv1 ) );
	UNIT_TEST( u, !( zero.greater_than( cv0 ) ) );
	UNIT_TEST( u, !( zero.greater_than( cv1 ) ) );
	UNIT_TEST( u, !( zero.greater_than_or_equals( cv1 ) ) );
}

// ----------------------------------------------------------------------------

void TestDefinedAddition()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Additions" );

	const defined_value zero;
	const defined_value one( 1UL );
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  one == 1.0L );
	defined_value sum = zero + one;
	UNIT_TEST( u, sum == 1.0L );
	UNIT_TEST( u, sum == one );
	UNIT_TEST( u, sum.to_string() == "1" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 0 );
	sum = one + one;
	UNIT_TEST( u, sum == 2.0L );
	UNIT_TEST( u, sum.to_string() == "2" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 0 );

	const long ninety = 90;
	const long eleven = 11;
	const defined_value ninetyValue( ninety );
	UNIT_TEST( u, ninetyValue == 90.0L );
	UNIT_TEST( u, ninetyValue.to_string() == "90" );
	UNIT_TEST( u, ninetyValue.get_most_sigdig_exponent() == 1 );
	const defined_value elevenValue( eleven );
	UNIT_TEST( u, elevenValue == 11.0L );
	UNIT_TEST( u, elevenValue.to_string() == "11" );
	UNIT_TEST( u, elevenValue.get_most_sigdig_exponent() == 1 );

	sum = ninetyValue + elevenValue;
	UNIT_TEST( u, sum == 101.0L );
	UNIT_TEST( u, sum.to_string() == "101" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 2 );
	sum = ninety + eleven; // Can also do arithmetic with direct conversion from long to defined_value.
	UNIT_TEST( u, sum == 101.0L );
	UNIT_TEST( u, sum.to_string() == "101" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 2 );

	const defined_value seven( 7.0L );
	sum = seven + one + one + one;
	UNIT_TEST( u, sum == 10.0L );
	UNIT_TEST( u, sum.to_string() == "10" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 1 );
}

// ----------------------------------------------------------------------------

void TestDefinedSubtraction()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Subtraction" );

	const defined_value zero;
	const defined_value one( 1UL );
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  one == 1.0L );
	defined_value diff = zero - one;
	UNIT_TEST( u, diff == -1.0L );
	UNIT_TEST( u, diff.to_string() == "-1" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 0 );

	diff = one - zero;
	UNIT_TEST( u, diff == 1.0L );
	UNIT_TEST( u, diff.to_string() == "1" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 0 );

	diff = one - one;
	UNIT_TEST( u, diff == 0.0L );
	UNIT_TEST( u, diff.to_string() == "0" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 0 );

	const defined_value ninety( 90L );
	UNIT_TEST( u, ninety == 90.0L );
	UNIT_TEST( u, ninety.to_string() == "90" );
	UNIT_TEST( u, ninety.get_most_sigdig_exponent() == 1 );
	const defined_value eleven( 11L );
	UNIT_TEST( u, eleven == 11.0L );
	UNIT_TEST( u, eleven.to_string() == "11" );
	UNIT_TEST( u, eleven.get_most_sigdig_exponent() == 1 );

	diff = ninety - eleven;
	UNIT_TEST( u, diff == 79.0L );
	UNIT_TEST( u, diff.to_string() == "79" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 1 );

	diff = eleven - ninety;
	UNIT_TEST( u, diff == -79.0L );
	UNIT_TEST( u, diff.to_string() == "-79" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 1 );
}

// ----------------------------------------------------------------------------

void TestDefinedMultiplication()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Multiplication" );

	const defined_value zero;
	const defined_value one( 1UL );
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  one == 1.0L );

	defined_value product = zero * one;
	UNIT_TEST( u, product == 0.0L );
	UNIT_TEST( u, product.to_string() == "0" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 0 );

	product = one * one;
	UNIT_TEST( u, product == 1.0L );
	UNIT_TEST( u, product.to_string() == "1" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 0 );

	const defined_value ninety( 90L );
	UNIT_TEST( u, ninety == 90.0L );
	UNIT_TEST( u, ninety.to_string() == "90" );
	UNIT_TEST( u, ninety.get_most_sigdig_exponent() == 1 );
	const defined_value eleven( 11L );
	UNIT_TEST( u, eleven == 11.0L );
	UNIT_TEST( u, eleven.to_string() == "11" );
	UNIT_TEST( u, eleven.get_most_sigdig_exponent() == 1 );

	product = ninety * one;
	UNIT_TEST( u, product == ninety );
	UNIT_TEST( u, product == 90.0L );
	UNIT_TEST( u, product.to_string() == "90" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 1 );

	product = eleven * one;
	UNIT_TEST( u, product == eleven );
	UNIT_TEST( u, product == 11.0L );
	UNIT_TEST( u, product.to_string() == "11" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 1 );

	product = eleven * ninety;
	UNIT_TEST( u, product == 990.0L );
	UNIT_TEST( u, product.to_string() == "990" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 2 );
}

// ----------------------------------------------------------------------------

void TestDefinedDivision()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Division" );

	const defined_value zero;
	const defined_value one( 1UL );
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  one == 1.0L );

	defined_value quotient = zero / one;
	UNIT_TEST( u, quotient == 0.0L );

	const defined_value ninety( 90L );
	UNIT_TEST( u, ninety == 90.0L );
	UNIT_TEST( u, ninety.to_string() == "90" );
	UNIT_TEST( u, ninety.get_most_sigdig_exponent() == 1 );
	const defined_value eleven( 11L );
	UNIT_TEST( u, eleven == 11.0L );
	UNIT_TEST( u, eleven.to_string() == "11" );
	UNIT_TEST( u, eleven.get_most_sigdig_exponent() == 1 );

	quotient = ninety / one;
	UNIT_TEST( u, quotient == ninety );
	UNIT_TEST( u, quotient == 90.0L );
	UNIT_TEST( u, quotient.to_string() == "90" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 1 );

	quotient = eleven / one;
	UNIT_TEST( u, quotient == eleven );
	UNIT_TEST( u, quotient == 11.0L );
	UNIT_TEST( u, quotient.to_string() == "11" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 1 );

	double tolerance = 0.000001;

	quotient = eleven / ninety;
	UNIT_TEST( u, quotient.equals( 0.122222, tolerance ) );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == -1 );

	quotient = ninety / eleven;
	UNIT_TEST( u, quotient.equals( 8.181818, tolerance ) );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 0 );
}

// ----------------------------------------------------------------------------

void TestDefinedPowers()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Defined_Powers" );

	defined_value exponent( 0.0L );
	const defined_value zero;
	defined_value result = zero.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	exponent = 1.0L;
	result = zero.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 0.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	result = zero.square_root();
	UNIT_TEST( u, result.get_value() == 0.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	result = zero.cube_root();
	UNIT_TEST( u, result.get_value() == 0.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );

	exponent = -1.0L;
	const defined_value one( 1UL );
	result = one.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	exponent = 0.0L;
	result = one.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	exponent = 1.0L;
	result = one.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	result = one.square_root();
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	result = one.cube_root();
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );

	exponent = -1.0L;
	double tolerance = 0.000001;
	const defined_value nine( 9UL );
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.equals( 0.111111L, tolerance ) );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == -1 );
	exponent = 0.0L;
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	exponent = 1.0L;
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 9.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	exponent = 2.0L;
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 81.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 1 );
	result = nine.square_root();
	UNIT_TEST( u, result.get_value() == 3.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	tolerance = 0.00001;
	result = nine.cube_root();
	UNIT_TEST( u, result.equals( 2.08008, tolerance ) );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );

	exponent = -1.0L;
	tolerance = 0.00001;
	const defined_value eight( 8UL );
	result = eight.to_power_of( exponent );
	UNIT_TEST( u, result.equals( 0.125, tolerance ) );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == -1 );
	exponent = 0.0L;
	result = eight.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	exponent = 1.0L;
	result = eight.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 8.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	exponent = 2.0L;
	result = eight.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 64.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 1 );
	exponent = 3.0L;
	result = eight.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 512.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 2 );
	result = eight.square_root();
	UNIT_TEST( u, result.equals( 2.828427, tolerance ) );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	result = eight.cube_root();
	UNIT_TEST( u, result.get_value() == 2.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
}

// ----------------------------------------------------------------------------
