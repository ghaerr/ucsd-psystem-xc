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

TEST_SUBJECT="idsearch"
. test_prelude

cat > example.text << 'fubar'
program example;
const
    MAXCURSOR = 1023;
type
    CURSRANGE = 0..MAXCURSOR;

               (*BASIC SYMBOLS, MUST MATCH ORDER IN IDSEARCH*)
    SYMBOL = (IDENT, COMMA, COLON, SEMICOLON, LPARENT, RPARENT, DOSY, TOSY,
              DOWNTOSY, ENDSY, UNTILSY, OFSY, THENSY, ELSESY, BECOMES, LBRACK,
              RBRACK, ARROW, PERIOD, BEGINSY, IFSY, CASESY, REPEATSY, WHILESY,
              FORSY, WITHSY, GOTOSY, LABELSY, CONSTSY, TYPESY, VARSY, PROCSY,
              FUNCSY, PROGSY, FORWARDSY, INTCONST, REALCONST, STRINGCONST,
              NOTSY, MULOP, ADDOP, RELOP, SETSY, PACKEDSY, ARRAYSY, RECORDSY,
              FILESY, OTHERSY, LONGCONST, USESSY, UNITSY, INTERSY, IMPLESY,
              EXTERNLSY, SEPARATSY);

    OPERATOR = (MUL,RDIV,ANDOP,IDIV,IMOD,PLUS,MINUS,OROP,LTOP,LEOP,
                GEOP,GTOP,NEOP,EQOP,INOP,NOOP);

    ALPHA = PACKED ARRAY [1..8] OF CHAR;

    SYMBUFARRAY = PACKED ARRAY [CURSRANGE] OF CHAR;

var
                                    (*MUST BE IN THIS ORDER FOR IDSEARCH*)
    SYMCURSOR: CURSRANGE;           (*CURRENT SCANNING INDEX IN SYMBUFP^*)
    SY: SYMBOL;                     (*SYMBOL FOUND BY INSYMBOL*)
    OP: OPERATOR;                   (*CLASSIFICATION OF LAST SYMBOL*)
    ID: ALPHA;                      (*LAST IDENTIFIER FOUND*)

    SYMBUFP: ^ SYMBUFARRAY;         (*SYMBOLIC BUFFER...ASCII OR CODED*)
begin
    IDSEARCH(SYMCURSOR,SYMBUFP^); (* MAGIC PROC *)
end.
fubar
test $? -eq 0 || no_result

cat > ok << 'fubar'
; Disassembly of "example.code"
;
; Code  Code   Segment   Segment  Seg Machine   System
; Addr  Leng   Name      Kind     Num Type      Version
; ----- -----  --------  -------- --- --------- --------
;     1    22  EXAMPLE   LINKED     1 P-Code LE 3.0
;
; Procedure 1:
****: A5 03             p1_0:   LAO     3
****: F1                        SLDO    10
****: 9E 07                     CSP     IDSEARCH
****: C1 00             p1_1:   RBP     0
****: D7                        NOP
; Procedure 1 Attribute Table:
****: 10 00                     .word   16              ; data size
****: 04 00                     .word   4               ; param size
****: 07 00                     .word   $ - p1_1        ; exit ic
****: 0E 00                     .word   $ - p1_0        ; enter ic
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
