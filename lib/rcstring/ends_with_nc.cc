//
// UCSD p-System cross compiler
// Copyright (C) 2006, 2007, 2012 Peter Miller
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

#include <lib/ac/string.h>
#include <lib/rcstring.h>


bool
rcstring::ends_with_nc(const rcstring &rhs)
    const
{
    const char *haystack = c_str();
    size_t haystack_len = size();
    const char *needle = rhs.c_str();
    size_t needle_len = rhs.size();
    return
    (
        haystack_len >= needle_len
    &&
        !strncasecmp(haystack + haystack_len - needle_len, needle, needle_len)
    );
}


// vim: set ts=8 sw=4 et :
