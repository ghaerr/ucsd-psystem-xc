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

#include <lib/cardinal.h>
#include <lib/expression/error.h>
#include <lib/expression/list.h>
#include <lib/pascal/lex.h>
#include <lib/type/integer.h>
#include <lib/type/long_integer.h>
#include <lib/type/real.h>

#include <ucsdpsys_compile/expression/abs/integer.h>
#include <ucsdpsys_compile/expression/abs/long_integer.h>
#include <ucsdpsys_compile/expression/abs/real.h>
#include <ucsdpsys_compile/expression/function.h>
#include <ucsdpsys_compile/symbol/function/abs.h>
#include <ucsdpsys_compile/translator/compile.h>


symbol_function_abs::~symbol_function_abs()
{
}


symbol_function_abs::symbol_function_abs(translator_compile *cntxt) :
    symbol_function("abs", location::builtin(), scope::pointer(), -1),
    code(*cntxt)
{
    //
    // function abs(number: integer): integer;
    // function abs(number: integer[*]): integer;
    // function abs(number: real): real;
    //
    variable_name_list names;
    names.push_back(variable_name("number", location::builtin()));
    type::pointer tp = type_integer::create();
    name_type_list args;
    args.push_back(name_type(names, tp));
    attach_function_parameters(args);
    attach_return_type(type_integer::create());
}


symbol_function_abs::pointer
symbol_function_abs::create(translator_compile *cntxt)
{
    return pointer(new symbol_function_abs(cntxt));
}


expression::pointer
symbol_function_abs::function_call_expression_factory(
    const expression_list &rhs) const
{
    if (rhs.size() != 2)
    {
        parameter_error_wrong_number(rhs, 1);
        return expression_error::create(rhs.get_location());
    }

    expression::pointer ep = code.call_noparam_func_if_necessary(rhs[1]);

    if (type_integer::is_a(ep))
    {
        return expression_abs_integer::create(ep, &code);
    }
    if (type_long_integer::is_a(ep))
    {
        return expression_abs_long_integer::create(ep, &code);
    }
    if (type_real::is_a(ep))
    {
        return expression_abs_real::create(ep, &code);
    }

    pascal_lex_error
    (
        rhs.get_location(),
        "call of function abs: parameter one: must be of an integer or real "
            "type, not a %s",
        ep->get_description().c_str()
    );
    return expression_error::create(rhs.get_location());
}


expression::pointer
symbol_function_abs::name_expression_factory(const symbol::pointer &sym,
    const location &where, int)
{
    assert(this == sym.get());
    symbol_function::pointer sfp =
        boost::dynamic_pointer_cast<symbol_function>(sym);
    assert(sfp);
    return expression_function::create(where, sfp, &code);
}


// vim: set ts=8 sw=4 et :
