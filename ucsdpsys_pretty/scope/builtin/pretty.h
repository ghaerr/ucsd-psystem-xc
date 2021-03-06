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

#ifndef UCSDPSYS_PRETTY_SCOPE_BUILTIN_PRETTY_H
#define UCSDPSYS_PRETTY_SCOPE_BUILTIN_PRETTY_H

#include <lib/scope/builtin.h>

class translator_pretty; // forward

/**
  * The scope_builtin_pretty class is used to represent
  * the builti-in symbol scope for the pretty printer.
  */
class scope_builtin_pretty:
    public scope_builtin
{
public:
    typedef boost::shared_ptr<scope_builtin_pretty> pointer;

    /**
      * The destructor.
      */
    virtual ~scope_builtin_pretty();

    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      *
      * @param context
      *     The translation context we are working within.
      */
    static pointer create(translator_pretty *context);

protected:
    // See base class for documentation.
    symbol_variable::pointer variable_factory(const variable_name &name,
        const type::pointer &tp, int lex_level);

    // See base class for documentation.
    symbol_variable::pointer parameter_factory(const variable_name &name,
        const type::pointer &tp, int lex_level);

    // See base class for documentation.
    symbol::pointer constant_factory(const variable_name &name,
        int lex_level, const expression::pointer &value);

private:
    /**
      * The constructor.
      * It is private on purpose, use a #create class method instead.
      *
      * @param context
      *     The translation context we are working within.
      */
    scope_builtin_pretty(translator_pretty *context);

    /**
      * The context instance variable is used to remember
      * the translation context we are working within.
      */
    translator_pretty *context;

    /**
      * The default constructor.  Do not use.
      */
    scope_builtin_pretty();

    /**
      * The copy constructor.  Do not use.
      *
      * @param rhs
      *     The right hand side of the initialisation.
      */
    scope_builtin_pretty(const scope_builtin_pretty &rhs);

    /**
      * The assignment operator.  Do not use.
      *
      * @param rhs
      *     The right hand side of the assignment.
      */
    scope_builtin_pretty &operator=(const scope_builtin_pretty &rhs);
};

#endif // UCSDPSYS_PRETTY_SCOPE_BUILTIN_PRETTY_H
// vim: set ts=8 sw=4 et :
