//
// UCSD p-System cross compiler
// Copyright (C) 2010, 2012 Peter Miller
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or (at
// you option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program. If not, see <http://www.gnu.org/licenses/>
//

#ifndef LIB_SEGVERSION_H
#define LIB_SEGVERSION_H

#include <lib/rcstring.h>

enum segversion_t
{
    segversion_pre_ii_1 = 0,
    segversion_ii_1 = 1,
    segversion_3_0 = 2,
    segversion_apple_1_3 = 6
};

/**
  * The getversion_name function is used to decode a version code
  * into a version name string.
  */
rcstring segversion_name(segversion_t value);

#endif // LIB_SEGVERSION_H
// vim: set ts=8 sw=4 et :
