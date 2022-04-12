// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#pragma once

#ifndef SIGDIG_CALCULATED_VALUE_HPP
#define SIGDIG_CALCULATED_VALUE_HPP

#include <string>

#include "significant_value.hpp"

namespace sigdig {

class measured_value;
class defined_value;

// ----------------------------------------------------------------------------

class calculated_value : public significant_value
{
public:

    explicit calculated_value( long double value = 0.0L );
    explicit calculated_value( long value );
    explicit calculated_value( unsigned long value );
    explicit calculated_value( const char * value );
    explicit calculated_value( const std::string & value );

    calculated_value( long double value, unsigned int digits );
    calculated_value( long value, unsigned int digits );
    calculated_value( unsigned long value, unsigned int digits );
    calculated_value( const char * value, unsigned int digits );
    calculated_value( const std::string & value, unsigned int digits );
    calculated_value( const calculated_value & that );

    ~calculated_value();

    calculated_value & swap( calculated_value & that );

    calculated_value & assign( long double value );
    calculated_value & assign( long double value, unsigned int digits );
    calculated_value & assign( long value );
    calculated_value & assign( long value, unsigned int digits );
    calculated_value & assign( unsigned long value );
    calculated_value & assign( unsigned long value, unsigned int digits );
    calculated_value & assign( const char * value );
    calculated_value & assign( const char * value, unsigned int digits );
    calculated_value & assign( const std::string & value );
    calculated_value & assign( const std::string & value, unsigned int digits );
    calculated_value & assign( const calculated_value & that );

    calculated_value & operator = ( long double value );
    calculated_value & operator = ( long value );
    calculated_value & operator = ( unsigned long value );
    calculated_value & operator = ( const char * value );
    calculated_value & operator = ( const std::string & value );

    calculated_value & operator = ( const calculated_value & that );
    calculated_value & operator = ( const defined_value & that );

    /// Declare the operator- function in base class as usable for this class to prevent shadowing.
    using significant_value::operator-;

    /// Unary minus operator returns the negative of this value.
    calculated_value operator-() const;

    calculated_value absolute() const;

    /// Returns nearest integer not greater than value. (Round down to integer closest to zero.)
    calculated_value truncate() const;

    calculated_value & operator += ( const significant_value & addend );
    calculated_value & operator += ( const defined_value & addend );

    calculated_value & operator -= ( const significant_value & subtrahend );
    calculated_value & operator -= ( const defined_value & subtrahend );

    calculated_value & operator *= ( const significant_value & factor );
    calculated_value & operator *= ( const defined_value & factor );

    calculated_value & operator /= ( const significant_value & divisor );
    calculated_value & operator /= ( const defined_value & divisor );

    calculated_value & operator ++ ();
    calculated_value & operator -- ();
    calculated_value   operator ++ ( int );
    calculated_value   operator -- ( int );

    // Power functions.
    calculated_value square_root() const;
    calculated_value cube_root() const;

    // Trigonometry functions.

    calculated_value sine() const;
    calculated_value cosine() const;
    calculated_value tangent() const;
    calculated_value arc_sine() const;
    calculated_value arc_cosine() const;
    calculated_value arc_tangent() const;

    // Hyperbolic Trigonometry functions.

    calculated_value hyper_sine() const;
    calculated_value hyper_cosine() const;
    calculated_value hyper_tangent() const;
    calculated_value hyper_arc_sine() const;
    calculated_value hyper_arc_cosine() const;
    calculated_value hyper_arc_tangent() const;

    // Exponent and Log functions.

    calculated_value e_to_power_of() const;
    calculated_value e_to_power_of_then_subtract_1() const;
    calculated_value two_to_power_of() const;
    calculated_value natural_log_of() const;
    calculated_value base_10_log_of() const;
    calculated_value base_2_log_of() const;

private:

    friend class significant_value;

    calculated_value( long double value, unsigned int digits, int exponent, int leastSigDig );

};

// ----------------------------------------------------------------------------

} // end namespace

#endif
