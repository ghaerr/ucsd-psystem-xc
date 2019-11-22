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

#ifndef UCSDPSYS_ASSEMBLE_OPCODE_PSEUDO_ARCH_H
#define UCSDPSYS_ASSEMBLE_OPCODE_PSEUDO_ARCH_H

#include <ucsdpsys_assemble/opcode/pseudo.h>

/**
  * The opcode_pseudo_arch class is used to represent
  * the ".arch" pseudo-opcode.
  */
class opcode_pseudo_arch:
    public opcode_pseudo
{
public:
    typedef boost::shared_ptr<opcode_pseudo_arch> pointer;

    /**
      * The destructor.
      */
    virtual ~opcode_pseudo_arch();

    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      *
      * @param context
      *     The assemly context we are working within.
      */
    static pointer create(assembler *context);

protected:
    // See base class for documentation.
    void interpret(const expression_list &args);

    // See base class for documentation.
    rcstring get_name(void) const;

    // See base class for documentation.
    kind_t get_kind(void) const;

    // See base class for documentation.
    bool next_argument_always_a_string(void) const;

private:
    /**
      * The constructor.
      * It is private on purpose, use the #create class method instead.
      *
      * @param context
      *     The assemly context we are working within.
      */
    opcode_pseudo_arch(assembler *context);

    /**
      * The default constructor.  Do not use.
      */
    opcode_pseudo_arch();

    /**
      * The copy constructor.  Do not use.
      *
      * @param rhs
      *     The right hand side of the initialisation.
      */
    opcode_pseudo_arch(const opcode_pseudo_arch &rhs);

    /**
      * The assignment operator.  Do not use.
      *
      * @param rhs
      *     The right hand side of the assignment.
      */
    opcode_pseudo_arch &operator=(const opcode_pseudo_arch &rhs);
};

#endif // UCSDPSYS_ASSEMBLE_OPCODE_PSEUDO_ARCH_H
// vim: set ts=8 sw=4 et :