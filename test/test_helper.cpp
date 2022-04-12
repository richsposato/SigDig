// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#ifdef __CYGWIN__
	#undef _REENT_ONLY
#endif


#include <helper.hpp>
#include <utility.hpp>

#include <UnitTest.hpp>

#include <cfloat>
#include <cmath>

#include <iostream>
#include <iomanip>


using namespace ut;
using namespace sigdig;

// ----------------------------------------------------------------------------

void TestMagnitude()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Magnitude" );

	// These test the highest and lowest extremes of exponents allowed.
	UNIT_TEST( u, utility::calculate_exponent(    1E-4931L ) == -4931 );
	UNIT_TEST( u, utility::calculate_exponent(   -1E-4931L ) == -4931 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-4930L ) == -4930 );
	UNIT_TEST( u, utility::calculate_exponent(   -1E-4930L ) == -4930 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+4931L ) == 4931 );
	UNIT_TEST( u, utility::calculate_exponent(   -1E+4931L ) == 4931 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+4932L ) == 4932 );
	UNIT_TEST( u, utility::calculate_exponent(   -1E+4932L ) == 4932 );

	// These test if the exponent binary search algorithm behaves correctly at and near the shortcuts.
	UNIT_TEST( u, utility::calculate_exponent(    1E-7L ) == -7 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-8L ) == -8 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-9L ) == -9 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-15L ) == -15 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-16L ) == -16 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-17L ) == -17 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-31L ) == -31 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-32L ) == -32 );
	UNIT_TEST( u, utility::calculate_exponent(    1E-33L ) == -33 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+7L ) == 7 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+8L ) == 8 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+9L ) == 9 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+15L ) == 15 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+16L ) == 16 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+17L ) == 17 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+31L ) == 31 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+32L ) == 32 );
	UNIT_TEST( u, utility::calculate_exponent(    1E+33L ) == 33 );

	UNIT_TEST( u, utility::calculate_exponent(    0.000000000000007L ) == -15 );
	UNIT_TEST( u, utility::calculate_exponent(    0.00000000000007L ) == -14 );
	UNIT_TEST( u, utility::calculate_exponent(    0.0000000000007L ) == -13 );
	UNIT_TEST( u, utility::calculate_exponent(    0.000000000007L ) == -12 );
	UNIT_TEST( u, utility::calculate_exponent(    0.00000000007L ) == -11 );
	UNIT_TEST( u, utility::calculate_exponent(    0.0000000007L ) == -10 );
	UNIT_TEST( u, utility::calculate_exponent(    0.000000007L ) == -9 );
	UNIT_TEST( u, utility::calculate_exponent(    0.00000007L ) == -8 );
	UNIT_TEST( u, utility::calculate_exponent(    0.0000007L ) == -7 );
	UNIT_TEST( u, utility::calculate_exponent(    0.000007L ) == -6 );
	UNIT_TEST( u, utility::calculate_exponent(    0.00001L   ) == -5 );
	UNIT_TEST( u, utility::calculate_exponent(    0.0000909L ) == -5 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.00001L   ) == -5 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.0000900L ) == -5 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.0001L   ) == -4 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.000562L ) == -4 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.000999L ) == -4 );
	UNIT_TEST( u, utility::calculate_exponent(    0.001L   ) == -3 );
	UNIT_TEST( u, utility::calculate_exponent(    0.00999L ) == -3 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.001L   ) == -3 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.00999L ) == -3 );
	UNIT_TEST( u, utility::calculate_exponent(    0.01L   ) == -2 );
	UNIT_TEST( u, utility::calculate_exponent(    0.0999L ) == -2 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.0324L ) == -2 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.01L   ) == -2 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.0999L ) == -2 );
	UNIT_TEST( u, utility::calculate_exponent(    0.1L   ) == -1 );
	UNIT_TEST( u, utility::calculate_exponent(    0.999L ) == -1 );
	UNIT_TEST( u, utility::calculate_exponent(    0.832L ) == -1 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.1L   ) == -1 );
	UNIT_TEST( u, utility::calculate_exponent(   -0.999L ) == -1 );
	UNIT_TEST( u, utility::calculate_exponent(    0.0000L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(    0.0L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(    1.0L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(   -1.0L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(    9.9L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(   -9.9L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(   10.0L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(  -10.0L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(   99.9L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(  -99.9L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(  100.0L ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent( -100.0L ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent(  999.9L ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent( -999.9L ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent(  1122330.0L ) == 6 );
	UNIT_TEST( u, utility::calculate_exponent( -1234500.0L ) == 6 );
	UNIT_TEST( u, utility::calculate_exponent( 12345000.0L ) == 7 );
	UNIT_TEST( u, utility::calculate_exponent(  9876543.901234L ) == 6 );
	UNIT_TEST( u, utility::calculate_exponent( -9002000.900002L ) == 6 );
	UNIT_TEST( u, utility::calculate_exponent( 151074654483364.945449829101562L ) == 14 );

	UNIT_TEST( u, utility::calculate_exponent(    0L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(    1L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(   -1L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(    9L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(   -9L ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(   10L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(  -10L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(   99L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(  -99L ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(  100L ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent( -100L ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent(  999L ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent( -999L ) == 2 );

	UNIT_TEST( u, utility::calculate_exponent(    0UL ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(    1UL ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(    9UL ) == 0 );
	UNIT_TEST( u, utility::calculate_exponent(   10UL ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(   99UL ) == 1 );
	UNIT_TEST( u, utility::calculate_exponent(  100UL ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent(  999UL ) == 2 );
	UNIT_TEST( u, utility::calculate_exponent(   98765432UL ) == 7 );
	UNIT_TEST( u, utility::calculate_exponent(  999999999UL ) == 8 );
	UNIT_TEST( u, utility::calculate_exponent( 1000000000UL ) == 9 );
	UNIT_TEST( u, utility::calculate_exponent( 2147483648UL ) == 9 );
	UNIT_TEST( u, utility::calculate_exponent(   16777216UL ) == 7 );
	UNIT_TEST( u, utility::calculate_exponent(     654321UL ) == 5 );
	UNIT_TEST( u, utility::calculate_exponent( 4294967295UL ) == 9 ); // max integer value for unsigned long
}

// ----------------------------------------------------------------------------

void TestRounding()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Rounding" );

	rounding_style style = rounding_style::truncate;
	UNIT_TEST( u, helper::calculate_rounding(    0.0L,       0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding(    1.0L,       0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding(   -1.05747L,  -3, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding(    2.04L,      1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 1230.0L,       3, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding(    0.04367L,  -1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -560.057246L,  2, style ) == 0.0L );

	style = rounding_style::floor;
	UNIT_TEST( u, helper::calculate_rounding( 0.0L,  0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L,  0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L,  1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L,  1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L, -1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L, -1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L,  2, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L,  2, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L, -2, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0L, -2, style ) == 0.0L );

	style = rounding_style::round_half;
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding( -1.0L, -4, style ),   -0.0005L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding(  1.0L, -4, style ),    0.0005L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding( -1.0L, -3, style ),   -0.005L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding(  1.0L, -3, style ),    0.005L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding( -1.0L, -2, style ),   -0.05L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding(  1.0L, -2, style ),    0.05L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding( -1.0L, -1, style ),   -0.5L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding(  1.0L, -1, style ),    0.5L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding( -1.0L,  0, style ),   -5.0L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding(  1.0L,  0, style ),    5.0L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding( -1.0L,  1, style ),  -50.0L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding(  1.0L,  1, style ),   50.0L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding( -1.0L,  2, style ), -500.0L ) );
	UNIT_TEST( u, utility::are_nearly_equal( helper::calculate_rounding(  1.0L,  2, style ),  500.0L ) );

	style = rounding_style::ceiling;
	UNIT_TEST( u, helper::calculate_rounding( -1.0L, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1.0L, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1.0L, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1.0L, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1.0L,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1.0L,  0, style ) ==    10.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1.0L,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1.0L,  1, style ) ==   100.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1.0L,  2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1.0L,  2, style ) ==  1000.0L );

	style = rounding_style::floor;
	UNIT_TEST( u, helper::calculate_rounding( -123.45, -2, style ) ==    -0.1L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45, -1, style ) ==    -1.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  0, style ) ==   -10.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  1, style ) ==  -100.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  2, style ) == -1000.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  2, style ) ==     0.0L );

	style = rounding_style::round_half;
	UNIT_TEST( u, helper::calculate_rounding( -123.45, -2, style ) ==   -0.05L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45, -2, style ) ==    0.05L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45, -1, style ) ==   -0.5L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45, -1, style ) ==    0.5L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  0, style ) ==   -5.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  0, style ) ==    5.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  1, style ) ==  -50.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  1, style ) ==   50.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  2, style ) == -500.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  2, style ) ==  500.0L );

	style = rounding_style::ceiling;
	UNIT_TEST( u, helper::calculate_rounding( -123.45, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45, -2, style ) ==     0.1L );  // 123.5
	UNIT_TEST( u, helper::calculate_rounding( -123.45, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45, -1, style ) ==     1.0L );  // 124
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  0, style ) ==    10.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  1, style ) ==   100.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123.45,  2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123.45,  2, style ) ==  1000.0L );

	style = rounding_style::floor;
	UNIT_TEST( u, helper::calculate_rounding( -123, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  0, style ) ==   -10.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  1, style ) ==  -100.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  2, style ) == -1000.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  2, style ) ==     0.0L );

	style = rounding_style::round_half;
	UNIT_TEST( u, helper::calculate_rounding( -123, -2, style ) ==   -0.05L );
	UNIT_TEST( u, helper::calculate_rounding(  123, -2, style ) ==    0.05L );
	UNIT_TEST( u, helper::calculate_rounding( -123, -1, style ) ==   -0.5L );
	UNIT_TEST( u, helper::calculate_rounding(  123, -1, style ) ==    0.5L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  0, style ) ==   -5.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  0, style ) ==    5.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  1, style ) ==  -50.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  1, style ) ==   50.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  2, style ) == -500.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  2, style ) ==  500.0L );

	style = rounding_style::ceiling;
	UNIT_TEST( u, helper::calculate_rounding( -123, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  0, style ) ==    10.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  1, style ) ==   100.0L );
	UNIT_TEST( u, helper::calculate_rounding( -123,  2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  123,  2, style ) ==  1000.0L );

	style = rounding_style::floor;
	UNIT_TEST( u, helper::calculate_rounding( -1200, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  2, style ) == -1000.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  2, style ) ==     0.0L );

	style = rounding_style::round_half;
	UNIT_TEST( u, helper::calculate_rounding( -1200, -2, style ) ==   -0.05L );
	UNIT_TEST( u, helper::calculate_rounding(  1200, -2, style ) ==    0.05L );
	UNIT_TEST( u, helper::calculate_rounding( -1200, -1, style ) ==   -0.5L );
	UNIT_TEST( u, helper::calculate_rounding(  1200, -1, style ) ==    0.5L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  0, style ) ==   -5.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  0, style ) ==    5.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  1, style ) ==  -50.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  1, style ) ==   50.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  2, style ) == -500.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  2, style ) ==  500.0L );

	style = rounding_style::ceiling;
	UNIT_TEST( u, helper::calculate_rounding( -1200, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -1200,  2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  1200,  2, style ) ==  1000.0L );

	style = rounding_style::floor;
	UNIT_TEST( u, helper::calculate_rounding( -0.123, -2, style ) ==    -0.1L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123, -1, style ) ==    -1.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  0, style ) ==   -10.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  1, style ) ==  -100.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  2, style ) == -1000.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  2, style ) ==     0.0L );

	style = rounding_style::round_half;
	UNIT_TEST( u, helper::calculate_rounding( -0.123, -2, style ) ==   -0.05L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123, -2, style ) ==    0.05L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123, -1, style ) ==   -0.5L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123, -1, style ) ==    0.5L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  0, style ) ==   -5.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  0, style ) ==    5.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  1, style ) ==  -50.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  1, style ) ==   50.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  2, style ) == -500.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  2, style ) ==  500.0L );

	style = rounding_style::ceiling;
	UNIT_TEST( u, helper::calculate_rounding( -0.123, -2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123, -2, style ) ==     0.1L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123, -1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123, -1, style ) ==     1.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  0, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  0, style ) ==    10.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  1, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  1, style ) ==   100.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.123,  2, style ) ==     0.0L );
	UNIT_TEST( u, helper::calculate_rounding(  0.123,  2, style ) ==  1000.0L );

	style = rounding_style::floor;
	UNIT_TEST( u, helper::calculate_rounding( 12300, 0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 2, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 3, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 4, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 5, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 2, style ) == -1000.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 3, style ) == -10000.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 4, style ) == -100000.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 5, style ) == -1000000.0L );

	style = rounding_style::ceiling;
	UNIT_TEST( u, helper::calculate_rounding( 12300, 0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 2, style ) == 1000.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 3, style ) == 10000.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 4, style ) == 100000.0L );
	UNIT_TEST( u, helper::calculate_rounding( 12300, 5, style ) == 1000000.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 2, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 3, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 4, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -12300, 5, style ) == 0.0L );

	style = rounding_style::floor;
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -6, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -5, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -4, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -3, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -2, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, 0, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -6, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -5, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -4, style ) == -0.001L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -3, style ) == -0.01L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -2, style ) == -0.1L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -1, style ) == -1.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, 0, style ) == -10.0L );

	style = rounding_style::ceiling;
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -6, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -5, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -4, style ) == 0.001L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -3, style ) == 0.01L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -2, style ) == 0.1L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, -1, style ) == 1.0L );
	UNIT_TEST( u, helper::calculate_rounding( 0.0123, 0, style ) == 10.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -5, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -4, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -3, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -2, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, -1, style ) == 0.0L );
	UNIT_TEST( u, helper::calculate_rounding( -0.0123, 0, style ) == 0.0L );
}

// ----------------------------------------------------------------------------

void TestStringDigitCounting()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "String Digit Counting" );

	const char * source = "0";
	long double value = 1.0L;
	unsigned int digits = 10;
	int exponent = 0;
	utility::count_digits_in_string( source, value, digits, exponent );
	UNIT_TEST( u, value == 0.0L );
	UNIT_TEST( u, digits == 1 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "0.0000", value, digits, exponent );
	UNIT_TEST( u, value == 0.0L );
	UNIT_TEST( u, digits == 5 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "0.000000", value, digits, exponent );
	UNIT_TEST( u, value == 0.0L );
	UNIT_TEST( u, digits == 7 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "0000.0000", value, digits, exponent );
	UNIT_TEST( u, value == 0.0L );
	UNIT_TEST( u, digits == 5 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "-0.000000000", value, digits, exponent );
	UNIT_TEST( u, value == 0.0L );
	UNIT_TEST( u, digits == 10 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "1.1", value, digits, exponent );
	UNIT_TEST( u, value == 1.1L );
	UNIT_TEST( u, digits == 2 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "2.1", value, digits, exponent );
	UNIT_TEST( u, value == 2.1L );
	UNIT_TEST( u, digits == 2 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "110", value, digits, exponent );
	UNIT_TEST( u, value == 110.0L );
	UNIT_TEST( u, digits == 2 );
	UNIT_TEST( u, exponent == 2 );

	utility::count_digits_in_string( "110.", value, digits, exponent );
	UNIT_TEST( u, value == 110.0L );
	UNIT_TEST( u, digits == 3 );
	UNIT_TEST( u, exponent == 2 );

	utility::count_digits_in_string( "110.0", value, digits, exponent );
	UNIT_TEST( u, value == 110.0L );
	UNIT_TEST( u, digits == 4 );
	UNIT_TEST( u, exponent == 2 );

	utility::count_digits_in_string( "8000", value, digits, exponent );
	UNIT_TEST( u, value == 8000.0L );
	UNIT_TEST( u, digits == 1 );
	UNIT_TEST( u, exponent == 3 );

	utility::count_digits_in_string( "8000.", value, digits, exponent );
	UNIT_TEST( u, value == 8000.0L );
	UNIT_TEST( u, digits == 4 );
	UNIT_TEST( u, exponent == 3 );

	utility::count_digits_in_string( "8001", value, digits, exponent );
	UNIT_TEST( u, value == 8001.0L );
	UNIT_TEST( u, digits == 4 );
	UNIT_TEST( u, exponent == 3 );

	utility::count_digits_in_string( "001.1", value, digits, exponent );
	UNIT_TEST( u, value == 1.1L );
	UNIT_TEST( u, digits == 2 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "0.0001234", value, digits, exponent );
	UNIT_TEST( u, value == 0.0001234L );
	UNIT_TEST( u, digits == 4 );
	UNIT_TEST( u, exponent == -4 );

	utility::count_digits_in_string( "0.01234", value, digits, exponent );
	UNIT_TEST( u, value == 0.01234L );
	UNIT_TEST( u, digits == 4 );
	UNIT_TEST( u, exponent == -2 );

	utility::count_digits_in_string( "0.00234", value, digits, exponent );
	UNIT_TEST( u, value == 0.00234L );
	UNIT_TEST( u, digits == 3 );
	UNIT_TEST( u, exponent == -3 );

	utility::count_digits_in_string( "0.0001234000", value, digits, exponent );
	UNIT_TEST( u, value == 0.0001234L );
	UNIT_TEST( u, digits == 7 );
	UNIT_TEST( u, exponent == -4 );

	utility::count_digits_in_string( "0.0123400", value, digits, exponent );
	UNIT_TEST( u, value == 0.01234L );
	UNIT_TEST( u, digits == 6 );
	UNIT_TEST( u, exponent == -2 );

	utility::count_digits_in_string( "0.0023004", value, digits, exponent );
	UNIT_TEST( u, value == 0.0023004L );
	UNIT_TEST( u, digits == 5 );
	UNIT_TEST( u, exponent == -3 );

	utility::count_digits_in_string( "0.002300400", value, digits, exponent );
	UNIT_TEST( u, value == 0.0023004L );
	UNIT_TEST( u, digits == 7 );
	UNIT_TEST( u, exponent == -3 );

	utility::count_digits_in_string( "1.100", value, digits, exponent );
	UNIT_TEST( u, value == 1.1L );
	UNIT_TEST( u, digits == 4 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "1.1000", value, digits, exponent );
	UNIT_TEST( u, value == 1.1L );
	UNIT_TEST( u, digits == 5 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "8000502", value, digits, exponent );
	UNIT_TEST( u, value == 8000502.0L );
	UNIT_TEST( u, digits == 7 );
	UNIT_TEST( u, exponent == 6 );

	utility::count_digits_in_string( "8000500", value, digits, exponent );
	UNIT_TEST( u, value == 8000500.0L );
	UNIT_TEST( u, digits == 5 );
	UNIT_TEST( u, exponent == 6 );

	utility::count_digits_in_string( "8000002", value, digits, exponent );
	UNIT_TEST( u, value == 8000002.0L );
	UNIT_TEST( u, digits == 7 );
	UNIT_TEST( u, exponent == 6 );

	utility::count_digits_in_string( "8000000", value, digits, exponent );
	UNIT_TEST( u, value == 8000000.0L );
	UNIT_TEST( u, digits == 1 );
	UNIT_TEST( u, exponent == 6 );

	utility::count_digits_in_string( "8020000", value, digits, exponent );
	UNIT_TEST( u, value == 8020000.0L );
	UNIT_TEST( u, digits == 3 );
	UNIT_TEST( u, exponent == 6 );

	utility::count_digits_in_string( "8000000.", value, digits, exponent );
	UNIT_TEST( u, value == 8000000.0L );
	UNIT_TEST( u, digits == 7 );
	UNIT_TEST( u, exponent == 6 );

	utility::count_digits_in_string( "0000000", value, digits, exponent );
	UNIT_TEST( u, value == 0.0L );
	UNIT_TEST( u, digits == 1 );
	UNIT_TEST( u, exponent == 0 );

	utility::count_digits_in_string( "12345000", value, digits, exponent );
	UNIT_TEST( u, value == 12345000.0L );
	UNIT_TEST( u, digits == 5 );
	UNIT_TEST( u, exponent == 7 );

	utility::count_digits_in_string( "1.54321E+10", value, digits, exponent );
	UNIT_TEST( u, value == 15432100000.0L );
	UNIT_TEST( u, digits == 6 );
	UNIT_TEST( u, exponent == 10 );

	utility::count_digits_in_string( "1.5432100000E+10", value, digits, exponent );
	UNIT_TEST( u, value == 15432100000.0L );
	UNIT_TEST( u, digits == 11 );
	UNIT_TEST( u, exponent == 10 );

	utility::count_digits_in_string( "-1.54321E-7", value, digits, exponent );
	UNIT_TEST( u, value == -0.000000154321L );
	UNIT_TEST( u, digits == 6 );
	UNIT_TEST( u, exponent == -7 );

	utility::count_digits_in_string( "-1.54321000E-7", value, digits, exponent );
	UNIT_TEST( u, value == -0.000000154321L );
	UNIT_TEST( u, digits == 9 );
	UNIT_TEST( u, exponent == -7 );
}

// ----------------------------------------------------------------------------

void TestComparisons()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Nearly Equal Comparisons" );

	UNIT_TEST( u, utility::are_nearly_equal( 0.0L, -0.0L ) );
	UNIT_TEST( u, utility::are_nearly_equal( -1.0L, -1.0L ) );
	UNIT_TEST( u, utility::are_nearly_equal( 1.0L, 1.0L ) );

	UNIT_TEST( u, helper::are_nearly_equal( 0.0L, -0.0L ) );
	UNIT_TEST( u, helper::are_nearly_equal( -1.0L, -1.0L ) );
	UNIT_TEST( u, helper::are_nearly_equal( 1.0L, 1.0L ) );

	UNIT_TEST( u, helper::are_nearly_equal(  0.0001L, 0.0001L ) );
	UNIT_TEST( u, !helper::are_nearly_equal( -1.0001L, 0.001L  ) );
	UNIT_TEST( u, !helper::are_nearly_equal( -1.0001L, 0.0001L ) );

	UNIT_TEST( u, !helper::are_nearly_equal( 1.0L, -1.0001L, 0.001L  ) );
}

// ----------------------------------------------------------------------------

void TestSigDigCounting()
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( "Counting Sig Digs" );

	UNIT_TEST( u, utility::count_significant_digits(       -0L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(        0L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       -1L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(        1L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      -10L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       10L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      -11L ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(       11L ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(     -100L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      100L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(     -110L ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(      110L ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(    -1000L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(     1000L ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(    -1230L ) == 3 );
	UNIT_TEST( u, utility::count_significant_digits(     1230L ) == 3 );
	UNIT_TEST( u, utility::count_significant_digits( -1230456L ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits(  1230456L ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits( 12345000L ) == 5 );

	UNIT_TEST( u, utility::count_significant_digits(        0UL ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(        1UL ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       10UL ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       11UL ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(      100UL ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      110UL ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(     1000UL ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(     1230UL ) == 3 );
	UNIT_TEST( u, utility::count_significant_digits(  1230456UL ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits( 12345000UL ) == 5 );

	UNIT_TEST( u, utility::count_significant_digits(      -0.0L      ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       0.0L      ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      -0.1L      ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       0.1L      ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      -1.0L      ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       1.0L      ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(       0.01L     ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      -0.012L    ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(      -0.0123L   ) == 3 );

	UNIT_TEST( u, utility::count_significant_digits(    -123.4L      ) == 4 );
	UNIT_TEST( u, utility::count_significant_digits(    -123.45L     ) == 5 );
	UNIT_TEST( u, utility::count_significant_digits(    -123.456L    ) == 6 );
	UNIT_TEST( u, utility::count_significant_digits(    -123.4567L   ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits(    -123.45678L  ) == 8 );
	UNIT_TEST( u, utility::count_significant_digits(    -123.456789L ) == 9 );
	UNIT_TEST( u, utility::count_significant_digits(       0.1234L      ) == 4 );
	UNIT_TEST( u, utility::count_significant_digits(       0.12345L     ) == 5 );
	UNIT_TEST( u, utility::count_significant_digits(       0.123456L    ) == 6 );
	UNIT_TEST( u, utility::count_significant_digits(       0.1234567L   ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits(       0.12345678L  ) == 8 );
	UNIT_TEST( u, utility::count_significant_digits(       0.123456789L ) == 9 );
	UNIT_TEST( u, utility::count_significant_digits(       0.0001234L      ) == 4 );
	UNIT_TEST( u, utility::count_significant_digits(       0.00012345L     ) == 5 );
	UNIT_TEST( u, utility::count_significant_digits(       0.000123456L    ) == 6 );
	UNIT_TEST( u, utility::count_significant_digits(       0.0001234567L   ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits(       0.00012345678L  ) == 8 );
	UNIT_TEST( u, utility::count_significant_digits(       0.000123456789L ) == 9 );
	UNIT_TEST( u, utility::count_significant_digits( 9876543.210987L ) == 13 );
	UNIT_TEST( u, utility::count_significant_digits(   -8154.02L     ) == 6 );
	UNIT_TEST( u, utility::count_significant_digits(       1.0L      ) == 1 );
	UNIT_TEST( u, utility::count_significant_digits(      21.0L      ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits(     321.0L      ) == 3 );
	UNIT_TEST( u, utility::count_significant_digits(    4321.0L      ) == 4 );
	UNIT_TEST( u, utility::count_significant_digits(   54321.0L      ) == 5 );
	UNIT_TEST( u, utility::count_significant_digits(  654321.0L      ) == 6 );
	UNIT_TEST( u, utility::count_significant_digits( 7654321.0L      ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits( 12345678.0L     ) == 8 );
	UNIT_TEST( u, utility::count_significant_digits( 12345670.0L     ) == 7 );
	UNIT_TEST( u, utility::count_significant_digits( 12345600.0L     ) == 6 );
	UNIT_TEST( u, utility::count_significant_digits( 12345000.0L     ) == 5 );
	UNIT_TEST( u, utility::count_significant_digits( 12340000.0L     ) == 4 );
	UNIT_TEST( u, utility::count_significant_digits( 12300000.0L     ) == 3 );
	UNIT_TEST( u, utility::count_significant_digits( 12000000.0L     ) == 2 );
	UNIT_TEST( u, utility::count_significant_digits( 10000000.0L     ) == 1 );
}

// ----------------------------------------------------------------------------

