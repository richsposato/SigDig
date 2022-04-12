// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#pragma once

#ifndef SIGDIG_DEFINED_VALUE_HPP
#define SIGDIG_DEFINED_VALUE_HPP

#include <string>
#include <ostream>

#include "Utility.hpp"

namespace sigdig {

class significant_value;
class calculated_value;

// ----------------------------------------------------------------------------

class defined_value
{
public:

    explicit defined_value( long double value = 0.0L );
    explicit defined_value( long value );
    explicit defined_value( unsigned long value );
    explicit defined_value( const char * value );
    explicit defined_value( const std::string & value );
    defined_value( const defined_value & that );

    defined_value & operator = ( long double value );
    defined_value & operator = ( long value );
    defined_value & operator = ( unsigned long value );
    defined_value & operator = ( const defined_value & that );

    ~defined_value();

    defined_value & swap( defined_value & that );

    /// Unary minus operator returns the negative of this value.
    defined_value operator-() const;

    /// Returns absolute value.
    defined_value absolute() const;

    /** Returns nearest integer not greater than value if positive, or nearest
     integer not less less than value if negative.
     */
    defined_value truncate() const;

    calculated_value remainder( const significant_value & that ) const;
    defined_value    remainder( const defined_value     & that ) const;

    calculated_value operator / ( const significant_value & that ) const;
    defined_value    operator / ( const defined_value     & that ) const;

    calculated_value operator * ( const significant_value & that ) const;
    defined_value    operator * ( const defined_value     & that ) const;

    calculated_value operator - ( const significant_value & that ) const;
    defined_value    operator - ( const defined_value     & that ) const;

    calculated_value operator + ( const significant_value & that ) const;
    defined_value    operator + ( const defined_value     & that ) const;
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool operator == ( T value ) const
    { return equals( static_cast< long double >( value ) ); }
*/
    bool operator == ( const significant_value & that ) const
    { return equals( that ); }

    bool operator == ( const defined_value & that ) const
    { return equals( that ); }

    bool operator == ( long double value ) const
    { return equals( value ); }

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool equals( T value ) const
    { return equals( static_cast< long double >( value ) ); }
*/
    bool equals( long double value ) const;

    bool equals( const significant_value & that ) const;

    bool equals( const defined_value & that ) const;
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool equals( T value, long double tolerance ) const
    { return equals( static_cast< long double >( value ), tolerance  ); }
*/
    bool equals( const defined_value & that, long double tolerance ) const;

    bool equals( long double value, long double tolerance ) const;

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool operator != ( T value ) const
    { return !( equals( static_cast< long double >( value ) ) ); }
*/
    bool operator != ( const significant_value & that ) const
    { return !( equals( that ) ); }

    bool operator != ( const defined_value & that ) const
    { return !( equals( that ) ); }

    bool operator != ( long double value ) const
    { return !( equals( value ) ); }

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool operator < ( T value ) const
    { return less_than( static_cast< long double >( value ) ); }
*/
    bool operator < ( const significant_value & that ) const
    { return less_than( that ); }

    bool operator < ( const defined_value & that ) const
    { return less_than( that ); }

    bool operator < ( long double value ) const
    { return less_than( value ); }

/*    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool less_than( T value ) const
    { return less_than( static_cast< long double >( value ) ); }
*/
    bool less_than( long double value ) const;

    bool less_than( const significant_value & that ) const;

    bool less_than( const defined_value & that ) const;

/*    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool less_than( T value, long double tolerance ) const
    { return less_than( static_cast< long double >( value ), tolerance  ); }
*/
    bool less_than( long double value, long double tolerance ) const;

    bool less_than( const defined_value & that, long double tolerance ) const;
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool operator > ( T value ) const
    { return greater_than( static_cast< long double >( value ) ); }
*/
    bool operator > ( const significant_value & that ) const
    { return greater_than( that ); }

    bool operator > ( const defined_value & that ) const
    { return greater_than( that ); }

    bool operator > ( long double value ) const
    { return greater_than( value ); }

/*    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool greater_than( T value ) const
    { return greater_than( static_cast< long double >( value ) ); }
*/
    bool greater_than( long double value ) const;

    bool greater_than( const significant_value & that ) const;

    bool greater_than( const defined_value & that ) const;
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool greater_than( T value, long double tolerance ) const
    { return greater_than( static_cast< long double >( value ), tolerance  ); }
*/
    bool greater_than( const defined_value & that,
        long double tolerance ) const;

    bool greater_than( long double value, long double tolerance ) const;
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool operator <= ( T value ) const
    { return less_than_or_equals( static_cast< long double >( value ) ); }
*/
    bool operator <= ( const significant_value & that ) const
    { return less_than_or_equals( that ); }

    bool operator <= ( const defined_value & that ) const
    { return less_than_or_equals( that ); }

    bool operator <= ( long double value ) const
    { return less_than_or_equals( value ); }
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool less_than_or_equals( T value ) const
    { return !greater_than( static_cast< long double >( value ) ); }
*/
    bool less_than_or_equals( long double value ) const
    { return !greater_than( value ); }

    bool less_than_or_equals( const significant_value & that ) const
    { return !greater_than( that ); }

    bool less_than_or_equals( const defined_value & that ) const
    { return !greater_than( that ); }

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool less_than_or_equals( T value, long double tolerance ) const
    { return !greater_than( static_cast< long double >( value ), tolerance  ); }
*/

    bool less_than_or_equals( long double value, long double tolerance ) const
    { return !greater_than( value, tolerance ); }

    bool less_than_or_equals( const defined_value & that,
        long double tolerance ) const
    { return !greater_than( that, tolerance ); }

/*    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool operator >= ( T value ) const
    { return greater_than_or_equals( static_cast< long double >( value ) ); }
*/
    bool operator >= ( const significant_value & that ) const
    { return greater_than_or_equals( that ); }

    bool operator >= ( const defined_value & that ) const
    { return greater_than_or_equals( that ); }

    bool operator >= ( long double value ) const
    { return greater_than_or_equals( value ); }
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool greater_than_or_equals( T value ) const
    { return greater_than_or_equals( static_cast< long double >( value ) ); }
*/
    bool greater_than_or_equals( long double value ) const
    { return !less_than( value ); }

    bool greater_than_or_equals( const significant_value & that ) const
    { return !less_than( that ); }

    bool greater_than_or_equals( const defined_value & that ) const
    { return !less_than( that ); }
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    >
    bool greater_than_or_equals( T value, long double tolerance ) const
    { return !less_than( static_cast< long double >( value ), tolerance  ); }
*/
    bool greater_than_or_equals( const defined_value & that,
        long double tolerance ) const
    { return !less_than( that, tolerance ); }

    bool greater_than_or_equals( long double value,
        long double tolerance ) const
    { return !less_than( value, tolerance ); }

    // Power functions.

    calculated_value to_power_of( const significant_value & exponent ) const;

    defined_value    to_power_of( const defined_value     & exponent ) const;

    defined_value square_root() const;

    defined_value cube_root() const;

    // Trigonometry functions.

    defined_value sine() const;

    defined_value cosine() const;

    defined_value tangent() const;

    defined_value arc_sine() const;

    defined_value arc_cosine() const;

    defined_value arc_tangent() const;

    // Hyperbolic Trigonometry functions.

    defined_value hyper_sine() const;

    defined_value hyper_cosine() const;

    defined_value hyper_tangent() const;

    defined_value hyper_arc_sine() const;

    defined_value hyper_arc_cosine() const;

    defined_value hyper_arc_tangent() const;

    // Exponent and Log functions.

    defined_value e_to_power_of() const;

    defined_value e_to_power_of_then_subtract_1() const;

    defined_value two_to_power_of() const;

    defined_value natural_log_of() const;

    defined_value base_10_log_of() const;

    defined_value base_2_log_of() const;

    long double get_value() const { return value_; }

    int get_most_sigdig_exponent() const { return exponent_; }

    std::string to_string(
        format_style formatting = format_style::decimal_fixed,
        rounding_style rounding = rounding_style::round_half,
        bool show_decimal = false ) const;

    std::string to_string( unsigned int digits,
        format_style formatting = format_style::decimal_fixed,
        rounding_style rounding = rounding_style::round_half,
        bool show_decimal = false ) const;

private:

    defined_value( long double value, int exponent );

    bool is_sane() const;

    long double value_;
    int exponent_;

};


std::ostream & operator << ( std::ostream & os, const defined_value & value );

// ----------------------------------------------------------------------------

} // end namespace

#endif
