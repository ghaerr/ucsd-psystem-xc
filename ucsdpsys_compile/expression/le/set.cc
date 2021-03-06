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
#include <lib/pcode.h>

#include <ucsdpsys_compile/expression/boolean/compile.h>
#include <ucsdpsys_compile/expression/le/set.h>
#include <ucsdpsys_compile/expression/set/compile.h>
#include <ucsdpsys_compile/translator/compile.h>


expression_le_set::~expression_le_set()
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);
}


expression_le_set::expression_le_set(
    const expression::pointer &a_lhs,
    const expression::pointer &a_rhs,
    translator_compile *cntxt
) :
    expression_le(a_lhs, a_rhs),
    code(*cntxt)
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);
    DEBUG(1, "lhs %s", a_lhs->get_type()->get_name().c_str());
    DEBUG(1, "rhs %s", a_rhs->get_type()->get_name().c_str());
}


expression_le_set::pointer
expression_le_set::create(const expression::pointer &a_lhs,
    const expression::pointer &a_rhs, translator_compile *cntxt)
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);
    expression::pointer lhs2 = a_lhs;
    expression::pointer rhs2 = a_rhs;
    cntxt->fix_binary_set_operands(lhs2, rhs2);

    pointer result(new expression_le_set(lhs2, rhs2, cntxt));
    DEBUG(1, "}");
    return result;
}


void
expression_le_set::post_order_traversal(int)
    const
{
    DEBUG(1, "%s", __PRETTY_FUNCTION__);
    code.breakpoint(get_location());
    code.emit_byte(LEQ);
    code.emit_byte(OP_CMP_SET);
}


expression::pointer
expression_le_set::optimize(void)
    const
{
    DEBUG(1, "%s {", __PRETTY_FUNCTION__);
    expression::pointer e1 = get_lhs()->optimize();
    expression::pointer e2 = get_rhs()->optimize();

    assert(e1->get_type() == e2->get_type());
    if (e1->is_constant() && e2->is_constant())
    {
        expression_set_compile::pointer lesp =
            boost::dynamic_pointer_cast<expression_set_compile>(e1);
        assert(lesp);
        expression_set_compile::pointer resp =
            boost::dynamic_pointer_cast<expression_set_compile>(e2);
        assert(resp);
        bool result = (lesp->get_value() <= resp->get_value());
        expression::pointer ep =
            expression_boolean_compile::create(get_location(), result, &code);
        DEBUG(1, "}");
        return ep;
    }

    if (e1->is_empty_set())
    {
        // ([] <= rhs) is always true
        expression::pointer ep =
            expression_boolean_compile::create(get_location(), true, &code);
        DEBUG(1, "}");
        return ep;
    }

    expression::pointer result = create(e1, e2, &code);
    DEBUG(1, "}");
    return result;
}


expression::pointer
expression_le_set::clone(const location &locn)
    const
{
    return create(get_lhs()->clone(locn), get_rhs()->clone(locn), &code);
}


void
expression_le_set::logical_traversal(int pprec,
    label::pointer &true_branch, label::pointer &false_branch,
    bool fall_through_preference) const
{
    DEBUG(1, "%s {", __PRETTY_FUNCTION__);
    traversal(pprec);
    if (fall_through_preference)
    {
        false_branch->branch_from_here_if_false();
    }
    else
    {
        // Note: you cannot manipulate this to get an FJP, because !(set <= set)
        // is not the same as (set > set) as it would be for numbers.
        true_branch->branch_from_here_if_true();
    }
    DEBUG(1, "}");
}


// vim: set ts=8 sw=4 et :
