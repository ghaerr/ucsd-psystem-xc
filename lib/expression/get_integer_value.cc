//
// UCSD p-System cross compiler
// Copyright (C) 2006, 2007, 2010, 2012 Peter Miller
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

#include <lib/ac/assert.h>
#include <lib/ac/typeinfo>

#include <lib/debug.h>
#include <lib/expression/integer.h>


long
expression::get_integer_value()
    const
{
    DEBUG(1, "class = %s", typeid(*this).name());
    assert(!"derived class should override this method, "
        "or you forgot to call optimize() first.");
    return 0;
}


// vim: set ts=8 sw=4 et :
