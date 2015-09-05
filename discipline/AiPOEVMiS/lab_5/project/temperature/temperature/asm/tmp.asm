default rel                     ; relative address mode
global  c_f:function
global  f_c:function
    
segment .data
    input       dq 0
    output      dq 0
    nine        dq 9.e0
    five        dq 5.e0
    thirty_two  dq 32.e0

segment .text
c_f:
    push        rbp
    mov         rbp, rsp

    movlps      [input], xmm0
    
    finit

    fld        qword  [input]
    fmul       qword  [nine]
    fdiv       qword  [five]
    fadd       qword  [thirty_two]
    fstp       qword  [output]
                       
    movlps     xmm0,  [output]
    
    mov        rsp, rbp
    pop        rbp
    ret

f_c:
    push        rbp
    mov         rbp, rsp

    movlps     [input], xmm0    
    
    finit
    fld        qword  [input]
    fsub       qword  [thirty_two]
    fmul       qword  [five]
    fdiv       qword  [nine]

    fstp       qword  [output]

    movlps     xmm0,  [output]
    
    pop        rbp
    ret
