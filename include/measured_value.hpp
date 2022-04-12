// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#pragma once

#ifndef SIGDIG_MEASURED_VALUE_HPP
#define SIGDIG_MEASURED_VALUE_HPP

#include <string>

#include "significant_value.hpp"

namespace sigdig {

// ----------------------------------------------------------------------------

class measured_value : public significant_value
{
public:

    explicit measured_value( long double value = 0.0L );
    explicit measured_value( long value );
    explicit measured_value( unsigned long value );
    explicit measured_value( const char * value );
    explicit measured_value( const std::string & value );

    measured_value( long double value, unsigned int digits );
    measured_value( long value, unsigned int digits );
    measured_value( unsigned long value, unsigned int digits );
    measured_value( const char * value, unsigned int digits );
    measured_value( const std::string & value, unsigned int digits );
    measured_value( const measured_value & that );

    ~measured_value();

    measured_value & swap( measured_value & that );

    measured_value & assign( long double value );
    measured_value & assign( long double value, unsigned int digits );
    measured_value & assign( long value );
    measured_value & assign( long value, unsigned int digits );
    measured_value & assign( unsigned long value );
    measured_value & assign( unsigned long value, unsigned int digits );
    measured_value & assign( const char * value );
    measured_value & assign( const char * value, unsigned int digits );
    measured_value & assign( const std::string & value );
    measured_value & assign( const std::string & value, unsigned int digits );
    measured_value & assign( const measured_value & that );

    measured_value & operator = ( long double value );
    measured_value & operator = ( long value );
    measured_value & operator = ( unsigned long value );
    measured_value & operator = ( const char * value );
    measured_value & operator = ( const std::string & value );
    measured_value & operator = ( const measured_value & that );

    /// Declare the operator- function in base class as usable for this class to prevent shadowing.
    using significant_value::operator -;

    /// Unary minus operator returns the negative of this value.
    measured_value operator-() const;

    measured_value absolute() const;

    /// Returns nearest integer not greater than value. (Round down to integer closest to zero.)
    measured_value truncate() const;

    // Power functions.
    measured_value square_root() const;
    measured_value cube_root() const;

    // Trigonometry functions.

    measured_value sine() const;
    measured_value cosine() const;
    measured_value tangent() const;
    measured_value arc_sine() const;
    measured_value arc_cosine() const;
    measured_value arc_tangent() const;

    // Hyperbolic Trigonometry functions.

    measured_value hyper_sine() const;
    measured_value hyper_cosine() const;
    measured_value hyper_tangent() const;
    measured_value hyper_arc_sine() const;
    measured_value hyper_arc_cosine() const;
    measured_value hyper_arc_tangent() const;

    // Exponent and Log functions.

    measured_value e_to_power_of() const;
    measured_value e_to_power_of_then_subtract_1() const;
    measured_value two_to_power_of() const;
    measured_value natural_log_of() const;
    measured_value base_10_log_of() const;
    measured_value base_2_log_of() const;

private:

    measured_value( long double value, unsigned int digits,
        int exponent, int leastSigDig );

};

// ----------------------------------------------------------------------------

} // end namespace

#endif
