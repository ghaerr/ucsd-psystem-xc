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

#include <ucsdpsys_assemble/opcode/6502/ply.h>


opcode_6502_ply::~opcode_6502_ply()
{
}


opcode_6502_ply::opcode_6502_ply(assembler *a_context, model_t a_model) :
    opcode_6502(a_context, a_model)
{
}


opcode_6502_ply::pointer
opcode_6502_ply::create(assembler *a_context, model_t a_model)
{
    return pointer(new opcode_6502_ply(a_context, a_model));
}


void
opcode_6502_ply::interpret(const expression_list &args)
{
    if (mode_is_implicit(args, 0x7A))
        model_warning(model_65c02);
    else
        argument_list_error(args);
}


rcstring
opcode_6502_ply::get_name(void)
    const
{
    return "ply";
}


// vim: set ts=8 sw=4 et :
