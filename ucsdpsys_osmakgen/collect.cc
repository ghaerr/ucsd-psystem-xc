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

#include <stdio.h>
#include <lib/config.h>
#include <lib/ac/string.h>

#include <ucsdpsys_osmakgen/collect.h>


void
collect_output_of(const rcstring &command, rcstring_list &result)
{
    FILE *fp = popen(command.c_str(), "r");
    for (;;)
    {
        char line[2000];
        if (!fgets(line, sizeof(line), fp))
            break;
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[--len] = 0;
        if (len > 0)
            result.push_back(line);
    }
    pclose(fp);
}


// vim: set ts=8 sw=4 et :
