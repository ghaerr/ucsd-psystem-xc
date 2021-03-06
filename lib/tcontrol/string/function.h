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

#ifndef LIB_TCONTROL_STRING_FUNCTION_H
#define LIB_TCONTROL_STRING_FUNCTION_H

#include <lib/tcontrol/string.h>

/**
  * The tcontrol_string_function class is used to represent a control
  * comment that calls a function with a single string parameter.
  */
class tcontrol_string_function:
    public tcontrol_string
{
public:
    typedef boost::shared_ptr<tcontrol_string_function> pointer;

    typedef void (*func_p)(const rcstring &);

    /**
      * The destructor.
      */
    virtual ~tcontrol_string_function();

    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      *
      * @param func
      *     The function to be called.
      */
    static pointer create(func_p func);

protected:
    // See base class for documentation.
    void set(const rcstring_list &args);

private:
    /**
      * The func instance variable is used to remember the fucntion to
      * be called with one string argukent.
      */
    func_p func;

    /**
      * The constructor.
      * It is private on purpose, use a #create class method instead.
      *
      * @param func
      *     The function to be called.
      */
    tcontrol_string_function(func_p func);

    /**
      * The default constructor.  Do not use.
      */
    tcontrol_string_function();

    /**
      * The copy constructor.  Do not use.
      *
      * @param rhs
      *     The right hand side of the initialisation.
      */
    tcontrol_string_function(const tcontrol_string_function &rhs);

    /**
      * The assignment operator.  Do not use.
      *
      * @param rhs
      *     The right hand side of the assignment.
      */
    tcontrol_string_function &operator=(const tcontrol_string_function &rhs);
};

#endif // LIB_TCONTROL_STRING_FUNCTION_H
// vim: set ts=8 sw=4 et :
