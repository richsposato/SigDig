// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#ifndef SIGDIG_HELPER_HPP
#define SIGDIG_HELPER_HPP

#pragma once

#include <string>

#include <cfloat>

#include "utility.hpp"

namespace sigdig {

// This is meant to be an internal header file.
// It is not meant to be included by source files outside of SigDig.

// ----------------------------------------------------------------------------

class helper
{
public:

    static const int lowest_exponent  = LDBL_MIN_10_EXP; // This is -4931.
    static const int highest_exponent = LDBL_MAX_10_EXP; // This is 4932.

    static constexpr long double max_sinh_value = 11357.0F;

    static constexpr double epsilon = 10.0L * LDBL_EPSILON;

    // A long double can store at most 34 base-10 digits because 113 bits are
    // used to store the significand. The formula to calculate the max number
    // of digits is floor( 113 / ( log(10) / log(2) ) ). The value of
    // 113 / ( log(10) / log(2) ) is about 34.016, and the floor of that is 34.
    static const unsigned int max_range_of_digits_for_long_double = 34;

    static unsigned int validate_digit_count( unsigned int digits );

    static long double validate_input_value( long double value );

    static void validate_input_value( long double value, unsigned int digits );

    static long double validate_input_value( const char * value );

    static std::string to_string( long double value, int exponent, format_style format = format_style::decimal_fixed,
        rounding_style rounding = rounding_style::round_half, bool show_decimal = false );

    static std::string to_string( long double value, int exponent, unsigned int digits,
        format_style format = format_style::decimal_fixed, rounding_style rounding = rounding_style::round_half,
        bool show_decimal = false );

    static long double calculate_rounding( long double value, int place, rounding_style rounding );

    static char get_format_type( format_style format, unsigned int & digits );

    static bool are_nearly_equal( long double v1, long double v2 );

    static bool are_nearly_equal( long double v1, long double v2, long double tolerance );

    static bool is_less_than( long double v1, long double v2 );

    static bool is_less_than( long double v1, long double v2, long double tolerance );

    static bool is_greater_than( long double v1, long double v2 );

    static bool is_greater_than( long double v1, long double v2, long double tolerance );

};

// ----------------------------------------------------------------------------

} // end namespace

#endif
