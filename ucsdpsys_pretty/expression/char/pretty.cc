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

#include <lib/ac/ctype.h>

#include <ucsdpsys_pretty/expression/char/pretty.h>
#include <ucsdpsys_pretty/translator/pretty.h>


expression_char_pretty::~expression_char_pretty()
{
}


expression_char_pretty::expression_char_pretty(
    const location &a_locn,
    unsigned char a_value,
    translator_pretty *cntxt
) :
    expression_char(a_locn, a_value),
    pretty(*cntxt)
{
}


expression_char_pretty::pointer
expression_char_pretty::create(const location &a_locn, unsigned char a_value,
    translator_pretty *cntxt)
{
    return pointer(new expression_char_pretty(a_locn, a_value, cntxt));
}


void
expression_char_pretty::traversal(int)
    const
{
    unsigned char c = get_integer_value();
    if (c == '\'')
        pretty.print_token("''''");
    else if (isprint(c))
        pretty.print_token(rcstring::printf("'%c'", c));
    else
        pretty.print_token(rcstring::printf("chr(%d)", c));
}


expression::pointer
expression_char_pretty::optimize(void)
    const
{
    return create(get_location(), get_integer_value(), &pretty);
}


expression::pointer
expression_char_pretty::clone(const location &locn)
    const
{
    return create(locn, get_integer_value(), &pretty);
}


// vim: set ts=8 sw=4 et :
