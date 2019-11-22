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

#ifndef UCSDPSYS_COMPILE_EXPRESSION_STORE_H
#define UCSDPSYS_COMPILE_EXPRESSION_STORE_H

#include <lib/expression.h>

class symbol; // forward
class translator_compile; // forward

/**
  * The expression_store class is used to represent an abstract
  * expression which stores its argument into the given address.
  */
class expression_store:
    public expression
{
public:
    /**
      * The destructor.
      */
    virtual ~expression_store();

    /**
      * The constructor.
      *
      * @param from
      *     The value to be stored into the address pointed at.
      */
    expression_store(const expression::pointer &from);

protected:
    // See base class for documentation.
    void traversal(int pprec) const;

    // See base class for documentation.
    void logical_traversal(int pprec, label::pointer &true_branch,
        label::pointer &false_branch, bool fall_through_preference) const;

    // See base class for documentation.
    int get_precedence() const;

    // See base class for documentation.
    type::pointer get_type() const;

    // See base class for documentation.
    bool is_lvalue() const;

    // See base class for documentation.
    side_effect_t has_side_effect() const;

    /**
      * The pre_order_traversal methoid is called by the traversal
      * method immediately before the from expression is traversed.
      */
    virtual void pre_order_traversal() const;

    /**
      * The post_order_traversal methoid is called by the traversal
      * method immediately after the from expression is traversed.
      */
    virtual void post_order_traversal() const;

    /**
      * The get_from method is used to obtain the right hand side of the
      * assignment, the value to be stored.
      */
    expression::pointer get_from() const { return from; }

private:
    /**
      * The from instance variable is used to remember the value to be
      * stored.
      */
    expression::pointer from;

    /**
      * The default constructor.  Do not use.
      */
    expression_store();

    /**
      * The copy constructor.  Do not use.
      */
    expression_store(const expression_store &);

    /**
      * The assignment operator.  Do not use.
      */
    expression_store &operator=(const expression_store &);
};

#endif // UCSDPSYS_COMPILE_EXPRESSION_STORE_H
// vim: set ts=8 sw=4 et :