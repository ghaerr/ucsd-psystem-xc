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

TAB=`awk 'BEGIN{printf("%c",9)}' /dev/null`

sed "s|{TAB}|$TAB|g" > ok << 'fubar'
#
# This file is generated by the ucsdpsys_osmakgen(1) command, from the
# ucsd-psystem-xc project.  The ucsd-psystem-xc project is distributed under the
# terms and conditions of the GNU GPL version 3.  As a special exception, the
# contents of this file are not subject to those terms and conditions.
#

# values provided by the ./configure script
prefix = @prefix@
exec_prefix = @exec_prefix@
datadir = $(DESTDIR)@datadir@
datarootdir = $(DESTDIR)@datarootdir@
sysconfdir = $(DESTDIR)@sysconfdir@

all: stage1.disks

host = klebsch

arch := $(shell ucsdpsys_osmakgen --arch-from-host $(host))

# cross compiler flags
XCFLAGS = --arch=$(arch) -Wno-shadow

# cross assembler flags
XAFLAGS = --arch=$(arch)

filenames = arch/6502/interpreter/main.asm.text system/main.text

ifeq ($(host),6502)

stage1/$(host)/codefiles/interpreter/main.asm.code: \
{TAB}{TAB}arch/6502/interpreter/main.asm.text
{TAB}@mkdir -p stage1/$(host)/codefiles/interpreter
{TAB}ucsdpsys_assemble $(XAFLAGS) -Iarch/6502/interpreter -o \
{TAB}{TAB}stage1/$(host)/codefiles/interpreter/main.asm.code \
{TAB}{TAB}arch/6502/interpreter/main.asm.text
endif

stage1/$(host)/codefiles/system/main.code: system/main.text
{TAB}@mkdir -p stage1/$(host)/codefiles/system
{TAB}ucsdpsys_compile $(XCFLAGS) -Isystem -o \
{TAB}{TAB}stage1/$(host)/codefiles/system/main.code system/main.text

stage1.disks: stage1/$(host)/system.vol

stage2.disks: stage2/$(host)/system.vol

stage3.disks: stage3/$(host)/system.vol

stage1/$(host)/diagnostic/system.$(host): \
{TAB}{TAB}stage1/$(host)/codefiles/interpreter/main.asm.code
{TAB}@mkdir -p stage1/$(host)/diagnostic
{TAB}cp stage1/$(host)/codefiles/interpreter/main.asm.code \
{TAB}{TAB}stage1/$(host)/diagnostic/system.$(host)

stage1/$(host)/system/system.$(host): \
{TAB}{TAB}stage1/$(host)/codefiles/interpreter/main.asm.code
{TAB}@mkdir -p stage1/$(host)/system
{TAB}cp stage1/$(host)/codefiles/interpreter/main.asm.code \
{TAB}{TAB}stage1/$(host)/system/system.$(host)

stage2/$(host)/diagnostic/system.$(host): \
{TAB}{TAB}stage2/$(host)/codefiles/interpreter/main.asm.code
{TAB}@mkdir -p stage2/$(host)/diagnostic
{TAB}cp stage2/$(host)/codefiles/interpreter/main.asm.code \
{TAB}{TAB}stage2/$(host)/diagnostic/system.$(host)

stage2/$(host)/system/system.$(host): \
{TAB}{TAB}stage2/$(host)/codefiles/interpreter/main.asm.code
{TAB}@mkdir -p stage2/$(host)/system
{TAB}cp stage2/$(host)/codefiles/interpreter/main.asm.code \
{TAB}{TAB}stage2/$(host)/system/system.$(host)

stage3/$(host)/diagnostic/system.$(host): \
{TAB}{TAB}stage3/$(host)/codefiles/interpreter/main.asm.code
{TAB}@mkdir -p stage3/$(host)/diagnostic
{TAB}cp stage3/$(host)/codefiles/interpreter/main.asm.code \
{TAB}{TAB}stage3/$(host)/diagnostic/system.$(host)

stage3/$(host)/system/system.$(host): \
{TAB}{TAB}stage3/$(host)/codefiles/interpreter/main.asm.code
{TAB}@mkdir -p stage3/$(host)/system
{TAB}cp stage3/$(host)/codefiles/interpreter/main.asm.code \
{TAB}{TAB}stage3/$(host)/system/system.$(host)

ifneq ($(wildcard host/$(host)/interpreter/main.asm.text),)
interpreter_stage1_diagnostic_code = stage1/$(host)/diagnostic/system.$(host)
interpreter_stage1_system_code = stage1/$(host)/system/system.$(host)
interpreter_stage2_diagnostic_code = stage2/$(host)/diagnostic/system.$(host)
interpreter_stage2_system_code = stage2/$(host)/system/system.$(host)
interpreter_stage3_diagnostic_code = stage3/$(host)/diagnostic/system.$(host)
interpreter_stage3_system_code = stage3/$(host)/system/system.$(host)
else
ifneq ($(wildcard arch/$(arch)/interpreter/main.asm.text),)
interpreter_stage1_diagnostic_code = stage1/$(host)/diagnostic/system.$(host)
interpreter_stage1_system_code = stage1/$(host)/system/system.$(host)
interpreter_stage2_diagnostic_code = stage2/$(host)/diagnostic/system.$(host)
interpreter_stage2_system_code = stage2/$(host)/system/system.$(host)
interpreter_stage3_diagnostic_code = stage3/$(host)/diagnostic/system.$(host)
interpreter_stage3_system_code = stage3/$(host)/system/system.$(host)
else
interpreter_stage1_diagnostic_code =
interpreter_stage1_system_code =
interpreter_stage2_diagnostic_code =
interpreter_stage2_system_code =
interpreter_stage3_diagnostic_code =
interpreter_stage3_system_code =
endif
endif

stage1/$(host)/system/system.pascal: stage1/$(host)/codefiles/system/main.code
{TAB}@mkdir -p stage1/$(host)/system
{TAB}cp stage1/$(host)/codefiles/system/main.code \
{TAB}{TAB}stage1/$(host)/system/system.pascal

# build stage one system disk image

stage1/$(host)/system.vol: $(interpreter_stage1_system_code) \
{TAB}{TAB}stage1/$(host)/system/system.pascal
{TAB}@mkdir -p stage1/$(host)
{TAB}ucsdpsys_mkfs --arch=$(arch) -B256 --label=system \
{TAB}{TAB}stage1/$(host)/system.vol
{TAB}ucsdpsys_disk --file stage1/$(host)/system.vol --text --put \
{TAB}{TAB}$(interpreter_stage1_system_code) \
{TAB}{TAB}stage1/$(host)/system/system.pascal
{TAB}ucsdpsys_disk --file stage1/$(host)/system.vol --crunch --list \
{TAB}{TAB}--sort=name

stage2/$(host)/system/system.pascal: stage2/$(host)/codefiles/system/main.code
{TAB}@mkdir -p stage2/$(host)/system
{TAB}cp stage2/$(host)/codefiles/system/main.code \
{TAB}{TAB}stage2/$(host)/system/system.pascal

# build stage two system disk image

stage2/$(host)/system.vol: $(interpreter_stage2_system_code) \
{TAB}{TAB}stage2/$(host)/system/system.pascal
{TAB}@mkdir -p stage2/$(host)
{TAB}ucsdpsys_mkfs --arch=$(arch) -B256 --label=system \
{TAB}{TAB}stage2/$(host)/system.vol
{TAB}ucsdpsys_disk --file stage2/$(host)/system.vol --text --put \
{TAB}{TAB}$(interpreter_stage2_system_code) \
{TAB}{TAB}stage2/$(host)/system/system.pascal
{TAB}ucsdpsys_disk --file stage2/$(host)/system.vol --crunch --list \
{TAB}{TAB}--sort=name

stage3/$(host)/system/system.pascal: stage3/$(host)/codefiles/system/main.code
{TAB}@mkdir -p stage3/$(host)/system
{TAB}cp stage3/$(host)/codefiles/system/main.code \
{TAB}{TAB}stage3/$(host)/system/system.pascal

# build stage three system disk image

stage3/$(host)/system.vol: $(interpreter_stage3_system_code) \
{TAB}{TAB}stage3/$(host)/system/system.pascal
{TAB}@mkdir -p stage3/$(host)
{TAB}ucsdpsys_mkfs --arch=$(arch) -B256 --label=system \
{TAB}{TAB}stage3/$(host)/system.vol
{TAB}ucsdpsys_disk --file stage3/$(host)/system.vol --text --put \
{TAB}{TAB}$(interpreter_stage3_system_code) \
{TAB}{TAB}stage3/$(host)/system/system.pascal
{TAB}ucsdpsys_disk --file stage3/$(host)/system.vol --crunch --list \
{TAB}{TAB}--sort=name

clean: clean-files
clean-files:
{TAB}rm -f stage1/$(host)/codefiles/interpreter/main.asm.code
{TAB}rm -f stage1/$(host)/codefiles/system/main.code
{TAB}rm -f stage1/$(host)/diagnostic/system.$(host) stage1/$(host)/system.vol
{TAB}rm -f stage1/$(host)/system/system.$(host)
{TAB}rm -f stage1/$(host)/system/system.pascal
{TAB}rm -f stage2/$(host)/diagnostic/system.$(host) stage2/$(host)/system.vol
{TAB}rm -f stage2/$(host)/system/system.$(host)
{TAB}rm -f stage2/$(host)/system/system.pascal
{TAB}rm -f stage3/$(host)/diagnostic/system.$(host) stage3/$(host)/system.vol
{TAB}rm -f stage3/$(host)/system/system.$(host)
{TAB}rm -f stage3/$(host)/system/system.pascal

distclean: clean dist-clean-files dist-clean-dirs
dist-clean-files:
{TAB}rm -f Makefile config.log config.status
dist-clean-dirs:
{TAB}rm -rf stage1

rebuild-makefile:
{TAB}ucsdpsys_osmakgen $(filenames)

install: stage1.install

stage1.install: stage1.disks
{TAB}mkdir -p $(datadir)/ucsd-psystem-os
{TAB}cp -r stage1/$(host)/diagnostic $(datadir)/ucsd-psystem-os/diagnostic
{TAB}cp stage1/$(host)/diagnostic.vol \
{TAB}{TAB}$(datadir)/ucsd-psystem-os/diagnostic.vol
{TAB}cp -r stage1/$(host)/system $(datadir)/ucsd-psystem-os/system
{TAB}cp stage1/$(host)/system.vol $(datadir)/ucsd-psystem-os/system.vol
{TAB}cp -r stage1/$(host)/utility $(datadir)/ucsd-psystem-os/utility
{TAB}cp stage1/$(host)/utility.vol $(datadir)/ucsd-psystem-os/utility.vol

stage2.install: stage2.disks
{TAB}mkdir -p $(datadir)/ucsd-psystem-os
{TAB}cp -r stage2/$(host)/diagnostic $(datadir)/ucsd-psystem-os/diagnostic
{TAB}cp stage2/$(host)/diagnostic.vol \
{TAB}{TAB}$(datadir)/ucsd-psystem-os/diagnostic.vol
{TAB}cp -r stage2/$(host)/system $(datadir)/ucsd-psystem-os/system
{TAB}cp stage2/$(host)/system.vol $(datadir)/ucsd-psystem-os/system.vol
{TAB}cp -r stage2/$(host)/utility $(datadir)/ucsd-psystem-os/utility
{TAB}cp stage2/$(host)/utility.vol $(datadir)/ucsd-psystem-os/utility.vol

stage3.install: stage3.disks
{TAB}mkdir -p $(datadir)/ucsd-psystem-os
{TAB}cp -r stage3/$(host)/diagnostic $(datadir)/ucsd-psystem-os/diagnostic
{TAB}cp stage3/$(host)/diagnostic.vol \
{TAB}{TAB}$(datadir)/ucsd-psystem-os/diagnostic.vol
{TAB}cp -r stage3/$(host)/system $(datadir)/ucsd-psystem-os/system
{TAB}cp stage3/$(host)/system.vol $(datadir)/ucsd-psystem-os/system.vol
{TAB}cp -r stage3/$(host)/utility $(datadir)/ucsd-psystem-os/utility
{TAB}cp stage3/$(host)/utility.vol $(datadir)/ucsd-psystem-os/utility.vol
fubar
test $? -eq 0 || no_result

mkdir -p arch/6502/interpreter system
test $? -eq 0 || no_result

touch arch/6502/interpreter/main.asm.text system/main.text
test $? -eq 0 || no_result

ucsdpsys_osmakgen -o test.makefile.out -b arch/6502/interpreter/main.asm.text \
        system/main.text
test $? -eq 0 || fail

diff ok test.makefile.out
test $? -eq 0 || fail

#
# The functionality exercised by this test worked.
# No other assertions are made.
#
pass
# vim: set ts=8 sw=4 et :