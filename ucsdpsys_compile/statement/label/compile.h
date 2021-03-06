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

#ifndef UCSDPSYS_COMPILE_STATEMENT_LABEL_COMPILE_H
#define UCSDPSYS_COMPILE_STATEMENT_LABEL_COMPILE_H

#include <lib/statement/label.h>

class translator_compile; // forward

/**
  * The statement_label_compile class is used to represent
  * the code generation required for the label statement.
  */
class statement_label_compile:
    public statement_label
{
public:
    typedef boost::shared_ptr<statement_label_compile> pointer;

    /**
      * The destructor.
      */
    virtual ~statement_label_compile();

private:
    /**
      * The default constructor.
      * It is private on purpose, use a #create class method instead.
      *
      * @param sym
      *     The label symbol being defined
      * @param body
      *     The statement following the label.
      * @param code
      *     The translator context we are working within.
      */
    statement_label_compile(const symbol::pointer &sym,
        const statement::pointer &body, translator_compile *code);

public:
    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      *
      * @param sym
      *     The label symbol being defined
      * @param body
      *     The statement following the label.
      * @param code
      *     The translator context we are working within.
      */
    static pointer create(const symbol::pointer &sym,
        const statement::pointer &body, translator_compile *code);

private:
    translator_compile &code;

    /**
      * The default constructor.  Do not use.
      */
    statement_label_compile();

    /**
      * The copy constructor.  Do not use.
      *
      * @param rhs
      *     The right hand side of the initialisation.
      */
    statement_label_compile(const statement_label_compile &rhs);

    /**
      * The assignment operator.  Do not use.
      *
      * @param rhs
      *     The right hand side of the assignment.
      */
    statement_label_compile &operator=(const statement_label_compile &rhs);
};

#endif // UCSDPSYS_COMPILE_STATEMENT_LABEL_COMPILE_H
// vim: set ts=8 sw=4 et :
