global main
    
extern factorial
extern exit
extern scanf
extern printf
extern flush_stdin    
        
segment .data

input_min       equ 0    
input_max       equ 20
    
msg_desc        db "This program calculates factorial of specified number.", 0xA, 0xA, 0   
msg_input       db "Input number in range [0; 20] and press <Enter>: ", 0
msg_incrt_input db "You number should be in specified range!", 0xA, 0xA, 0
newline         db 0xA, 0
    
tpl_input       db "%lu", 0    
input           dq 0   

msg_result      db "The factorial of %lu is: %lu", 0xA, 0    
result          dq 0
    
segment .text

main:
    push    rbp
    mov     rbp, rsp

    ;; print usage message
    ;; push arguments to printf in reverse order
    mov     rdi, msg_desc          ; fmt string 
    call    printf

.input:
    ;; print input message
    mov     rdi, msg_input          ; fmt string 
    call    printf
    
    ;; get user input
    ;; push arguments to scanf in reverse order
    mov     rsi, input
    mov     rdi, tpl_input
    call    scanf

    ;; check user input
    cmp     rax, 0              ; by return value of scanf
    je      .incorrect
    
    mov     rdx, [input]        ; by input value    
    cmp     rdx, input_min
    jl      .incorrect
    cmp     rdx, input_max
    jg      .incorrect
    jmp     .correct

.incorrect:    
    ;; print msg about incorrect user input
    ;; push arguments to printf in reverse order
    mov     rdi, msg_incrt_input          ; fmt string 
    call    printf

    ;; clear input buffer
    call flush_stdin

    jmp     .input
    
.correct:    
    ;; calculate factorial
    mov     rdi, [input]
    call    factorial
    mov     [result], rax

    ;; print result
    ;; push arguments to printf in reverse order
    mov     rdx, [result]            ; result of factorial
    mov     rsi, [input]             ; source value
    mov     rdi, msg_result          ; fmt string 
    call    printf

    ;; exit 
    mov     rdi, 0
    call    exit

    pop     rbp
    ret
