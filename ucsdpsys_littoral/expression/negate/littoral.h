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

#ifndef UCSDPSYS_PRETTY_EXPRESSION_NEGATE_PRETTY_H
#define UCSDPSYS_PRETTY_EXPRESSION_NEGATE_PRETTY_H

#include <lib/expression/negate.h>

class translator_littoral; // forward

/**
  * The expression_negate_littoral class is used to represent littoral
  * printing an arithmetic negation expression.
  */
class expression_negate_littoral:
    public expression_negate
{
public:
    typedef boost::shared_ptr<expression_negate_littoral> pointer;

    /**
      * The destructor.
      */
    virtual ~expression_negate_littoral();

private:
    /**
      * The constructor.
      */
    expression_negate_littoral(const expression::pointer &arg,
        translator_littoral *cntxt);

public:
    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      */
    static pointer create(const expression::pointer &arg,
        translator_littoral *cntxt);

protected:
    // See base class for documentation.
    void pre_order_traversal(int pprec) const;

    // See base class for documentation.
    void post_order_traversal(int pprec) const;

    // See base class for documentation.
    expression::pointer optimize(void) const;

    // See base class for documentation.
    expression::pointer clone(const location &locn) const;

    // See base class for documentation.
    long get_integer_value(void) const;

private:
    /**
      * The littoral instance variable is used to remember where to send
      * our littoral source code.
      */
    translator_littoral &littoral;

    /**
      * The default constructor.  Do not use.
      */
    expression_negate_littoral();

    /**
      * The copy constructor.  Do not use.
      */
    expression_negate_littoral(const expression_negate_littoral &);

    /**
      * The assignment operator.  Do not use.
      */
    expression_negate_littoral &operator=(const expression_negate_littoral &);
};

#endif // UCSDPSYS_PRETTY_EXPRESSION_NEGATE_PRETTY_H
// vim: set ts=8 sw=4 et :
