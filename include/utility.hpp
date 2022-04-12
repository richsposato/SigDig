// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#pragma once

#ifndef SIGDIG_UTILITY_HPP
#define SIGDIG_UTILITY_HPP

namespace sigdig {

// ----------------------------------------------------------------------------

enum rounding_style
{
    truncate   = 0, ///< Truncates off any digits lower than those requested. Similar to rounding toward zero regardless of negative or positive.
    floor      = 1, ///< Rounds to nearest floor. (Round toward zero for positive values, and away from zero for negative values.)
    round_half = 2, ///< Rounds toward zero if first spurious digit is from 0 through 4, and away from zero if digit is from 5 through 9.
    ceiling    = 3, ///< Rounds to nearest ceiling. (Round away from zero for positive values, and toward zero for negative values.)
    from_zero  = 4, ///< Rounds away from zero regardless of negative or postive. Similar to floor for negative values, and ceiling for positive values.
};

enum format_style
{
    decimal_fixed        = 1,
    decimal_exponent     = 2, ///< This is equivalent to scientific notation.
    hexadecimal_exponent = 3
};

// ----------------------------------------------------------------------------

/** @class utility This class provides standalone functions that might be
 useful to code outside of the SigDig library.
 */

class utility
{
public:

    static int get_lowest_exponent_allowed();
    static int get_highest_exponent_allowed();

    /// Returns max number of significant digits supported.
    static unsigned int get_max_precision();

    static int calculate_exponent( long double value );
    static int calculate_exponent( long value );
    static int calculate_exponent( unsigned long value );

    static unsigned int count_significant_digits( long double value, int & exponent );
    static unsigned int count_significant_digits( long double value );
    static unsigned int count_significant_digits( long value );
    static unsigned int count_significant_digits( unsigned long value );

    static void count_digits_in_string( const char * source,
        long double & target, unsigned int & digits, int & exponent );

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
