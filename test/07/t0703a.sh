#!/bin/sh
#
# UCSD p-System cross compiler
# Copyright (C) 2010-2012 Peter Miller
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or (at
# you option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>
#

TEST_SUBJECT="ucsdpsys_osmakgen vs interpreter"
. test_prelude

cat > ok << 'fubar'
/*
 * This file is generated by the ucsdpsys_osmakgen(1) command, from the
 * ucsd-psystem-xc project.  The ucsd-psystem-xc project is distributed under
 * the terms and conditions of the GNU GPL version 3.  As a special exception,
 * the contents of this file are not subject to those terms and conditions.
 */
set mkdir;
set unlink;
if [not [defined DESTDIR]] then DESTDIR = ;

/*
 * values provided by the ./configure script
 */
prefix = @prefix@;
exec_prefix = @exec_prefix@;
datadir = [DESTDIR]@datadir@;
datarootdir = [DESTDIR]@datarootdir@;
sysconfdir = [DESTDIR]@sysconfdir@;

all: stage1.disks;

host = klebsch;

arch = [collect ucsdpsys_osmakgen --arch-from-host [host]];

/*
 * cross compiler flags
 */
XCFLAGS = --arch\=[arch] -Wno-shadow;

/*
 * cross assembler flags
 */
XAFLAGS = --arch\=[arch];

filenames = arch/6502/interpreter/main.asm.text system/main.text;

if [in [host] 6502] then
{

stage1/[host]/codefiles/interpreter/main.asm.code:
        arch/6502/interpreter/main.asm.text
{
    ucsdpsys_assemble [XAFLAGS] -Iarch/6502/interpreter -J. -Jbl -Jblbl -Jblblbl
        -o stage1/[host]/codefiles/interpreter/main.asm.code [resolve
        arch/6502/interpreter/main.asm.text];
}
}

stage1/[host]/codefiles/system/main.code: system/main.text
{
    ucsdpsys_compile [XCFLAGS] -J. -Jbl -Jblbl -Jblblbl -Isystem -o
        stage1/[host]/codefiles/system/main.code [resolve system/main.text];
}

stage1.disks: stage1/[host]/system.vol;

stage2.disks: stage2/[host]/system.vol;

stage3.disks: stage3/[host]/system.vol;

stage1/[host]/diagnostic/system.[host]:
        stage1/[host]/codefiles/interpreter/main.asm.code
{
    cp [resolve stage1/[host]/codefiles/interpreter/main.asm.code]
        stage1/[host]/diagnostic/system.[host];
}

stage1/[host]/system/system.[host]:
        stage1/[host]/codefiles/interpreter/main.asm.code
{
    cp [resolve stage1/[host]/codefiles/interpreter/main.asm.code]
        stage1/[host]/system/system.[host];
}

stage2/[host]/diagnostic/system.[host]:
        stage2/[host]/codefiles/interpreter/main.asm.code
{
    cp [resolve stage2/[host]/codefiles/interpreter/main.asm.code]
        stage2/[host]/diagnostic/system.[host];
}

stage2/[host]/system/system.[host]:
        stage2/[host]/codefiles/interpreter/main.asm.code
{
    cp [resolve stage2/[host]/codefiles/interpreter/main.asm.code]
        stage2/[host]/system/system.[host];
}

stage3/[host]/diagnostic/system.[host]:
        stage3/[host]/codefiles/interpreter/main.asm.code
{
    cp [resolve stage3/[host]/codefiles/interpreter/main.asm.code]
        stage3/[host]/diagnostic/system.[host];
}

stage3/[host]/system/system.[host]:
        stage3/[host]/codefiles/interpreter/main.asm.code
{
    cp [resolve stage3/[host]/codefiles/interpreter/main.asm.code]
        stage3/[host]/system/system.[host];
}

if [exists [resolve host/[host]/interpreter/main.asm.text]] then
{
interpreter_stage1_diagnostic_code = stage1/[host]/diagnostic/system.[host];
interpreter_stage1_system_code = stage1/[host]/system/system.[host];
interpreter_stage2_diagnostic_code = stage2/[host]/diagnostic/system.[host];
interpreter_stage2_system_code = stage2/[host]/system/system.[host];
interpreter_stage3_diagnostic_code = stage3/[host]/diagnostic/system.[host];
interpreter_stage3_system_code = stage3/[host]/system/system.[host];
}
else
{
if [exists [resolve arch/[arch]/interpreter/main.asm.text]] then
{
interpreter_stage1_diagnostic_code = stage1/[host]/diagnostic/system.[host];
interpreter_stage1_system_code = stage1/[host]/system/system.[host];
interpreter_stage2_diagnostic_code = stage2/[host]/diagnostic/system.[host];
interpreter_stage2_system_code = stage2/[host]/system/system.[host];
interpreter_stage3_diagnostic_code = stage3/[host]/diagnostic/system.[host];
interpreter_stage3_system_code = stage3/[host]/system/system.[host];
}
else
{
interpreter_stage1_diagnostic_code = ;
interpreter_stage1_system_code = ;
interpreter_stage2_diagnostic_code = ;
interpreter_stage2_system_code = ;
interpreter_stage3_diagnostic_code = ;
interpreter_stage3_system_code = ;
}
}

stage1/[host]/system/system.pascal: stage1/[host]/codefiles/system/main.code
{
    cp [resolve stage1/[host]/codefiles/system/main.code]
        stage1/[host]/system/system.pascal;
}

/*
 * build stage one system disk image
 */

stage1/[host]/system.vol: [interpreter_stage1_system_code]
        stage1/[host]/system/system.pascal
{
    ucsdpsys_mkfs --arch\=[arch] -B256 --label\=system stage1/[host]/system.vol;
    ucsdpsys_disk --file stage1/[host]/system.vol --text --put [resolve
        [interpreter_stage1_system_code] stage1/[host]/system/system.pascal];
    ucsdpsys_disk --file stage1/[host]/system.vol --crunch --list --sort\=name;
}

stage2/[host]/system/system.pascal: stage2/[host]/codefiles/system/main.code
{
    cp [resolve stage2/[host]/codefiles/system/main.code]
        stage2/[host]/system/system.pascal;
}

/*
 * build stage two system disk image
 */

stage2/[host]/system.vol: [interpreter_stage2_system_code]
        stage2/[host]/system/system.pascal
{
    ucsdpsys_mkfs --arch\=[arch] -B256 --label\=system stage2/[host]/system.vol;
    ucsdpsys_disk --file stage2/[host]/system.vol --text --put [resolve
        [interpreter_stage2_system_code] stage2/[host]/system/system.pascal];
    ucsdpsys_disk --file stage2/[host]/system.vol --crunch --list --sort\=name;
}

stage3/[host]/system/system.pascal: stage3/[host]/codefiles/system/main.code
{
    cp [resolve stage3/[host]/codefiles/system/main.code]
        stage3/[host]/system/system.pascal;
}

/*
 * build stage three system disk image
 */

stage3/[host]/system.vol: [interpreter_stage3_system_code]
        stage3/[host]/system/system.pascal
{
    ucsdpsys_mkfs --arch\=[arch] -B256 --label\=system stage3/[host]/system.vol;
    ucsdpsys_disk --file stage3/[host]/system.vol --text --put [resolve
        [interpreter_stage3_system_code] stage3/[host]/system/system.pascal];
    ucsdpsys_disk --file stage3/[host]/system.vol --crunch --list --sort\=name;
}

clean: clean-files;
clean-files:
    set errok
{
    rm -f stage1/[host]/codefiles/interpreter/main.asm.code;
    rm -f stage1/[host]/codefiles/system/main.code;
    rm -f stage1/[host]/diagnostic/system.[host] stage1/[host]/system.vol;
    rm -f stage1/[host]/system/system.[host] stage1/[host]/system/system.pascal;
    rm -f stage2/[host]/diagnostic/system.[host] stage2/[host]/system.vol;
    rm -f stage2/[host]/system/system.[host] stage2/[host]/system/system.pascal;
    rm -f stage3/[host]/diagnostic/system.[host] stage3/[host]/system.vol;
    rm -f stage3/[host]/system/system.[host] stage3/[host]/system/system.pascal;
}

distclean: clean dist-clean-files dist-clean-dirs;
dist-clean-files:
    set errok
{
    rm -f config.log config.status;
}
dist-clean-dirs:
    set errok
{
    rm -rf stage1;
}

rebuild-makefile:
{
    ucsdpsys_osmakgen [filenames];
}

install: stage1.install;

stage1.install: stage1.disks
{
    mkdir -p [datadir]/ucsd-psystem-os;
    cp -r stage1/[host]/diagnostic [datadir]/ucsd-psystem-os/diagnostic;
    cp [resolve stage1/[host]/diagnostic.vol]
        [datadir]/ucsd-psystem-os/diagnostic.vol;
    cp -r stage1/[host]/system [datadir]/ucsd-psystem-os/system;
    cp [resolve stage1/[host]/system.vol] [datadir]/ucsd-psystem-os/system.vol;
    cp -r stage1/[host]/utility [datadir]/ucsd-psystem-os/utility;
    cp [resolve stage1/[host]/utility.vol]
        [datadir]/ucsd-psystem-os/utility.vol;
}

stage2.install: stage2.disks
{
    mkdir -p [datadir]/ucsd-psystem-os;
    cp -r stage2/[host]/diagnostic [datadir]/ucsd-psystem-os/diagnostic;
    cp [resolve stage2/[host]/diagnostic.vol]
        [datadir]/ucsd-psystem-os/diagnostic.vol;
    cp -r stage2/[host]/system [datadir]/ucsd-psystem-os/system;
    cp [resolve stage2/[host]/system.vol] [datadir]/ucsd-psystem-os/system.vol;
    cp -r stage2/[host]/utility [datadir]/ucsd-psystem-os/utility;
    cp [resolve stage2/[host]/utility.vol]
        [datadir]/ucsd-psystem-os/utility.vol;
}

stage3.install: stage3.disks
{
    mkdir -p [datadir]/ucsd-psystem-os;
    cp -r stage3/[host]/diagnostic [datadir]/ucsd-psystem-os/diagnostic;
    cp [resolve stage3/[host]/diagnostic.vol]
        [datadir]/ucsd-psystem-os/diagnostic.vol;
    cp -r stage3/[host]/system [datadir]/ucsd-psystem-os/system;
    cp [resolve stage3/[host]/system.vol] [datadir]/ucsd-psystem-os/system.vol;
    cp -r stage3/[host]/utility [datadir]/ucsd-psystem-os/utility;
    cp [resolve stage3/[host]/utility.vol]
        [datadir]/ucsd-psystem-os/utility.vol;
}
fubar
test $? -eq 0 || no_result

mkdir -p arch/6502/interpreter system
test $? -eq 0 || no_result

touch arch/6502/interpreter/main.asm.text system/main.text
test $? -eq 0 || no_result

ucsdpsys_osmakgen -o test.cook -b arch/6502/interpreter/main.asm.text \
        system/main.text
test $? -eq 0 || fail

diff ok test.cook
test $? -eq 0 || fail

#
# The functionality exercised by this test worked.
# No other assertions are made.
#
pass


/* vim: set ts=8 sw=4 et : */
