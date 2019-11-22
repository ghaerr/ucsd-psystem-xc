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

#include <lib/expression/list.h>
#include <lib/pcode.h>

#include <ucsdpsys_compile/translator/compile.h>
#include <ucsdpsys_compile/expression/writeln/long_integer.h>


expression_writeln_long_integer::~expression_writeln_long_integer()
{
}


expression_writeln_long_integer::expression_writeln_long_integer(
    const expression::pointer &a_value,
    const expression::pointer &a_width,
    translator_compile *a_code
) :
    expression_writeln(a_value, a_width),
    code(a_code)
{
    code->need_segment(DECOPS_SEG_NUM);
}


expression::pointer
expression_writeln_long_integer::create(const expression::pointer &a_value,
    const expression::pointer &a_width, translator_compile *a_code)
{
    return
        pointer(new expression_writeln_long_integer(a_value, a_width, a_code));
}


expression::pointer
expression_writeln_long_integer::function_call_expression_factory(
    const expression::pointer &file) const
{
    expression_list args;
    expression::pointer ep =
        code->name_expression(file->get_location(), "sys:fwritedec");
    args.push_back(ep);
    args.push_back(file);
    args.push_back(get_value());
    args.push_back(get_width());
    return ep->function_call_expression_factory(args);
}


rcstring
expression_writeln_long_integer::lisp_representation(void)
    const
{
    return
        (
            "(writeln-long-integer "
        +
            get_value()->lisp_representation()
        +
            " "
        +
            get_width()->lisp_representation()
        +
            ")"
        );
}


expression::pointer
expression_writeln_long_integer::optimize(void)
    const
{
    return create(get_value()->optimize(), get_width()->optimize(), code);
}


expression::pointer
expression_writeln_long_integer::clone(const location &locn)
    const
{
    return create(get_value()->clone(locn), get_width()->clone(locn), code);
}


// vim: set ts=8 sw=4 et :
