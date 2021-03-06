#!/bin/sh
#
# UCSD p-System cross compiler
# Copyright (C) 2010, 2012 Peter Miller
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

TEST_SUBJECT="CONCAT"
. test_prelude

cat > example.text << 'fubar'
program example;
var shortstring: string;
    longstring: string[255];
begin
    short_string := 'This is a string';
    long_string := 'This is a very long string.';
    longstring :=
      concat(
        'Start ',
        shortstring,
        '-',
        longstring
      );
    writeln(longstring)
end.
fubar
test $? -eq 0 || no_result

cat > ok << 'fubar'
; Disassembly of "example.code"
;
; Code  Code   Segment   Segment  Seg Machine   System
; Addr  Leng   Name      Kind     Num Type      Version
; ----- -----  --------  -------- --- --------- --------
;     1   146  EXAMPLE   LINKED     1 P-Code LE 3.0
;
; Procedure 1:
****: A5 03             p1_0:   LAO     3
****: D7                        NOP
****: A6 10 54 68 69            LSA     16, "This is a string"
      73 20 69 73 20
      61 20 73 74 72
      69 6E 67
****: AA 50                     SAS     80
****: A5 2C                     LAO     44
****: A6 1B 54 68 69            LSA     27, "This is a very long string."
      73 20 69 73 20
      61 20 76 65 72
      79 20 6C 6F 6E
      67 20 73 74 72
      69 6E 67 2E
****: AA FF                     SAS     255
****: A5 2C                     LAO     44
****: A5 80 AC                  LAO     172
****: A6 06 53 74 61            LSA     6, "Start "
      72 74 20
****: AA FF                     SAS     255
****: A5 80 AC                  LAO     172
****: A5 03                     LAO     3
****: C7 FF 00                  LDCI    255
****: CD 00 17                  CXP     0, 23           ; sconcat
****: A5 80 AC                  LAO     172
****: A6 01 2D                  LSA     1, "-"
****: C7 FF 00                  LDCI    255
****: CD 00 17                  CXP     0, 23           ; sconcat
****: A5 80 AC                  LAO     172
****: A5 2C                     LAO     44
****: C7 FF 00                  LDCI    255
****: CD 00 17                  CXP     0, 23           ; sconcat
****: A5 80 AC                  LAO     172
****: AA FF                     SAS     255
****: B6 01 03                  LOD     1, 3
****: A5 2C                     LAO     44
****: 00                        SLDC    0
****: CD 00 13                  CXP     0, 19           ; fwritestring
****: 9E 00                     CSP     IOCHECK
****: B6 01 03                  LOD     1, 3
****: CD 00 16                  CXP     0, 22           ; fwriteln
****: 9E 00                     CSP     IOCHECK
****: C1 00             p1_1:   RBP     0
****: D7                        NOP
; Procedure 1 Attribute Table:
****: 52 02                     .word   594             ; data size
****: 04 00                     .word   4               ; param size
****: 07 00                     .word   $ - p1_1        ; exit ic
****: 8A 00                     .word   $ - p1_0        ; enter ic
****: 01                p1_at:  .byte   1               ; procedure number
****: 00                        .byte   0               ; lex level

;
; Procedure dictionary:
;
****: 02 00                     .word   $ - p1_at       ; procedure 1
****: 01                        .byte   1               ; segment number
****: 01                        .byte   1               ; number of procedures
;
; ------------------------------------------------------------------
fubar
test $? -eq 0 || no_result

ucsdpsys_compile example.text
test $? -eq 0 || fail

ucsdpsys_disassemble -a example.code -o test.out
test $? -eq 0 || no_result

diff ok test.out
test $? -eq 0 || fail

#
# The functionality exercised by this test worked.
# No other assertions are made.
#
pass
# vim: set ts=8 sw=4 et :
