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

#include <ucsdpsys_assemble/expression/special/a.h>


expression_special_a::~expression_special_a()
{
}


expression_special_a::expression_special_a(const location &locn) :
    expression_special(locn)
{
}


expression_special_a::pointer
expression_special_a::create(const location &locn)
{
    return pointer(new expression_special_a(locn));
}


rcstring
expression_special_a::get_name()
    const
{
    return "a";
}


expression::pointer
expression_special_a::optimize(void)
    const
{
    return create(get_location());
}


expression::pointer
expression_special_a::clone(const location &locn)
    const
{
    return create(locn);
}


// vim: set ts=8 sw=4 et :
