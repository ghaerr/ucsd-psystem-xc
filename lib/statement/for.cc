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

#include <lib/statement/for.h>


statement_for::~statement_for()
{
}


statement_for::statement_for(
    const expression::pointer &a_var,
    const expression::pointer &a_limit1,
    bool a_descending,
    const expression::pointer &a_limit2,
    const statement::pointer &a_body
) :
    var(a_var),
    limit1(a_limit1),
    descending(a_descending),
    limit2(a_limit2),
    body(a_body)
{
}


bool
statement_for::execution_flows_out(void)
    const
{
    return true;
}


// vim: set ts=8 sw=4 et :
