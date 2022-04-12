// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#include "utility.hpp"

#include <cassert>
#include <cmath>
#include <cstring>

#include <array>

#include "lookup.hpp"
#include "helper.hpp"

#include <iostream>

namespace sigdig {

// ----------------------------------------------------------------------------

int utility::calculate_exponent( long value )
{
    if ( value == 0L )
    {
        return 0;
    }
    const unsigned long v = std::abs( value );
    int exponent = calculate_exponent( v );
    return exponent;
}

// ----------------------------------------------------------------------------

static const unsigned long integerExponentLookupTable[] =
{
              0UL,
             10UL,
            100UL,
           1000UL,
          10000UL,
         100000UL,
        1000000UL,
       10000000UL,
      100000000UL,
     1000000000UL
};

static const unsigned int integerExponentLookupTableSize =
    sizeof( integerExponentLookupTable )
        / sizeof( integerExponentLookupTable[0] );

// ----------------------------------------------------------------------------

int utility::calculate_exponent( unsigned long value )
{

    unsigned int first = 0;
    unsigned int last = integerExponentLookupTableSize;
    unsigned int place;
    while ( first < last )
    {
        place = ( first + last ) / 2;
        if ( integerExponentLookupTable[ place ] <= value )
        {
            if ( integerExponentLookupTable[ place+1 ] > value )
            {
                break;
            }
            first = place;
        }
        else
        {
            last = place;
        }
    }

    return place;
}

// ----------------------------------------------------------------------------

int utility::calculate_exponent( long double value )
{
    const int exponent = lookup::calculate_exponent(
        helper::validate_input_value( value ) );
    return exponent;
}

// ----------------------------------------------------------------------------

int count_integer_significant_digits( const char * chars, unsigned int bytes )
{
    if ( *chars == '-' )
    {
        ++chars;
        --bytes;
    }
    const char * p = chars + bytes - 1;
    while ( p >= chars )
    {
        if ( '0' != *p )
        {
            break;
        }
        --p;
    }
    const int count = ( p <= chars ) ? 1 : ( p - chars ) + 1;
    assert( 0 < count );
    return count;
}

// ----------------------------------------------------------------------------

unsigned int utility::count_significant_digits( long double value, int & exponent )
{
    helper::validate_input_value( value );
    if ( value == 0.0L )
    {
        exponent = 0;
        return 1;
    }

    value = std::fabs( value );
    const long double underflow_threshold = value * helper::epsilon;
    exponent = lookup::calculate_exponent( value );
    int magnitude = exponent;
    long double power_of_ten;
    unsigned int count = 1;
    for ( unsigned int i = 0; i <= helper::max_range_of_digits_for_long_double; i++ )
    {
        power_of_ten = std::pow( 10.0L, magnitude );
        const long double y = std::round( value / power_of_ten ) * power_of_ten;
        if ( std::abs( value - y ) < underflow_threshold )
            break;
        ++count;
        --magnitude;
    }

    return count;
}

// ----------------------------------------------------------------------------

unsigned int utility::count_significant_digits( long double value )
{
    helper::validate_input_value( value );
    if ( value == 0.0L )
    {
        return 1;
    }
    int exponent = 0;
    unsigned int count = count_significant_digits( value, exponent );
    return count;
}

// ----------------------------------------------------------------------------

unsigned int utility::count_significant_digits( long value )
{
    const unsigned long v = std::abs( value );
    const unsigned int count = count_significant_digits( v );
    return count;
}

// ----------------------------------------------------------------------------

unsigned int utility::count_significant_digits( unsigned long value )
{
    std::array< char, 256 > chars;
    const int bytes = std::snprintf( chars.data(), chars.size(), "%lu", value );
    assert( bytes > 0 );
    const unsigned int counted = count_integer_significant_digits( chars.data(), bytes );
    return counted;
}

// ----------------------------------------------------------------------------

bool count_digits_in_fixed_string( const char * source, unsigned int & digits, int & exponent )
{

    unsigned int digit_count = 0;
    unsigned int zero_count = 0;
    int digits_on_left = 0;
    int place_on_right = -1;
    bool found_digit = false;
    bool found_point = false;
    bool found_nonzero = false;
    bool keep_going = true;
    for ( const char * s = source; keep_going; ++s )
    {
        const char ch = *s;
        switch ( ch )
        {
            case '.' :
            {
                if ( found_point && !found_digit )
                {
                    throw std::invalid_argument(
                        "Error! String containing number may not have more than one decimal point." );
                }
                if ( found_point )
                {
                    keep_going = false;
                }
                if ( found_nonzero )
                {
                    digit_count += zero_count;
                }
                found_point = true;
                break;
            }
            case '0' :
            {
                if ( found_nonzero )
                {
                    if ( found_point )
                    {
                        ++digit_count;
                    }
                    else
                    {
                        ++zero_count;
                        ++digits_on_left;
                    }
                }
                else if ( found_point )
                {
                    --place_on_right;
                }
                found_digit = true;
                break;
            }
            case '1' :
            case '2' :
            case '3' :
            case '4' :
            case '5' :
            case '6' :
            case '7' :
            case '8' :
            case '9' :
            {
                if ( 0 != zero_count )
                {
                    digit_count += zero_count;
                }
                if ( !found_point )
                {
                    ++digits_on_left;
                }
                zero_count = 0;
                found_nonzero = true;
                found_digit = true;
                ++digit_count;
                break;
            }
            default:
            {
                if ( !found_digit )
                {
                    throw std::invalid_argument(
                        "Error! String does not contain a number." );
                }
                keep_going = false;
                break;
            }
        }
    }

    digits = ( found_nonzero ) ? digit_count : -place_on_right;
    exponent = ( digits_on_left != 0 ) ? digits_on_left - 1 :
        ( found_nonzero ) ? place_on_right : 0;
    return true;
}

// ----------------------------------------------------------------------------

bool count_digits_in_scientific_string( const char * source,
    unsigned int & digits, int & exponent, const char * e_place )
{

    // Check if string is in scientific notation. "#.####E+##" or "#E+##"
    const char exponent_sign = e_place[ 1 ];
    if ( ( exponent_sign != '-' ) && ( exponent_sign != '+' ) )
    {
        return false;
    }
    if ( std::isdigit( e_place[ 2 ] ) == 0 )
    {
        return false;
    }

    const bool has_dot = ( source[ 1 ] == '.' );
    const std::size_t digit_count =
        ( has_dot ) ? std::strspn( source + 2, "0123456789" ) : 0;
    const size_t dot_count = ( has_dot ) ? 1 : 0;
    if ( source + 1 + dot_count + digit_count != e_place )
    {
        return false;
    }

    digits = digit_count + 1;
    exponent = std::atoi( e_place + 1 );

    return true;
}

// ----------------------------------------------------------------------------

void utility::count_digits_in_string( const char * source,
    long double & target, unsigned int & digits, int & exponent )
{
    if ( ( nullptr == source ) || ( '\0' == *source ) )
    {
        throw std::invalid_argument(
            "Error! String is empty instead of containing number." );
        return;
    }
    long double value = helper::validate_input_value( source );
/*    if ( 0.0L == value )
    {
        target = value;
        digits = 1;
        exponent = 0;
        return;
    }*/
    if ( '-' == *source )
    {
        ++source;
    }

    const char * e_place = std::strpbrk( source, "eE" );
    if ( e_place == nullptr )
    {
        if ( count_digits_in_fixed_string( source, digits, exponent ) )
        {
            target = value;
            return;
        }
        else
        {
            throw std::invalid_argument(
                "Error! String does not contain number in scientific notation nor fixed notation." );
        }
    }

    if ( count_digits_in_scientific_string( source, digits, exponent, e_place ) )
    {
        target = value;
        return;
    }

    throw std::invalid_argument(
        "Error! String does not contain number in scientific notation." );
}

// ----------------------------------------------------------------------------

int utility::get_lowest_exponent_allowed()
{
    return helper::lowest_exponent;
}

// ----------------------------------------------------------------------------

int utility::get_highest_exponent_allowed()
{
    return helper::highest_exponent;
}

// ----------------------------------------------------------------------------

unsigned int utility::get_max_precision()
{
    return helper::max_range_of_digits_for_long_double;
}

// ----------------------------------------------------------------------------

bool utility::are_nearly_equal( long double v1, long double v2, long double tolerance )
{
    helper::validate_input_value( v1 );
    helper::validate_input_value( v2 );
    helper::validate_input_value( tolerance );
    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in utility::are_nearly_equal! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    const bool nearly_equal = helper::are_nearly_equal( v1, v2, tolerance );
    return nearly_equal;
}

// ----------------------------------------------------------------------------

bool utility::are_nearly_equal( long double v1, long double v2 )
{
    helper::validate_input_value( v1 );
    helper::validate_input_value( v2 );
    const bool nearly_equal = helper::are_nearly_equal( v1, v2 );
    return nearly_equal;
}

// ----------------------------------------------------------------------------

bool utility::is_less_than( long double v1, long double v2 )
{
    helper::validate_input_value( v1 );
    helper::validate_input_value( v2 );
    const bool less_than = helper::is_less_than( v1, v2 );
    return less_than;
}

// ----------------------------------------------------------------------------

bool utility::is_less_than( long double v1, long double v2,
    long double tolerance )
{
    helper::validate_input_value( v1 );
    helper::validate_input_value( v2 );
    helper::validate_input_value( tolerance );
    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in utility::are_nearly_equal! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    const bool less_than = helper::is_less_than( v1, v2, tolerance );
    return less_than;
}

// ----------------------------------------------------------------------------

bool utility::is_greater_than( long double v1, long double v2 )
{
    helper::validate_input_value( v1 );
    helper::validate_input_value( v2 );
    const bool greater_than = helper::is_greater_than( v1, v2 );
    return greater_than;
}

// ----------------------------------------------------------------------------

bool utility::is_greater_than( long double v1, long double v2,
    long double tolerance )
{
    helper::validate_input_value( v1 );
    helper::validate_input_value( v2 );
    helper::validate_input_value( tolerance );
    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in utility::are_nearly_equal! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    const bool greater_than = helper::is_greater_than( v1, v2, tolerance );
    return greater_than;
}

// ----------------------------------------------------------------------------

} // end namespace
