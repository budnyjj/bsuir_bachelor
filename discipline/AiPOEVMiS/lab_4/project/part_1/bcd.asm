;; macro for memory initialization
;; di = len1-1+offset mem1
;; si = len2-1+offset mem2
;; cx = min(len1, len2)
Init    macro   mem1,len1,mem2,len2
    local _assign_len1_,_assign_len2_,_end_
    push    ax
    push    dx

    mov     ax, len1
    sub     ax,1
    add     ax, offset mem1
    mov     di,ax

    mov     dx, len2
    sub     dx, 1
    add     dx, offset mem2
    mov     si,dx

    mov     ax, len1
    cmp     ax, len2
    jg      _assign_len2_

_assign_len1_:
    mov     cx, len1
    jmp     _end_

_assign_len2_:
    mov     cx, len2
    jmp     _end_

_end_:
    pop     dx
    pop     ax
    endm

;; ax = length of essential part BCD number
LenBCD      macro mem,len_mem,pos_dot, max_size
            local _start_zero_,_end_

    mov     si, offset mem
    mov     cx, max_size
    call    LenBCDp

    cmp     ax, pos_dot
    je      _start_zero_
    jmp     _end_

_start_zero_:
    inc     ax
    jmp     _end_

_end_:
    mov     len_mem, ax
    endm

;; Check, if BCD number is equal to zero, and place result in CF
IsZeroBCD      macro mem,len
    mov     si, offset mem
    mov     cx, len
    call    IsZeroBCDp
    endm

;; Align position of BCD number by
;; right border of memory:
;; [12343---] => [---12343]
AlignBCD    macro mem,len,max_size
    Init    mem,max_size,mem,len
    mov     cx, len
    call    CpBCDp

    mov     di, offset mem
    ;; cx = max_size - len
    mov     cx, max_size
    sub     cx, len
    call    SetZerop
    endm

; Copy mem2 to mem1
CpBCD   macro   mem1,mem2,max_size
    Init mem1,max_size,mem2,max_size
    call CpBCDp
    endm

;; Addition of BCD numbers
;; Store result of addition in mem1
;;
;; In:
;; mem1 -- first operand
;; sign1 -- sign of first operand
;; pos_dot1 -- position of dot in first operand
;;
;; mem2 -- second operand
;; sign2 -- sign of second operand
;; pos_dot2 -- position of dot in second operand
;;
;; max_size -- maximal size of mem1 and mem2
;;
;; Out:
;; len_mem1 -- essential part length of mem1 (result)
AddBCD  macro   mem1,len_mem1,sign1,pos_dot1, mem2,len_mem2,sign2,pos_dot2, max_size
        local _compare_signs_,_signs_equal_,_signs_not_equal_,_mem1_gz_mem2_,_mem1_lz_mem2,_rest1_gz_rest2_,_rest1_lz_rest2_,_corrections_,_end_

    ;; adjust bcd by dot pos
    mov     ax, pos_dot1
    mov     dx, pos_dot2
    cmp     ax, dx
    jg      _rest1_gz_rest2_
    jl      _rest1_lz_rest2_

    CpBCD   mem_overhead,mem2,max_size
    jmp     _compare_signs_

_rest1_gz_rest2_:
    ;; pos_dot1 > pos_dot2

    mov     di, offset mem_overhead
    mov     cx, max_size
    call    SetZerop

    ;; si = offset mem2 - 1 + max_size
    mov     si, offset mem2
    add     si, max_size
    sub     si, 1

    ;; di = offset mem_overhead+max_size-(pos_dot1-pos_dot2)-1
    mov     di, offset mem_overhead
    add     di, max_size
    add     di, pos_dot2
    sub     di, pos_dot1
    sub     di, 1

    mov     cx, len_mem2
    call    CpBCDp
    jmp     _compare_signs_

_rest1_lz_rest2_:
    ;; pos_dot1 < pos_dot2

    mov     di, offset mem_overhead
    mov     cx, max_size
    call    SetZerop

    ;; si = offset mem2 - 1 + max_size
    mov     si, offset mem1
    add     si, max_size
    sub     si, 1

    ;; di = offset mem_overhead+max_size-(pos_dot2 - pos_dot1)-1
    mov     di, offset mem_overhead
    add     di, max_size
    sub     di, pos_dot2
    add     di, pos_dot1
    sub     di, 1

    mov     cx, len_mem1
    call    CpBCDp

    CpBCD   mem1, mem_overhead, max_size

    jmp     _compare_signs_

_compare_signs_:
    mov     ah, sign1
    mov     al, sign2
    xor     ah, al
    cmp     ah, 0

    je      _signs_equal_
    jmp     _signs_not_equal_

_signs_equal_:
;; sign1 == sign2
;; mem1 = mem1 + mem2
;; sign1 = sign1
    Init    mem1,max_size,mem_overhead,max_size
    call    AddBCDp
    jmp     _corrections_

_signs_not_equal_:
;; sign1 != sign2
;; mem1 = max(mem1, mem2) - min(mem1, mem2)
;; sign1 = sign(max(mem1, mem2))
    mov     di, offset mem1
    mov     si, offset mem_overhead
    mov     cx, max_size
    call    CmpBCDp
    jc      _mem1_gz_mem2_
    jmp     _mem1_lz_mem2_

_mem1_gz_mem2_:
    Init    mem1,max_size,mem_overhead,max_size
    call    SubBCDp
    jmp     _corrections_

_mem1_lz_mem2_:
    mov al, sign2
    mov sign1, al

    Init    mem_overhead,max_size,mem1,max_size
    call    SubBCDp
    CpBCD   mem1,mem_overhead,max_size

    jmp     _corrections_

_corrections_:
    LenBCD  mem1,len_mem1,pos_dot1,max_size

    ;; check, if result == 0, and set sign to 0
    IsZeroBCD mem1,max_size
    jnc     _end_
    mov     sign1, 0
    jmp     _end_

_end_:
    endm

;; Subtraction of BCD numbers
;; Store result of subtraction in mem1
;;
;; In:
;; mem1 -- first operand
;; sign1 -- sign of first operand
;;
;; mem2 -- second operand
;; sign2 -- sign of second operand
;;
;; max_size -- maximal size of mem1 and mem2
;;
;; Out:
;; len_mem1 -- essential part length of mem1 (result)
SubBCD  macro   mem1,len_mem1,sign1,pos_dot1, mem2,len_mem2,sign2,pos_dot2, max_size
        local   _compare_signs_,_signs_equal_,_signs_not_equal_,_mem1_gz_mem2_,_mem1_gz_mem2_gz_0_,_mem1_lz_mem2_lz_0_,_mem1_lz_mem2,_mem1_lz_mem2_,_mem2_gz_mem1_gz_0_,_mem2_lz_mem1_lz_0_,_mem1_sub_mem2_,_mem2_sub_mem1_,_corrections_,_end_

    ;; adjust bcd by dot pos
    mov     ax, pos_dot1
    mov     dx, pos_dot2
    cmp     ax, dx
    jg      _rest1_gz_rest2_
    jl      _rest1_lz_rest2_

    CpBCD   mem_overhead,mem2,max_size
    jmp     _compare_signs_

_rest1_gz_rest2_:
    ;; pos_dot1 > pos_dot2

    mov     di, offset mem_overhead
    mov     cx, max_size
    call    SetZerop

    ;; si = offset mem2 - 1 + max_size
    mov     si, offset mem2
    add     si, max_size
    sub     si, 1

    ;; di = offset mem_overhead+max_size-(pos_dot1-pos_dot2)-1
    mov     di, offset mem_overhead
    add     di, max_size
    add     di, pos_dot2
    sub     di, pos_dot1
    sub     di, 1

    mov     cx, len_mem2
    call    CpBCDp
    jmp     _compare_signs_

_rest1_lz_rest2_:
    ;; pos_dot1 < pos_dot2

    mov     di, offset mem_overhead
    mov     cx, max_size
    call    SetZerop

    ;; si = offset mem2 - 1 + max_size
    mov     si, offset mem1
    add     si, max_size
    sub     si, 1

    ;; di = offset mem_overhead+max_size-(pos_dot2 - pos_dot1)-1
    mov     di, offset mem_overhead
    add     di, max_size
    sub     di, pos_dot2
    add     di, pos_dot1
    sub     di, 1

    mov     cx, len_mem1
    call    CpBCDp

    CpBCD   mem1, mem_overhead, max_size

    jmp     _compare_signs_

_compare_signs_:
    mov     ah, sign1
    mov     al, sign2
    xor     ah, al
    cmp     ah, 0
    je      _signs_equal_
    jmp     _signs_not_equal_

_signs_not_equal_:
;; sign1 != sign2
;; mem1 = max(mem1, mem2) - min(mem1, mem2)
;; sign1 = sign(max(mem1, mem2))
    Init    mem1,max_size,mem_overhead,max_size
    call    AddBCDp
    jmp     _corrections_

_signs_equal_:
;; sign1 == sign2
;; mem1 = mem1 + mem2
;; sign1 = sign1
    mov     di, offset mem1
    mov     si, offset mem_overhead
    mov     cx, max_size
    call    CmpBCDp
    jc      _mem1_gz_mem2_
    jmp     _mem1_lz_mem2_

;; by absolute value
_mem1_gz_mem2_:
    mov     al, sign2
    cmp     al, 0
    je      _mem1_gz_mem2_gz_0_
    jmp     _mem1_lz_mem2_lz_0_

;; by absolute value
_mem1_lz_mem2_:
    mov     al, sign2
    mov     al, 0
    je      _mem2_gz_mem1_gz_0_
    jmp     _mem2_lz_mem1_lz_0_

_mem1_gz_mem2_gz_0_:
_mem1_lz_mem2_lz_0_:
    jmp     _mem1_sub_mem2_

_mem2_gz_mem1_gz_0_:
    mov     sign1, 1
    jmp     _mem2_sub_mem1_

_mem2_lz_mem1_lz_0_:
    mov     sign1, 1
    jmp     _mem2_sub_mem1_

_mem1_sub_mem2_:
    Init    mem1,max_size,mem_overhead,max_size
    call    SubBCDp
    jmp     _corrections_

_mem2_sub_mem1_:
    Init    mem_overhead,max_size,mem1,max_size
    call    SubBCDp
    CpBCD   mem1,mem_overhead,max_size

    jmp     _corrections_

_corrections_:
    LenBCD  mem1,len_mem1,pos_dot1,max_size

    IsZeroBCD mem1,max_size
    jnc     _end_
    mov     sign1, 0
    jmp     _end_

_end_:
    endm

;; Multiplication of BCD numbers
;; Store lower part of result in mem1,
;; higher part --- in mem2
;;
;; In:
;; mem1 -- first operand
;; sign1 -- sign of first operand
;;
;; mem2 -- second operand
;; sign2 -- sign of second operand
;;
;; max_size -- maximal size of mem1 and mem2
;;
;; Out:
;; len_mem1 -- essential part length of mem1 (result)
MulBCD  macro   mem1,len_mem1,sign1,pos_dot1, mem2,len_mem2,sign2,pos_dot2, max_size
        local   _mul_,_end_
    ;; determine sign of result
    mov     ah, sign1
    mov     al, sign2
    xor     ah, al
    mov     sign1, ah

    ;; determine dot position of result
    mov     ax, pos_dot1
    add     ax, pos_dot2
    mov     pos_dot1, ax

_mul_:
    ;; copy mem2 number to temporary place
    CpBCD   mem_overhead,mem2,max_size

    ;CpBCD   mem1,mem_overhead,max_size

    Init    mem1,max_size,mem_overhead,max_size

    call    MulBCDp

    LenBCD  mem1,len_mem1,pos_dot1,max_size

    IsZeroBCD mem1,max_size
    jnc     _end_
    mov     sign1, 0
    jmp     _end_

_end_:
    endm

;; Division of BCD numbers
;; Store result of division in mem1,
;; rest --- in mem2
;;
;; In:
;; mem1 -- first operand
;; sign1 -- sign of first operand
;;
;; mem2 -- second operand
;; sign2 -- sign of second operand
;;
;; max_size -- maximal size of mem1 and mem2
;;
;; Out:
;; len_mem1 -- essential part length of mem1 (result)
DivBCD  macro   mem1,len_mem1,sign1,pos_dot1, mem2,len_mem2,sign2,pos_dot2, max_size
        local   _div_,_end_
    ;; determine sign of result
    mov     ah, sign1
    mov     al, sign2
    xor     ah, al
    mov     sign1, ah

    ;; TODO: determine dot position of result
    ;; mov     ax, pos_dot1
    ;; sub     ax, pos_dot2
    ;; mov     pos_dot1, ax

_div_:
    ;; copy mem2 number to temporary place
    CpBCD   mem_overhead,mem2,max_size
    mov     di,offset mem1
    mov     si,offset mem_overhead
    mov     cx,max_size
    call    DivBCDp

    LenBCD  mem1,len_mem1,pos_dot1, max_size

    IsZeroBCD mem1,max_size
    jnc     _end_
    mov     sign1, 0
    jmp     _end_

_end_:
    endm

;; Print single character stored in al
OutChar macro char
    push    ax
    push    dx
    mov     ah, 02h
    mov     dl,char
    int     21h
    pop     dx
    pop     ax
    endm

;; Print characater string,
;; start address stored in dx
OutStr macro str
    push    ax
    push    dx
    mov     ah, 09h
    mov     dx, offset str
    int     21h
    pop     dx
    pop     ax
    endm

;; Print BCD-number to screen with dot and sign
OutBCD  macro   mem,max_size,len,pos_dot,sign
        local _minus_,_out_,_integer_,_rational_,_end_
    push    ax

    mov     al, sign
    cmp     al, 1
    je      _minus_
    jmp     _out_

_minus_:
    mov     al, 45
    OutChar al
    jmp     _out_

_out_:
    mov     ax, pos_dot
    cmp     ax, 0
    je      _integer_
    jmp     _rational_

_integer_:
    ;; si = (offset mem) + (max_size - len)
    ;; cx = len
    mov     ax, offset mem
    add     ax, max_size
    sub     ax, len
    mov     si, ax

    mov     cx, len

    call    OutBCDp
    jmp     _end_

_rational_:
    ;; print integer part
    ;; si = (offset mem) + (max_size - len)
    ;; cx = len - pos_dot
    mov     ax, offset mem
    add     ax, max_size
    sub     ax, len
    mov     si, ax

    mov     cx, len
    sub     cx, pos_dot
    call    OutBCDp

    ;; print dot
    mov     al, 46
    OutChar al

    ;; print rest part
    ;; si = (offset mem) + (max_size - pos_dot)
    ;; cx = pos_dot
    mov     ax, offset mem
    add     ax, max_size
    sub     ax, pos_dot
    mov     si, ax

    mov     cx, pos_dot
    call    OutBCDp

_end_:
    OutStr  newline
    pop     ax
    endm

;; Write BCD-number as string to mem_buffer with dot and sign
;; Set mem_buffer_len = length(str(BCD-number))
BCD2Str macro   mem,max_size,len,pos_dot,sign, mem_buffer,mem_buffer_len
        local   _minus_,_out_,_integer_,_rational_,_end_
    push    ax
    push    dx                  ; number of wrote chars

    xor     dx, dx
    mov     di, offset mem_buffer

    mov     al, sign
    cmp     al, 1
    je      _minus_
    jmp     _out_

_minus_:
    mov     al, 45
    stosb
    inc     dx
    jmp     _out_

_out_:
    mov     ax, pos_dot
    cmp     ax, 0
    je      _integer_
    jmp     _rational_

_integer_:
    ;; si = (offset mem) + (max_size - len)
    ;; cx = len
    mov     ax, offset mem
    add     ax, max_size
    sub     ax, len
    mov     si, ax
    mov     cx, len

    call    BCD2Strp            ; don't change dx

    jmp     _end_

_rational_:
    ;; print integer part
    ;; si = (offset mem) + (max_size - len)
    ;; cx = len - pos_dot
    mov     ax, offset mem
    add     ax, max_size
    sub     ax, len
    mov     si, ax

    mov     cx, len
    sub     cx, pos_dot
    call    BCD2Strp

    ;; print dot
    mov     al, 46
    stosb
    inc     dx

    ;; print rest part
    ;; si = (offset mem) + (max_size - pos_dot)
    ;; cx = pos_dot
    mov     ax, offset mem
    add     ax, max_size
    sub     ax, pos_dot
    mov     si, ax

    mov     cx, pos_dot
    call    BCD2Strp

_end_:
    add     dx, len
    mov     mem_buffer_len, dx

    pop     dx
    pop     ax
    endm


; copy value pointed by far ptr to local memory
ptr2local_word macro far_ptr_src, mem_dest
    push ds
    push si

    ; construct far_ptr value
    mov ds, word ptr [ far_ptr_src + 2 ]
    mov si, word ptr [ far_ptr_src ]
    mov ax, [ds:si]

    ; set local data segment
    mov bx, @data
    mov ds, bx

    ; write data pointed by far_ptr to local mem
    mov mem_dest, ax

    pop si
    pop ds
    endm

; copy value pointed by far ptr to local memory
ptr2local_byte macro far_ptr_src, mem_dest
    push ds
    push si

    ; construct far_ptr value
    mov ds, word ptr [ far_ptr_src + 2 ]
    mov si, word ptr [ far_ptr_src ]
    mov al, [ds:si]

    ; set local data segment
    mov bx, @data
    mov ds, bx

    ; write data pointed by far_ptr to local mem
    mov mem_dest, al

    pop si
    pop ds
    endm

; copy far_src to local mem
ptr2local_mem macro far_ptr_src, mem_dest, len_mem
    push ds
    push si

    ; source
    mov ds, word ptr [ far_ptr_src + 2 ]
    mov si, word ptr [ far_ptr_src ]

    ; dest
    mov ax, @data
    mov es, ax
    lea di, mem_dest

    ; length
    mov cx, len_mem

    cld
rep movsb

    pop si
    pop ds
    endm

; copy local memory value into pointer
local_word2ptr macro mem_src, far_ptr_dest
    push ds
    push si

    ; set local data segment
    mov bx, @data
    mov ds, bx

    ; read local mem
    mov ax, mem_src

    ; construct far_ptr value
    mov ds, word ptr [ far_ptr_dest + 2 ]
    mov si, word ptr [ far_ptr_dest ]

    ; write local mem to pointer
    mov [ds:si], ax

    pop si
    pop ds
    endm

; copy local memory value into pointer
local_byte2ptr macro mem_src, far_ptr_dest
    push ds
    push si

    ; set local data segment
    mov bx, @data
    mov ds, bx

    ; read local mem
    mov al, mem_src

    ; construct far_ptr value
    mov ds, word ptr [ far_ptr_dest + 2 ]
    mov si, word ptr [ far_ptr_dest ]

    ; write local mem to pointer
    mov [ds:si], al

    pop si
    pop ds
    endm

; copy local mem to far pointer
local_mem2ptr macro mem_src, far_ptr_dest, len_mem
    push ds
    push si

    ; source
    mov ax, @data
    mov ds, ax
    lea si, mem_src

    ; dest
    mov es, word ptr [ far_ptr_dest + 2 ]
    mov di, word ptr [ far_ptr_dest ]

    ; length
    mov cx, len_mem

    cld
rep movsb

    pop si
    pop ds
    endm


.MODEL small

.STACK

.DATA
CR          equ     0Dh
LF          equ     0Ah
EOS         equ     '$'
;; maximal memory size used to store numbers
len_mem     equ     20
;; maximal length of user input
len_input   equ     10
;; maximal memory size used to store number size values
len_size    equ     2

newline     db  CR, LF, EOS
len_newline dw  2               ; without EOS

; input value
a           db  len_mem dup(?)
; length of essential part
len_a       dw  0
; dot position
pos_a       dw  0
; sign (0 -- plus, 1 -- minus)
sign_a      db  0

; ========= temp ===========
temp           dw  len_mem dup(?)

; addition
thirty_two    db  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2
; length of essential part
len_thirty_two  dw  2
; dot position
pos_thirty_two  dw  0
; sign (0 -- plus, 1 -- minus)
sign_thirty_two db  0

; first coefficient
five          db  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5
; length of essential part
len_five      dw  1
; dot position
pos_five      dw  0
; sign (0 -- plus, 1 -- minus)
sign_five     db  0

; second coefficient
nine          db   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9
; length of essential part
len_nine      dw  1
; dot position
pos_nine      dw  0
; sign (0 -- plus, 1 -- minus)
sign_nine     db  0

; additional memory for mul and div purpouses
mem_overhead  db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
buffer        db  512 dup(?)

; special buffer for bcd->str convertion purpouses
len_mem_cnv   equ len_mem+2
mem_cnv       db len_mem_cnv dup(?)
len_cnv       dw 0


.CODE
.386

;; Send bytes from si to di cx times
CpBCDp proc
    std
rep movsb
    ret
    endp

;; Fill specified part of memory with zeros
;; Size of memory specified in cx
SetZerop proc
    cld
    push    ax
    mov     al, 0
rep stosb
    pop     ax
    ret
    endp

;; Check, if BCD is equal to zero
;; Set CF=1, if true, CF=0 otherwise
IsZeroBCDp proc
    push    ax
    cld
_is_zero_loop_:
    lodsb
    cmp     al, 0
    jne     _is_zero_false_
    loop    _is_zero_loop_

    jmp     _is_zero_true_

_is_zero_true_:
    stc
    jmp _is_zero_end_

_is_zero_false_:
    clc
    jmp _is_zero_end_

_is_zero_end_:
    pop ax
    ret
    endp

;; Determine essential part size of BCD number
;; Store result in ax
LenBCDp proc
    cld

_len_next_:
    lodsb
    cmp     al, 0
    jne     _len_end_           ; first essential digit
    loop    _len_next_

_len_end_:
    mov     ax, cx
    ret
    endp

;; Add two BCD numbers without signs
AddBCDp proc
    push    ax
    push    di
    push    si
    push    cx
    std
    clc
_add_:
    lodsb
    adc al,[di]
    aaa
    stosb
    loop    _add_
    pop cx
    pop si
    pop di
    pop ax
    ret
    endp

;; Subtract two BCD numbers without signs
SubBCDp     proc
    push    ax
    push    di
    push    si
    push    cx
    std
    clc
_sub_:
    lodsb
    sbb     [di],al
    mov     al,[di]
    aas
    stosb
    loop    _sub_
    pop     cx
    pop     si
    pop     di
    pop     ax
    ret
    endp

;; Multiplicate two BCD numbers without signs
MulBCDp proc
    push    ax
    push    bx
    push    di
    push    si
    push    cx
    std
    mov     bx,offset buffer
    mov     dh,cl
    push    bx
    shl     cx,1
    xor     al,al

_null_:
    mov     [bx],al
    inc     bx
    loop    _null_
    mov     cl,dh
    pop     bx

_mul_o_:
    xor     dl,dl
    push    cx
    push    bx
    push    si
    mov     cl,dh

_mul_i_:
    lodsb
    mul     byte ptr [di]
    aam
    add     al,dl
    aaa
    add     al,[bx]

    aaa
    mov     dl,ah
    xor     ah,ah
    mov     [bx],al
    inc     bx
    loop    _mul_i_
    mov     [bx],dl
    pop     si
    pop     bx
    inc     bx
    dec     di

    pop     cx
    loop    _mul_o_
    mov     cl,dh
    sub     bx,cx
    add     di,cx

_move_l_:
    mov     al,[bx]
    inc     bx
    stosb
    loop    _move_l_
    mov     cl,dh
    mov     di,si

_move_h_:
    mov     al,[bx]
    inc     bx
    stosb
    loop    _move_h_
    pop     cx
    pop     si
    pop     di
    pop     bx
    pop     ax
    ret
    endp

;; вспомогательная процедура для операции деления
;; производит вызов процедуры вычитания
;; без начальной инициализации
SubInvBCDp  proc
    push    si
    push    di
    add     si,cx
    dec     si
    add     di,cx
    dec     di
    call    SubBCDp
    pop     di
    pop     si
    ret
    endp

;; Compare two BCD numbers
;; Set CF=0, if [si]>[di], else CF=1
CmpBCDp proc
    push    ax
    push    di
    push    si
    push    cx
    cld
_cmp_:
    lodsb
    cmp al,[di]
    jl      _less_
    jg      _greater_
    inc     di
    loop    _cmp_
_less_:
    stc
    jc      _cmp_q_
_greater_:
    clc
_cmp_q_:
    pop     cx
    pop     si
    pop     di
    pop     ax
    ret
    endp

;; процедура инициализации буфера
;; для операции деления
PrepareForDiv   proc
    cld
    ;; 0,[di] -> buffer
    push    di
    push    si
    push    di
    pop     si
    mov     di,offset buffer
    xor     al,al
    push    cx
    stosb
    rep     movsb
    ;;  0,[si] -> buffer
    pop     cx
    stosb
    pop     si
    push    cx

_find_:
    lodsb
    dec     cx
    cmp     al,0
    je      _find_
    dec     si
    inc     cx
    mov     dx,cx
    rep     movsb
    pop     cx
    push    cx

    ;; 0,0..0 -> buffer
    xor     al,al
    rep     stosb

    ;; reassign registers
    mov     di,offset buffer
    pop     cx
    mov     si,di
    inc     cx
    add     si,cx
    pop     bx
    ret
    endp

;; Divide two BCD numbers
DivBCDp proc
    push    ax  ;сохраним изменяемые регистры
    push    bx
    push    di
    push    si
    push    cx
    push    di
    call    PrepareForDiv   ;подготовим буфер
    xor     ax,ax   ;в al - очередная цифра результата
            ;в ah - количество цифр в результате
    call    CmpBCDp
    jnc     _next_1_
_div_:
    call    CmpBCDp
    jnc     _next_
    inc     al
    call    SubInvBCDp
    jmp     _div_
_next_:
    mov     [bx],al ;сохраним очередную цифру
    inc     bx  ;уменьшим порядок делимого
_next_1_:
    inc     di
    dec     cx
    xor     al,al
    inc     ah
    cmp     cx,dx   ;сравним порядки делимого и делителя
    jne     _div_
    dec     ah
    pop     di
    pop     cx
    push    cx
;пересылаем результат из буфера в операнды
    mov     si,di
    add     di,cx
    push    cx
    mov     cl,ah
    add     si,cx
    dec     si
    dec     di
    std
rep movsb
    pop     cx
    sub     cl,ah
    xor     al,al
rep stosb
    pop     cx
    pop     si
    push    si
    push    cx
    mov     di,si
    mov     si,offset buffer
    inc     si
    cld
rep movsb
    pop     cx  ;восстановим регистры
    pop     si
    pop     di
    pop     bx
    pop     ax
    ret
    endp

OutBCDp proc
;процедура вывода BCD-чисел на экран
    mov     ah,06h
    cld
_outbcd_out_:
    lodsb
    or      al,30h
    mov     dl,al
    int     21h
    loop    _outbcd_out_
    ret
    endp

BCD2Strp    proc
;процедура вывода BCD-чисел в буффер
    mov     ah,06h
    cld
_bcd2str_out_:
    lodsb
    or      al,30h
    stosb
    loop    _bcd2str_out_
    ret
    endp

public _CF
_CF proc far
    push bp
    mov  bp, sp
    push es
    push ds
    push si

    ; copy ptr_src array to local variable a
    ptr2local_mem bp+6, a, len_mem

    ; copy len_a to local mem
    ptr2local_word bp+10, len_a

    ; copy pos_a to local mem
    ptr2local_word bp+14, pos_a

    ; copy sign_a to local mem
    ptr2local_byte bp+18, sign_a

    mov ax, @data
    mov ds, ax
    mov es, ax

    ; convert Celsius to Farengheit, store result in a
    MulBCD  a,len_a,sign_a,pos_a, nine,len_nine,sign_nine,pos_nine, len_mem ; *9
    DivBCD  a,len_a,sign_a,pos_a, five,len_five,sign_five,pos_five, len_mem ; /5
    AddBCD  a,len_a,sign_a,pos_a, thirty_two,len_thirty_two,sign_thirty_two,pos_thirty_two, len_mem ; +32

    ; copy local sign_a into remote pointer
    local_byte2ptr sign_a, bp+18

    ; copy local pos_a into remote pointer
    local_word2ptr pos_a, bp+14

    ; copy local len_a into remote pointer
    local_word2ptr len_a, bp+10

    ; copy local mem into remote pointer
    local_mem2ptr a, bp+6, len_mem

    pop si
    pop ds
    pop es
    pop bp
    ret
_CF endp

_end_:
    mov     ax,4c00h
    int     21h
end
