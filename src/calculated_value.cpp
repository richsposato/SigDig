// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#include "calculated_value.hpp"

#include <cassert>
#include <cmath>

#include <stdexcept>

#include "measured_value.hpp"
#include "defined_value.hpp"
#include "helper.hpp"

namespace sigdig {

// ----------------------------------------------------------------------------

calculated_value::calculated_value( long double value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( long double value, unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( long value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( long value, unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( unsigned long value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( unsigned long value,
    unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( const char * value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( const char * value, unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( const std::string & value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( const std::string & value,
    unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( const calculated_value & that ) :
    significant_value( that )
{
}

// ----------------------------------------------------------------------------

calculated_value::calculated_value( long double value, unsigned int digits,
    int exponent, int least_sigdig_exponent ) :
    significant_value( value, digits, exponent, least_sigdig_exponent )
{
}

// ----------------------------------------------------------------------------

calculated_value::~calculated_value()
{
    // No need to call is_sane since base class destructor will do that.
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( long double value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( long double value,
    unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( long value, unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( unsigned long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( unsigned long value,
    unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( const char * value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( const char * value,
    unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( const std::string & value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign(
    const std::string & value, unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::assign( const calculated_value & that )
{
    assert( is_sane() );
    assert( that.is_sane() );
    if ( &that != this )
    {
        value_ = that.value_;
        digits_ = that.digits_;
        most_sigdig_exponent_ = that.most_sigdig_exponent_;
        least_sigdig_exponent_ = that.least_sigdig_exponent_;
    }
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator = ( long double value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator = ( long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator = ( unsigned long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator = ( const char * value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator = ( const std::string & value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator = (
    const calculated_value & that )
{
    assert( is_sane() );
    if ( &that != this )
    {
        value_  = that.value_;
        digits_ = that.digits_;
        most_sigdig_exponent_  = that.most_sigdig_exponent_;
        least_sigdig_exponent_ = that.least_sigdig_exponent_;
        assert( is_sane() );
    }
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator = ( const defined_value & that )
{
    assert( is_sane() );
    value_ = that.get_value();
    digits_ = utility::count_significant_digits( value_ );
    most_sigdig_exponent_ = that.get_most_sigdig_exponent();
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::operator - () const
{
    assert( is_sane() );
    calculated_value negative( -value_, digits_, most_sigdig_exponent_, least_sigdig_exponent_ );
    return negative;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::absolute() const
{
    assert( is_sane() );
    const long double v = std::abs( value_ );
    calculated_value result( v, digits_, most_sigdig_exponent_, least_sigdig_exponent_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::truncate() const
{
    assert( is_sane() );
    const long double v = std::trunc( value_ );
    const int least_sigdig_exponent = 0;
    const int digits = most_sigdig_exponent_ + 1;
    calculated_value result( v, digits, most_sigdig_exponent_, least_sigdig_exponent );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator += (
    const significant_value & addend )
{
    assert( is_sane() );
    const long double sum = value_ + addend.get_exact_value();
    const int exponent = utility::calculate_exponent( sum );
    const int digits = exponent - least_sigdig_exponent_ + 1;
    const int highest_least_sigdig_exponent =
        std::max( least_sigdig_exponent_, addend.get_least_sigdig_exponent() );
    value_ = sum;
    digits_ = digits;
    most_sigdig_exponent_ = exponent;
    least_sigdig_exponent_ = highest_least_sigdig_exponent;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator += (
    const defined_value & addend )
{
    assert( is_sane() );
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a defined value.
    value_ += addend.get_value();
    most_sigdig_exponent_ = utility::calculate_exponent( value_ );
    digits_ = most_sigdig_exponent_ - least_sigdig_exponent_ + 1;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator -= (
    const significant_value & subtrahend )
{
    assert( is_sane() );
    const long double sum = value_ - subtrahend.get_exact_value();
    const int exponent = utility::calculate_exponent( sum );
    const int digits = exponent - least_sigdig_exponent_ + 1;
    const int highest_least_sigdig_exponent = std::max( least_sigdig_exponent_,
        subtrahend.get_least_sigdig_exponent() );
    value_ = sum;
    digits_ = digits;
    most_sigdig_exponent_ = exponent;
    least_sigdig_exponent_ = highest_least_sigdig_exponent;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator -= (
    const defined_value & subtrahend )
{
    assert( is_sane() );
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a defined value.
    value_ -= subtrahend.get_value();
    most_sigdig_exponent_ = utility::calculate_exponent( value_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator *= (
    const significant_value & factor )
{
    assert( is_sane() );
    value_ *= factor.get_exact_value();
    digits_ = std::min( digits_, factor.get_digit_count() );
    most_sigdig_exponent_ = utility::calculate_exponent( value_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator *= (
    const defined_value & factor )
{
    assert( is_sane() );
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a defined value.
    value_ *= factor.get_value();
    most_sigdig_exponent_ = utility::calculate_exponent( value_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator /= (
    const significant_value & divisor )
{
    assert( is_sane() );
    if ( divisor.get_exact_value() == 0.0L )
    {
        throw std::invalid_argument(
            "Division by zero error in calculated_value::operator /=" );
    }
    value_ /= divisor.get_exact_value();
    digits_ = std::min( digits_, divisor.get_digit_count() );
    most_sigdig_exponent_ = utility::calculate_exponent( value_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator /= (
    const defined_value & divisor )
{
    assert( is_sane() );
    if ( divisor.get_value() == 0.0L )
    {
        throw std::invalid_argument(
            "Division by zero error in calculated_value::operator /=" );
    }
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a defined value.
    value_ /= divisor.get_value();
    most_sigdig_exponent_ = utility::calculate_exponent( value_ );
    least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator ++ ()
{
    assert( is_sane() );
    value_ += 1.0L;
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a constant value.
    const int new_exponent = utility::calculate_exponent( value_ );
    if ( most_sigdig_exponent_ != new_exponent )
    {
        most_sigdig_exponent_ = new_exponent;
        least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    }
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::operator -- ()
{
    assert( is_sane() );
    value_ -= 1.0L;
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a constant value.
    const int new_exponent = utility::calculate_exponent( value_ );
    if ( most_sigdig_exponent_ != new_exponent )
    {
        most_sigdig_exponent_ = new_exponent;
        least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    }
    assert( is_sane() );
    return *this;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::operator ++ ( int )
{
    assert( is_sane() );
    calculated_value post( *this );
    value_ += 1.0L;
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a constant value.
    const int new_exponent = utility::calculate_exponent( value_ );
    if ( most_sigdig_exponent_ != new_exponent )
    {
        most_sigdig_exponent_ = new_exponent;
        least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    }
    assert( is_sane() );
    return post;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::operator -- ( int )
{
    assert( is_sane() );
    calculated_value pre( *this );
    value_ -= 1.0L;
    // No need to assign digits_ data member since the number of significant
    // digits does not change during operations with a constant value.
    const int new_exponent = utility::calculate_exponent( value_ );
    if ( most_sigdig_exponent_ != new_exponent )
    {
        most_sigdig_exponent_ = new_exponent;
        least_sigdig_exponent_ = most_sigdig_exponent_ - digits_ + 1;
    }
    assert( is_sane() );
    return pre;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::square_root() const
{
    assert( is_sane() );
    if ( value_ < 0.0L )
    {
        throw std::invalid_argument(
            "Error. Cannot calculate the square root of a negative number." ); 
    }
    const long double v = std::sqrt( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::cube_root() const
{
    assert( is_sane() );
    const long double v = std::cbrt( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::sine() const
{
    assert( is_sane() );
    const long double v = std::sin( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::cosine() const
{
    assert( is_sane() );
    const long double v = std::cos( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::tangent() const
{
    assert( is_sane() );
    const long double v = std::tan( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::arc_sine() const
{
    assert( is_sane() );
    if ( ( value_ < -1.0 ) || ( value_ > 1.0 ) )
    {
        throw std::domain_error( "Error! Value for arc_sine must be from -1.0 to 1.0." );
    }
    const long double v = std::asin( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::arc_cosine() const
{
    assert( is_sane() );
    if ( ( value_ < -1.0 ) || ( value_ > 1.0 ) )
    {
        throw std::domain_error( "Error! Value for arc_cosine must be from -1.0 to 1.0." );
    }
    const long double v = std::acos( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::arc_tangent() const
{
    assert( is_sane() );
    const long double v = std::atan( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::hyper_sine() const
{
    assert( is_sane() );
    if ( ( value_ > helper::max_sinh_value ) || ( value_ < -helper::max_sinh_value ) )
    {
        throw std::domain_error( "Error! Absolute value for hyper_sine may not be greater than 11357.0F." );
    }
    const long double v = std::sinh( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::hyper_cosine() const
{
    assert( is_sane() );
    if ( ( value_ > helper::max_sinh_value ) || ( value_ < -helper::max_sinh_value ) )
    {
        throw std::domain_error( "Error! Absolute value for hyper_cosine may not be greater than 11357.0F." );
    }
    const long double v = std::cosh( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::hyper_tangent() const
{
    assert( is_sane() );
    const long double v = std::tanh( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::hyper_arc_sine() const
{
    assert( is_sane() );
    const long double v = std::asinh( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::hyper_arc_cosine() const
{
    assert( is_sane() );
    if ( value_ < 1.0F )
    {
        throw std::domain_error( "Error! Value for hyper_arc_cosine may not be less than 1.0." );
    }
    const long double v = std::acosh( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::hyper_arc_tangent() const
{
    assert( is_sane() );
    if ( ( value_ <= 1.0F ) || ( value_ >= 1.0F ) )
    {
        throw std::domain_error( "Error! Absolute value for hyper_arc_tangent must be less than 1.0." );
    }
    const long double v = std::atanh( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::e_to_power_of() const
{
    assert( is_sane() );
    const long double v = std::exp( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::e_to_power_of_then_subtract_1() const
{
    assert( is_sane() );
    const long double v = std::expm1( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::two_to_power_of() const
{
    assert( is_sane() );
    const long double v = std::exp2( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::natural_log_of() const
{
    assert( is_sane() );
    const long double v = std::log( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::base_10_log_of() const
{
    assert( is_sane() );
    const long double v = std::log10( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value calculated_value::base_2_log_of() const
{
    assert( is_sane() );
    const long double v = std::log2( value_ );
    calculated_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

calculated_value & calculated_value::swap( calculated_value & that )
{
    // No need to call is_sane since base class swap function calls is_sane.
    significant_value::swap( that );
    return *this;
}

// ----------------------------------------------------------------------------

} // end namespace
