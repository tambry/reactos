/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            ntdll/dispatch/amd64/dispatch.S
 * PURPOSE:         Usermode dispatcher stubs
 *
 * PROGRAMMER:      Timo kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <asm.inc>
#include <ksamd64.inc>

EXTERN NtContinue:PROC
EXTERN LdrpInit:PROC
EXTERN ZwCallbackReturn:PROC
EXTERN RtlRaiseStatus:PROC

.code

PUBLIC LdrInitializeThunk
.PROC LdrInitializeThunk
    mov rbp, 0
    .setframe rbp, 0
    .endprolog

    /* First parameter is the APC context */
    mov rcx, r9
    jmp LdrpInit

.ENDP

EXTERN NtSetContextThread:PROC
EXTERN RtlCaptureContext:PROC

PUBLIC KiUserApcDispatcher
.PROC KiUserApcDispatcher
    .endprolog
    /* We enter with a 16 byte aligned stack */
    int 3
    sub rsp, 200h

    mov [rsp + CxSegSs], ss

    lea rcx, [rsp]
    call RtlCaptureContext

    lea rax, [rsp + CxSegSs]
    mov [rsp + CxDr0], rax

    or qword ptr [rsp + CxDr7], 0F01h
    lea rcx, [dostuff]
    mov [rsp + CxRip], rcx

    mov rcx, -2
    lea rdx, [rsp]
    call NtSetContextThread

    nop
dostuff:
    mov ss, [rsp + CxSegSs]
    int 3

    mov rcx, [rsp + CONTEXT_P1Home] /* NormalContext */
    mov rdx, [rsp + CONTEXT_P2Home] /* SystemArgument1 */
    mov r8, [rsp + CONTEXT_P3Home]  /* SystemArgument2 */
    lea r9, [rsp]                   /* Context */
    call qword ptr [rsp + CONTEXT_P4Home] /* NormalRoutine */

    /* NtContinue(Context, TRUE); */
    lea rcx, [rsp]
    mov dl, 1
    call NtContinue

    nop
    int 3
.ENDP


PUBLIC KiRaiseUserExceptionDispatcher
.PROC KiRaiseUserExceptionDispatcher
    .endprolog
    int 3

.ENDP

PUBLIC KiUserCallbackDispatcher
.PROC KiUserCallbackDispatcher

    ; The stack is set up with a UCALLOUT_FRAME
    ; The frame ends with a MACHINE_FRAME.
    .PUSHFRAME

    ; This is for the Home space, Buffer, Length and ApiNumber
    .ALLOCSTACK 6 * 8
    .ENDPROLOG

#if DBG
    ; We enter the function with a fully setup stack, so it must be aligned!
    test rsp, 15
    jz AlignmentOk
    int HEX(2C)
AlignmentOk:
#endif

    ; Get the parameters from the callout frame
    mov rcx, [rsp + CkBuffer]
    mov edx, [rsp + CkLength]
    mov r8d, [rsp + CkApiNumber]

    ; Get the callback table
    mov rax, gs:[TePeb]
    mov r9, [rax + PeKernelCallbackTable]

    ; Call the routine
    call qword ptr [r9 + r8 * 8]

    ; Return from callback
    xor ecx, ecx
    xor edx, edx
    mov r8d, eax
    call ZwCallbackReturn

    ; Save callback return value
    mov esi, eax

    ; Raise status
StatusRaise:
    mov ecx, esi
    call RtlRaiseStatus
    jmp StatusRaise

.ENDP

PUBLIC KiUserExceptionDispatcher
.PROC KiUserExceptionDispatcher
    .endprolog
    int 3

.ENDP

END

