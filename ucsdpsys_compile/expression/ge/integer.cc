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

#include <lib/label.h>
#include <lib/pcode.h>
#include <lib/type.h>
#include <ucsdpsys_compile/expression/boolean/compile.h>
#include <ucsdpsys_compile/expression/ge/integer.h>
#include <ucsdpsys_compile/expression/lt/integer.h>
#include <ucsdpsys_compile/translator/compile.h>


expression_ge_integer::~expression_ge_integer()
{
}


expression_ge_integer::expression_ge_integer(
    const expression::pointer &a_lhs,
    const expression::pointer &a_rhs,
    translator_compile *cntxt
) :
    expression_ge(a_lhs, a_rhs),
    code(*cntxt)
{
}


expression_ge_integer::pointer
expression_ge_integer::create(const expression::pointer &a_lhs,
    const expression::pointer &a_rhs, translator_compile *cntxt)
{
    return pointer(new expression_ge_integer(a_lhs, a_rhs, cntxt));
}


void
expression_ge_integer::post_order_traversal(int)
    const
{
    code.breakpoint(get_location());
    code.emit_byte(GEQI);
}


expression::pointer
expression_ge_integer::optimize(void)
    const
{
    expression::pointer c1 = get_lhs();
    expression::pointer c2 = get_rhs();
    expression::pointer e1 = c1->optimize();
    expression::pointer e2 = c2->optimize();

    assert(e1->get_type() == e2->get_type());
    if (e1->is_constant() && e2->is_constant())
    {
        return
            expression_boolean_compile::create
            (
                get_location(),
                e1->get_integer_value() >= e2->get_integer_value(),
                &code
            );
    }

    return expression_ge_integer::create(e1, e2, &code);
}


expression::pointer
expression_ge_integer::clone(const location &locn)
    const
{
    return create(get_lhs()->clone(locn), get_rhs()->clone(locn), &code);
}


void
expression_ge_integer::logical_traversal(int pprec,
    label::pointer &true_branch, label::pointer &false_branch,
    bool fall_through_preference) const
{
    if (fall_through_preference)
    {
        // code gen positive, FJP to false_branch
        traversal(pprec);
        false_branch->branch_from_here_if_false();
    }
    else
    {
        // code gen negative, FJP to true_branch
        expression::pointer nep =
            expression_lt_integer::create(get_lhs(), get_rhs(), &code);
        nep->traversal(pprec);
        true_branch->branch_from_here_if_false();
    }
}


// vim: set ts=8 sw=4 et :
