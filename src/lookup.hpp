// Copyright Richard D. Sposato (c) 2022
//
// Permission to use, copy, modify, distribute and sell this software for any  purpose is hereby granted under
// the terms stated in the MIT License, provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in supporting documentation.

#ifndef SIGDIG_LOOKUP_HPP
#define SIGDIG_LOOKUP_HPP

#pragma once

namespace sigdig
{

// This is meant to be an internal header file. It is not meant to be included by source files outside of SigDig.

// ----------------------------------------------------------------------------

class lookup
{
public:

    static int calculate_exponent( long double value );

    static long double lookup_tolerance( int exponent );

	static long double lookup_ceiling_offset( int exponent );

};

// ----------------------------------------------------------------------------

}

#endif
