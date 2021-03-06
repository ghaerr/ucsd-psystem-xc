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

#include <lib/debug.h>
#include <lib/expression/error.h>
#include <lib/expression/list.h>
#include <lib/pascal/lex.h>
#include <lib/type/integer.h>
#include <lib/type/reference.h>
#include <lib/type/string.h>

#include <ucsdpsys_compile/expression/function.h>
#include <ucsdpsys_compile/expression/function_call/user_defined.h>
#include <ucsdpsys_compile/expression/integer/compile.h>
#include <ucsdpsys_compile/expression/string/compile.h>
#include <ucsdpsys_compile/symbol/function/insert.h>
#include <ucsdpsys_compile/translator/compile.h>


symbol_function_insert::~symbol_function_insert()
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);
}


symbol_function_insert::symbol_function_insert(
    translator_compile *a_code
) :
    symbol_function("insert", location::builtin(), scope::pointer(), -1),
    code(*a_code)
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);

    //
    // procedure insert(sub: string; var strg: string, index: integer);
    //
    name_type_list args;
    {
        variable_name_list names;
        names.push_back(variable_name("needle", location::builtin()));
        type::pointer tp = type_string::create(255);
        args.push_back(name_type(names, tp));
    }
    {
        variable_name_list names;
        names.push_back(variable_name("haystack", location::builtin()));
        type::pointer tp = type_reference::create(type_string::create(255));
        args.push_back(name_type(names, tp));
    }
    {
        variable_name_list names;
        names.push_back(variable_name("insinx", location::builtin()));
        type::pointer tp = type_integer::create();
        args.push_back(name_type(names, tp));
    }
    attach_function_parameters(args);
}


symbol_function_insert::pointer
symbol_function_insert::create(translator_compile *a_code)
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);
    return pointer(new symbol_function_insert(a_code));
}


static int
get_size_of_string(const expression::pointer &ep)
{
    type_string::pointer tsp =
        boost::dynamic_pointer_cast<type_string>(ep->get_type());
    assert(tsp);
    return tsp->get_size();
}


expression::pointer
symbol_function_insert::function_call_expression_factory(
    const expression_list &rhs) const
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);
    expression_list rhs2 = check_parameters(rhs, code);
    if (rhs2.empty())
        return expression_error::create(rhs.get_location());
    assert(rhs2.size() == 4);

    // [1] => needle
    // [2] => haystack
    // [3] => position
    if (rhs2[3]->is_constant())
    {
        expression::pointer ep = rhs2[3];
        int pos = ep->optimize()->get_integer_value();
        int max = get_size_of_string(rhs[2]);
        if (pos < 1 || pos > max)
        {
            pascal_lex_error
            (
                ep->get_location(),
                "insert: parameter three: the position must be in the "
                    "range 1..%d, not %d",
                max,
                pos
            );
            pos = 1;
        }
    }

    expression_list args;
    expression::pointer func =
        code.name_expression(rhs.get_location(), "sys:sinsert");
    args.push_back(func);
    args.push_back(rhs2[1]);
    args.push_back(rhs2[2]);
    expression::pointer ep =
        expression_integer_compile::create
        (
            rhs2[2]->get_location(),
            get_size_of_string(rhs[2]),
            &code
        );
    args.push_back(ep);
    args.push_back(rhs2[3]);
    return expression_function_call_user_defined::create(args, &code);
}


expression::pointer
symbol_function_insert::name_expression_factory(const symbol::pointer &sym,
    const location &where, int)
{
    assert(this == sym.get());
    symbol_function::pointer sfp =
        boost::dynamic_pointer_cast<symbol_function>(sym);
    assert(sfp);
    return expression_function::create(where, sfp, &code);
}


// vim: set ts=8 sw=4 et :
