//
// UCSD p-System cross compiler
// Copyright (C) 2010, 2012 Peter Miller
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at
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

#include <lib/ac/stdio.h>
#include <lib/ac/stdlib.h>
#include <lib/ac/string.h>
#include <unistd.h>

#include <lib/debug.h>
#include <lib/version.h>

#include <test_long_integer/grammar.h>


static void
usage(void)
{
    const char *prog = "test_long_integer";
    fprintf(stderr, "Usage: %s [ <infile> [ <outfile> ]]\n", prog);
    fprintf(stderr, "       %s -V\n", prog);
    exit(1);
}


int
main(int argc, char **argv)
{
    for (;;)
    {
        int c = getopt(argc, argv, "dV");
        if (c == EOF)
            break;
        switch (c)
        {
        case 'd':
            ++debug_level;
            break;

        case 'V':
            version_print();
            return 0;

        default:
            usage();
        }
    }
    const char *filename = "-";
    switch (argc - optind)
    {
    case 2:
        if (0 != strcmp(argv[optind + 1], "-"))
            freopen(argv[optind + 1], "w", stdout);
        // Fall through...

    case 1:
        filename = argv[optind];
        break;

    case 0:
        break;

    default:
        usage();
    }

    parse(filename);

    return 0;
}


// vim: set ts=8 sw=4 et :
