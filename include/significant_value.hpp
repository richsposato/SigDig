// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#pragma once

#ifndef SIGDIG_SIGNIFICANT_VALUE_HPP
#define SIGDIG_SIGNIFICANT_VALUE_HPP

#include <string>
#include <ostream>

#include "utility.hpp"

namespace sigdig {

class defined_value;
class calculated_value;

// ----------------------------------------------------------------------------

class significant_value
{
public:

/*
    /// @note The equals function checks if a value is within tolerance range.
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool operator == ( T value ) const
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
    > bool equals( T value ) const
    { return equals( static_cast< long double >( value ), digits_ ); }
*/

    template
    <
        typename V,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename T,
        typename = typename
            std::enable_if< std::is_integral< T >::value, T >::type
    > bool equals( V value, T digits ) const
    {
        return equals( static_cast< long double >( value ),
            static_cast< unsigned int >( digits ) );
    }

    bool equals( long double value ) const
    { return equals( value, digits_ ); }

    bool equals( long double value, unsigned int digits ) const;

    /** @note The equals function checks if that significant_value and
     this have overlapping tolerance ranges.
     */
    bool equals( const significant_value & that ) const;

    bool equals( const defined_value & that ) const;


    template
    <
        typename V,
        typename T,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename = typename
            std::enable_if< std::is_floating_point< T >::value, T >::type
    > bool equals( V value, T tolerance ) const
    {
        return equals( static_cast< long double >( value ),
            static_cast< long double >( tolerance ) );
    }

    bool equals( long double value, long double tolerance ) const;

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool operator != ( T value ) const
    { return !equals( static_cast< long double >( value ), digits_ ); }
*/
    bool operator != ( const significant_value & that ) const
    { return !( equals( that ) ); }

    bool operator != ( const defined_value & that ) const
    { return !( equals( that ) ); }

    bool operator != ( long double value ) const
    { return !equals( value, digits_ ); }
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool operator < ( T value ) const
    { return less_than( static_cast< long double >( value ), digits_ ); }
*/
    bool operator < ( long double value ) const
    { return less_than( value, digits_ ); }

    bool operator < ( const significant_value & that ) const
    { return less_than( that ); }

    bool operator < ( const defined_value & that ) const
    { return less_than( that ); }

/*    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool less_than( T value ) const
    { return less_than( static_cast< long double >( value ), digits_ ); }
*/
    template
    <
        typename V,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename T,
        typename = typename
            std::enable_if< std::is_integral< T >::value, T >::type
    > bool less_than( V value, T digits ) const
    {
        return less_than( static_cast< long double >( value ),
            static_cast< unsigned int >( digits ) );
    }

    bool less_than( long double value ) const
    { return less_than( value, digits_ ); }

    bool less_than( long double value, unsigned int digits ) const;

    bool less_than( const significant_value & that ) const;

    bool less_than( const defined_value & that ) const;

    template
    <
        typename V,
        typename T,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename = typename
            std::enable_if< std::is_floating_point< T >::value, T >::type
    > bool less_than( V value, T tolerance ) const
    {
        return less_than( static_cast< long double >( value ),
            static_cast< long double >( tolerance ) );
    }

    bool less_than( long double value, long double tolerance ) const;

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool operator > ( T value ) const
    { return greater_than( static_cast< long double >( value ), digits_ ); }
*/
    bool operator > ( long double value ) const
    { return greater_than( value, digits_ ); }

    bool operator > ( const significant_value & that ) const
    { return greater_than( that ); }

    bool operator > ( const defined_value & that ) const
    { return greater_than( that ); }

/*    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool greater_than( T value ) const
    { return greater_than( static_cast< long double >( value ), digits_ ); }
*/
    template
    <
        typename V,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename T,
        typename = typename
            std::enable_if< std::is_integral< T >::value, T >::type
    > bool greater_than( V value, T digits ) const
    {
        return greater_than( static_cast< long double >( value ),
            static_cast< unsigned int >( digits ) );
    }

    bool greater_than( long double value ) const
    { return greater_than( value, digits_ ); }

    bool greater_than( long double value, unsigned int digits ) const;

    bool greater_than( const significant_value & that ) const;

    bool greater_than( const defined_value & that ) const;


    template
    <
        typename V,
        typename T,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename = typename
            std::enable_if< std::is_floating_point< T >::value, T >::type
    > bool greater_than( V value, T tolerance ) const
    {
        return greater_than( static_cast< long double >( value ),
            static_cast< long double >( tolerance ) );
    }

    bool greater_than( long double value, long double tolerance ) const;

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool operator <= ( T value ) const
    { return !greater_than( static_cast< long double >( value ), digits_ ); }
*/
    bool operator <= ( long double value ) const
    { return !greater_than( value, digits_ ); }

    bool operator <= ( const significant_value & that ) const
    { return !greater_than( that ); }

    bool operator <= ( const defined_value & that ) const
    { return !greater_than( that ); }

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool less_than_or_equals( T value ) const
    { return !greater_than( static_cast< long double >( value ), digits_ ); }
*/
    template
    <
        typename V,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename T,
        typename = typename
            std::enable_if< std::is_integral< T >::value, T >::type
    > bool less_than_or_equals( V value, T digits ) const
    {
        return !greater_than( static_cast< long double >( value ),
            static_cast< unsigned int >( digits ) );
    }

    bool less_than_or_equals( long double value ) const
    { return !greater_than( value, digits_ ); }

    bool less_than_or_equals( long double value, unsigned int digits ) const
    { return !greater_than( value, digits  ); }

    bool less_than_or_equals( const significant_value & that ) const
    { return !greater_than( that ); }

    bool less_than_or_equals( const defined_value & that ) const
    { return !greater_than( that ); }

    template
    <
        typename V,
        typename T,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename = typename
            std::enable_if< std::is_floating_point< T >::value, T >::type
    > bool less_than_or_equals( V value, T tolerance ) const
    {
        return !greater_than( static_cast< long double >( value ),
            static_cast< long double >( tolerance ) );
    }

    bool less_than_or_equals( long double value, long double tolerance ) const
    { return !greater_than( value, tolerance ); }

/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool operator >= ( T value ) const
    { return greater_than_or_equals( value ); }
*/
    bool operator >= ( long double value ) const
    { return greater_than_or_equals( value ); }

    bool operator >= ( const significant_value & that ) const
    { return greater_than_or_equals( that ); }

    bool operator >= ( const defined_value & that ) const
    { return greater_than_or_equals( that ); }
/*
    template
    <
        typename T,
        typename =
            typename std::enable_if< std::is_arithmetic< T >::value, T >::type
    > bool greater_than_or_equals( T value ) const
    { return !less_than( static_cast< long double >( value ), digits_ ); }
*/
    template
    <
        typename V,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename T,
        typename = typename
            std::enable_if< std::is_integral< T >::value, T >::type
    > bool greater_than_or_equals( V value, T digits ) const
    {
        return !less_than( static_cast< long double >( value ),
            static_cast< unsigned int >( digits ) );
    }

    bool greater_than_or_equals( long double value ) const
    { return !less_than( value, digits_ ); }

    bool greater_than_or_equals( long double value, unsigned int digits ) const
    { return !less_than( value, digits ); }

    bool greater_than_or_equals( const significant_value & that ) const
    { return !less_than( that ); }

    bool greater_than_or_equals( const defined_value & that ) const
    { return !less_than( that ); }

    template
    <
        typename V,
        typename T,
        typename = typename
            std::enable_if< std::is_arithmetic< V >::value, V >::type,
        typename = typename
            std::enable_if< std::is_floating_point< T >::value, T >::type
    > bool greater_than_or_equals( V value, T tolerance ) const
    {
        return !less_than( static_cast< long double >( value ),
            static_cast< long double >( tolerance ) );
    }

    bool greater_than_or_equals( long double value,
        long double tolerance ) const
    { return !less_than( value, tolerance ); }


    long double get_value( rounding_style rounding = rounding_style::round_half ) const
    { return get_value( digits_, rounding ); }

    long double get_value( int digits, rounding_style rounding = rounding_style::round_half ) const;

    std::string to_string(
        format_style formatting = format_style::decimal_fixed,
        rounding_style rounding = rounding_style::round_half,
        bool show_decimal = false ) const;

    std::string to_string( unsigned int digits,
        format_style formatting = format_style::decimal_fixed,
        rounding_style rounding = rounding_style::round_half,
        bool show_decimal = false ) const;

    inline long double get_exact_value() const { return value_; }

    inline int get_most_sigdig_exponent() const
    { return most_sigdig_exponent_; }

    inline int get_least_sigdig_exponent() const
    { return least_sigdig_exponent_; }

    inline unsigned int get_digit_count() const { return digits_; }

    long double get_tolerance() const;

    long double get_tolerance_lower() const;

    long double get_tolerance_upper() const;

    calculated_value remainder( const significant_value & divisor ) const;

    calculated_value remainder( const defined_value & divisor ) const;

    calculated_value operator / ( const significant_value & divisor ) const;

    calculated_value operator / ( const defined_value & divisor ) const;

    calculated_value operator * ( const significant_value & factor ) const;

    calculated_value operator * ( const defined_value & factor ) const;

    calculated_value operator - (
        const significant_value & subtrahend ) const;

    calculated_value operator - ( const defined_value & subtrahend ) const;

    calculated_value operator + ( const significant_value & addend ) const;

    calculated_value operator + ( const defined_value & addend ) const;

    // Power functions.
    calculated_value to_power_of( const significant_value & exponent ) const;

    calculated_value to_power_of( const defined_value & exponent ) const;


protected:

    significant_value( long double value );
    significant_value( long double value, unsigned int digits );
    significant_value( long value );
    significant_value( long value, unsigned int digits );
    significant_value( unsigned long value );
    significant_value( unsigned long value, unsigned int digits );
    significant_value( const char * value );
    significant_value( const char * value, unsigned int digits );
    significant_value( const std::string & value );
    significant_value( const std::string & value, unsigned int digits );
    significant_value( const significant_value & that );
    significant_value( long double value, unsigned int digits,
        int most_sigdig_exponent, int least_sigdig_exponent );
    ~significant_value();

    void assign( long double value );
    void assign( long double value, unsigned int digits );
    void assign( long value );
    void assign( long value, unsigned int digits );
    void assign( unsigned long value );
    void assign( unsigned long value, unsigned int digits );
    void assign( const char * value );
    void assign( const char * value, unsigned int digits );
    void assign( const std::string & value );
    void assign( const std::string & value, unsigned int digits );

    void swap( significant_value & that );

    bool is_sane() const;

    long double value_;
    unsigned int digits_;
    int most_sigdig_exponent_;
    int least_sigdig_exponent_;

private:

    significant_value() = delete;

};

std::ostream & operator << ( std::ostream & os, const significant_value & value );

// ----------------------------------------------------------------------------

} // end namespace

#endif
