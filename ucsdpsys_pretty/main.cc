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

#include <lib/ac/stdio.h>
#include <lib/ac/stdlib.h>
#include <lib/ac/string.h>
#include <lib/ac/getopt.h>
#include <unistd.h>

#include <lib/debug.h>
#include <lib/pascal/lex.h>
#include <lib/rcstring.h>
#include <lib/version.h>

#include <ucsdpsys_pretty/translator/pretty.h>


static void
usage(void)
{
    const char *prog = "ucsdpsys_pretty";
    fprintf(stderr, "Usage: %s [ -y ] <input-file-name>\n", prog);
    fprintf(stderr, "       %s -V\n", prog);
    exit(1);
}


int
main(int argc, char **argv)
{
    rcstring output_file_name;
    bool grammar_debug = false;
    rcstring_list warnings;
    rcstring listing_file_name;
    for (;;)
    {
        static struct option options[] =
        {
            { "debug", 0, 0, 'd' },
            { "feature", 1, 0, 'f' },
            { "include", 1, 0, 'I' },
            { "output", 1, 0, 'o' },
            { "version", 0, 0, 'V' },
            { "warning", 0, 0, 'W' },
            { "grammar-trace", 0, 0, 'y' },
            { 0, 0, 0, 0 }
        };
        int c = getopt_long(argc, argv, "df:I:o:VW:y", options, 0);
        if (c == EOF)
            break;
        switch (c)
        {
        case 'd':
            ++debug_level;
            break;

        case 'f':
            {
                const char *eq = strchr(optarg, '=');
                if (eq)
                {
                    rcstring name(optarg, eq - optarg);
                    rcstring value(eq + 1);
                    warnings.push_back
                    (
                        rcstring::printf
                        (
                            "$feature %s %s",
                            name.c_str(),
                            value.c_str()
                        )
                    );
                }
                else
                {
                    rcstring name = optarg;
                    rcstring value = "true";
                    if (name.downcase().substring(0, 3) == "no-")
                    {
                        name = name.substring(3, name.size() - 3);
                        value = "false";
                    }
                    warnings.push_back("$feature " + name + " " + value);
                }
                warnings.push_back(optarg);
            }
            break;

        case 'I':
            pascal_lex_include_directory(optarg);
            break;

        case 'o':
            freopen(optarg, "w", stdout);
            break;

        case 'V':
            version_print();
            return 0;

        case 'W':
            {
                const char *eq = strchr(optarg, '=');
                if (eq)
                {
                    rcstring name(optarg, eq - optarg);
                    rcstring value(eq + 1);
                    warnings.push_back
                    (
                        rcstring::printf
                        (
                            "$warning %s %s",
                            name.c_str(),
                            value.c_str()
                        )
                    );
                }
                else
                {
                    rcstring name = optarg;
                    rcstring value = "true";
                    if (name.downcase().substring(0, 3) == "no-")
                    {
                        name = name.substring(3, name.size() - 3);
                        value = "false";
                    }
                    warnings.push_back("$warning " + name + " " + value);
                }
                warnings.push_back(optarg);
            }
            break;

        case 'y':
            grammar_debug = true;
            break;

        default:
            usage();
            // NOTREACHED
        }
    }
    if (optind + 1 != argc)
        usage();
    rcstring input_file_name(argv[optind]);

    translator_pretty slurp;

    // set the selected warnings
    for (size_t j = 0; j < warnings.size(); ++j)
        slurp.comment(warnings[j]);

    //
    // Parse the Pascal file and print it out again as Pascal.
    //
    if (grammar_debug)
        slurp.enable_grammar_debug();
    slurp.parse(input_file_name);

    //
    // Write out the pretty text.
    //
    slurp.traversal();
    fflush(stdout);
    return 0;
}


// vim: set ts=8 sw=4 et :
