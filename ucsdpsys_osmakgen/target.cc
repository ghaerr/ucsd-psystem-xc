//
// UCSD p-System cross compiler
// Copyright (C) 2010-2012 Peter Miller
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

#include <lib/config.h>

#include <ucsdpsys_osmakgen/target.h>


target::~target()
{
}


target::target(const rcstring &filename) :
    op(output::factory(filename))
{
}


void
target::set_default_host(const rcstring &)
{
    printf
    (
        "this target does not support the --host option"
    );
    exit(1);
}


void
target::set_default_arch(const rcstring &)
{
    printf
    (
        "this target does not support the --architecture option"
    );
    exit(1);
}


void
target::no_blurb(void)
{
    printf
    (
        "this target does not support the --no-blurb option"
    );
    exit(1);
}


void
target::set_notice(const rcstring &)
{
    printf
    (
        "this target does not support the --copyright option"
    );
    exit(1);
}


void
target::set_version(const rcstring &)
{
    printf
    (
        "this target does not support the --revision option"
    );
    exit(1);
}


// vim: set ts=8 sw=4 et :
