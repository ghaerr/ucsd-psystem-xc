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

#ifndef UCSDPSYS_PRETTY_EXPRESSION_TERNARY_PRETTY_H
#define UCSDPSYS_PRETTY_EXPRESSION_TERNARY_PRETTY_H

#include <lib/expression/ternary.h>

class translator_littoral; // forward

/**
  * The expression_ternary_littoral class is used to represent the processing
  * necessary for littoral print a ternary expression (e1?e2:e3).
  */
class expression_ternary_littoral:
    public expression_ternary
{
public:
    typedef boost::shared_ptr<expression_ternary_littoral> pointer;

    /**
      * The destructor.
      */
    virtual ~expression_ternary_littoral();

private:
    /**
      * The constructor.
      * It is private on purpose, use a #create class method instead.
      *
      * @param cond
      *     The control expression.  It must be a boolean value.
      * @param lhs
      *     The value to use if cond is true.
      * @param rhs
      *     The value to use if cond is false.
      * @param littoral
      *     The translation context we are working within.
      */
    expression_ternary_littoral(const expression::pointer &cond,
        const expression::pointer &lhs, const expression::pointer &rhs,
        translator_littoral *littoral);

public:
    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      *
      * @param cond
      *     The control expression.  It must be a boolean value.
      * @param lhs
      *     The value to use if cond is true.
      * @param rhs
      *     The value to use if cond is false.
      * @param littoral
      *     The translation context we are working within.
      */
    static pointer create(const expression::pointer &cond,
        const expression::pointer &lhs, const expression::pointer &rhs,
        translator_littoral *littoral);

protected:
    // See base class for documentation.
    expression::pointer optimize(void) const;

    // See base class for documentation.
    expression::pointer clone(const location &locn) const;

    // See base class for documentation.
    void pre_order_traversal(int pprec) const;

    // See base class for documentation.
    void quest_order_traversal(int pprec) const;

    // See base class for documentation.
    void colon_order_traversal(int pprec) const;

    // See base class for documentation.
    void post_order_traversal(int pprec) const;

    // See base class for documentation.
    bool is_constant(void) const;

private:
    /**
      * The littoral instance variable is used to remeber the translation
      * context we are working within.
      */
    translator_littoral &littoral;

    /**
      * The default constructor.  Do not use.
      */
    expression_ternary_littoral();

    /**
      * The copy constructor.  Do not use.
      *
      * @param rhs
      *     The right hand side of the initialisation.
      */
    expression_ternary_littoral(const expression_ternary_littoral &rhs);

    /**
      * The assignment operator.  Do not use.
      *
      * @param rhs
      *     The right hand side of the assignment.
      */
    expression_ternary_littoral &operator=(
        const expression_ternary_littoral &rhs);
};

#endif // UCSDPSYS_PRETTY_EXPRESSION_TERNARY_PRETTY_H
// vim: set ts=8 sw=4 et :
