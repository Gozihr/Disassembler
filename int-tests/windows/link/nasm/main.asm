global main
extern GetStdHandle
extern WriteFile

section .text
main:
    mov     rcx, 0fffffff5h
    call    GetStdHandle

    mov     rcx, rax
    mov     rdx, NtlpBuffer
    mov     r8, [NtnNBytesToWrite]
    mov     r9, NtlpNBytesWritten
    sub     rsp, 40
    mov     dword [rsp + 32], 00h
    call    WriteFile
    add     rsp, 40
ExitProgram:
    xor     eax, eax
    ret

section .data
NtlpBuffer:        db    'Hello, World!', 00h
NtnNBytesToWrite:  dq    0eh

section .bss
NtlpNBytesWritten: resd  01h