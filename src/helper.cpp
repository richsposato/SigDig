// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#include "helper.hpp"

#include <stdexcept>

#include <cassert>
#include <cmath>

#include <array>

#include "lookup.hpp"

#ifdef DEBUG
    #include <iostream>
#endif

namespace sigdig {

static const long double log_of_10 = 2.3025850929940456840179914546844L;
static const long double log_of_16 = 2.7725887222397812376689284858327L;
// This is the ratio of significant digits in base 16 as compared to base 10.
// This is about 0.8305. That is about 5 hex digits for every 6 decimal digits.
static const long double base_16_to_base_10_digit_ratio = log_of_10 / log_of_16;


// ----------------------------------------------------------------------------

unsigned int calculate_digits_to_write( format_style format, int exponent,
    unsigned int digits, unsigned int & on_left, unsigned int & on_right )
{
    unsigned int digits_to_write = 0;
    if ( format == format_style::decimal_fixed )
    {
        if ( exponent < 0 )
        {
            // All of the digits are to the right of the decimal.
            digits_to_write = ( digits - exponent ) - 1;
            on_left = 0;
            on_right = digits_to_write;
        }
        else if ( exponent + 1 >= static_cast< int >( digits ) )
        {
            // All of the digits are to the left of the decimal.
            digits_to_write = exponent + 1;
            on_left = digits_to_write;
            on_right = 0;
        }
        else
        {
            // Some digits are on the left and some are on the right.
            digits_to_write = digits + 1;
            on_left = exponent + 1;
            on_right = digits - on_left;
        }
    }
    else
    {
        // In scientific notation, there is only 1 digit on the left, and the
        // rest are on the right of the decimal. Add one more to right of the
        // decimal (which will be truncated later) to prevent snprintf from
        // rounding away requested digits.
        digits_to_write = digits;
        on_left = 1;
        on_right = digits + 1;
    }

    return digits_to_write;
}

// ----------------------------------------------------------------------------

char helper::get_format_type( format_style format, unsigned int & digits )
{
    char format_type = '\0';
    switch ( format )
    {
        case decimal_fixed:
        {
            format_type = 'f';
            break;
        }
        case decimal_exponent:
        {
            format_type = 'E';
            break;
        }
        case hexadecimal_exponent:
        {
            format_type = 'A';
            const long double hex_digits = ( digits * base_16_to_base_10_digit_ratio );
            digits = static_cast< unsigned int >( hex_digits + 0.5L );
            break;
        }
        default:
        {
            throw std::invalid_argument(
                "Error. Invalid formatting style for converting number to string." );
        }
    }

    return format_type;
}

// ----------------------------------------------------------------------------

long double calculate_ceiling( long double value, int place )
{
    const long double v = std::abs( value );
    const long double rounding_value =
        lookup::lookup_ceiling_offset( place + 1 );
    const long double underflow_threshold = v * 1000.0L * LDBL_EPSILON;
    const long double remainder =
        std::abs( std::remainderl( v, rounding_value ) );
    const bool is_divisible = ( remainder < underflow_threshold );
    if ( is_divisible )
    {
        return 0.0L;
    }
    return rounding_value;
}

// ----------------------------------------------------------------------------

long double helper::calculate_rounding( long double value, int place,
    rounding_style rounding )
{
    if ( value == 0.0L )
    {
        return 0.0L;
    }

    const bool is_negative = ( value < 0.0L );
    switch ( rounding )
    {
        case rounding_style::truncate:
        {
            return 0.0L;
        }
        case rounding_style::floor:
        {
            const long double rounding_value = ( is_negative ) ? -calculate_ceiling( value, place ) : 0.0L;
            return rounding_value;
        }
        case rounding_style::round_half:
        {
            long double rounding_value = lookup::lookup_tolerance( place );
            if ( is_negative )
            {
                rounding_value = -rounding_value;
            }
            return rounding_value;
        }
        case rounding_style::ceiling:
        {
            const long double rounding_value = ( is_negative ) ? 0.0L : calculate_ceiling( value, place );
            return rounding_value;
        }
        case rounding_style::from_zero:
        {
            long double rounding_value = calculate_ceiling( value, place );
            if ( is_negative )
            {
                rounding_value = -rounding_value;
            }
            return rounding_value;
        }
        default: break;
    }
    assert( false );
}

// ----------------------------------------------------------------------------

void helper::validate_input_value( long double value, unsigned int digits )
{
    validate_digit_count( digits );
    validate_input_value( value );
}

// ----------------------------------------------------------------------------

long double helper::validate_input_value( long double value )
{
    const int number_type = std::fpclassify( value );
    switch ( number_type )
    {
        case FP_INFINITE:  throw std::invalid_argument( "Value provided must not be infinite." );
        case FP_NAN:       throw std::invalid_argument( "Value provided is not a number." );
        case FP_SUBNORMAL: throw std::invalid_argument( "Value provided must not be an underflow result." );
        case FP_ZERO:      break;
        case FP_NORMAL:    break;
        default:           break;
    }
    return value;
}

// ----------------------------------------------------------------------------

long double helper::validate_input_value( const char * s )
{
    if ( ( nullptr == s ) || ( '\0' == *s ) )
    {
        throw std::invalid_argument( "String may not be null or empty." );
    }
    char * end = nullptr;
    const long double value = std::strtold( s, &end );
    if ( ( 0 == value ) && ( end == s ) )
    {
        throw std::invalid_argument( "String is not parsable as a number." );
    }
    return value;
}

// ----------------------------------------------------------------------------

unsigned int helper::validate_digit_count( unsigned int digits )
{
    if ( digits < 1 )
    {
        throw std::invalid_argument(
            "Error. The number of significant digits cannot be zero." );
    }
        if ( digits > helper::max_range_of_digits_for_long_double )
    {
        throw std::invalid_argument(
            "Long double does not support a precision more than 34 digits." );
    }
    return digits;    
}

// ----------------------------------------------------------------------------

void format_fixed_string( std::string & result, rounding_style rounding,
    unsigned int digits, unsigned int digits_to_write_on_left,
    unsigned int digits_to_write_on_right, bool show_decimal, bool is_negative,
    bool do_rounding, bool is_least_sigdig_in_tens_place )
{

    const std::string::size_type dot_place = result.find( '.' );
    const bool has_decimal = ( dot_place != std::string::npos );
    const unsigned int digits_on_right =
        ( has_decimal ) ? result.size() - ( dot_place + 1 ) : 0;
    unsigned int digits_on_left = ( has_decimal ) ? dot_place : result.size();
    if ( is_negative ) --digits_on_left;
    bool need_to_overwrite = ( digits_to_write_on_left > digits );
    bool need_to_add_more  = ( digits_on_right < digits_to_write_on_right );
    bool need_to_truncate  = ( digits_to_write_on_right < digits_on_right );

#ifdef DEBUG
    std::cout << __LINE__ << " \t add to left: [" << digits_to_write_on_left << "] \t on left: [" << digits_on_left << "] \t add to right: [" << digits_to_write_on_right << "] \t on right: [" << digits_on_right << ']' << std::endl;
#endif
    // These boolean flags cannot both be true.
    assert( !( need_to_overwrite && need_to_add_more  ) );
    assert( !( need_to_truncate  && need_to_add_more  ) );

    if ( need_to_overwrite )
    {
        // There are spurious digits are to the left of the decimal place, so
        // replace the spurious digits with zeros.
        std::string::size_type place = digits;
        if ( is_negative ) ++place; // add 1 for the minus sign.
        const std::string::size_type replace_count = digits_to_write_on_left - digits;
        if ( replace_count > 0 )
        {
            result.replace( place, replace_count, replace_count, '0' );
        }
        if ( show_decimal && is_least_sigdig_in_tens_place )
        {
            result.push_back( '.' );
        }
    }
    else if ( need_to_add_more )
    {
        // The caller wants more digits than are currently in the string, so
        // add more to the right.
        const unsigned int zeros_to_add = digits_on_right - digits_to_write_on_right;
        result.reserve( 1 + zeros_to_add );
        if ( dot_place == std::string::npos )
        {
            result.push_back( '.' );
        }
        result.append( zeros_to_add, '0' );
    }
    if ( need_to_truncate )
    {
        // spurious digits are to the right of the decimal. Remove them.
        assert( dot_place != std::string::npos );
        std::string::size_type truncate_place = result.size() - ( digits_on_right - digits_to_write_on_right );
        assert( 1 < truncate_place );
        assert( truncate_place < result.size() );
        assert( dot_place < truncate_place );
        const bool just_past_dot_place = ( dot_place + 1 == truncate_place );
        if ( just_past_dot_place && !show_decimal )
        {
            truncate_place = dot_place;
        }
        const bool adjust_for_ceiling = ( do_rounding && (
            ( rounding == rounding_style::from_zero ) ||
            ( ( rounding == rounding_style::ceiling ) && !is_negative ) ||
            ( ( rounding == rounding_style::floor   ) &&  is_negative ) ) );
        if ( adjust_for_ceiling )
        {
            std::string::size_type zero_place = ( 0 < digits_to_write_on_right ) ?
                dot_place + digits_to_write_on_right + 1 :
                dot_place + 1;
            if ( digits_to_write_on_left == 0 ) ++zero_place;
            assert( zero_place != dot_place );
            if ( zero_place < truncate_place )
            {
                result[ zero_place ] = '0';
            }
    #ifdef DEBUG
            std::cout << __LINE__ << " \t string: [" << result << "] \t zero_place: [" << zero_place << "] \t dot_place: [" << dot_place << ']' << std::endl;
    #endif
        }
    #ifdef DEBUG
        std::cout << __LINE__ << " \t string: [" << result << "] \t truncate: [" << truncate_place << "] \t size: [" << result.size() << ']' << std::endl;
    #endif
        result.erase( truncate_place );
    }
}

// ----------------------------------------------------------------------------

// result string should be in this format. "0.0E+00"

void format_exponent_string( std::string & result, unsigned int digits,
    bool show_decimal, bool is_negative )
{
#ifdef DEBUG
    std::cout << __LINE__ << " \t string: [" << result << " \t show_decimal: [" << show_decimal << ']' << std::endl;
#endif
    if ( ' ' == result[ 0 ] )
    {
        // Remove any leading spaces from result string.
        const std::string::size_type nonspace_spot =
            result.find_first_not_of( ' ' );
        result.erase( 0, nonspace_spot );
#ifdef DEBUG
        std::cout << __LINE__ << " \t string: [" << result << ']' << std::endl;
#endif
    }
    const std::string::size_type dot_place = result.find( '.' );
    const unsigned int dot_offset = ( is_negative ) ? 2 : 1;
    assert( dot_place == dot_offset );
    const std::string::size_type exponent_place = result.find( 'E' );
    assert( exponent_place != std::string::npos );
    const std::string::size_type after_exponent = exponent_place + 2;
    assert( after_exponent < result.size() );
    if ( result[ after_exponent ] == '0' )
    {
        // remove the extra zero after the E.
        result.erase( after_exponent, 1 );
        // result string is now in this format, "0.0E+0" instead of "0.0E+00".
    }
#ifdef DEBUG
    std::cout << __LINE__ << " \t string: [" << result << ']' << std::endl;
#endif
    if ( ( digits == 1 ) && !show_decimal )
    {
        const std::string::size_type digits_to_erase =
            exponent_place - dot_offset;
        result.erase( dot_offset, digits_to_erase );
    }
    else
    {
        // make sure number of digits in result matches digits parameter.
        const std::string::size_type digits_after_dot =
            ( exponent_place - dot_place ) - 1;
#ifdef DEBUG
        std::cout << __LINE__ << " \t string: [" << result << " \t digits_after_dot: [" << digits_after_dot << ']' << std::endl;
#endif
        if ( digits_after_dot > digits - 1 )
        {
            const unsigned int digits_to_erase =
                digits_after_dot - ( digits - 1 );
#ifdef DEBUG
            std::cout << __LINE__ << " \t digits_to_erase: [" << digits_to_erase << ']' << std::endl;
#endif
            result.erase( exponent_place - digits_to_erase, digits_to_erase );
        }
    }
}

// ----------------------------------------------------------------------------

std::string helper::to_string( long double value, int exponent,
    format_style formatting, rounding_style rounding, bool show_decimal )
{
    const unsigned int digits = utility::count_significant_digits( value );
    std::string result = to_string( value, exponent, digits, formatting,
        rounding, show_decimal );
    return result;
}

// ----------------------------------------------------------------------------

std::string helper::to_string( long double value, int exponent,
    unsigned int digits, format_style formatting, rounding_style rounding,
    bool show_decimal )
{

    const bool is_negative = ( value < 0.0 );
    const int exponent_below_least_sigdig =
        exponent - static_cast< int >( digits );
    const long double rounding_value = helper::calculate_rounding(
        value, exponent_below_least_sigdig, rounding );
    const long double raw_value = value + rounding_value;
    unsigned int digits_to_write_on_left = 0;
    unsigned int digits_to_write_on_right = 0;
    const char format_type = get_format_type( formatting, digits );
    const unsigned int digits_to_write = calculate_digits_to_write( formatting,
        exponent, digits, digits_to_write_on_left, digits_to_write_on_right );
    std::array< char, 32 > format;
    // Format for more digits than requested to avoid rounding by snprintf.
    std::snprintf( format.data(), format.size(), "%%%u.%uL%c",
        digits_to_write + 1, digits_to_write_on_right + 1, format_type );
    // Need this many chars because the most digits in fixed point format is
    // 4932. Then add 4 more for the decimal point, leading zero, minus sign,
    // and terminating NIL char.
    std::array< char, helper::highest_exponent + 4 > chars;
    const int bytes = std::snprintf( chars.data(), chars.size(),
        format.data(), raw_value );
    assert( bytes > 0 );
    std::string result( chars.data(), bytes );
    assert( static_cast< unsigned int >( bytes ) == result.size() );

#ifdef DEBUG
    std::cout << std::fixed;
    std::cout << __LINE__ << " \t value : [" << value << "] \t raw value: [" << raw_value << "] \t rounding Value: [" << rounding_value << "] \t rounding style: [" << rounding << ']' << std::endl;
    std::cout << __LINE__ << " \t string: [" << result << "] \t format: [" << format.data() << "] \t digits_to_write: [" << digits_to_write << "] \t bytes: [" << bytes << ']' << std::endl;
    std::cout << __LINE__ << " \t digits: [" << digits << "] \t exponent: [" << exponent << "] \t exponent_below_least_sigdig: [" << exponent_below_least_sigdig << "] \t formatting: [" << formatting << ']' << std::endl;
#endif
    if ( formatting == format_style::decimal_fixed )
    {
        const bool do_rounding = ( rounding_value != 0.0L );
        const bool is_least_sigdig_in_tens_place =
            ( 0 == exponent_below_least_sigdig );
        format_fixed_string( result, rounding, digits,
            digits_to_write_on_left, digits_to_write_on_right, show_decimal,
            is_negative, do_rounding, is_least_sigdig_in_tens_place );
    }
    else
    {
        format_exponent_string( result, digits, show_decimal, is_negative );
    }
#ifdef DEBUG
    std::cout << __LINE__ << " \t result: [" << result << ']' << std::endl;
#endif

    return result;
}

// ----------------------------------------------------------------------------

bool helper::are_nearly_equal( long double v1, long double v2, long double tolerance )
{
    const long double diff = std::fabs( v1 - v2 );
    const bool nearly_equal = ( diff <= tolerance );
    if ( nearly_equal )
    {
        return true;
    }

    // The if statement above handles most cases where v1 and v2 are
    // very close together. It does not handle well cases where v1 and v2 are
    // both very small, so the code below checks for those situations.
    if ( ( std::fabs( v1 ) > helper::epsilon )
      || ( std::fabs( v2 ) > helper::epsilon ) )
    {
        return false;
    }

    int v1_magnitude;
    int v2_magnitude;
    const unsigned int v1_digits = utility::count_significant_digits( v1, v1_magnitude );
    const unsigned int v2_digits = utility::count_significant_digits( v2, v2_magnitude );
    const int diff_magnitude = utility::calculate_exponent( diff );
    const int v1_below_lowest_digit = v1_magnitude - v1_digits;
    const int v2_below_lowest_digit = v2_magnitude - v2_digits;
    const int max_lowest_digit = std::max( v1_below_lowest_digit, v2_below_lowest_digit );
    const bool is_tiny_diff = ( diff_magnitude <= max_lowest_digit );
    return is_tiny_diff;
}

// ----------------------------------------------------------------------------

bool helper::are_nearly_equal( long double v1, long double v2 )
{
    const long double v1_tolerance = v1 * 10.0L * LDBL_EPSILON;
    const long double v2_tolerance = v2 * 10.0L * LDBL_EPSILON;
    const long double tolerance = std::fabs( std::min( v1_tolerance, v2_tolerance ) );
    const long double diff = std::fabs( v1 - v2 );
    const bool nearly_equal = ( diff <= tolerance );
    return nearly_equal;
}

// ----------------------------------------------------------------------------

bool helper::is_less_than( long double v1, long double v2 )
{
    const long double v1_tolerance = v1 * helper::epsilon;
    const long double v2_tolerance = v2 * helper::epsilon;
    const bool less_than = ( v1 + v1_tolerance < v2 - v2_tolerance );
    return less_than;
}

// ----------------------------------------------------------------------------

bool helper::is_less_than( long double v1, long double v2, long double tolerance )
{
    const bool less_than = ( v1 + tolerance < v2 );
    return less_than;
}

// ----------------------------------------------------------------------------

bool helper::is_greater_than( long double v1, long double v2 )
{
    const long double v1_tolerance = v1 * helper::epsilon;
    const long double v2_tolerance = v2 * helper::epsilon;
    const bool greater_than = ( v1 - v1_tolerance > v2 + v2_tolerance );
    return greater_than;
}

// ----------------------------------------------------------------------------

bool helper::is_greater_than( long double v1, long double v2, long double tolerance )
{
    const bool greater_than = ( v1 - tolerance > v2 );
    return greater_than;
}

// ----------------------------------------------------------------------------

} // end namespace
