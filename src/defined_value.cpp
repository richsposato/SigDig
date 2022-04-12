// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#include "defined_value.hpp"

#include <cassert>
#include <cmath>

#include <iostream>

#include <array>
#include <stdexcept>

#include "significant_value.hpp"
#include "calculated_value.hpp"
#include "helper.hpp"

namespace sigdig {

// ----------------------------------------------------------------------------

defined_value::defined_value( long double value ) :
    value_( helper::validate_input_value( value ) ),
    exponent_( utility::calculate_exponent( value ) )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value::defined_value( long value ) :
    value_( static_cast< long double >( value ) ),
    exponent_( utility::calculate_exponent( value ) )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value::defined_value( unsigned long value ) :
    value_( static_cast< long double >( value ) ),
    exponent_( utility::calculate_exponent( value ) )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value::defined_value( const char * value ) :
    value_( helper::validate_input_value( value ) ),
    exponent_( utility::calculate_exponent( value_ ) )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value::defined_value( const std::string & value ) :
    value_( helper::validate_input_value( value.c_str() ) ),
    exponent_( utility::calculate_exponent( value_ ) )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value::defined_value( long double value, int exponent ) :
    value_( helper::validate_input_value( value ) ),
    exponent_( exponent )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value::defined_value( const defined_value & that ) :
    value_ ( that.value_ ),
    exponent_( that.exponent_ )
{
    assert( that.is_sane() );
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value::~defined_value()
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

defined_value & defined_value::operator = ( long double value )
{
    assert( is_sane() );
    value_ = helper::validate_input_value( value );
    exponent_ = utility::calculate_exponent( value );
    return *this;
}

// ----------------------------------------------------------------------------

defined_value & defined_value::operator = ( long value )
{
    assert( is_sane() );
    value_ = static_cast< long double >( value );
    exponent_ = utility::calculate_exponent( value );
    return *this;
}

// ----------------------------------------------------------------------------

defined_value & defined_value::operator = ( unsigned long value )
{
    assert( is_sane() );
    value_ = static_cast< long double >( value );
    exponent_ = utility::calculate_exponent( value );
    return *this;
}

// ----------------------------------------------------------------------------

defined_value & defined_value::operator = ( const defined_value & that )
{
    assert( is_sane() );
    assert( that.is_sane() );
    if ( this != &that )
    {
        value_ = that.value_;
        exponent_ = that.exponent_;
    }
    return *this;
}

// ----------------------------------------------------------------------------

defined_value defined_value::operator - () const
{
    assert( is_sane() );
    defined_value v( -value_, exponent_ );
    return v;
}

// ----------------------------------------------------------------------------

defined_value defined_value::absolute() const
{
    assert( is_sane() );
    const long double v = std::abs( value_ );
    defined_value result( v, exponent_ );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::truncate() const
{
    assert( is_sane() );
    const long double v = std::trunc( value_ );
    defined_value result( v, exponent_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value defined_value::remainder(
    const significant_value & that ) const
{
    assert( is_sane() );
    const long double v = std::remainder( value_, that.get_exact_value() );
    calculated_value result( v, that.get_digit_count() );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::remainder( const defined_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    const long double v = std::remainder( value_, that.get_value() );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value defined_value::operator / (
    const significant_value & that ) const
{
    assert( is_sane() );
    if ( that.get_exact_value() == 0.0L )
    {
        throw std::invalid_argument(
            "Division by zero error in defined_value::operator /" );
    }
    const long double v = value_ / that.get_exact_value();
    calculated_value result( v, that.get_digit_count() );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::operator / ( const defined_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    if ( that.value_ == 0.0L )
    {
        throw std::invalid_argument(
            "Division by zero error in defined_value::operator /" );
    }
    defined_value result( value_ / that.value_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value defined_value::operator * (
    const significant_value & that ) const
{
    assert( is_sane() );
    const long double v = value_ * that.get_exact_value();
    calculated_value result( v, that.get_digit_count() );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::operator * ( const defined_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    defined_value result( value_ * that.value_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value defined_value::operator - (
    const significant_value & that ) const
{
    assert( is_sane() );
    const long double v = value_ - that.get_exact_value();
    calculated_value result( v, that.get_digit_count() );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::operator - ( const defined_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    defined_value result( value_ - that.value_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value defined_value::operator + ( const significant_value & that ) const
{
    assert( is_sane() );
    const long double v = value_ + that.get_exact_value();
    calculated_value result( v, that.get_digit_count() );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::operator + ( const defined_value & that ) const
{
    assert( is_sane() );
    defined_value result( value_ + that.value_ );
    return result;
}

// ----------------------------------------------------------------------------

bool defined_value::equals( long double value, long double tolerance ) const
{
    assert( is_sane() );
    helper::validate_input_value( value );
    helper::validate_input_value( tolerance );

    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( value_ != 0.0L ) && ( std::abs( value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }

    const bool is_equal = helper::are_nearly_equal( value_, value, tolerance );
    return is_equal;
}

// ----------------------------------------------------------------------------

bool defined_value::equals( long double value ) const
{
    assert( is_sane() );
    const bool nearly_equal = helper::are_nearly_equal(
        value_, helper::validate_input_value( value ) );
    return nearly_equal;
}

// ----------------------------------------------------------------------------

bool defined_value::equals( const defined_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    const bool nearly_equal = helper::are_nearly_equal( value_, that.value_ );
    return nearly_equal;
}

// ----------------------------------------------------------------------------

bool defined_value::equals( const significant_value & that ) const
{
    assert( is_sane() );
    const bool isEqual = that.equals( *this );
    return isEqual;
}

// ----------------------------------------------------------------------------

bool defined_value::equals( const defined_value & that,
    long double tolerance ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    helper::validate_input_value( tolerance );

    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( value_ != 0.0L ) && ( std::abs( value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( that.value_ != 0.0L ) && ( std::abs( that.value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, that.value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }

    const bool is_equal= helper::are_nearly_equal( value_, that.value_, tolerance );
    return is_equal;
}

// ----------------------------------------------------------------------------

bool defined_value::less_than( long double value ) const
{
    assert( is_sane() );
    const bool is_less_than = helper::is_less_than(
        value_, helper::validate_input_value( value ) );
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool defined_value::less_than( const defined_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    const bool is_less_than = helper::is_less_than( value_, that.value_ );
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool defined_value::less_than( long double value, long double tolerance ) const
{
    assert( is_sane() );
    helper::validate_input_value( value );
    helper::validate_input_value( tolerance );

    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( value_ != 0.0L ) && ( std::abs( value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }

    const bool is_less_than = helper::is_less_than( value_, value, tolerance );
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool defined_value::less_than( const significant_value & that ) const
{
    assert( is_sane() );
    const bool is_less_than = that.greater_than( *this );
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool defined_value::less_than( const defined_value & that,
    long double tolerance ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    helper::validate_input_value( tolerance );

    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( value_ != 0.0L ) && ( std::abs( value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( that.value_ != 0.0L ) && ( std::abs( that.value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, that.value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }

    const bool is_less_than = helper::is_less_than(
        value_, that.value_, tolerance );
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool defined_value::greater_than( long double value,
    long double tolerance ) const
{
    assert( is_sane() );
    helper::validate_input_value( value );
    helper::validate_input_value( tolerance );

    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( value_ != 0.0L ) && ( std::abs( value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }

    const bool more_than = helper::is_greater_than( value_, value, tolerance );
    return more_than;
}

// ----------------------------------------------------------------------------

bool defined_value::greater_than( long double value ) const
{
    assert( is_sane() );
    const bool more_than = helper::is_greater_than(
        value_, helper::validate_input_value( value ) );
    return more_than;
}

// ----------------------------------------------------------------------------

bool defined_value::greater_than( const defined_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    const bool more_than = helper::is_greater_than( value_, that.value_ );
    return more_than;
}

// ----------------------------------------------------------------------------

bool defined_value::greater_than( const significant_value & that ) const
{
    assert( is_sane() );
    const bool is_greater_than = that.less_than( *this );
    return is_greater_than;
}

// ----------------------------------------------------------------------------

bool defined_value::greater_than( const defined_value & that,
    long double tolerance ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    helper::validate_input_value( tolerance );

    if ( tolerance < 0.0L )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is less than zero.",
            tolerance );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( value_ != 0.0L ) && ( std::abs( value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }
    if ( ( that.value_ != 0.0L ) && ( std::abs( that.value_ ) < tolerance ) )
    {
        std::array< char, 256 > chars;
        const int bytes = std::snprintf( chars.data(), chars.size(),
            "Error in defined_value::greater_than! Unable to do greater than comparison since tolerance (%Lf) is greater than value (%Lf).",
            tolerance, that.value_ );
        assert( bytes > 0 );        
        throw std::invalid_argument( chars.data() );
    }

    const bool more_than =
        helper::is_greater_than( value_, that.value_, tolerance );
    return more_than;
}

// ----------------------------------------------------------------------------

calculated_value defined_value::to_power_of(
    const significant_value & exponent ) const
{
    assert( is_sane() );
    if ( ( value_ < 0.0L )
      && ( std::abs( exponent.get_exact_value() ) < 1.0L ) )
    {
        throw std::invalid_argument(
            "Error. Cannot calculate power of negative numbers where absolute value of power is less than 1.0" ); 
    }
    const long double v = std::pow( value_, exponent.get_exact_value() );
    calculated_value result( v, exponent.get_digit_count() );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::to_power_of(
    const defined_value & exponent ) const
{
    assert( is_sane() );
    if ( ( value_ < 0.0L ) && ( std::abs( exponent.value_ ) < 1.0L ) )
    {
        throw std::invalid_argument(
            "Error. Cannot calculate power of negative numbers where absolute value of power is less than 1.0" ); 
    }
    const long double v = std::pow( value_, exponent.value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::square_root() const
{
    assert( is_sane() );
    if ( value_ < 0.0L )
    {
        throw std::invalid_argument(
            "Error. Cannot calculate the square root of a negative number." ); 
    }
    const long double v = std::sqrt( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::cube_root() const
{
    assert( is_sane() );
    const long double v = std::cbrt( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::sine() const
{
    assert( is_sane() );
    const long double v = std::sin( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::cosine() const
{
    assert( is_sane() );
    const long double v = std::cos( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::tangent() const
{
    assert( is_sane() );
    const long double v = std::tan( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::arc_sine() const
{
    assert( is_sane() );
    const long double v = std::asin( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::arc_cosine() const
{
    assert( is_sane() );
    const long double v = std::acos( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::arc_tangent() const
{
    assert( is_sane() );
    const long double v = std::atan( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::hyper_sine() const
{
    assert( is_sane() );
    const long double v = std::sinh( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::hyper_cosine() const
{
    assert( is_sane() );
    const long double v = std::cosh( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::hyper_tangent() const
{
    assert( is_sane() );
    const long double v = std::tanh( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::hyper_arc_sine() const
{
    assert( is_sane() );
    const long double v = std::asinh( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::hyper_arc_cosine() const
{
    assert( is_sane() );
    const long double v = std::acosh( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::hyper_arc_tangent() const
{
    assert( is_sane() );
    const long double v = std::atanh( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::e_to_power_of() const
{
    assert( is_sane() );
    const long double v = std::exp( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::e_to_power_of_then_subtract_1() const
{
    assert( is_sane() );
    const long double v = std::expm1( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::two_to_power_of() const
{
    assert( is_sane() );
    const long double v = std::exp2( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::natural_log_of() const
{
    assert( is_sane() );
    const long double v = std::log( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::base_10_log_of() const
{
    assert( is_sane() );
    const long double v = std::log10( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value defined_value::base_2_log_of() const
{
    assert( is_sane() );
    const long double v = std::log2( value_ );
    defined_value result( v );
    return result;
}

// ----------------------------------------------------------------------------

defined_value & defined_value::swap( defined_value & that )
{
    assert( is_sane() );
    assert( that.is_sane() );
    if ( &that != this )
    {
        std::swap( value_, that.value_ );
        std::swap( exponent_, that.exponent_ );
    }
    return *this;
}

// ----------------------------------------------------------------------------

std::string defined_value::to_string( format_style formatting,
    rounding_style rounding, bool show_decimal ) const
{
    assert( is_sane() );
    std::string result = helper::to_string( value_, exponent_, formatting,
        rounding, show_decimal );
    return result;
}

// ----------------------------------------------------------------------------

std::string defined_value::to_string( unsigned int digits,
    format_style formatting, rounding_style rounding, bool show_decimal ) const
{
    assert( is_sane() );
    helper::validate_digit_count( digits );
    std::string result = helper::to_string( value_, exponent_, digits,
        formatting, rounding, show_decimal );
    return result;
}

// ----------------------------------------------------------------------------

bool defined_value::is_sane() const
{
    assert( this != nullptr );
    const int numberType = std::fpclassify( value_ );
    assert( numberType != FP_INFINITE );
    assert( numberType != FP_NAN );
    assert( numberType != FP_SUBNORMAL );
    assert( exponent_ >= LDBL_MIN_10_EXP );
    assert( exponent_ <= LDBL_MAX_10_EXP );
    return true;
}

// ----------------------------------------------------------------------------

std::ostream & operator << ( std::ostream & os, const defined_value & value )
{
    const std::string buffer = value.to_string();
    os << buffer;
    return os;
}

// ----------------------------------------------------------------------------

} // end namespace
