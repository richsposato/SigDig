// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#include "significant_value.hpp"

#include <cassert>
#include <cmath>

#include <stdexcept>

#ifdef DEBUG
    #include <iostream>
#endif

#include "helper.hpp"
#include "lookup.hpp"
#include "calculated_value.hpp"
#include "defined_value.hpp"

namespace sigdig {

// ----------------------------------------------------------------------------

significant_value::significant_value( long double value ) :
    value_( helper::validate_input_value( value ) ),
    digits_( utility::count_significant_digits( value ) ),
    most_sigdig_exponent_( lookup::calculate_exponent( value ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( long double value,
    unsigned int digits ) :
    value_ ( helper::validate_input_value( value ) ),
    digits_( helper::validate_digit_count( digits ) ),
    most_sigdig_exponent_( lookup::calculate_exponent( value ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( long value ) :
    value_( static_cast< long double >( value ) ),
    digits_( utility::count_significant_digits( value ) ),
    most_sigdig_exponent_( utility::calculate_exponent( value ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( long value, unsigned int digits ) :
    value_( static_cast< long double >( value ) ),
    digits_( helper::validate_digit_count( digits ) ),
    most_sigdig_exponent_( utility::calculate_exponent( value ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( unsigned long value ) :
    value_( static_cast< long double >( value ) ),
    digits_( utility::count_significant_digits( value ) ),
    most_sigdig_exponent_( utility::calculate_exponent( value ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( unsigned long value,
    unsigned int digits ) :
    value_( static_cast< long double >( value ) ),
    digits_( helper::validate_digit_count( digits ) ),
    most_sigdig_exponent_( utility::calculate_exponent( value ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( const char * value ) :
    value_( 0.0L ),
    digits_( 0 ),
    most_sigdig_exponent_( 0 ),
    least_sigdig_exponent_( 0 )
{
    utility::count_digits_in_string( value, value_, digits_,
        most_sigdig_exponent_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( const char * value,
    unsigned int digits ) :
    value_( helper::validate_input_value( value ) ),
    digits_( helper::validate_digit_count( digits ) ),
    most_sigdig_exponent_( lookup::calculate_exponent( value_ ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( const std::string & value ) :
    value_( 0.0L ),
    digits_( 0 ),
    most_sigdig_exponent_( 0 ),
    least_sigdig_exponent_( 0 )
{
    utility::count_digits_in_string( value.c_str(), value_, digits_,
        most_sigdig_exponent_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( const std::string & value,
    unsigned int digits ) :
    value_( helper::validate_input_value( value.c_str() ) ),
    digits_( helper::validate_digit_count( digits ) ),
    most_sigdig_exponent_( lookup::calculate_exponent( value_ ) ),
    least_sigdig_exponent_( most_sigdig_exponent_ - digits_ + 1 )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( const significant_value & that ) :
    value_ ( that.value_ ),
    digits_( that.digits_ ),
    most_sigdig_exponent_( that.most_sigdig_exponent_ ),
    least_sigdig_exponent_( that.least_sigdig_exponent_ )
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::significant_value( long double value, unsigned int digits,
    int exponent, int least_sigdig_exponent ) :
    value_( value ),
    digits_( digits ),
    most_sigdig_exponent_( exponent ),
    least_sigdig_exponent_( least_sigdig_exponent )
{
    // There is no need to call either helper::validate_input_value() or
    // helper::validate_digit_count() since whatever called this protected
    // function should have provided correct input values. The is_sane()
    // function will check for validity anyway.
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

significant_value::~significant_value()
{
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( long double value )
{
    assert( is_sane() );
    // Call the function to count the digits and assign the exponent before
    // assigning other data members. That function might throw an exception, so
    // by calling it first, this function provides the strong (no-change)
    // exception safety level.
    digits_ = utility::count_significant_digits(
        helper::validate_input_value( value ), most_sigdig_exponent_ );
    value_ = value;
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( long double value, unsigned int digits )
{
    assert( is_sane() );
    // Call the function to validate the value and the digits before assigning
    // other data members. That function might throw an exceptions, so by
    // calling it first, this function provides the strong (no-change)
    // exception safety level.
    helper::validate_input_value( value, digits );
    most_sigdig_exponent_ = lookup::calculate_exponent( value );
    digits_ = digits;
    value_ = value;
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( long value )
{
    assert( is_sane() );
    // Call the function to count the digits before assigning the other data
    // members. That functions might throw an exception, so by calling it first,
    // this function provides the strong (no-change) exception safety level.
    digits_ = utility::count_significant_digits( value );
    most_sigdig_exponent_ = utility::calculate_exponent( value );
    value_ = static_cast< long double >( value );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( long value, unsigned int digits )
{
    assert( is_sane() );
    // Call the function to validate the digits before assigning other values.
    // That function might throw an exception, so by calling it first, this
    // function provides the strong (no-change) exception safety level.
    digits_ = helper::validate_digit_count( digits );
    most_sigdig_exponent_ = utility::calculate_exponent( value );
    value_ = static_cast< long double >( value );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( unsigned long value )
{
    assert( is_sane() );
    digits_ = utility::count_significant_digits( value );
    most_sigdig_exponent_ = utility::calculate_exponent( value );
    value_ = static_cast< long double >( value );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( unsigned long value, unsigned int digits )
{
    assert( is_sane() );
    // Call the function to validate the digits before assigning other values.
    // That function might throw an exception, so by calling it first, this
    // function provides the strong (no-change) exception safety level.
    digits_ = helper::validate_digit_count( digits );
    most_sigdig_exponent_ = utility::calculate_exponent( value );
    value_ = static_cast< long double >( value );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( const char * value )
{
    assert( is_sane() );
    // Call the function to validate the string before assigning other values.
    // That function might throw an exception, so by calling it first, this
    // function provides the strong (no-change) exception safety level.
    utility::count_digits_in_string( value, value_, digits_,
        most_sigdig_exponent_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( const char * value, unsigned int digits )
{
    assert( is_sane() );
    // Call the functions to validate the digit count and convert value from a
    // string before assigning other values. Those functions might throw
    // exceptions, so by calling then first, this function provides the strong
    // (no-change) exception safety level.
    const unsigned int temp_digits = helper::validate_digit_count( digits );
    const long double temp_value = helper::validate_input_value( value );
    most_sigdig_exponent_ = lookup::calculate_exponent( temp_value );
    digits_ = temp_digits;
    value_ = temp_value;
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( const std::string & value )
{
    assert( is_sane() );
    // Call the function to validate the string before assigning other values.
    // That function might throw an exception, so by calling it first, this
    // function provides the strong (no-change) exception safety level.
    utility::count_digits_in_string( value.c_str(), value_, digits_,
        most_sigdig_exponent_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

void significant_value::assign( const std::string & value,
    unsigned int digits )
{
    assert( is_sane() );
    // Call the functions to validate the digit count and convert value from a
    // string before assigning other values. Those functions might throw
    // exceptions, so by calling then first, this function provides the strong
    // (no-change) exception safety level.
    digits_ = helper::validate_digit_count( digits );
    value_ = helper::validate_input_value( value.c_str() );
    most_sigdig_exponent_ = lookup::calculate_exponent( value_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
}

// ----------------------------------------------------------------------------

bool significant_value::equals( long double value,
    long double tolerance ) const
{
    helper::validate_input_value( value );
    helper::validate_input_value( tolerance );
    assert( is_sane() );

    const long double lower_end = value_ - tolerance;
    const bool is_less_than = value < lower_end;
    if ( is_less_than )
    {
        return false;
    }
    const long double upper_end = value_ + tolerance;
    const bool is_more_than = value > upper_end;
    return !is_more_than;
}

// ----------------------------------------------------------------------------

bool significant_value::equals( long double value, unsigned int digits ) const
{
    helper::validate_input_value( value, digits );
    assert( is_sane() );
    const int below_least_sigdig_exponent =
        most_sigdig_exponent_ - static_cast< int >( digits );
    const long double tolerance =
        lookup::lookup_tolerance( below_least_sigdig_exponent );
    const long double lower_end = value_ - tolerance;
    const bool is_less_than = value < lower_end;
    if ( is_less_than )
    {
        return false;
    }
    const long double upper_end = value_ + tolerance;
    const bool is_more_than = value > upper_end;
    return !is_more_than;
}

// ----------------------------------------------------------------------------

bool significant_value::equals( const significant_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    const long double this_tolerance =
        lookup::lookup_tolerance( least_sigdig_exponent_ - 1 );
    const long double that_tolerance =
        lookup::lookup_tolerance( that.least_sigdig_exponent_ - 1 );
    const long double this_upper_end = value_ + this_tolerance;
    const long double that_lower_end = that.value_ - that_tolerance;
    const bool that_is_more_than = this_upper_end < that_lower_end;
    if ( that_is_more_than )
    {
        return false;
    }
    const long double this_lower_end = value_ - this_tolerance;
    const long double that_upper_end = that.value_ + that_tolerance;
    const bool that_is_less_than = that_upper_end < this_lower_end;
    return !that_is_less_than;
}

// ----------------------------------------------------------------------------

bool significant_value::equals( const defined_value & that ) const
{
    // No need to call is_sane since this calls another equals function that
    // checks for sanity.
    const long double value = that.get_value();
    const bool is_equal = equals( value, digits_ );
    return is_equal;
}

// ----------------------------------------------------------------------------

bool significant_value::less_than( long double value,
    long double tolerance ) const
{
    helper::validate_input_value( value );
    helper::validate_input_value( tolerance );
    assert( is_sane() );
    const long double upper_end = value_ + tolerance;
    const bool is_less_than = upper_end < value;
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool significant_value::less_than( long double value,
    unsigned int digits ) const
{
    helper::validate_input_value( value, digits );
    assert( is_sane() );
    const int below_least_sigdig_exponent =
        most_sigdig_exponent_ - static_cast< int >( digits );
    const long double tolerance =
        lookup::lookup_tolerance( below_least_sigdig_exponent );
    const long double upper_end = value_ + tolerance;
    const bool is_less_than = upper_end < value;
#ifdef DEBUG
    std::cout << "value_: [" << value_ << "] \t below_least_sigdig_exponent: [" << below_least_sigdig_exponent
        << "] \t tolerance: [" << tolerance << ']' << std::endl;
    std::cout << "value: [" << value << "] \t upper_end: [" << upper_end << "] \t is_less_than: [" << is_less_than << ']' << std::endl;
#endif
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool significant_value::less_than( const significant_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    const long double this_tolerance =
        lookup::lookup_tolerance( least_sigdig_exponent_ - 1 );
    const long double that_tolerance =
        lookup::lookup_tolerance( that.least_sigdig_exponent_ - 1 );
    const long double this_upper_end = value_ + this_tolerance;
    const long double that_upper_end = that.value_ - that_tolerance;
    const bool this_is_less_than = this_upper_end < that_upper_end;
    return this_is_less_than;
}

// ----------------------------------------------------------------------------

bool significant_value::less_than( const defined_value & that ) const
{
    // No need to call is_sane since this calls another less_than function that
    // checks for sanity.
    const long double value = that.get_value();
    const bool is_less_than = less_than( value, digits_ );
    return is_less_than;
}

// ----------------------------------------------------------------------------

bool significant_value::greater_than( long double value,
    long double tolerance ) const
{
    helper::validate_input_value( value );
    helper::validate_input_value( tolerance );
    assert( is_sane() );
    const long double lower_end = value_ - tolerance;
    const bool is_more_than = value < lower_end;
    return is_more_than;
}

// ----------------------------------------------------------------------------

bool significant_value::greater_than( long double value,
    unsigned int digits ) const
{
    helper::validate_input_value( value, digits );
    assert( is_sane() );
    const int below_least_sigdig_exponent =
        most_sigdig_exponent_ - static_cast< int >( digits );
    const long double tolerance =
        lookup::lookup_tolerance( below_least_sigdig_exponent );
    const long double lower_end = value_ - tolerance;
    const bool is_more_than = value < lower_end;
    return is_more_than;
}

// ----------------------------------------------------------------------------

bool significant_value::greater_than( const significant_value & that ) const
{
    assert( is_sane() );
    assert( that.is_sane() );
    const long double this_tolerance =
        lookup::lookup_tolerance( least_sigdig_exponent_ -  1 );
    const long double that_tolerance =
        lookup::lookup_tolerance( that.least_sigdig_exponent_ - 1 );
    const long double this_lower_end = value_ - this_tolerance;
    const long double that_upper_end = that.value_ + that_tolerance;
    const bool this_is_more_than = that_upper_end < this_lower_end;
    return this_is_more_than;
}

// ----------------------------------------------------------------------------

bool significant_value::greater_than( const defined_value & that ) const
{
    // No need to call is_sane since this calls another greater_than function
    // that checks for sanity.
    const long double value = that.get_value();
    const bool is_more_than = greater_than( value, digits_ );
    return is_more_than;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::remainder(
    const significant_value & divisor ) const
{
    assert( is_sane() );
    const unsigned int digits = std::min( divisor.get_digit_count(), digits_ );
    const long double v = std::remainder( value_, digits );
    calculated_value result( v, divisor.get_digit_count() );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::remainder(
    const defined_value & divisor ) const
{
    assert( is_sane() );
    const long double v = std::remainder( value_, divisor.get_value() );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator / (
    const significant_value & divisor ) const
{
    assert( is_sane() );
    const unsigned int digits = std::min( digits_, divisor.get_digit_count() );
    calculated_value quotient( value_ / divisor.get_exact_value(), digits );
    return quotient;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator / (
    const defined_value & divisor ) const
{
    assert( is_sane() );
    calculated_value quotient( value_ / divisor.get_value(), digits_ );
    return quotient;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator * (
    const significant_value & factor ) const
{
    assert( is_sane() );
    const unsigned int digits = std::min( digits_, factor.get_digit_count() );
    calculated_value product( value_ * factor.get_exact_value(), digits );
    return product;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator * (
    const defined_value & factor ) const
{
    assert( is_sane() );
    calculated_value product( value_ * factor.get_value(), digits_ );
    return product;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator - (
    const significant_value & subtrahend ) const
{
    assert( is_sane() );
    const long double difference = value_ - subtrahend.get_exact_value();
    const int highest_least_sigdig = std::max(
        least_sigdig_exponent_, subtrahend.get_least_sigdig_exponent() );
    const int exponent = lookup::calculate_exponent( difference );
    const int digits = exponent - highest_least_sigdig + 1;
    calculated_value result(
        difference, digits, exponent, highest_least_sigdig );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator - (
    const defined_value & subtrahend ) const
{
    assert( is_sane() );
    const long double difference = value_ - subtrahend.get_value();
    const int exponent = lookup::calculate_exponent( difference );
    const int digits = exponent - least_sigdig_exponent_ + 1;
    calculated_value result(
        difference, digits, exponent, least_sigdig_exponent_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator + (
    const significant_value & addend ) const
{
    assert( is_sane() );
    const long double sum = value_ + addend.get_exact_value();
    const int highest_least_sigdig =
        std::max( least_sigdig_exponent_, addend.get_least_sigdig_exponent() );
    const int exponent = lookup::calculate_exponent( sum );
    const int digits = exponent - highest_least_sigdig + 1;
    calculated_value result( sum, digits, exponent, highest_least_sigdig );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::operator + (
    const defined_value & addend ) const
{
    assert( is_sane() );
    const long double sum = value_ + addend.get_value();
    const int exponent = lookup::calculate_exponent( sum );
    const int digits = exponent - least_sigdig_exponent_ + 1;
    calculated_value result( sum, digits, exponent, least_sigdig_exponent_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::to_power_of(
    const defined_value & exponent ) const
{
    assert( is_sane() );
    if ( ( value_ < 0.0L ) && ( std::abs( exponent.get_value() ) < 1.0L ) )
    {
        throw std::invalid_argument(
            "Error. Cannot calculate power of negative numbers where absolute value of power is less than 1.0" ); 
    }
    const long double v = std::pow( value_, exponent.get_value() );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value significant_value::to_power_of(
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
    const unsigned int digits =
        std::min( digits_, exponent.get_digit_count() );
    calculated_value result( v, digits );
    return result;
}

// ----------------------------------------------------------------------------

long double significant_value::get_value( int digits,
    rounding_style rounding ) const
{
    assert( is_sane() );
    const std::string result =
        to_string( digits, format_style::decimal_fixed, rounding );
    char * place = nullptr;
    const long double value = std::strtold( result.c_str(), &place );
    return value;
}

// ----------------------------------------------------------------------------

std::string significant_value::to_string( format_style formatting,
    rounding_style rounding, bool show_decimal ) const
{
    assert( is_sane() );
    std::string result = helper::to_string( value_, most_sigdig_exponent_,
        digits_, formatting, rounding, show_decimal );
    return result;
}

// ----------------------------------------------------------------------------

std::string significant_value::to_string( unsigned int digits,
    format_style formatting, rounding_style rounding, bool show_decimal ) const
{
    assert( is_sane() );
    helper::validate_digit_count( digits );
    std::string result = helper::to_string( value_, most_sigdig_exponent_,
        digits, formatting, rounding, show_decimal );
    return result;
}

// ----------------------------------------------------------------------------

long double significant_value::get_tolerance() const
{
    assert( is_sane() );
    const long double tolerance =
        lookup::lookup_tolerance( least_sigdig_exponent_ - 1 );
    return tolerance;
}

// ----------------------------------------------------------------------------

long double significant_value::get_tolerance_lower() const
{
    assert( is_sane() );
    const long double tolerance = get_tolerance();
    const long double lower_end = value_ - tolerance;
    return lower_end;
}

// ----------------------------------------------------------------------------

long double significant_value::get_tolerance_upper() const
{
    assert( is_sane() );
    const long double tolerance = get_tolerance();
    const long double upper_end = value_ + tolerance;
    return upper_end;
}

// ----------------------------------------------------------------------------

void significant_value::swap( significant_value & that )
{
    assert( is_sane() );
    assert( that.is_sane() );
    std::swap( value_, that.value_ );
    std::swap( digits_, that.digits_ );
    std::swap( most_sigdig_exponent_, that.most_sigdig_exponent_ );
    std::swap( least_sigdig_exponent_, that.least_sigdig_exponent_ );
}

// ----------------------------------------------------------------------------

bool significant_value::is_sane() const
{
    assert( this != nullptr );
    const int number_type = std::fpclassify( value_ );
    assert( number_type != FP_INFINITE );
    assert( number_type != FP_NAN );
    assert( number_type != FP_SUBNORMAL );
    assert( most_sigdig_exponent_ >= least_sigdig_exponent_ );
    assert( most_sigdig_exponent_ >= helper::lowest_exponent );
    assert( most_sigdig_exponent_ <= helper::highest_exponent );
    assert( digits_ >= 1 );
    assert( digits_ <= helper::max_range_of_digits_for_long_double );
    const int least_sigdig_exponent = most_sigdig_exponent_ - digits_ + 1;
    assert( least_sigdig_exponent_ == least_sigdig_exponent );
    return true;
}

// ----------------------------------------------------------------------------

std::ostream & operator << ( std::ostream & os, const significant_value & value )
{
    const std::string buffer = value.to_string();
    os << buffer;
    return os;
}

// ----------------------------------------------------------------------------

} // end namespace
