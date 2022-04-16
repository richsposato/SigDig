// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#include "measured_value.hpp"

#include <cassert>
#include <cmath>

#include <stdexcept>

#ifdef DEBUG
    #include <iostream>
#endif

#include "helper.hpp"

namespace sigdig {

// ----------------------------------------------------------------------------

measured_value::measured_value( long double value  ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( long double value, unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( long value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( long value, unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( unsigned long value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( unsigned long value, unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( const char * value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( const char * value, unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( const std::string & value ) :
    significant_value( value )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( const std::string & value,
    unsigned int digits ) :
    significant_value( value, digits )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( const measured_value & that ) :
    significant_value( that )
{
}

// ----------------------------------------------------------------------------

measured_value::measured_value( long double value, unsigned int digits,
    int exponent, int least_sigdig_exponent ) :
    significant_value( value, digits, exponent, least_sigdig_exponent )
{
}

// ----------------------------------------------------------------------------

measured_value::~measured_value()
{
    // No need to call is_sane since base class destructor will do that.
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( long double value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( long double value,
    unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( long value, unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( unsigned long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( unsigned long value,
    unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( const char * value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( const char * value,
    unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( const std::string & value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( const std::string & value,
    unsigned int digits )
{
    significant_value::assign( value, digits );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::assign( const measured_value & that )
{
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::operator = ( long double value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::operator = ( long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::operator = ( unsigned long value )
{
    significant_value::assign( value );
    return *this;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::operator = ( const measured_value & that )
{
    assert( is_sane() );
    assert( that.is_sane() );
    if ( this != &that )
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

measured_value measured_value::operator - () const
{
    assert( is_sane() );
    measured_value difference( -value_, digits_, most_sigdig_exponent_,
        least_sigdig_exponent_ );
    return difference;
}

// ----------------------------------------------------------------------------

measured_value measured_value::absolute() const
{
    assert( is_sane() );
    const long double v = std::abs( value_ );
    measured_value result( v, digits_, most_sigdig_exponent_,
        least_sigdig_exponent_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::truncate() const
{
    assert( is_sane() );
    const long double v = std::trunc( value_ );
    const int least_sigdig_exponent = 0;
    const int digits = most_sigdig_exponent_ + 1;
    measured_value result( v, digits, most_sigdig_exponent_,
        least_sigdig_exponent );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::square_root() const
{
    assert( is_sane() );
    if ( value_ < 0.0L )
    {
        throw std::invalid_argument(
            "Error. Cannot calculate the square root of a negative number." ); 
    }
    const long double v = std::sqrt( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::cube_root() const
{
    assert( is_sane() );
    const long double v = std::cbrt( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::sine() const
{
    assert( is_sane() );
    const long double v = std::sin( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::cosine() const
{
    assert( is_sane() );
    const long double v = std::cos( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::tangent() const
{
    assert( is_sane() );
    const long double v = std::tan( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::arc_sine() const
{
    assert( is_sane() );
    if ( ( value_ < -1.0 ) || ( value_ > 1.0 ) )
    {
        throw std::domain_error( "Error! Value for arc_sine must be from -1.0 to 1.0." );
    }
    const long double v = std::asin( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::arc_cosine() const
{
    assert( is_sane() );
    if ( ( value_ < -1.0 ) || ( value_ > 1.0 ) )
    {
        throw std::domain_error( "Error! Value for arc_cosine must be from -1.0 to 1.0." );
    }
    const long double v = std::acos( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::arc_tangent() const
{
    assert( is_sane() );
    const long double v = std::atan( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::hyper_sine() const
{
    assert( is_sane() );
    if ( ( value_ > helper::max_sinh_value ) || ( value_ < -helper::max_sinh_value ) )
    {
        throw std::domain_error( "Error! Absolute value for hyper_sine may not be greater than 11357.0F." );
    }
    const long double v = std::sinh( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::hyper_cosine() const
{
    assert( is_sane() );
    if ( ( value_ > helper::max_sinh_value ) || ( value_ < -helper::max_sinh_value ) )
    {
        throw std::domain_error( "Error! Absolute value for hyper_cosine may not be greater than 11357.0F." );
    }
    const long double v = std::cosh( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::hyper_tangent() const
{
    assert( is_sane() );
    const long double v = std::tanh( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::hyper_arc_sine() const
{
    assert( is_sane() );
    const long double v = std::asinh( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::hyper_arc_cosine() const
{
    assert( is_sane() );
    if ( value_ < 1.0F )
    {
        throw std::domain_error( "Error! Value for hyper_arc_cosine may not be less than 1.0." );
    }
    const long double v = std::acosh( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::hyper_arc_tangent() const
{
    assert( is_sane() );
    if ( ( value_ <= 1.0F ) || ( value_ >= 1.0F ) )
    {
        throw std::domain_error( "Error! Absolute value for hyper_arc_tangent must be less than 1.0." );
    }
    const long double v = std::atanh( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::e_to_power_of() const
{
    assert( is_sane() );
    const long double v = std::exp( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::e_to_power_of_then_subtract_1() const
{
    assert( is_sane() );
    const long double v = std::expm1( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::two_to_power_of() const
{
    assert( is_sane() );
    const long double v = std::exp2( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::natural_log_of() const
{
    assert( is_sane() );
    const long double v = std::log( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::base_10_log_of() const
{
    assert( is_sane() );
    const long double v = std::log10( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value measured_value::base_2_log_of() const
{
    assert( is_sane() );
    const long double v = std::log2( value_ );
    measured_value result( v, digits_ );
    return result;
}

// ----------------------------------------------------------------------------

measured_value & measured_value::swap( measured_value & that )
{
    // No need to call is_sane since base class swap function calls is_sane.
    significant_value::swap( that );
    return *this;
}

// ----------------------------------------------------------------------------

} // end namespace
