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

#include <lib/config.h>
#include <lib/ac/string.h>

#include <ucsdpsys_errors/arch/adaptable.h>


arch_adaptable::~arch_adaptable()
{
}


arch_adaptable::arch_adaptable(mtype_t a_mtype) :
    arch(a_mtype)
{
}


static bool
stdio_stream(const rcstring &fn)
{
    return (fn.empty() || fn == "-");
}


void
arch_adaptable::read_text(const rcstring &filename)
{
    data.clear();
    FILE *fp =
        (
            stdio_stream(filename)
        ?
            stdin
        :
            fopen(filename.c_str(), "r")
        );
    int linum = 0;
    for (;;)
    {
        char line[1000];
        if (!fgets(line, sizeof(line), fp))
            break;
        ++linum;
        if (line[0] == '#')
            continue;
        char *ep = strchr(line, ':');
        if (ep)
        {
            rcstring number = rcstring(line, ep - line).trim();
            rcstring text = rcstring(ep + 1).trim();
            char *end = 0;
            long n = strtol(number.c_str(), &end, 10);
            if (end == number.c_str() || *end)
            {
                printf
                (
                    "%s: %d: error number malformed",
                    filename.c_str(),
                    linum
                );
                exit(1);
            }
            if (n < 0 || (get_string_length() + 2) * n > 32767)
            {
                printf
                (
                    "%s: %d: error number %ld out of range",
                    filename.c_str(),
                    linum,
                    n
                );
                exit(1);
            }
            size_t un = n;
            if (un < data.size() && !data[un].empty())
            {
                printf
                (
                    "%s: %d: error number %ld duplicate",
                    filename.c_str(),
                    linum,
                    n
                );
                exit(1);
            }
            if (text.size() > get_string_length())
            {
                printf
                (
                    "%s: %d: text too long, by %d",
                    filename.c_str(),
                    linum,
                    int(text.size() - get_string_length())
                );
                exit(1);
            }
            while (data.size() <= un)
                data.push_back(rcstring());
            data[un] = text;
        }
        else
        {
            rcstring text = rcstring(line).trim();
            if (!text.empty())
            {
                printf
                (
                    "%s: %d: error number missing",
                    filename.c_str(),
                    linum
                );
                exit(1);
            }
        }
    }
    fclose(fp);
}


unsigned
arch_adaptable::get_string_length(void)
    const
{
    return 40;
}


void
arch_adaptable::read_binary(const rcstring &filename)
{
    FILE *fp =
        (
            stdio_stream(filename)
        ?
            stdin
        :
            fopen(filename.c_str(), "rb")
        );
    data.clear();
    size_t nbytes = 1 + get_string_length();
    if (nbytes & 1)
        ++nbytes;
    assert(nbytes <= 256);
    for (unsigned n = 0; n < 32767; ++n)
    {
        unsigned char line[256];
        size_t m = fread(line, 1, nbytes, fp);
        if (!m)
            break;
        if (m != nbytes) {
            printf("%s: short file", filename.c_str());
            exit(1);
        }
        size_t len = line[0];
        if (len + 1 > nbytes)
            len = nbytes - 1;
        rcstring text = rcstring(line + 1, len).trim();
        data.push_back(text);
    }
    fclose(fp);
}


void
arch_adaptable::write_text(const rcstring &filename)
    const
{
    FILE *fp =
        (
            stdio_stream(filename)
        ?
            stdout
        :
            fopen(filename.c_str(), "w")
        );
    for (size_t j = 0; j < data.size(); ++j)
    {
        rcstring s = data[j];
        if (!s.empty())
            fprintf(fp, "%3d: %s\n", int(j), s.c_str());
    }
    fflush(fp);
    if (fp != stdout)
        fclose(fp);
}


void
arch_adaptable::write_binary(const rcstring &filename)
    const
{
    FILE *fp =
        (
            stdio_stream(filename)
        ?
            stdout
        :
            fopen(filename.c_str(), "wb")
        );
    size_t nbytes = 1 + get_string_length();
    if (nbytes & 1)
        ++nbytes;
    assert(nbytes <= 256);
    for (size_t j = 0; j < data.size(); ++j)
    {
        rcstring s = data[j];
        if (s.empty())
            s = " ";
        size_t len = s.size();
        if (len + 1 > nbytes)
            len = nbytes - 1;
        unsigned char line[256];
        memset(line, 0, nbytes);
        line[0] = len;
        memcpy(line + 1, s.c_str(), len);
        fwrite(line, 1, nbytes, fp);
    }
    fflush(fp);
    if (fp != stdout)
        fclose(fp);
}


// vim: set ts=8 sw=4 et :
