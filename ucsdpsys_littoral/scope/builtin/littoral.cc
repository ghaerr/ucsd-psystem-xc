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

#include <ucsdpsys_littoral/scope/builtin/littoral.h>
#include <ucsdpsys_littoral/symbol/variable/normal/littoral.h>
#include <ucsdpsys_littoral/symbol/expression/constant/littoral.h>


scope_builtin_littoral::~scope_builtin_littoral()
{
}


scope_builtin_littoral::scope_builtin_littoral(translator_littoral *a_context) :
    context(a_context)
{
}


scope_builtin_littoral::pointer
scope_builtin_littoral::create(translator_littoral *a_context)
{
    return pointer(new scope_builtin_littoral(a_context));
}


symbol_variable::pointer
scope_builtin_littoral::variable_factory(const variable_name &vname,
    const type::pointer &vtype, int lex_level)
{
    return
        symbol_variable_normal_littoral::create
        (
            vname,
            vtype,
            lex_level,
            symbol_variable::kind_variable,
            context
        );
}


symbol::pointer
scope_builtin_littoral::constant_factory(const variable_name &vname,
    int lex_level, const expression::pointer &value)
{
    return
        symbol_expression_constant_littoral::create
        (
            vname,
            lex_level,
            value,
            context
        );
}


symbol_variable::pointer
scope_builtin_littoral::parameter_factory(const variable_name &vname,
    const type::pointer &vtype, int lex_level)
{
    return
        symbol_variable_normal_littoral::create
        (
            vname,
            vtype,
            lex_level,
            symbol_variable::kind_parameter,
            context
        );
}


// vim: set ts=8 sw=4 et :
