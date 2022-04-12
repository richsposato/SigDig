// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#ifdef __CYGWIN__
	#undef _REENT_ONLY
#endif

#include "test_functions.hpp"

#include <utility.hpp>
#include <defined_value.hpp>
#include <measured_value.hpp>
#include <calculated_value.hpp>

#include <UnitTest.hpp>

#include <cfloat>
#include <cmath>

#include <iostream>
#include <iomanip>

using namespace ut;
using namespace sigdig;


// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueStringOutput( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	measured_value v;
	UNIT_TEST( u, v.to_string() == "0" );
	UNIT_TEST( u, v.to_string( 2 ) == "0.0" );
	UNIT_TEST( u, v.to_string( 3 ) == "0.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor    ) == "0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor    ) == "0.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor    ) == "0.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling  ) == "0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling  ) == "0.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling  ) == "0.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "0.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "0.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "0.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "0.00" );

	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor    ) == "0E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor    ) == "0.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor    ) == "0.00E+0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling  ) == "0E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling  ) == "0.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling  ) == "0.00E+0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "0E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "0.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "0.00E+0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "0E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero) == "0.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "0.00E+0" );

	v = 1.0L;
	UNIT_TEST( u, v.to_string() == "1" );
	UNIT_TEST( u, v.to_string( 2 ) == "1.0" );
	UNIT_TEST( u, v.to_string( 3 ) == "1.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor    ) == "1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor    ) == "1.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor    ) == "1.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling  ) == "1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling  ) == "1.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling  ) == "1.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "1.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "1.00" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "1.0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "1.00" );

	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor    ) == "1E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor    ) == "1.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor    ) == "1.00E+0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling  ) == "1E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling  ) == "1.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling  ) == "1.00E+0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "1E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "1.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "1.00E+0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "1E+0" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.0E+0" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.00E+0" );

	v = 16.0L;
	UNIT_TEST( u, v.to_string() == "16" );
	UNIT_TEST( u, v.to_string( 2 ) == "16" );
	UNIT_TEST( u, v.to_string( 3 ) == "16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "10" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "20" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "10" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "20" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "16.0" );

	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "1E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "1.60E+1" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "2E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "1.60E+1" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "1E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "1.60E+1" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "2E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.60E+1" );

	v = -16.0L;
	UNIT_TEST( u, v.to_string() == "-16" );
	UNIT_TEST( u, v.to_string( 2 ) == "-16" );
	UNIT_TEST( u, v.to_string( 3 ) == "-16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "-20" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "-16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "-16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "-10" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "-16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "-16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "-10" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "-16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "-16.0" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "-20" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "-16" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "-16.0" );

	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "-2E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "-1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "-1.60E+1" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "-1E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.60E+1" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "-1E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "-1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "-1.60E+1" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "-2E+1" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.6E+1" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.60E+1" );

	v = 123.45L;
	UNIT_TEST( u, v.to_string() == "123.45" );
	UNIT_TEST( u, v.to_string( 2 ) == "120" );
	UNIT_TEST( u, v.to_string( 3 ) == "123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "100" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "200" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "130" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "124" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "123." );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half, true ) == "123." );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "124." );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "100" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "123" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::truncate ) == "123.4" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::truncate ) == "123.45" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::truncate ) == "123.450" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "200" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "130" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "124" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::from_zero ) == "123.5" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::from_zero ) == "123.45" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::from_zero ) == "123.450" );

	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "1E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "1.2E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "2E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "1.3E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "1.24E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor,   true ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half,  true ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling, true ) == "1.24E+2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "1E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "1.2E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_exponent, rounding_style::truncate ) == "1.234E+2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::truncate ) == "1.2345E+2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::truncate ) == "1.23450E+2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "2E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.3E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.24E+2" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_exponent, rounding_style::from_zero ) == "1.235E+2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::from_zero ) == "1.2345E+2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::from_zero ) == "1.23450E+2" );

	v = 123.0L;
	UNIT_TEST( u, v.to_string() == "123" );
	UNIT_TEST( u, v.to_string( 2 ) == "120" );
	UNIT_TEST( u, v.to_string( 3 ) == "123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "123." );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "123." );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "123." );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "100" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "200" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "130" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "100" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "123" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::truncate ) == "123.0" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::truncate ) == "123.00" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::truncate ) == "123.000" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "200" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "130" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "123" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::from_zero ) == "123.0" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::from_zero ) == "123.00" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::from_zero ) == "123.000" );

	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor,   true ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half,  true ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling, true ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "1E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "1.2E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "2E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "1.3E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "1E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "1.2E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_exponent, rounding_style::truncate ) == "1.230E+2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::truncate ) == "1.2300E+2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::truncate ) == "1.23000E+2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "2E+2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.3E+2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.23E+2" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_exponent, rounding_style::from_zero ) == "1.230E+2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::from_zero ) == "1.2300E+2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::from_zero ) == "1.23000E+2" );

	v = 12345000.0L;
	UNIT_TEST( u, v.to_string() == "12345000" );
	UNIT_TEST( u, v.to_string( 2 ) == "12000000" );
	UNIT_TEST( u, v.to_string( 3 ) == "12300000" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "12300000." );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "12300000." );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "12400000." );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor    ) == "10000000" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor    ) == "12000000" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor    ) == "12300000" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling  ) == "20000000" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling  ) == "13000000" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling  ) == "12400000" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "10000000" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "12000000" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "12300000" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::truncate ) == "12340000" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::truncate ) == "12345000" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::truncate ) == "12345000" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "20000000" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "13000000" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "12400000" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::from_zero ) == "12350000" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::from_zero ) == "12345000" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::from_zero ) == "12345000" );

	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::round_half, true  ) == "1.E+7" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::round_half, false ) == "1E+7" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::round_half ) == "1.2E+7" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half ) == "1.23E+7" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_exponent, rounding_style::round_half ) == "1.235E+7" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor    ) == "1E+7" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor    ) == "1.2E+7" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor    ) == "1.23E+7" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling  ) == "2E+7" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling  ) == "1.3E+7" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling  ) == "1.24E+7" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "1E+7" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "1.2E+7" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "1.23E+7" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_exponent, rounding_style::truncate ) == "1.234E+7" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::truncate ) == "1.2345E+7" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::truncate ) == "1.23450E+7" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "2E+7" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.3E+7" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.24E+7" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_exponent, rounding_style::from_zero ) == "1.235E+7" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::from_zero ) == "1.2345E+7" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::from_zero ) == "1.23450E+7" );

	v = -0.0123L;
	UNIT_TEST( u, v.to_string() == "-0.0123" );
	UNIT_TEST( u, v.to_string( 2 ) == "-0.012" );
	UNIT_TEST( u, v.to_string( 3 ) == "-0.0123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "-0.0123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "-0.0123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "-0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor   ) == "-0.02" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor   ) == "-0.013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor   ) == "-0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.01" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "-0.01" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "-0.012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "-0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.02" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.0123" );

	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor,   true ) == "-1.23E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half,  true ) == "-1.23E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling, true ) == "-1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor   ) == "-2E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor   ) == "-1.3E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor   ) == "-1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "-1E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.2E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "-1E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "-1.2E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "-1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "-2E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.3E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.23E-2" );

	v = 0.0123L;
	UNIT_TEST( u, v.to_string() == "0.0123" );
	UNIT_TEST( u, v.to_string( 2 ) == "0.012" );
	UNIT_TEST( u, v.to_string( 3 ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "0.01" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "0.012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "0.02" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "0.013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::truncate ) == "0.01" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::truncate ) == "0.012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::truncate ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "0.02" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "0.013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "0.0123" );

	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor,   true ) == "1.E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::round_half,  true ) == "1.E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling, true ) == "2.E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "1.23E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half ) == "1.23E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "1E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "1.2E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "2E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "1.3E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::truncate ) == "1E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::truncate ) == "1.2E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::truncate ) == "1.23E-2" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "2E-2" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.3E-2" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.23E-2" );

	v = -0.00123L;
	UNIT_TEST( u, v.to_string() == "-0.00123" );
	UNIT_TEST( u, v.to_string( 2 ) == "-0.0012" );
	UNIT_TEST( u, v.to_string( 3 ) == "-0.00123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "-0.00123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "-0.00123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "-0.00123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "-0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "-0.0013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "-0.00123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.001" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.00123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.0013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.00123" );

	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor,   true ) == "-1.23E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half,  true ) == "-1.23E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling, true ) == "-1.23E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "-2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "-1.3E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "-1.23E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "-1E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.23E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "-2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.3E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.23E-3" );

	v = 0.00123L;
	UNIT_TEST( u, v.to_string() == "0.00123" );
	UNIT_TEST( u, v.to_string( 2 ) == "0.0012" );
	UNIT_TEST( u, v.to_string( 3 ) == "0.00123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "0.00123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "0.00123" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "0.00123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "0.001" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "0.00123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "0.0013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "0.00123" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "0.0013" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "0.00123" );

	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor,   true ) == "1.23E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half,  true ) == "1.23E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling, true ) == "1.23E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "1E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "1.23E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "1.3E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "1.23E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.3E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.23E-3" );

	v = -0.0012L;
	UNIT_TEST( u, v.to_string() == "-0.0012" );
	UNIT_TEST( u, v.to_string( 2 ) == "-0.0012" );
	UNIT_TEST( u, v.to_string( 3 ) == "-0.00120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "-0.00120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "-0.00120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "-0.00120" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "-0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "-0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "-0.00120" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.001" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.00120" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.00120" );

	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor,   true ) == "-1.20E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half,  true ) == "-1.20E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling, true ) == "-1.20E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "-2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "-1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "-1.20E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "-1E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.20E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "-2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.20E-3" );

	v = 0.0012L;
	UNIT_TEST( u, v.to_string() == "0.0012" );
	UNIT_TEST( u, v.to_string( 2 ) == "0.0012" );
	UNIT_TEST( u, v.to_string( 3 ) == "0.00120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor,   true ) == "0.00120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::round_half,  true ) == "0.00120" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling, true ) == "0.00120" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::floor ) == "0.001" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::floor ) == "0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "0.00120" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::ceiling ) == "0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::ceiling ) == "0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "0.00120" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_fixed, rounding_style::from_zero ) == "0.002" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_fixed, rounding_style::from_zero ) == "0.0012" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::from_zero ) == "0.00120" );

	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor,   true ) == "1.20E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::round_half,  true ) == "1.20E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling, true ) == "1.20E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::floor ) == "1E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::floor ) == "1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::floor ) == "1.20E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::ceiling ) == "2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::ceiling ) == "1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::ceiling ) == "1.20E-3" );
	UNIT_TEST( u, v.to_string( 1, format_style::decimal_exponent, rounding_style::from_zero ) == "2E-3" );
	UNIT_TEST( u, v.to_string( 2, format_style::decimal_exponent, rounding_style::from_zero ) == "1.2E-3" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_exponent, rounding_style::from_zero ) == "1.20E-3" );

	v = -0.012345678L;
	UNIT_TEST( u, v.to_string() == "-0.012345678" );
	UNIT_TEST( u, v.to_string( 5 ) == "-0.012346" );
	UNIT_TEST( u, v.to_string( 6 ) == "-0.0123457" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::floor   ) == "-0.012346" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::floor   ) == "-0.0123457" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::floor   ) == "-0.01234568" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.012345" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.0123456" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::ceiling ) == "-0.01234567" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::truncate ) == "-0.012345" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::truncate ) == "-0.0123456" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::truncate ) == "-0.01234567" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.012346" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.0123457" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::from_zero ) == "-0.01234568" );

	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::floor   ) == "-1.2346E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::floor   ) == "-1.23457E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::floor   ) == "-1.234568E-2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.2345E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.23456E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::ceiling ) == "-1.234567E-2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::truncate ) == "-1.2345E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::truncate ) == "-1.23456E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::truncate ) == "-1.234567E-2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.2346E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.23457E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::from_zero ) == "-1.234568E-2" );

	v = 0.012345678L;
	UNIT_TEST( u, v.to_string() == "0.012345678" );
	UNIT_TEST( u, v.to_string( 6 ) == "0.0123457" );
	UNIT_TEST( u, v.to_string( 7 ) == "0.01234568" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::floor ) == "0.0123" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::floor ) == "0.01234" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::floor ) == "0.012345" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::floor ) == "0.0123456" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::floor ) == "0.01234567" );
	UNIT_TEST( u, v.to_string( 3, format_style::decimal_fixed, rounding_style::ceiling ) == "0.0124" );
	UNIT_TEST( u, v.to_string( 4, format_style::decimal_fixed, rounding_style::ceiling ) == "0.01235" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::ceiling ) == "0.012346" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::ceiling ) == "0.0123457" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::ceiling ) == "0.01234568" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::truncate ) == "0.012345" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::truncate ) == "0.0123456" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::truncate ) == "0.01234567" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_fixed, rounding_style::from_zero ) == "0.012346" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_fixed, rounding_style::from_zero ) == "0.0123457" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_fixed, rounding_style::from_zero ) == "0.01234568" );

	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::floor ) == "1.2345E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::floor ) == "1.23456E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::floor ) == "1.234567E-2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::ceiling ) == "1.2346E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::ceiling ) == "1.23457E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::ceiling ) == "1.234568E-2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::truncate ) == "1.2345E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::truncate ) == "1.23456E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::truncate ) == "1.234567E-2" );
	UNIT_TEST( u, v.to_string( 5, format_style::decimal_exponent, rounding_style::from_zero ) == "1.2346E-2" );
	UNIT_TEST( u, v.to_string( 6, format_style::decimal_exponent, rounding_style::from_zero ) == "1.23457E-2" );
	UNIT_TEST( u, v.to_string( 7, format_style::decimal_exponent, rounding_style::from_zero ) == "1.234568E-2" );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueGetters( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	value_test_type v;
	UNIT_TEST( u, v.get_exact_value() == 0.0L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, v.get_digit_count() == 1 );
	UNIT_TEST( u, v.get_tolerance() == 0.5L );
	UNIT_TEST( u, v.get_tolerance_lower() == -0.5L );
	UNIT_TEST( u, v.get_tolerance_upper() == 0.5L );
	UNIT_TEST( u, v.get_value() == 0.0L );
	UNIT_TEST( u, v.get_value( 2 ) == 0.0L );

	v = 1.0L;
	UNIT_TEST( u, v.get_exact_value() == 1.0L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, v.get_digit_count() == 1 );
	UNIT_TEST( u, v.get_tolerance() == 0.5L );
	UNIT_TEST( u, v.get_tolerance_lower() == 0.5L );
	UNIT_TEST( u, v.get_tolerance_upper() == 1.5L );
	UNIT_TEST( u, v.get_value() == 1.0L );
	UNIT_TEST( u, v.get_value( 2 ) == 1.0L );

	v = 16.0L;
	UNIT_TEST( u, v.get_exact_value() == 16.0L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, v.get_digit_count() == 2 );
	UNIT_TEST( u, v.get_tolerance() == 0.5L );
	UNIT_TEST( u, v.get_tolerance_lower() == 15.5L );
	UNIT_TEST( u, v.get_tolerance_upper() == 16.5L );
	UNIT_TEST( u, v.get_value() == 16.0L );
	UNIT_TEST( u, v.get_value( 1 ) == 20.0L );

	v = -16.0L;
	UNIT_TEST( u, v.get_exact_value() == -16.0L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, v.get_digit_count() == 2 );
	UNIT_TEST( u, v.get_tolerance() == 0.5L );
	UNIT_TEST( u, v.get_tolerance_lower() == -16.5L );
	UNIT_TEST( u, v.get_tolerance_upper() == -15.5L );
	UNIT_TEST( u, v.get_value() == -16.0L );
	UNIT_TEST( u, v.get_value( 1 ) == -20.0L );

	v = 123.45L;
	UNIT_TEST( u, v.get_exact_value() == 123.45L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == 2 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == -2 );
	UNIT_TEST( u, v.get_digit_count() == 5 );
	UNIT_TEST( u, v.get_tolerance() == 0.005L );
	UNIT_TEST( u, utility::are_nearly_equal( v.get_tolerance_lower(), 123.445L ) );
	UNIT_TEST( u, utility::are_nearly_equal( v.get_tolerance_upper(), 123.455L ) );
	UNIT_TEST( u, v.get_value() == 123.45L );
	UNIT_TEST( u, v.get_value( 1 ) == 100.0L );

	v = 123.0L;
	UNIT_TEST( u, v.get_exact_value() == 123.0L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == 2 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, v.get_digit_count() == 3 );
	UNIT_TEST( u, v.get_tolerance() == 0.5L );
	UNIT_TEST( u, v.get_tolerance_lower() == 122.5L );
	UNIT_TEST( u, v.get_tolerance_upper() == 123.5L );
	UNIT_TEST( u, v.get_value() == 123.0L );
	UNIT_TEST( u, v.get_value( 1 ) == 100.0L );

	v = 12345000.0L;
	UNIT_TEST( u, v.get_exact_value() == 12345000.0L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == 7 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == 3 );
	UNIT_TEST( u, v.get_digit_count() == 5 );
	UNIT_TEST( u, v.get_tolerance() == 500.0L );
	UNIT_TEST( u, v.get_tolerance_lower() == 12344500.0L );
	UNIT_TEST( u, v.get_tolerance_upper() == 12345500.0L );
	UNIT_TEST( u, v.get_value() == 12345000.0L );
	UNIT_TEST( u, v.get_value( 1 ) == 10000000.0L );

	v = -0.0123L;
	UNIT_TEST( u, v.get_exact_value() == -0.0123L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == -2 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == -4 );
	UNIT_TEST( u, v.get_digit_count() == 3 );
	UNIT_TEST( u, v.get_tolerance() == 0.00005L );
	UNIT_TEST( u, v.get_tolerance_lower() == -0.01235L );
	UNIT_TEST( u, v.get_tolerance_upper() == -0.01225L );
	UNIT_TEST( u, v.get_value() == -0.0123L );
	UNIT_TEST( u, v.get_value( 1 ) == -0.01L );

	v = 0.0123L;
	UNIT_TEST( u, v.get_exact_value() == 0.0123L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == -2 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == -4 );
	UNIT_TEST( u, v.get_digit_count() == 3 );
	UNIT_TEST( u, v.get_tolerance() == 0.00005L );
	UNIT_TEST( u, v.get_tolerance_lower() == 0.01225L );
	UNIT_TEST( u, v.get_tolerance_upper() == 0.01235L );
	UNIT_TEST( u, v.get_value() == 0.0123L );
	UNIT_TEST( u, v.get_value( 1 ) == 0.01L );

	v = -0.00123L;
	UNIT_TEST( u, v.get_exact_value() == -0.00123L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == -3 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == -5 );
	UNIT_TEST( u, v.get_digit_count() == 3 );
	UNIT_TEST( u, v.get_tolerance() == 0.000005L );
	UNIT_TEST( u, v.get_tolerance_lower() == -0.001235L );
	UNIT_TEST( u, v.get_tolerance_upper() == -0.001225L );
	UNIT_TEST( u, v.get_value() == -0.00123L );
	UNIT_TEST( u, v.get_value( 1 ) == -0.001L );

	v = 0.00123L;
	UNIT_TEST( u, v.get_exact_value() == 0.00123L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == -3 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == -5 );
	UNIT_TEST( u, v.get_digit_count() == 3 );
	UNIT_TEST( u, v.get_tolerance() == 0.000005L );
	UNIT_TEST( u, v.get_tolerance_lower() == 0.001225L );
	UNIT_TEST( u, v.get_tolerance_upper() == 0.001235L );
	UNIT_TEST( u, v.get_value() == 0.00123L );
	UNIT_TEST( u, v.get_value( 1 ) == 0.001L );

	v = -0.0012L;
	UNIT_TEST( u, v.get_exact_value() == -0.0012L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == -3 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == -4 );
	UNIT_TEST( u, v.get_digit_count() == 2 );
	UNIT_TEST( u, v.get_tolerance() == 0.00005L );
	UNIT_TEST( u, v.get_tolerance_lower() == -0.00125L );
	UNIT_TEST( u, v.get_tolerance_upper() == -0.00115L );
	UNIT_TEST( u, v.get_value() == -0.0012L );
	UNIT_TEST( u, v.get_value( 1 ) == -0.001L );

	v = 0.0012L;
	UNIT_TEST( u, v.get_exact_value() == 0.0012L );
	UNIT_TEST( u, v.get_most_sigdig_exponent() == -3 );
	UNIT_TEST( u, v.get_least_sigdig_exponent() == -4 );
	UNIT_TEST( u, v.get_digit_count() == 2 );
	UNIT_TEST( u, v.get_tolerance() == 0.00005L );
	UNIT_TEST( u, v.get_tolerance_lower() == 0.00115L );
	UNIT_TEST( u, v.get_tolerance_upper() == 0.00125L );
	UNIT_TEST( u, v.get_value() == 0.0012L );
	UNIT_TEST( u, v.get_value( 1 ) == 0.001L );
}


// ----------------------------------------------------------------------------

template < typename test_value_type >
void TestValueStringParsing( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	test_value_type value( "-0.0643" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -0.0643L ) );
	UNIT_TEST( u, value.get_digit_count() == 3 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -2 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -4 );

	value.assign( "123" );
	UNIT_TEST( u, value.get_exact_value() == 123.0L );
	UNIT_TEST( u, value.get_digit_count() == 3 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 2 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 0 );

	value.assign( "9876.54321" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), 9876.54321L ) );
	UNIT_TEST( u, value.get_digit_count() == 9 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 3 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -5 );

	value.assign( "1.54321E+10" );
	UNIT_TEST( u, value.get_exact_value() == 15432100000.0L );
	UNIT_TEST( u, value.get_digit_count() == 6 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 10 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 5 );

	value.assign( "1.543210000E+10" );
	UNIT_TEST( u, value.get_exact_value() == 15432100000.0L );
	UNIT_TEST( u, value.get_digit_count() == 10 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 10 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 1 );

	value.assign( "-1.54321E-7" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -0.000000154321L ) );
	UNIT_TEST( u, value.get_digit_count() == 6 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -7 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -12 );

	value.assign( "-1.54321000E-7" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -0.000000154321L ) );
	UNIT_TEST( u, value.get_digit_count() == 9 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -7 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -15 );

	value.assign( "-1.23456789E-4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -1.23456789E-4931L ) );
	UNIT_TEST( u, value.get_digit_count() == 9 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -4939 );

	value.assign( "-1E+4932" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -1E+4932L ) );
	UNIT_TEST( u, value.get_digit_count() == 1 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 4932 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 4932 );

	value.assign( "-1E+4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -1E+4931L ) );
	UNIT_TEST( u, value.get_digit_count() == 1 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 4931 );

	value.assign( "1.E+49" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), 1E+49L ) );
	UNIT_TEST( u, value.get_digit_count() == 1 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 49 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 49 );

	// This is the second biggest positive value allowed. If you add 1 to the power of ( utility::get_highest_exponent_allowed() - utility::get_max_precision() to this number, you get the highest number allowed.)
	value.assign( "9.999999999999999999999999999999999E+4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), 9.999999999999999999999999999999999E+4931L ) );
	UNIT_TEST( u, value.get_digit_count() == utility::get_max_precision() );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 4898 );

	// 1E+4932 is the biggest positive value allowed because 1.0000000000000000000000000000000001E+4932 causes an overflow of long double.
	value.assign( "1E+4932" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), 1E+4932L ) );
	UNIT_TEST( u, value.get_digit_count() == 1 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 4932 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 4932 );

	// 1E-4931 is the smallest positive value allowed.
	value.assign( "1E-4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), 1E-4931L ) );
	UNIT_TEST( u, value.get_digit_count() == 1 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -4931 );

	// 1E-4931 is the second smallest positive value allowed.
	value.assign( "1.000000000000000000000000000000001E-4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), 1.0000000000000000000000000000000001E-4931L ) );
	UNIT_TEST( u, value.get_digit_count() == utility::get_max_precision() );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -4964 );

	long double tolerance = 9.999999999999999999999999999999999E-4931L;
	value.assign( "9.999999999999999999999999999999999E-4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), 9.999999999999999999999999999999999E-4931L, tolerance ) );
	UNIT_TEST( u, value.get_digit_count() == utility::get_max_precision() );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -4964 );

	// -1E-4931 is the smallest negative value allowed.
	value.assign( "-1E-4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -1E-4931L ) );
	UNIT_TEST( u, value.get_digit_count() == 1 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -4931 );

	// This is the second smallest negative value allowed.
	value.assign( "-9.999999999999999999999999999999999E-4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -9.999999999999999999999999999999999E-4931L, tolerance ) );
	UNIT_TEST( u, value.get_digit_count() == utility::get_max_precision() );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == -4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == -4964 );

	// This is the second biggest negative value allowed.
	value.assign( "-9.999999999999999999999999999999999E+4931" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -9.999999999999999999999999999999999E+4931L ) );
	UNIT_TEST( u, value.get_digit_count() == utility::get_max_precision() );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 4931 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 4898 );

	// This is the biggest negative value allowed because -1.0000000000000000000000000000000001E+4932 causes an overflow of long double.
	value.assign( "-1E+4932" );
	UNIT_TEST( u, utility::are_nearly_equal( value.get_exact_value(), -1E+4932L ) );
	UNIT_TEST( u, value.get_digit_count() == 1 );
	UNIT_TEST( u, value.get_most_sigdig_exponent() == 4932 );
	UNIT_TEST( u, value.get_least_sigdig_exponent() == 4932 );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueBasics( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	// Basic tests with the value zero.
	const value_test_type zero;
	UNIT_TEST( u,  zero.get_value() == 0.0L );
	UNIT_TEST( u,  zero.to_string() == "0" );
	UNIT_TEST( u,  zero.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u,  zero.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  zero.get_digit_count() == 1 );

	// Basic tests with the value one.
	const value_test_type one( 1.0L );
	UNIT_TEST( u,  one.get_value() == 1.0L );
	UNIT_TEST( u,  one.to_string() == "1" );
	UNIT_TEST( u,  one.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u,  one.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  one.get_digit_count() == 1 );

	value_test_type d2;
	UNIT_TEST( u, zero == d2 ); // Default constructed value should be equal to another default-constructed value.
	UNIT_TEST( u, zero.equals( d2 ) );

	d2 = 1.0L;
	UNIT_TEST( u, zero == d2 ); // Seems odd to say zero == 1.0, but both have a least-sig-dig of exponent zero, so both have an uncertainty of 0.5, which means their certainty ranges overlap at a single point.
	UNIT_TEST( u, !( zero != d2 ) ); // 
	UNIT_TEST( u, zero.equals( d2 ) ); //
	UNIT_TEST( u, !( zero < d2 ) ); // Since the certainty range of 0.0 is from -0.5 to 0.5, and the certainty range of 1.0 is from 0.5 to 1.5, this cannot claim with certainty that 0.0 < 1.0.
	UNIT_TEST( u, !zero.less_than( d2 ) );
	UNIT_TEST( u, zero <= d2 );
	UNIT_TEST( u, zero.less_than_or_equals( d2 ) );

	d2 = 1.1L; // This value has an certainty range of 1.05 through 1.15.
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

	value_test_type d3( one );
	UNIT_TEST( u, d3 == one );
	UNIT_TEST( u, d3.equals( one ) );
	UNIT_TEST( u, d3 == d2 );
	UNIT_TEST( u, d3.equals( d2 ) );
	UNIT_TEST( u, d3 == zero );
	UNIT_TEST( u, d3.equals( zero ) );

	d2.swap( d3 );
	UNIT_TEST( u,  d3 == one );
	UNIT_TEST( u,  d3.equals( one ) );
	UNIT_TEST( u,  d3 == d2 );
	UNIT_TEST( u,  d3.equals( d2 ) );
	UNIT_TEST( u,  d3 == zero );
	UNIT_TEST( u,  d3.equals( zero ) );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueNegation( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	value_test_type zero;
	value_test_type one( 1UL );
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  one == 1.0L );

	zero = -zero;
	UNIT_TEST( u, zero == 0.0L );

	one = -one;
	UNIT_TEST( u, one == -1.0L );

	value_test_type v( -one );
	UNIT_TEST( u, v == 1.0L );
	v = -v;
	UNIT_TEST( u, v == -1.0L );

	value_test_type notNegative = zero.absolute();
	UNIT_TEST( u, notNegative == 0.0L );
	UNIT_TEST( u, notNegative.get_most_sigdig_exponent() == zero.get_most_sigdig_exponent() );
	UNIT_TEST( u, notNegative.get_digit_count() == zero.get_digit_count() );
	UNIT_TEST( u, notNegative.get_least_sigdig_exponent() == zero.get_least_sigdig_exponent() );

	notNegative = v.absolute(); // v is negative.
	UNIT_TEST( u, notNegative == 1.0L );
	UNIT_TEST( u, notNegative.get_digit_count() == v.get_digit_count() );
	UNIT_TEST( u, notNegative.get_least_sigdig_exponent() == v.get_least_sigdig_exponent() );
	UNIT_TEST( u, notNegative.get_most_sigdig_exponent() == v.get_most_sigdig_exponent() );

	notNegative = one.absolute();
	UNIT_TEST( u, notNegative == 1.0L );
	UNIT_TEST( u, notNegative.get_digit_count() == one.get_digit_count() );
	UNIT_TEST( u, notNegative.get_least_sigdig_exponent() == one.get_least_sigdig_exponent() );
	UNIT_TEST( u, notNegative.get_most_sigdig_exponent() == one.get_most_sigdig_exponent() );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueEquals( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	const char  zeroChar  = 0;
	const short zeroShort = 0;
	const int   zeroInt   = 0;
	const long  zeroLong  = 0;
	const float zeroFloat = 0.0L;
	const char  oneChar   = 1;
	const short oneShort  = 1;
	const int   oneInt    = 1;
	const long  oneLong   = 1;
	const float oneFloat  = 1.0L;
	const char  minusOneChar  = -1;
	const short minusOneShort = -1;
	const int   minusOneInt   = -1;
	const long  minusOneLong  = -1;
	const float minusOneFloat = -1.0L;
	const float floatTenthTolerance = 0.1;
	const double doubleTenthTolerance = 0.1;
	const long double longDoubleTenthTolerance = 0.1;
	const float floatNinePercentTolerance = 0.09;
	const double doubleNinePercentTolerance = 0.09;
	const long double longDoubleNinePercentTolerance = 0.09;
	const value_test_type zero;
	const value_test_type one( 1.0L );

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
	UNIT_TEST( u,  zero.equals( 0.0L ) );
	UNIT_TEST( u,  zero.equals( 0.0L, 1 ) );
	UNIT_TEST( u,  zero.equals( zeroChar ) );
	UNIT_TEST( u,  zero.equals( zeroShort ) );
	UNIT_TEST( u,  zero.equals( zeroInt ) );
	UNIT_TEST( u,  zero.equals( zeroLong ) );
	UNIT_TEST( u,  zero.equals( zeroChar,  1 ) );
	UNIT_TEST( u,  zero.equals( zeroShort, 1 ) );
	UNIT_TEST( u,  zero.equals( zeroInt,   1 ) );
	UNIT_TEST( u,  zero.equals( zeroLong,  1 ) );
	UNIT_TEST( u, !zero.equals( oneFloat,  1 ) );
	UNIT_TEST( u, !zero.equals( oneChar,   1 ) );
	UNIT_TEST( u, !zero.equals( oneShort,  1 ) );
	UNIT_TEST( u, !zero.equals( oneInt,    1 ) );
	UNIT_TEST( u, !zero.equals( oneLong,   1 ) );
	UNIT_TEST( u,  zero.equals( zeroChar,  2 ) );
	UNIT_TEST( u,  zero.equals( zeroShort, 2 ) );
	UNIT_TEST( u,  zero.equals( zeroInt,   2 ) );
	UNIT_TEST( u,  zero.equals( zeroLong,  2 ) );
	UNIT_TEST( u,  zero.equals( zeroFloat, 2 ) );
	UNIT_TEST( u, !zero.equals( oneFloat,  2 ) );
	UNIT_TEST( u, !zero.equals( oneChar,   2 ) );
	UNIT_TEST( u, !zero.equals( oneShort,  2 ) );
	UNIT_TEST( u, !zero.equals( oneInt,    2 ) );
	UNIT_TEST( u, !zero.equals( oneLong,   2 ) );
	UNIT_TEST( u, !zero.equals( oneFloat,  2 ) );
	UNIT_TEST( u, !zero.equals( minusOneChar,   2 ) );
	UNIT_TEST( u, !zero.equals( minusOneShort,  2 ) );
	UNIT_TEST( u, !zero.equals( minusOneInt,    2 ) );
	UNIT_TEST( u, !zero.equals( minusOneLong,   2 ) );
	UNIT_TEST( u, !zero.equals( minusOneFloat,  2 ) );
	UNIT_TEST( u,  zero.equals(  0.0001L, 1 ) );
	UNIT_TEST( u,  zero.equals( -0.0001L, 1 ) );
	// Tolerance is too big, so number could be equal to value.
	UNIT_TEST( u,  zero.equals( -0.1L, floatTenthTolerance ) );
	UNIT_TEST( u,  zero.equals(  0.1L, floatTenthTolerance ) );
	UNIT_TEST( u,  zero.equals( -0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u,  zero.equals(  0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u,  zero.equals( -0.1L, longDoubleTenthTolerance ) );
	UNIT_TEST( u,  zero.equals(  0.1L, longDoubleTenthTolerance ) );
	// Tolerance is smaller than difference between number and value, so numbers cannot be equal.
	UNIT_TEST( u, !zero.equals( -0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u, !zero.equals(  0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u, !zero.equals( -0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.equals(  0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.equals( -0.1L, longDoubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.equals(  0.1L, longDoubleNinePercentTolerance ) );

	UNIT_TEST( u,  one == oneFloat );
	UNIT_TEST( u,  one.equals( oneFloat ) );
	UNIT_TEST( u,  one.equals( oneFloat, 1 ) );
	UNIT_TEST( u,  one != 0.0L );
	UNIT_TEST( u,  one.equals( oneFloat ) );
	UNIT_TEST( u,  one.equals( 1.0001L, 1 ) );

	UNIT_TEST( u,  one == one  );
	UNIT_TEST( u,  one == zero ); // One and zero have overlapping tolerance ranges, so it seems as if they are equal.
	UNIT_TEST( u, zero == zero );
	UNIT_TEST( u, zero == one  );

	defined_value dv0;
	defined_value dv1( 1.0L );
	UNIT_TEST( u, zero == dv0 );
	UNIT_TEST( u, zero != dv1 );
	UNIT_TEST( u, !( zero != dv0 ) );
	UNIT_TEST( u, !( zero == dv1 ) );
	UNIT_TEST( u, one != dv0 );
	UNIT_TEST( u, one == dv1 );
	UNIT_TEST( u, !( one == dv0 ) );
	UNIT_TEST( u, !( one != dv1 ) );

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
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueLessThan( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	const char  zeroChar  = 0;
	const short zeroShort = 0;
	const int   zeroInt   = 0;
	const long  zeroLong  = 0;
	const float zeroFloat = 0.0L;
	const char  oneChar   = 1;
	const short oneShort  = 1;
	const int   oneInt    = 1;
	const long  oneLong   = 1;
	const float oneFloat  = 1.0L;
	const char  minusOneChar  = -1;
	const short minusOneShort = -1;
	const int   minusOneInt   = -1;
	const long  minusOneLong  = -1;
	const float minusOneFloat = -1.0L;
	const float floatTenthTolerance = 0.1;
	const double doubleTenthTolerance = 0.1;
	const long double longDoubleTenthTolerance = 0.1;
	const float floatNinePercentTolerance = 0.09;
	const double doubleNinePercentTolerance = 0.09;
	const long double longDoubleNinePercentTolerance = 0.09;
	const value_test_type zero;
	const value_test_type one( 1UL );

	// every test in this section is for operator< or less_than.
	UNIT_TEST( u, !( zero < minusOneFloat ) );
	UNIT_TEST( u, !( zero < minusOneChar  ) );
	UNIT_TEST( u, !( zero < minusOneShort ) );
	UNIT_TEST( u, !( zero < minusOneInt   ) );
	UNIT_TEST( u, !( zero < minusOneLong  ) );
	UNIT_TEST( u, ( zero < oneFloat ) );
	UNIT_TEST( u, ( zero < oneChar  ) );
	UNIT_TEST( u, ( zero < oneShort ) );
	UNIT_TEST( u, ( zero < oneInt   ) );
	UNIT_TEST( u, ( zero < oneLong  ) );
	UNIT_TEST( u,  zero.less_than( oneChar,  1 ) );
	UNIT_TEST( u,  zero.less_than( oneShort, 1 ) );
	UNIT_TEST( u,  zero.less_than( oneInt,   1 ) );
	UNIT_TEST( u,  zero.less_than( oneLong,  1 ) );
	UNIT_TEST( u,  zero.less_than( oneFloat, 1 ) );
	UNIT_TEST( u, !zero.less_than( minusOneChar,  1 ) );
	UNIT_TEST( u, !zero.less_than( minusOneShort, 1 ) );
	UNIT_TEST( u, !zero.less_than( minusOneInt,   1 ) );
	UNIT_TEST( u, !zero.less_than( minusOneLong,  1 ) );
	UNIT_TEST( u, !zero.less_than( minusOneFloat, 1 ) );
	UNIT_TEST( u,  zero.less_than( oneChar,  2 ) );
	UNIT_TEST( u,  zero.less_than( oneShort, 2 ) );
	UNIT_TEST( u,  zero.less_than( oneInt,   2 ) );
	UNIT_TEST( u,  zero.less_than( oneLong,  2 ) );
	UNIT_TEST( u,  zero.less_than( oneFloat, 2 ) );
	UNIT_TEST( u, !zero.less_than( minusOneChar,  2 ) );
	UNIT_TEST( u, !zero.less_than( minusOneShort, 2 ) );
	UNIT_TEST( u, !zero.less_than( minusOneInt,   2 ) );
	UNIT_TEST( u, !zero.less_than( minusOneLong,  2 ) );
	UNIT_TEST( u, !zero.less_than( minusOneFloat, 2 ) );
	UNIT_TEST( u, !zero.less_than(  0.0001L, 1 ) );
	UNIT_TEST( u, !zero.less_than( -0.0001L, 1 ) );
	// Tolerance is too big, so number cannot be less than value.
	UNIT_TEST( u, !zero.less_than( -0.1L, floatTenthTolerance ) );
	UNIT_TEST( u, !zero.less_than(  0.1L, floatTenthTolerance ) );
	UNIT_TEST( u, !zero.less_than( -0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u, !zero.less_than(  0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u, !zero.less_than( -0.1L, longDoubleTenthTolerance ) );
	UNIT_TEST( u, !zero.less_than(  0.1L, longDoubleTenthTolerance ) );
	// Tolerance is smaller than difference between number and value.
	UNIT_TEST( u, !zero.less_than( -0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u,  zero.less_than(  0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u, !zero.less_than( -0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u,  zero.less_than(  0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.less_than( -0.1L, longDoubleNinePercentTolerance ) );
	UNIT_TEST( u,  zero.less_than(  0.1L, longDoubleNinePercentTolerance ) );

	UNIT_TEST( u,  zero.less_than( oneFloat,  1 ) );
	UNIT_TEST( u,  zero.less_than( oneChar,   1 ) );
	UNIT_TEST( u,  zero.less_than( oneShort,  1 ) );
	UNIT_TEST( u,  zero.less_than( oneInt,    1 ) );
	UNIT_TEST( u,  zero.less_than( oneLong,   1 ) );
	UNIT_TEST( u, !zero.less_than( zeroChar,  2 ) );
	UNIT_TEST( u, !zero.less_than( zeroShort, 2 ) );
	UNIT_TEST( u, !zero.less_than( zeroInt,   2 ) );
	UNIT_TEST( u, !zero.less_than( zeroLong,  2 ) );
	UNIT_TEST( u, !zero.less_than( zeroFloat, 2 ) );
	UNIT_TEST( u,  zero.less_than( oneFloat,  2 ) );
	UNIT_TEST( u,  zero.less_than( oneChar,   2 ) );
	UNIT_TEST( u,  zero.less_than( oneShort,  2 ) );
	UNIT_TEST( u,  zero.less_than( oneInt,    2 ) );
	UNIT_TEST( u,  zero.less_than( oneLong,   2 ) );
	UNIT_TEST( u,  zero.less_than( oneFloat,  2 ) );

	UNIT_TEST( u,  zero.less_than_or_equals( oneFloat,  1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneChar,   1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneShort,  1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneInt,    1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneLong,   1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zeroChar,  2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zeroShort, 2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zeroInt,   2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zeroLong,  2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zeroFloat, 2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneFloat,  2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneChar,   2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneShort,  2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneInt,    2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneLong,   2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneFloat,  2 ) );

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
	UNIT_TEST( u,  zero.less_than_or_equals( oneChar,  1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneShort, 1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneInt,   1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneLong,  1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneFloat, 1 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneFloat, 1 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneChar,  1 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneShort, 1 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneInt,   1 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneLong,  1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneChar,  2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneShort, 2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneInt,   2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneLong,  2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( oneFloat, 2 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneFloat, 2 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneChar,  2 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneShort, 2 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneInt,   2 ) );
	UNIT_TEST( u, !zero.less_than_or_equals( minusOneLong,  2 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( 0.0001L, 1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals( -0.0001L, 1 ) );
	UNIT_TEST( u,  zero.less_than_or_equals(  0.0001L, 1 ) );
	 // Tolerance is too big, so number cannot be less than value, but could be equal.
	UNIT_TEST( u,  zero.less_than_or_equals( -0.1L, floatTenthTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals(  0.1L, floatTenthTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals( -0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals(  0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals( -0.1L, longDoubleTenthTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals(  0.1L, longDoubleTenthTolerance ) );
	// Tolerance is smaller than difference between number and value.
	UNIT_TEST( u, !zero.less_than_or_equals( -0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals(  0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u, !zero.less_than_or_equals( -0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals(  0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.less_than_or_equals( -0.1L, longDoubleNinePercentTolerance ) );
	UNIT_TEST( u,  zero.less_than_or_equals(  0.1L, longDoubleNinePercentTolerance ) );

	UNIT_TEST( u, !( one < 1.1L ) );
	UNIT_TEST( u, !one.less_than( 1.1L ) );
	UNIT_TEST( u, !one.less_than( 1.0001L, 1 ) );
	UNIT_TEST( u,  one <= 1.1L );
	UNIT_TEST( u,  one.less_than_or_equals( 1.1L ) );
	UNIT_TEST( u,  one.less_than_or_equals( 1.0001L, 1 ) );

	UNIT_TEST( u, zero <= one  );
	UNIT_TEST( u, !( zero <  one ) );
	UNIT_TEST( u,  !one.less_than( zero ) );
	UNIT_TEST( u,  !one.less_than( one  ) );
	UNIT_TEST( u,   one.less_than_or_equals( zero ) );
	UNIT_TEST( u,   one.less_than_or_equals( one  ) );
	UNIT_TEST( u, !zero.less_than( zero ) );
	UNIT_TEST( u, !zero.less_than( one  ) );
	UNIT_TEST( u,  zero.less_than_or_equals( zero ) );
	UNIT_TEST( u,  zero.less_than_or_equals( one  ) );
	UNIT_TEST( u,  zero.less_than( one.get_exact_value(), 1 ) );
	UNIT_TEST( u,  zero.less_than( one.get_exact_value(), 2 ) );

	defined_value dv0;
	defined_value dv1( 1.0L );
	UNIT_TEST( u, zero < dv1 );
	UNIT_TEST( u, !( zero < dv0 ) );
	UNIT_TEST( u, zero <= dv0 );
	UNIT_TEST( u, zero <= dv1 );
	UNIT_TEST( u, zero.less_than( dv1 ) );
	UNIT_TEST( u, !( zero.less_than( dv0 ) ) );
	UNIT_TEST( u, zero.less_than_or_equals( dv0 ) );
	UNIT_TEST( u, zero.less_than_or_equals( dv1 ) );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueGreaterThan( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	const char  zeroChar  = 0;
	const short zeroShort = 0;
	const int   zeroInt   = 0;
	const long  zeroLong  = 0;
	const float zeroFloat = 0.0L;
	const char  oneChar   = 1;
	const short oneShort  = 1;
	const int   oneInt    = 1;
	const long  oneLong   = 1;
	const float oneFloat  = 1.0L;
	const char  minusOneChar  = -1;
	const short minusOneShort = -1;
	const int   minusOneInt   = -1;
	const long  minusOneLong  = -1;
	const float minusOneFloat = -1.0L;
	const float floatTenthTolerance = 0.1;
	const double doubleTenthTolerance = 0.1;
	const long double longDoubleTenthTolerance = 0.1;
	const float floatNinePercentTolerance = 0.09;
	const double doubleNinePercentTolerance = 0.09;
	const long double longDoubleNinePercentTolerance = 0.09;
	const value_test_type zero;
	const value_test_type one( 1UL );

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
	UNIT_TEST( u,  zero.greater_than( minusOneChar,  1 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneShort, 1 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneInt,   1 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneLong,  1 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneFloat, 1 ) );
	UNIT_TEST( u,  !zero.greater_than( oneChar,  1 ) );
	UNIT_TEST( u,  !zero.greater_than( oneShort, 1 ) );
	UNIT_TEST( u,  !zero.greater_than( oneInt,   1 ) );
	UNIT_TEST( u,  !zero.greater_than( oneLong,  1 ) );
	UNIT_TEST( u,  !zero.greater_than( oneFloat, 1 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneChar,  2 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneShort, 2 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneInt,   2 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneLong,  2 ) );
	UNIT_TEST( u,  zero.greater_than( minusOneFloat, 2 ) );
	UNIT_TEST( u,  !zero.greater_than( oneChar,  2 ) );
	UNIT_TEST( u,  !zero.greater_than( oneShort, 2 ) );
	UNIT_TEST( u,  !zero.greater_than( oneInt,   2 ) );
	UNIT_TEST( u,  !zero.greater_than( oneLong,  2 ) );
	UNIT_TEST( u,  !zero.greater_than( oneFloat, 2) );
	UNIT_TEST( u,  !zero.greater_than( -0.0001L, 1 ) );
	UNIT_TEST( u,  !zero.greater_than(  0.0001L, 1 ) );
	 // Tolerance is too big, so number cannot be greater than value, but could be equal.
	UNIT_TEST( u, !zero.greater_than( -0.1L, floatTenthTolerance ) );
	UNIT_TEST( u, !zero.greater_than(  0.1L, floatTenthTolerance ) );
	UNIT_TEST( u, !zero.greater_than( -0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u, !zero.greater_than(  0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u, !zero.greater_than( -0.1L, longDoubleTenthTolerance ) );
	UNIT_TEST( u, !zero.greater_than(  0.1L, longDoubleTenthTolerance ) );
	// Tolerance is smaller than difference between number and value.
	UNIT_TEST( u,  zero.greater_than( -0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u, !zero.greater_than(  0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u,  zero.greater_than( -0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.greater_than(  0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u,  zero.greater_than( -0.1L, longDoubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.greater_than(  0.1L, longDoubleNinePercentTolerance ) );

	UNIT_TEST( u, !zero.greater_than( oneFloat,  1 ) );
	UNIT_TEST( u, !zero.greater_than( oneChar,   1 ) );
	UNIT_TEST( u, !zero.greater_than( oneShort,  1 ) );
	UNIT_TEST( u, !zero.greater_than( oneInt,    1 ) );
	UNIT_TEST( u, !zero.greater_than( oneLong,   1 ) );
	UNIT_TEST( u, !zero.greater_than( zeroChar,  2 ) );
	UNIT_TEST( u, !zero.greater_than( zeroShort, 2 ) );
	UNIT_TEST( u, !zero.greater_than( zeroInt,   2 ) );
	UNIT_TEST( u, !zero.greater_than( zeroLong,  2 ) );
	UNIT_TEST( u, !zero.greater_than( zeroFloat, 2 ) );
	UNIT_TEST( u, !zero.greater_than( oneFloat,  2 ) );
	UNIT_TEST( u, !zero.greater_than( oneChar,   2 ) );
	UNIT_TEST( u, !zero.greater_than( oneShort,  2 ) );
	UNIT_TEST( u, !zero.greater_than( oneInt,    2 ) );
	UNIT_TEST( u, !zero.greater_than( oneLong,   2 ) );
	UNIT_TEST( u, !zero.greater_than( oneFloat,  2 ) );

	UNIT_TEST( u, !zero.greater_than_or_equals( oneFloat,  1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneChar,   1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneShort,  1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneInt,    1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneLong,   1 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zeroChar,  2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zeroShort, 2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zeroInt,   2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zeroLong,  2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zeroFloat, 2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneFloat,  2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneChar,   2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneShort,  2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneInt,    2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneLong,   2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneFloat,  2 ) );

	// every test in this section is for operator>= or greater_than_or_equals.
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
	UNIT_TEST( u, !zero.greater_than_or_equals( oneChar,  1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneShort, 1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneInt,   1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneLong,  1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneFloat, 1 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneChar,  1 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneShort, 1 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneInt,   1 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneLong,  1 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneFloat, 1 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneChar,  2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneShort, 2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneInt,   2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneLong,  2 ) );
	UNIT_TEST( u, !zero.greater_than_or_equals( oneFloat, 2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneChar,  2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneShort, 2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneInt,   2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneLong,  2 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( minusOneFloat, 2 ) );

	UNIT_TEST( u,  zero.greater_than_or_equals( -0.0001L, 1 ) );
	UNIT_TEST( u,  zero.greater_than_or_equals(  0.0001L, 1 ) );
	 // Tolerance is too big, so number cannot be greater than value, but could be equal.
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.1L, floatTenthTolerance ) );
	UNIT_TEST( u,  zero.greater_than_or_equals(  0.1L, floatTenthTolerance ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u,  zero.greater_than_or_equals(  0.1L, doubleTenthTolerance ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.1L, longDoubleTenthTolerance ) );
	UNIT_TEST( u,  zero.greater_than_or_equals(  0.1L, longDoubleTenthTolerance ) );
	// Tolerance is smaller than difference between number and value.
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u, !zero.greater_than_or_equals(  0.1L, floatNinePercentTolerance ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.greater_than_or_equals(  0.1L, doubleNinePercentTolerance ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( -0.1L, longDoubleNinePercentTolerance ) );
	UNIT_TEST( u, !zero.greater_than_or_equals(  0.1L, longDoubleNinePercentTolerance ) );

	UNIT_TEST( u, !( one > 0.9L ) );
	UNIT_TEST( u, !one.greater_than( 1.0L ) );
	UNIT_TEST( u, !one.greater_than( 1.0001L, 1 ) );
	UNIT_TEST( u, ( one >= 0.9L ) );
	UNIT_TEST( u, one.greater_than_or_equals( 0.9L ) );
	UNIT_TEST( u, one.greater_than_or_equals( 0.9001L, 1 ) );

	UNIT_TEST( u, !( one > zero ) );
	UNIT_TEST( u,  one >= zero );
	UNIT_TEST( u,   one.greater_than_or_equals( zero ) );
	UNIT_TEST( u,   one.greater_than_or_equals( one  ) );
	UNIT_TEST( u,  !one.greater_than( zero ) );
	UNIT_TEST( u,  !one.greater_than( one  ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( zero ) );
	UNIT_TEST( u,  zero.greater_than_or_equals( one  ) );
	UNIT_TEST( u, !zero.greater_than( zero ) );
	UNIT_TEST( u, !zero.greater_than( one  ) );

	defined_value dv0;
	defined_value dv1( 1.0L );
	UNIT_TEST( u, one > dv0 );
	UNIT_TEST( u, !( one > dv1 ) );
	UNIT_TEST( u, one >= dv0 );
	UNIT_TEST( u, one >= dv1 );
	UNIT_TEST( u, one.greater_than( dv0 ) );
	UNIT_TEST( u, !( one.greater_than( dv1 ) ) );
	UNIT_TEST( u, one.greater_than_or_equals( dv0 ) );
	UNIT_TEST( u, one.greater_than_or_equals( dv1 ) );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueAddition( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	const value_test_type zero;
	const value_test_type one( 1UL );
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  one == 1.0L );
	UNIT_TEST( u, zero.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, zero.get_digit_count() == 1 );
	UNIT_TEST( u,  one.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  one.get_digit_count() == 1 );

	calculated_value sum = zero + one;
	UNIT_TEST( u, sum == 1.0L );
	UNIT_TEST( u, sum == one );
	UNIT_TEST( u, sum.to_string() == "1" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_digit_count() == 1 );

	sum = one + one;
	UNIT_TEST( u, sum == 2.0L );
	UNIT_TEST( u, sum.to_string() == "2" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_digit_count() == 1 );

	const long ninety = 90;
	const long eleven = 11;
	const value_test_type ninetyValue( ninety, 2 );
	UNIT_TEST( u, ninetyValue == 90.0L );
	UNIT_TEST( u, ninetyValue.to_string() == "90" );
	UNIT_TEST( u, ninetyValue.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, ninetyValue.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, ninetyValue.get_digit_count() == 2 );
	const value_test_type elevenValue( eleven );
	UNIT_TEST( u, elevenValue == 11.0L );
	UNIT_TEST( u, elevenValue.to_string() == "11" );
	UNIT_TEST( u, elevenValue.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, elevenValue.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, elevenValue.get_digit_count() == 2 );

	sum = ninetyValue + elevenValue;
	UNIT_TEST( u, sum == 101.0L );
	UNIT_TEST( u, sum.get_exact_value() == 101.0L );
	UNIT_TEST( u, sum.to_string() == "101" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 2 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_digit_count() == 3 );

	sum = ninety + eleven; // Can also do arithmetic with direct conversion from long to Value.
	UNIT_TEST( u, sum == 101.0L );
	UNIT_TEST( u, sum.get_exact_value() == 101.0L );
	UNIT_TEST( u, sum.to_string() == "101" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 2 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_digit_count() == 3 );

	const value_test_type seven( 7.0L );
	sum = seven + one + one + one;
	UNIT_TEST( u, sum == 10.0L );
	UNIT_TEST( u, sum.get_exact_value() == 10.0L );
	UNIT_TEST( u, sum.to_string() == "10" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_digit_count() == 2 );

	value_test_type value1( 552340.0L, 5 );
	sum = value1 + elevenValue;
	UNIT_TEST( u, sum == 552351.0L );
	UNIT_TEST( u, sum.get_exact_value() == 552351.0L );
	UNIT_TEST( u, sum.to_string() == "552350" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 5 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, sum.get_digit_count() == 5 );

	value1.assign( 552340.067L, 5 );
	sum = value1 + elevenValue;
	UNIT_TEST( u, sum == 552351.0L );
	UNIT_TEST( u, sum.get_exact_value() == 552351.067L );
	UNIT_TEST( u, sum.to_string() == "552350" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 5 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, sum.get_digit_count() == 5 );

	// This test confirms that addition 
	value1.assign( 552340.067L, 9 );
	sum = value1 + elevenValue;
	UNIT_TEST( u, sum == 552351.0L );
	UNIT_TEST( u, sum.get_exact_value() == 552351.067L );
	UNIT_TEST( u, sum.to_string() == "552351" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 5 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_digit_count() == 6 );

	// This test confirms that addition only causes the number of sig-digs to go up when the order-of-exponent goes up.
	value1.assign( 2.0L, 1 );
	sum = value1 + elevenValue;
	UNIT_TEST( u, sum == 13.0L );
	UNIT_TEST( u, sum.get_exact_value() == 13.0L );
	UNIT_TEST( u, sum.to_string() == "13" );
	UNIT_TEST( u, sum.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, sum.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, sum.get_digit_count() == 2 );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueSubtraction( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	const value_test_type zero;
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  zero.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  zero.get_digit_count() == 1 );

	const value_test_type one( 1UL );
	UNIT_TEST( u,  one == 1.0L );
	UNIT_TEST( u,  one.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  one.get_digit_count() == 1 );

	calculated_value diff = zero - one;
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

	const value_test_type ninety( 90L, 2 );
	UNIT_TEST( u, ninety == 90.0L );
	UNIT_TEST( u, ninety.to_string() == "90" );
	UNIT_TEST( u, ninety.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, ninety.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, ninety.get_digit_count() == 2 );

	const value_test_type eleven( 11L );
	UNIT_TEST( u, eleven == 11.0L );
	UNIT_TEST( u, eleven.to_string() == "11" );
	UNIT_TEST( u, eleven.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, eleven.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, eleven.get_digit_count() == 2 );

	diff = ninety - eleven;
	UNIT_TEST( u, diff == 79.0L );
	UNIT_TEST( u, diff.to_string() == "79" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, diff.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, diff.get_digit_count() == 2 );

	diff = eleven - ninety;
	UNIT_TEST( u, diff == -79.0L );
	UNIT_TEST( u, diff.to_string() == "-79" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, diff.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, diff.get_digit_count() == 2 );

	value_test_type value1( 552340.0L, 5 );
	const value_test_type elevenValue( eleven );
	diff = value1 - elevenValue;
	UNIT_TEST( u, diff == 552329.0L );
	UNIT_TEST( u, diff.get_value() == 552330.0L ); // Since value1 is only known to tens place, then diff is rounded to tens place.
	UNIT_TEST( u, diff.get_exact_value() == 552329.0L );
	UNIT_TEST( u, diff.to_string() == "552330" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 5 );
	UNIT_TEST( u, diff.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, diff.get_digit_count() == 5 );

	value1.assign( 552340.067L, 5 );
	diff = value1 - elevenValue;
	UNIT_TEST( u, diff == 552329.0L );
	UNIT_TEST( u, diff.get_value() == 552330.0L ); // Since value1 is only known to tens place, then diff is rounded to tens place.
	UNIT_TEST( u, diff.get_exact_value() == 552329.067L );
	UNIT_TEST( u, diff.to_string() == "552330" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 5 );
	UNIT_TEST( u, diff.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, diff.get_digit_count() == 5 );

	// This test confirms that subtraction 
	value1.assign( 552340.067L, 9 );
	diff = value1 - elevenValue;
	UNIT_TEST( u, diff == 552329.0L );
	UNIT_TEST( u, diff.get_exact_value() == 552329.067L );
	UNIT_TEST( u, diff.to_string() == "552329" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 5 );
	UNIT_TEST( u, diff.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, diff.get_digit_count() == 6 );

	// This test confirms that subtraction only causes the number of sig-digs to go down when the order-of-exponent goes down.
	value1.assign( 2.0L, 1 );
	diff = value1 - elevenValue;
	UNIT_TEST( u, diff == -9.0L );
	UNIT_TEST( u, diff.get_exact_value() == -9.0L );
	UNIT_TEST( u, diff.to_string() == "-9" );
	UNIT_TEST( u, diff.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, diff.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, diff.get_digit_count() == 1 );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueMultiplication( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	const value_test_type zero;
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u,  zero.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  zero.get_digit_count() == 1 );

	const value_test_type one( 1UL );
	UNIT_TEST( u,  one == 1.0L );
	UNIT_TEST( u,  one.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  one.get_digit_count() == 1 );

	calculated_value product = zero * one;
	UNIT_TEST( u, product == 0.0L );
	UNIT_TEST( u, product.to_string() == "0" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 0 );

	product = one * one;
	UNIT_TEST( u, product == 1.0L );
	UNIT_TEST( u, product.to_string() == "1" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 0 );

	const value_test_type ninety( 90L, 2 );
	UNIT_TEST( u, ninety == 90.0L );
	UNIT_TEST( u, ninety.to_string() == "90" );
	UNIT_TEST( u, ninety.get_most_sigdig_exponent() == 1 );
	const value_test_type eleven( 11L );
	UNIT_TEST( u, eleven == 11.0L );
	UNIT_TEST( u, eleven.to_string() == "11" );
	UNIT_TEST( u, eleven.get_most_sigdig_exponent() == 1 );

	product = ninety * one;
	UNIT_TEST( u, product == ninety );
	UNIT_TEST( u, product == 90.0L );
	UNIT_TEST( u, product.get_exact_value() == 90.0L );
	UNIT_TEST( u, product.to_string() == "90" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 1 );

	product = eleven * one;
	UNIT_TEST( u, product == eleven );
	UNIT_TEST( u, product == 11.0L );
	UNIT_TEST( u, product.get_value() == 10.0L );
	UNIT_TEST( u, product.get_exact_value() == 11.0L );
	UNIT_TEST( u, product.to_string() == "10" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 1 );

	product = eleven * ninety;
	UNIT_TEST( u, product == 990.0L );
	UNIT_TEST( u, product.to_string() == "990" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 2 );

	value_test_type value1( 552340.0L, 5 );
	const value_test_type elevenValue( eleven );
	product = value1 * elevenValue;
	UNIT_TEST( u, product == 6100000.0L );
	UNIT_TEST( u, product.get_value() == 6100000.0L );
	UNIT_TEST( u, product.get_exact_value() == 6075740.0L );
	UNIT_TEST( u, product.to_string() == "6100000" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 6 );
	UNIT_TEST( u, product.get_least_sigdig_exponent() == 5 );
	UNIT_TEST( u, product.get_digit_count() == 2 );

	value1.assign( 552340.067L, 5 );
	product = value1 * elevenValue;
	double tolerance = 0.0001;
	UNIT_TEST( u, product == 6100000.0L );
	UNIT_TEST( u, product.get_value() == 6100000.0L );
	UNIT_TEST( u, product.equals( 6075740.737, tolerance ) );
	UNIT_TEST( u, product.to_string() == "6100000" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 6 );
	UNIT_TEST( u, product.get_least_sigdig_exponent() == 5 );
	UNIT_TEST( u, product.get_digit_count() == 2 );

	value1.assign( 552340.067L, 9 );
	product = value1 * elevenValue;
	UNIT_TEST( u, product == 6100000.0L );
	UNIT_TEST( u, product.equals( 6075740.737, tolerance ) );
	UNIT_TEST( u, product.to_string() == "6100000" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 6 );
	UNIT_TEST( u, product.get_least_sigdig_exponent() == 5 );
	UNIT_TEST( u, product.get_digit_count() == 2 );

	value1.assign( 2.0L, 1 );
	product = value1 * elevenValue;
	UNIT_TEST( u, product == 20.0L );
	UNIT_TEST( u, product.get_exact_value() == 22.0L );
	UNIT_TEST( u, product.to_string() == "20" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, product.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, product.get_digit_count() == 1 );

	value1.assign( 53453.0L, 5 );
	value_test_type factor( 213UL );
	product = value1 * factor;
	UNIT_TEST( u, product == 11400000.0L );
	UNIT_TEST( u, product.get_exact_value() == 11385489.0L );
	UNIT_TEST( u, product.to_string() == "11400000" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 7 );
	UNIT_TEST( u, product.get_least_sigdig_exponent() == 5 );
	UNIT_TEST( u, product.get_digit_count() == 3 );

	factor.assign( 213UL, 2 );
	product = value1 * factor;
	UNIT_TEST( u, product == 11000000.0L );
	UNIT_TEST( u, product.get_exact_value() == 11385489.0L );
	UNIT_TEST( u, product.to_string() == "11000000" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 7 );
	UNIT_TEST( u, product.get_least_sigdig_exponent() == 6 );
	UNIT_TEST( u, product.get_digit_count() == 2 );

	value1.assign( 621.03L, 5 );
	factor.assign( 987600L, 4 );
	product = value1 * factor;
	UNIT_TEST( u, product == 613300000.0L );
	UNIT_TEST( u, product.get_exact_value() == 613329228 );
	UNIT_TEST( u, product.to_string() == "613300000" );
	UNIT_TEST( u, product.get_most_sigdig_exponent() == 8 );
	UNIT_TEST( u, product.get_least_sigdig_exponent() == 5 );
	UNIT_TEST( u, product.get_digit_count() == 4 );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueDivision( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	const value_test_type zero;
	UNIT_TEST( u, zero == 0.0L );
	UNIT_TEST( u, zero.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, zero.get_digit_count() == 1 );

	const value_test_type one( 1UL );
	UNIT_TEST( u,  one == 1.0L );
	UNIT_TEST( u,  one.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u,  one.get_digit_count() == 1 );

	calculated_value quotient = zero / one;
	UNIT_TEST( u, quotient == 0.0L );

	const value_test_type ninety( 90L, 2 );
	UNIT_TEST( u, ninety == 90.0L );
	UNIT_TEST( u, ninety.to_string() == "90" );
	UNIT_TEST( u, ninety.get_digit_count() == 2 );
	UNIT_TEST( u, ninety.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, ninety.get_most_sigdig_exponent() == 1 );

	const value_test_type eleven( 11L );
	UNIT_TEST( u, eleven == 11.0L );
	UNIT_TEST( u, eleven.to_string() == "11" );
	UNIT_TEST( u, eleven.get_digit_count() == 2 );
	UNIT_TEST( u, eleven.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, eleven.get_most_sigdig_exponent() == 1 );

	quotient = ninety / one;
	UNIT_TEST( u, quotient == ninety );
	UNIT_TEST( u, quotient == 90.0L );
	UNIT_TEST( u, quotient.to_string() == "90" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, quotient.get_digit_count() == 1 );

	quotient = eleven / one;
	UNIT_TEST( u, quotient == eleven );
	UNIT_TEST( u, quotient == 10.0L );
	UNIT_TEST( u, quotient.to_string() == "10" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, quotient.get_digit_count() == 1 );

	double tolerance = 0.01;

	quotient = eleven / ninety;
	UNIT_TEST( u, quotient.get_value() == 0.12L );
	UNIT_TEST( u, quotient.equals( 0.122222L, tolerance ) );
	UNIT_TEST( u, quotient.equals( 0.12L, tolerance ) );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == -1 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == -2 );
	UNIT_TEST( u, quotient.get_digit_count() == 2 );

	quotient = ninety / eleven;
	tolerance = 0.0001L;
	UNIT_TEST( u, quotient.get_value() == 8.2L );
	UNIT_TEST( u, quotient.equals( 8.181818L, tolerance ) );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == -1 );
	UNIT_TEST( u, quotient.get_digit_count() == 2 );

	value_test_type value1( 552340.0L, 5 );
	const value_test_type elevenValue( eleven );
	quotient = value1 / elevenValue;
	tolerance = 0.001L;
	UNIT_TEST( u, quotient == 50000.0L );
	UNIT_TEST( u, quotient.get_value() == 50000.0L );
	UNIT_TEST( u, quotient.equals( 50212.727L, tolerance ) );
	UNIT_TEST( u, quotient.to_string() == "50000" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 4 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == 3 );
	UNIT_TEST( u, quotient.get_digit_count() == 2 );

	value1.assign( 552340.067L, 5 );
	quotient = value1 / elevenValue;
	tolerance = 0.000001L;
	UNIT_TEST( u, quotient == 50000.0L );
	UNIT_TEST( u, quotient.get_value() == 50000.0L );
	UNIT_TEST( u, quotient.equals( 50212.733363L, tolerance ) );
	UNIT_TEST( u, quotient.to_string() == "50000" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 4 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == 3 );
	UNIT_TEST( u, quotient.get_digit_count() == 2 );

	value1.assign( 552340.067L, 9 );
	quotient = value1 / elevenValue;
	UNIT_TEST( u, quotient == 50000.0L );
	UNIT_TEST( u, quotient.equals( 50212.733363L, tolerance ) );
	UNIT_TEST( u, quotient.to_string() == "50000" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 4 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == 3 );
	UNIT_TEST( u, quotient.get_digit_count() == 2 );

	value1.assign( 2.0L, 1 );
	quotient = value1 / elevenValue;
	tolerance = 0.0001L;
	UNIT_TEST( u, quotient == 0.2L );
	UNIT_TEST( u, quotient.equals( 0.181818L, tolerance ) );
	UNIT_TEST( u, quotient.to_string() == "0.2" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == -1 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == -1 );
	UNIT_TEST( u, quotient.get_digit_count() == 1 );

	value1.assign( 53453.0L, 5 );
	value_test_type divisor( 213UL );
	quotient = value1 / divisor;
	tolerance = 0.0001;
	UNIT_TEST( u, quotient == 251.0L );
	UNIT_TEST( u, quotient.equals( 250.953L, tolerance ) );
	UNIT_TEST( u, quotient.to_string() == "251" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 2 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, quotient.get_digit_count() == 3 );

	divisor.assign( 213UL, 2 );
	quotient = value1 / divisor;
	UNIT_TEST( u, quotient == 250.0L );
	UNIT_TEST( u, quotient.equals( 250.953L, tolerance ) );
	UNIT_TEST( u, quotient.to_string() == "250" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == 2 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, quotient.get_digit_count() == 2 );

	value1.assign( 621.03L, 5 );
	divisor.assign( 987600L, 4 );
	quotient = value1 / divisor;
	tolerance = 0.0000001L;
	UNIT_TEST( u, quotient == 0.0006288L );
	UNIT_TEST( u, quotient.equals( 0.00062882L, tolerance ) );
	UNIT_TEST( u, quotient.to_string() == "0.0006288" );
	UNIT_TEST( u, quotient.get_most_sigdig_exponent() == -4 );
	UNIT_TEST( u, quotient.get_least_sigdig_exponent() == -7 );
	UNIT_TEST( u, quotient.get_digit_count() == 4 );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValuePowers( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

	value_test_type exponent;
	const value_test_type zero;
	calculated_value result = zero.to_power_of( exponent );
	UNIT_TEST( u, result.get_exact_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == zero.get_digit_count() );
	exponent = 1.0L;
	result = zero.to_power_of( exponent );
	UNIT_TEST( u, result.get_exact_value() == 0.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == zero.get_digit_count() );
	value_test_type result1 = zero.square_root();
	UNIT_TEST( u, result1.get_exact_value() == 0.0L );
	UNIT_TEST( u, result1.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_digit_count() == zero.get_digit_count() );
	result1 = zero.cube_root();
	UNIT_TEST( u, result1.get_exact_value() == 0.0L );
	UNIT_TEST( u, result1.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_digit_count() == zero.get_digit_count() );

	exponent = 0.0L;
	const value_test_type one( 1.0L );
	result = one.to_power_of( exponent );
	UNIT_TEST( u, result.get_exact_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == one.get_digit_count() );
	exponent = 1.0L;
	result = one.to_power_of( exponent );
	UNIT_TEST( u, result.get_exact_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == one.get_digit_count() );
	exponent = -1.0L;
	result = one.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == one.get_digit_count() );
	result1 = one.square_root();
	UNIT_TEST( u, result1.get_exact_value() == 1.0L );
	UNIT_TEST( u, result1.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_digit_count() == one.get_digit_count() );
	result1 = one.cube_root();
	UNIT_TEST( u, result1.get_exact_value() == 1.0L );
	UNIT_TEST( u, result1.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_digit_count() == one.get_digit_count() );

	exponent = -1.0L;
	double tolerance = 0.000001L;
	value_test_type nine( 9UL );
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.equals( 0.111111L, tolerance ) );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == -1 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == -1 );
	UNIT_TEST( u, result.get_digit_count() == nine.get_digit_count() );
	exponent = 0.0L;
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 1.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == nine.get_digit_count() );
	exponent = 1.0L;
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 9.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == nine.get_digit_count() );
	exponent = 2.0L;
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_value() == 80.0L ); // value is 80 due to rounding to single digit.
	UNIT_TEST( u, result.get_exact_value() == 81.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 1 );
	UNIT_TEST( u, result.get_digit_count() == nine.get_digit_count() );
	result1 = nine.square_root();
	UNIT_TEST( u, result1.get_value() == 3.0L );
	UNIT_TEST( u, result1.equals( 3.0L, tolerance ) );
	UNIT_TEST( u, result1.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_digit_count() == nine.get_digit_count() );
	result1 = nine.cube_root();
	UNIT_TEST( u, result1.get_value() == 2.0L ); // value is 2 due to rounding to single digit.
	UNIT_TEST( u, result1.equals( 2.080084L, tolerance ) );
	UNIT_TEST( u, result1.get_most_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result1.get_digit_count() == nine.get_digit_count() );

	// This test and the next one show that when the base is a significant number, but the exponent is a defined value, the result will have
	// the same number of sig-digs as the base.
	defined_value exponent2( 2.0L );
	value_test_type big( 200UL );
	result = big.to_power_of( exponent2 );
	UNIT_TEST( u, result.get_exact_value() == 40000.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 4 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 4 );
	UNIT_TEST( u, result.get_digit_count() == big.get_digit_count() );

	big.assign( 200.0L, 3 );
	UNIT_TEST( u, big.get_digit_count() == 3 );
	result = big.to_power_of( exponent2 );
	UNIT_TEST( u, result.get_exact_value() == 40000.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 4 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 2 );
	UNIT_TEST( u, result.get_digit_count() == big.get_digit_count() );

	nine.assign( 9.0L, 2 );
	exponent.assign( 2.0L, 3 );
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_exact_value() == 81.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == std::min( nine.get_digit_count(), exponent.get_digit_count() ) );

	nine.assign( 9.0L, 3 );
	exponent.assign( 2.0L, 2 );
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_exact_value() == 81.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == 0 );
	UNIT_TEST( u, result.get_digit_count() == std::min( nine.get_digit_count(), exponent.get_digit_count() ) );

	nine.assign( 9.0L, 3 );
	exponent.assign( 2.0L, 4 );
	result = nine.to_power_of( exponent );
	UNIT_TEST( u, result.get_exact_value() == 81.0L );
	UNIT_TEST( u, result.get_most_sigdig_exponent() == 1 );
	UNIT_TEST( u, result.get_least_sigdig_exponent() == -1 );
	UNIT_TEST( u, result.get_digit_count() == std::min( nine.get_digit_count(), exponent.get_digit_count() ) );
}

// ----------------------------------------------------------------------------

template< typename value_test_type >
void TestValueTrig( const char * testname )
{
    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    ut::UnitTest * u = uts.AddUnitTest( testname );

    const long double tolerance = 0.0000001L;
	const value_test_type radians1( 1.0L, 6 );
	value_test_type result = radians1.sine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.841471L ) );
	UNIT_TEST( u, result.get_digit_count() == radians1.get_digit_count() );

	result = radians1.cosine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.540302L ) );
	UNIT_TEST( u, result.get_digit_count() == radians1.get_digit_count() );

	result = radians1.tangent();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.557407L ) );
	UNIT_TEST( u, result.get_digit_count() == radians1.get_digit_count() );

	result = radians1.arc_sine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.570796L ) );
	UNIT_TEST( u, result.get_digit_count() == radians1.get_digit_count() );

	result = radians1.arc_cosine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.0L ) );
	UNIT_TEST( u, result.get_digit_count() == radians1.get_digit_count() );

	result = radians1.arc_tangent();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.785398L ) );
	UNIT_TEST( u, result.get_digit_count() == radians1.get_digit_count() );

	const value_test_type radiansPi( 3.1415926535L );
	result = radiansPi.sine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.0L, tolerance ) );
	UNIT_TEST( u, result.get_digit_count() == radiansPi.get_digit_count() );

	result = radiansPi.cosine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), -1.0L ) );
	UNIT_TEST( u, result.get_digit_count() == radiansPi.get_digit_count() );

	result = radiansPi.tangent();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.0L, tolerance ) );
	UNIT_TEST( u, result.get_digit_count() == radiansPi.get_digit_count() );

#ifdef NEED_UNIT_TEST_FOR_CHECKING_EXCEPTIONS
	UNIT_TEST( u, result = radiansPi.arc_sine() );

	UNIT_TEST( u, result = radiansPi.arc_cosine() );
#endif

	result = radiansPi.arc_tangent();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.262627256L ) );
	UNIT_TEST( u, result.get_digit_count() == radiansPi.get_digit_count() );

	const value_test_type radians2Pi( 6.283185307L );
	UNIT_TEST( u, radians2Pi.get_digit_count() == 10 );
	result = radians2Pi.sine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.0L, tolerance ) );
	UNIT_TEST( u, result.get_digit_count() == radians2Pi.get_digit_count() );

	result = radians2Pi.cosine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.0L ) );
	UNIT_TEST( u, result.get_digit_count() == radians2Pi.get_digit_count() );

	result = radians2Pi.tangent();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.0L, tolerance ) );
	UNIT_TEST( u, result.get_digit_count() == radians2Pi.get_digit_count() );

#ifdef NEED_UNIT_TEST_FOR_CHECKING_EXCEPTIONS
	result = radians2Pi.arc_sine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.570796L ) );
	UNIT_TEST( u, result.get_digit_count() == radians2Pi.get_digit_count() );

	result = radians2Pi.arc_cosine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.540302L ) );
	UNIT_TEST( u, result.get_digit_count() == radians2Pi.get_digit_count() );
#endif

	result = radians2Pi.arc_tangent();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.412965137L ) );
	UNIT_TEST( u, result.get_digit_count() == radians2Pi.get_digit_count() );

	const value_test_type radiansHalfPi( 1.57079632679489L );
	UNIT_TEST( u, radiansHalfPi.get_digit_count() == 15 );
	result = radiansHalfPi.sine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.0L ) );
	UNIT_TEST( u, result.get_digit_count() == radiansHalfPi.get_digit_count() );

	result = radiansHalfPi.cosine();
	UNIT_TEST( u, result.get_most_sigdig_exponent() <= -13 );
	UNIT_TEST( u, result.get_digit_count() == radiansHalfPi.get_digit_count() );

	result = radiansHalfPi.tangent();
	UNIT_TEST( u, result.get_most_sigdig_exponent() >= 13 );
	UNIT_TEST( u, result.get_digit_count() == radiansHalfPi.get_digit_count() );

#ifdef NEED_UNIT_TEST_FOR_CHECKING_EXCEPTIONS
	result = radiansHalfPi.arc_sine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.570796L ) );
	UNIT_TEST( u, result.get_digit_count() == radiansHalfPi.get_digit_count() );

	result = radiansHalfPi.arc_cosine();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 0.540302L ) );
	UNIT_TEST( u, result.get_digit_count() == radiansHalfPi.get_digit_count() );
#endif

	result = radiansHalfPi.arc_tangent();
	UNIT_TEST( u, utility::are_nearly_equal( result.get_exact_value(), 1.003884822L ) );
	UNIT_TEST( u, result.get_digit_count() == radiansHalfPi.get_digit_count() );
}

// ----------------------------------------------------------------------------

#ifdef PRINT_LIMITS
void PrintLimits()
{
	std::cout << std::fixed << std::setprecision( 40 );
	std::cout << "float \n FLT_MIN: [" << FLT_MIN << std::setprecision( 0 ) << "]\n FLT_MAX: [" << FLT_MAX
		<< "]\n FLT_EPSILON: [" << FLT_EPSILON << "]\n FLT_MIN_10_EXP: [" << FLT_MIN_10_EXP << "]\n FLT_MAX_10_EXP: [" << FLT_MAX_10_EXP << ']' << std::endl << std::endl;

	std::cout << std::fixed << std::setprecision( 308 );
	std::cout << "double \n DBL_MIN: [" << DBL_MIN << std::setprecision( 0 ) << "]\n  DBL_MAX: [" << DBL_MAX
		<< std::setprecision( 60 ) << "]\n DBL_EPSILON: [" << DBL_EPSILON << "]\n DBL_MIN_10_EXP: [" << DBL_MIN_10_EXP << "]\n DBL_MAX_10_EXP: [" << DBL_MAX_10_EXP << ']' << std::endl << std::endl;

	std::cout << std::fixed << std::setprecision( 308 );
	std::cout << "long double \n LDBL_MIN: [" << LDBL_MIN << std::setprecision( 0 ) << "]\n LDBL_MAX: [" << LDBL_MAX
		<< std::setprecision( 60 ) << "]\n LDBL_EPSILON: [" << LDBL_EPSILON << "]\n LDBL_MIN_10_EXP: [" << LDBL_MIN_10_EXP << "]\n LDBL_MAX_10_EXP: [" << LDBL_MAX_10_EXP << ']' << std::endl << std::endl;
}
#endif

// ----------------------------------------------------------------------------

int main( int argc, const char * argv[] )
{

	std::cout << std::fixed << std::setprecision( 40 );

	const ut::UnitTestSet::OutputOptions options = static_cast< ut::UnitTestSet::OutputOptions >(
		ut::UnitTestSet::SendToCout | ut::UnitTestSet::SummaryTable | ut::UnitTestSet::AddTestIndex |
		ut::UnitTestSet::Headers | ut::UnitTestSet::TimeStamp | ut::UnitTestSet::Messages | ut::UnitTestSet::Dividers );
    const ut::UnitTestSet::ErrorState status = ut::UnitTestSet::Create(
        "SigDig Tests", "sigdig_unit_tests.txt", nullptr, nullptr, options, true );
    if ( ( status != ut::UnitTestSet::Success )
      && ( status != ut::UnitTestSet::AlreadyExists ) )
    {
        std::cout << "An error occurred when creating the UnitTestSet singleton!" << std::endl;
        return 1;
    }

    ut::UnitTestSet & uts = ut::UnitTestSet::GetIt();
    if ( !uts.DoesOutputOption( options ) )
    {
        std::cout << "The UnitTestSet singleton does not apply the same output options requested." << std::endl;
        return 2;
    }

	TestMagnitude();
	TestRounding();
	TestSigDigCounting();
	TestStringDigitCounting();
	TestComparisons();

	TestDefinedValueBasics();
	TestDefinedStringOutput();
	TestDefinedStringParsing();
	TestDefinedNegation();
	TestDefinedEquals();
	TestDefinedLessThan();
	TestDefinedGreaterThan();
	TestDefinedAddition();
	TestDefinedSubtraction();
	TestDefinedMultiplication();
	TestDefinedDivision();
	TestDefinedPowers();

	TestValueGetters< measured_value >( "measured Getters" );
	TestValueStringOutput< measured_value >( "measured String Output" );
	TestValueStringParsing< measured_value >( "measured String Parsing" );
	TestValueBasics< measured_value >( "measured Basics" );
	TestValueNegation< measured_value >( "measured Negation" );
	TestValueEquals< measured_value >( "measured Equals" );
	TestValueLessThan< measured_value >( "measured Less Than" );
	TestValueGreaterThan< measured_value >( "measured Greater Than" );
	TestValueAddition< measured_value >( "measured Addition" );
	TestValueSubtraction< measured_value >( "measured Subtraction" );
	TestValueMultiplication< measured_value >( "measured Multiplication" );
	TestValueDivision< measured_value >( "measured Division" );
	TestValuePowers< measured_value >( "measured Powers" );
	TestValueTrig< measured_value >( "measured Trig" );

	TestValueGetters< calculated_value >( "calculated Getters" );
	TestValueStringOutput< calculated_value >( "calculated String Output" );
	TestValueStringParsing< calculated_value >( "calculated String Parsing" );
	TestValueBasics< calculated_value >( "calculated Basics" );
	TestValueNegation< calculated_value >( "calculated Negation" );
	TestValueEquals< calculated_value >( "calculated Equals" );
	TestValueLessThan< calculated_value >( "calculated Less Than" );
	TestValueGreaterThan< calculated_value >( "calculated Greater Than" );
	TestValueAddition< calculated_value >( "calculated Addition" );
	TestValueSubtraction< calculated_value >( "calculated Subtraction" );
	TestValueMultiplication< calculated_value >( "calculated Multiplication" );
	TestValueDivision< calculated_value >( "calculated Division" );
	TestValuePowers< calculated_value >( "calculated Powers" );
	TestValueTrig< calculated_value >( "calculated Trig" );

#ifdef PRINT_LIMITS
	PrintLimits();
#endif

	return 0;
}

// ----------------------------------------------------------------------------
