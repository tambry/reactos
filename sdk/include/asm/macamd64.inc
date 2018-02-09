;++
; PROJECT:     ReactOS SDK
; LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
; PURPOSE:     ReactOS AMD64 architecture asm macros
; COPYRIGHT:   Timo Kreuzer (timo.kreuzer@reactos.org)
;--

#include <asm.inc>

MACRO(push_reg, Reg)

    push Reg
    .pushreg Reg

ENDM

rex_push_reg macro Reg

        db      048h
        push    Reg
        .pushreg Reg

        endm


push_eflags macro

        pushfq
        .allocstack 8

        endm

rex_push_eflags macro

        db      048h
        pushfq
        .allocstack 8

        endm

rex_jmp_reg macro Reg

        db      048h                    ; hint tail call to unwinder
        jmp     Reg

        endm

ret_zero macro

        ret

        endm

alloc_stack macro Size

        sub     rsp, Size
        .allocstack Size

        endm

save_reg macro Reg, Offset

        mov     Offset[rsp], Reg
        .savereg Reg, Offset

        endm

save_xmm128 macro Reg, Offset

        movaps  Offset[rsp], Reg
        .savexmm128 Reg, Offset

        endm

push_frame macro Code

        .pushframe Code

        endm

set_frame macro Reg, Offset

if Offset

        lea     Reg, Offset[rsp]

else

        mov     Reg, rsp

endif

        .setframe Reg, Offset

        endm

END_PROLOGUE macro

        .endprolog

        endm

BEGIN_EPILOGUE macro

        .beginepilog

        endm


LEAF_ENTRY macro Name, Section, NoPad

Section segment para 'CODE'

ifb <NoPad>

        db      6 dup (0cch)

endif

        align   16

        public  Name
Name    proc    frame

        END_PROLOGUE

        endm


LEAF_ENTRY_ARG1 macro Name, Section, Arg1, NoPad

Section segment para 'CODE'

ifb <NoPad>

        db      6 dup (0cch)

endif

        align   16

        public  Name
Name    proc    frame

        END_PROLOGUE

        endm


LEAF_ENTRY_ARG2 macro Name, Section, Arg1, Arg2, NoPad

Section segment para 'CODE'

ifb <NoPad>

        db      6 dup (0cch)

endif

        align   16

        public  Name
Name    proc    frame

        END_PROLOGUE

        endm


LEAF_ENTRY_ARG3 macro Name, Section, Arg1, Arg2, Arg3, NoPad

Section segment para 'CODE'

ifb <NoPad>

        db      6 dup (0cch)

endif

        align   16

        public  Name
Name    proc    frame

        END_PROLOGUE

        endm

LEAF_END macro Name, section

Name    endp

Section ends

        endm


NESTED_ENTRY macro Name, Section, Handler, NoPad

ifdef _CurrentSection_

ifdif <Section>, _CurrentSection_

.err <NESTED_ENTRY invoked for different sections within same module>

endif

endif

_CurrentSection_ EQU <Section>

Section segment para 'CODE'

ifb <NoPad>

        db      6 dup (0cch)

endif

        align   16

        public  Name

ifb <Handler>

Name    proc    frame

else

Name    proc    frame:Handler

endif

        endm


NESTED_END macro Name, section

Name    endp

Section ends

        endm


ALTERNATE_ENTRY macro Name

Name:
        endm


Yield   macro

        pause

        endm


