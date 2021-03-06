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

#ifndef UCSDPSYS_ASSEMBLE_TYPE_LINKSYM_RELATIVE_H
#define UCSDPSYS_ASSEMBLE_TYPE_LINKSYM_RELATIVE_H

#include <lib/expression.h>
#include <lib/type.h>

/**
  * The type_linksym_relative class is used to represent type type of a
  * value that represents a byte address relative to a linker symbol.
  */
class type_linksym_relative:
    public type
{
public:
    typedef boost::shared_ptr<type_linksym_relative> pointer;

    /**
      * The destructor.
      */
    virtual ~type_linksym_relative();

    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      *
      * @param name
      *     The name of the referenced symbol.
      */
    static pointer create(const rcstring &name);

    /**
      * The is_a method is used to determine if the given type is
      * of integer type, or an integer subrange type.
      *
      * @param candidate
      *     The type to be tested
      * @returns
      *     bool; true if it is an integer type, false if not
      */
    static bool is_a(const type::pointer &candidate);

    /**
      * The is_a method is used to determine if the given expression is
      * of integer type, or an integer subrange type.
      *
      * @param candidate
      *     The expression to be tested
      * @returns
      *     bool; true if it is an integer expression, false if not
      */
    static bool is_a(const expression::pointer &candidate);

    rcstring get_symbol_name(void) const { return symbol_name; }

protected:
    // See base class for documentation.
    rcstring get_name(void) const;

    // See base class for documentation.
    rcstring get_pascal_name(void) const;

    // See base class for documentation.
    rcstring get_c_declaration(const rcstring &name) const;

    // See base class for documentation.
    type::pointer get_subtype(void) const;

    // See base class for documentation.
    unsigned get_size_in_bits(void) const;

    // See base class for documentation.
    bool same_type_as(const type::pointer &rhs) const;

    // See base class for documentation.
    bool is_a_variable(void) const;

    // See base class for documentation.
    bool need_late_binding(void) const;

    // See base class for documentation.
    rcstring get_human_readable_representation_of_value(int n) const;

private:
    /**
      * The constructor.
      * It is private on purpose, use a #create class method instead.
      *
      * @param name
      */
    type_linksym_relative(const rcstring &name);

    /**
      * The symbol_name instance variable is used to remember the name
      * of the symbol being referenced.
      */
    rcstring symbol_name;

    /**
      * The default constructor.
      * It is private on purpose, use a #create class method instead.
      */
    type_linksym_relative();

    /**
      * The copy constructor.  Do not use.
      *
      * @param rhs
      *     The right hand side of the initialisation.
      */
    type_linksym_relative(const type_linksym_relative &rhs);

    /**
      * The assignment operator.  Do not use.
      *
      * @param rhs
      *     The right hand side of the assignment.
      */
    type_linksym_relative &operator=(const type_linksym_relative &rhs);
};

#endif // UCSDPSYS_ASSEMBLE_TYPE_LINKSYM_RELATIVE_H
// vim: set ts=8 sw=4 et :
