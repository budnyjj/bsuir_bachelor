Init	macro   mem1,len1,mem2,len2
    local _assign_len1_,_assign_len2_,_end_
;макрос для инициализации адресных регистров        
    push    ax
    push    dx
        
    mov     ax, len1            ; ax = len1-1+offset mem1
    sub     ax,1
    add     ax, offset mem1
    mov	    di,ax
        
    mov     dx, len2            ; dx = len2-1+offset mem2
    sub     dx, 1
    add     dx, offset mem2      
	mov	    si,dx

    mov     ax, len1
    cmp     ax, len2             ; в cx --- длина наименьшего
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

LenBCD      macro mem,len
; помещает в ax длину значимой части BCD числа
    mov si, offset mem
    mov cx, len
    call LenBCDp
    endm
        
AlignBCD    macro mem,len,max_size
; выравнивание положения BCD-числа
; по правой границе ячейки
; и обнуление старших разрядов
    Init    mem,max_size,mem,len
    call    CpBCDp

    mov     di, offset mem
    ;; cx = max_size - len
    mov     cx, max_size
    sub     cx, len    
    call    SetZerop
    endm

CpBCD   macro   mem1,mem2,max_size
; copy mem2 to mem1
    Init mem1,max_size,mem2,max_size   
    call CpBCDp
    endm

AddBCD	macro	mem1,sign1, mem2,sign2, max_size,len_mem1
        local _mem1_gz_,_mem1_gz_mem2_gz_,_mem1_gz_mem2_lz_,_mem1_lz_,_mem1_lz_mem2_gz_,_mem1_lz_mem2_lz_,_end_
;сложение BCD-чисел
;результат помещается в первый операнд
; mem1 -- память (первый операнд)
; sign1 -- знак первого операнда
;
; mem2 -- память (второй операнд)
; sign2 -- знак второго операнда
;
; max_size  -- максимальный размер mem1 и mem2
; len_mem1 -- длина значимой части mem1 (результата)
    mov al, sign1
    cmp al, 0
    je _mem1_gz_
    jmp _mem1_lz_
        
_mem1_gz_:                      ; mem1 > 0
    mov al, sign2
    cmp al, 0
    je _mem1_gz_mem2_gz_
    jmp _mem1_gz_mem2_lz_
        
_mem1_lz_:                      ; mem1 < 0
    mov al, sign2
    cmp al, 0
    je _mem1_lz_mem2_gz_
    jmp _mem1_lz_mem2_lz_

_mem1_gz_mem2_gz_:
;; mem1 > 0, mem2 > 0
;; mem1 = mem1 + mem2
    Init	mem1,max_size,mem2,max_size
	call	AddBCDp
    jmp _end_

_mem1_gz_mem2_lz_:
;; mem1 > 0, mem2 < 0
;;  
    jmp _end_
        
_mem1_lz_mem2_gz_:
;; mem1 < 0, mem2 > 0
    
    jmp _end_

_mem1_lz_mem2_lz_:
;; mem1 < 0, mem2 < 0
        
    jmp _end_
        

_end_:  
    LenBCD  mem1,max_size
    mov     len_mem1,ax
	endm
        
SubBCD	macro	mem1,mem2,max_size,len_mem1
;вычитание BCD-чисел
;результат помещается в первый операнд
	Init	mem1,max_size,mem2,max_size
	call	SubBCDp

    LenBCD  mem1,max_size
    mov     len_mem1,ax    
	endm
        
MulBCD	macro	mem1,mem2,max_size,len_mem1
;умножение BCD-чисел
;результат:
;младшая часть помещается в первый операнд,
;старшая часть - во второй операнд
    CpBCD   mem_overhead,mem2,max_size ; copy mem2 number to temporary place

    Init	mem1,max_size,mem_overhead,max_size
	call	MulBCDp

    LenBCD  mem1,max_size
    mov     len_mem1,ax
	endm

DivBCD	macro	mem1,mem2,max_size,len_mem1
; деление BCD-чисел
; результат:
; частное помещается в первый операнд
;остаток - во второй операнд
; mem1 -- память (первый операнд)
; mem2 -- память (второй операнд)
; max_size  -- максимальный размер mem1 и mem2
; len_mem1 -- длина значимой части mem1 (результата)
    CpBCD   mem_overhead,mem2,max_size ; copy mem2 number to temporary place
	mov	    di,offset mem1
	mov	    si,offset mem_overhead
	mov	    cx,max_size
	call	DivBCDp

    LenBCD  mem1, max_size
    mov     len_mem1, ax    
	endm
        
OutChar macro char
;; print single character
        push ax
        push dx
        mov ah, 02h           
	    mov dl,char
	    int 21h
	    pop dx
        pop ax
        endm

OutStr macro str
;; print characater string
        push ax
        push dx
        mov ah, 09h
        mov dx, offset str
        int 21h
        pop dx
        pop ax
        endm
        
OutBCD	macro	mem,max_size,len,pos_dot,sign
        local _out_minus_,_out_bcd_,_out_integer_part_,_out_dot_,_out_rest_part_
; print BCD-number to screen with dot and sign
    push    ax
        
    ; print minus if sign == 1
    mov al, sign
    cmp al, 1
    je _out_minus_
    jmp _out_bcd_

_out_minus_:
    mov al, 45
    OutChar al
    jmp _out_bcd_

_out_bcd_:      
    mov ax, pos_dot
    cmp ax, 0                   ; only integer part
    je _out_rest_part_
    jmp _out_integer_part_
        
_out_integer_part_:     
;; si = (offset mem) + (max_size - len)
;; cx = pos_dot
    mov     ax, max_size
    sub     ax, len
    add     ax, offset mem
    mov     si, ax              
    mov     cx, pos_dot    
	call	OutBCDp
    jmp _out_dot_
        
_out_dot_:
    mov al, 46
    OutChar al
    jmp _out_rest_part_

_out_rest_part_:
;; si = (offset mem) + (max_size - len + pos_dot)        
;; cx = len - pos_dot                        
    mov ax, max_size
    sub ax, len
    add ax, pos_dot
    add ax, offset mem
    mov si, ax
    mov cx, len
    sub cx, pos_dot
    call OutBCDp

    OutStr  newline
    pop     ax
        
	endm

InChar  macro
; Input single character to al
        mov	    ah,08h
        int	    21h
        endm
        
InBCD	macro	mem,max_size,len_read,pos_dot,sign
; ввод BCD-числа с экрана в текущую позицию
; mem -- участок памяти для хранения
; max_size -- максимальная длина ввода
; len_read -- область памяти для сохранения числа считанных байт
; pos_dot -- область памяти для хранения похиции запятой
; sign -- облать памяти для хранения знака
	mov	di,offset mem
	mov	cx,max_size
	call	InBCDp
    mov     len_read, ax
    mov     pos_dot, bx
    mov     sign, dl
    ; выравнивание по правой границе
    AlignBCD mem,len_read,max_size
	endm

OutMenu macro
    OutStr  slct_prmpt

    OutStr  var_cf
    OutStr  var_fc
    OutStr  var_quit
    OutStr  newline
    endm
        
stk segment stack
stk ends
        
data	segment
;для операций умножения и деления необходим буфер
;размер буфера не менее 3*SIZE,
;где SIZE-размер чисел
CR equ 0Dh
LF equ 0Ah
EOS equ '$'
len_num equ 10                      ; максимальная длина числа
len_size    equ  2                   ; максимальная длина полей размера

newline     db  CR, LF, EOS        
prg_desc_1  db  'This program can be used to convert temperature', CR, LF, EOS
prg_desc_2  db  'beetween Celsius and Farengheit scales.', CR, LF, EOS
slct_prmpt  db  'Select direction of convertation (1,2), or press q to exit', CR, LF, EOS  

var_cf      db  '1) Convert Celsius to Farengheit', CR, LF, EOS
var_fc      db  '2) Convert Farengheit to Celsius', CR, LF, EOS
var_quit    db  'q) Quit from program', CR, LF, EOS

cf_prpmt    db  'Input temperature level by Celsius scale and press <Enter>: ', EOS
cf_answer   db  'Temperature level by Farengheit scale is: ', EOS

fc_prpmt    db  'Input temperature level by Farengheit scale and press <Enter>: ', EOS
fc_answer   db  'Temperature level by Celsius scale is: ', EOS

        
a	        db	len_num dup(?)         ; вводимое пользователем значение
len_a       dw  0                      ; длина значимой части числа
pos_a       dw  0                      ; позиция запятой        
sign_a      db  0                      ; знак (0 -- плюс, 1 -- минус)
        
b           db  0,0,0,0,0,0,0,0,3,2    ; добавка
len_b       dw  0                      ; длина значимой части числа
pos_b       dw  0                      ; позиция запятой
sign_b      db  0                      ; знак (0 -- плюс, 1 -- минус)
        
k1          db  0,0,0,0,0,0,0,0,0,5    ; коэффициент умножения
        
k2          db   0,0,0,0,0,0,0,0,0,9    ; коэффициент умножения

mem_overhead db 0,0,0,0,0,0,0,0,0,0   ; дополнительная область для операций умножения и деления 
        
buffer      db  512 dup(?)
;; b	db	0,0,0,0,0,3,8,9,7,8
;; c	db	2,8,0,1,0,0,1,9,8,3
;; d	db	9,9,3,3,3,3,3,3,3,3
data	    ends

code	    segment
.386
assume	    cs:code,ds:data,es:data
CpBCDp proc
; процедура побайтового копирования BCD-числа
    std
rep movsb                       ; пересылаем байты из si в di
    ret
    endp
        
SetZerop proc
; заполняет нулями указанный участок памяти
; в cx -- длина участка
    cld
    push ax
    mov al, 0
rep stosb                       ; заполняем нулями
    pop ax
    ret
    endp

LenBCDp proc
; подсчитывает число значимых цифр в BCD-числе
; результат помещает в ax
    cld
       
_len_next_:
    lodsb
    cmp al, 0
    je _len_dec_
    jmp _len_end_               ; встретили первую значимую цифру
        
_len_dec_:
    jmp _len_loop_
        
_len_loop_: 
    loop _len_next_

_len_end_:  
    mov ax, cx
    ret
    endp
        
AddBCDp	proc
;процедура сложения BCD-чисел
	push	ax	;сохраним изменяемые регистры
	push	di
	push	si
	push	cx
	std		;начинаем с младших разрядов
	clc		;обнулим значение переноса
_add_:
	lodsb		;возьмем очередную цифру
	adc	al,[di]	;сложение с учетом переноса
	aaa		;выровняем в формат BCD-чисел
	stosb		;сохраним результат
	loop	_add_
	pop	cx	;восстановим регистры
	pop	si
	pop	di
	pop	ax
	ret
	endp
        
SubBCDp	    proc
;процедура вычитания BCD-чисел
	push	ax	;сохраним изменяемые регистры
	push	di
	push	si
	push	cx
	std		;начинаем с младших разрядов
	clc		;обнулим значение переноса
_sub_:
	lodsb		;возьмем очередную цифру
	sbb	    [di],al	;вычитание с учетом переноса
	mov	    al,[di]
	aas		;выровняем в формат BCD-чисел
	stosb		;сохраним результат
	loop	_sub_
	pop	    cx	;восстановим регистры
	pop	    si
	pop	    di
	pop	    ax
	ret
	endp

MulBCDp	proc
;процедура умножения BCD-чисел
	push	ax	;сохраним изменяемые регистры
	push	bx
	push	di
	push	si
	push	cx
	std		;начинаем с младших разрядов
	mov	    bx,offset buffer
	mov	    dh,cl	;запомним исходное
			;состояние счетчика
	push	bx
;заполним буфер результата нулями
	shl	    cx,1	;необходим размер 2*SIZE
	xor	    al,al	;символ-заполнитель = 0
_null_:
	mov	    [bx],al
	inc	    bx
	loop	_null_
	mov	    cl,dh
	pop	    bx
;умножение будем проводить "столбиком"
;цикл по всем цифрам первого операнда
_mul_o_:
	xor	    dl,dl	;обнулим значение переноса
	push	cx
	push	bx	;сохраним некоторые регистры
	push	si
	mov	    cl,dh	;восстановим исходное
			;значение счетчика
;цикл по всем цифрам второго операнда
_mul_i_:
	lodsb		;возьмем очередную цифру
	mul	    byte ptr [di]	;умножим
	aam		;коррекция результата
	add	    al,dl	;учтем перенос
	aaa
	add	    al,[bx]	;сложим с результатом
			        ;предыдущего умножения
	aaa
	mov	    dl,ah	;запомним значение переноса
	xor	    ah,ah
	mov	    [bx],al	;сохраним результат
	inc	    bx
	loop	_mul_i_
	mov	    [bx],dl
	pop	    si	;восстановим регистры
	pop	    bx
	inc	    bx
	dec	    di	;перейдем к следующей
			;цифре второго операнда
	pop	    cx
	loop	_mul_o_
	mov	    cl,dh	;восстановим исходное
			;значение счетчика
	sub	    bx,cx	;сместим bx на младшую
			;часть результата
	add	    di,cx
;занесем результат (мл. часть) в первый операнд
_move_l_:
	mov	    al,[bx]
	inc	    bx
	stosb
	loop	_move_l_
	mov	    cl,dh
	mov	    di,si
;занесем результат (ст. часть) во второй операнд
_move_h_:
	mov	    al,[bx]
	inc	    bx
	stosb
	loop	_move_h_
	pop	    cx	;восстановим регистры
	pop	    si
	pop	    di
	pop	    bx
	pop	    ax
	ret
	endp

SubInvBCDp	proc
;вспомогательная процедура для операции деления
;производит вызов процедуры вычитания
;без начальной инициализации
	push	si
	push	di
	add	si,cx
	dec	si
	add	di,cx
	dec	di
	call	SubBCDp
	pop	di
	pop	si
	ret
	ENDP
        
CmpBCDp	proc
;процедура сравнения BCD-чисел
;CF=0, если [si]>[di], иначе CF=1
	push	ax
	push	di
	push	si
	push	cx
	cld
_cmp_:
	lodsb
	cmp	al,[di]
	jl	_less_
	jg	_greater_
	inc	di
	loop	_cmp_
_less_:
	stc
	jc	_cmp_q_
_greater_:
	clc
_cmp_q_:
	pop	cx
	pop	si
	pop	di
	pop	ax
	ret
	endp
        
PrepareForDiv	proc
;процедура инициализации буфера
;для операции деления
	cld
;0,[di] -> buffer (первый операнд в буфер)
	push	di
	push	si
	push	di
	pop	si
	mov	di,offset buffer
	xor	al,al
	push	cx
	stosb
	rep	movsb
;0,[si] -> buffer (второй операнд в буфер)
	pop	cx
	stosb
	pop	si
	push	cx
;для начала найдем первую значащую цифру
_find_:
	lodsb
	dec	cx
	cmp	al,0
	je	_find_
	dec	si
	inc	cx
	mov	dx,cx
	rep movsb
	pop	cx
	push	cx
; 0,0..0 -> buffer (очистить место для результата в буфере)
	xor	al,al
	rep	stosb
;переназначение регистров
	mov	di,offset buffer
	pop	cx
	mov	si,di
	inc	cx
	add	si,cx
	pop	bx
	ret
	endp
        
DivBCDp	proc
;процедура деления BCD-чисел
	push	ax	;сохраним изменяемые регистры
	push	bx
	push	di
	push	si
	push	cx
	push	di
	call	PrepareForDiv	;подготовим буфер
	xor	ax,ax	;в al - очередная цифра результата
			;в ah - количество цифр в результате
	call	CmpBCDp
	jnc	_next_1_
_div_:
	call	CmpBCDp
	jnc	_next_
	inc	al
	call	SubInvBCDp
	jmp	_div_
_next_:
	mov	[bx],al	;сохраним очередную цифру
	inc	bx	;уменьшим порядок делимого
_next_1_:
	inc	di
	dec	cx
	xor	al,al
	inc	ah
	cmp	cx,dx	;сравним порядки делимого и делителя
	jne	_div_
	dec	ah
	pop	di
	pop	cx
	push	cx
;пересылаем результат из буфера в операнды
	mov	si,di
	add	di,cx
	push	cx
	mov	cl,ah
	add	si,cx
	dec	si
	dec	di
	std
rep	movsb
	pop	cx
	sub	cl,ah
	xor	al,al
rep	stosb
	pop	cx
	pop	si
	push	si
	push	cx
	mov	di,si
	mov	si,offset buffer
	inc	si
	cld
rep	movsb
	pop	cx	;восстановим регистры
	pop	si
	pop	di
	pop	bx
	pop	ax
	ret
	endp
        
OutBCDp	proc
;процедура вывода BCD-чисел на экран
	mov	    ah,06h
	cld
_out_:
	lodsb
	or	    al,30h
	mov	    dl,al
	int	    21h
	loop	_out_
	ret
	endp

InBCDp	proc
; процедура ввода BCD-чисел с клавиатуры
; не учитывает ведущие нули
; помещает в ax число успешно считанных цифр,
; помещает в bx число цифр до запятой,
; помещает в dl 0 или 1 в зависимости от знака
	cld 
    mov     dx, 0                   ; число считанных цифр
    mov     bx, 0                   ; число значимых цифр до запятой
    mov     si, 0
_in_:
    InChar
    cmp     al, 0                   ; extended keystroke
    je      _extended_
    cmp     al, 13                  ; enter
    je      _success_ 
    cmp     al, 113                 ; q
    je      _error_
    cmp     al, 81                  ; Q
    je      _error_
    cmp     al, 45                  ; got -
    je      _minus_
    cmp     al,46                   ; got .
    je      _dot_
    cmp     al, 30h                 ; got char with code <= 30h
    jl      _not_digit_
    cmp     al, 40h                 ; got char with code >= 40h
    jge     _not_digit_
    jmp     _digit_
        
_digit_:
    OutChar al
        
    sub	    al,30h
    stosb

    inc     dx
    jmp     _loop_

_loop_:
	loop	_in_
    jmp     _success_               ; goto success if cx = 0
        
_not_digit_:
    inc     cx
    jmp     _loop_

_minus_:
    inc     cx
        
    cmp     dx, 0                   ; ввод минуса только в начале числа   
    jne     _loop_

    OutChar al
    mov     si,1
    jmp     _loop_    

_dot_:
    inc     cx
    cmp     dx, 0                   ; запрет ввода точки перед числом
    je      _loop_
        
    cmp     bx, 0                   ; запрет ввода нескольких точек или запятых
    jne     _loop_

    OutChar al
    mov     bx, dx
    jmp     _loop_
        
_success_:
    mov     ax, dx
    mov     dx, si
    jmp     _exit_

_extended_:
    InChar
    jmp     _loop_
        
_error_:
    mov     ax, 0
    jmp     _exit_

_exit_:
    OutStr newline                  ; вывод новой строки
    ret
	endp
        
main	proc
	mov	    ax,data
	mov	    ds,ax
	mov	    es,ax

_begin_:        
    OutStr  prg_desc_1
    OutStr  prg_desc_2
    OutStr  newline

_main_menu_:    
    OutMenu

_main_menu_choose_variant_:     
    InChar                      ; Choose variant

    cmp al, 31h                  ; '1'
    je _cf_
    cmp al, 32h                  ; '2'
    je _fc_
    cmp al, 113                 ; q
    je _end_    
    cmp al, 81                 ; Q
    je _end_
    jmp _main_menu_choose_variant_
        
_cf_:                           ; Celsius to Farengheit
    OutStr  cf_prpmt

    InBCD   a,len_num,len_a,pos_a,sign_a
        
    cmp     len_a, 0            ; length of input is 0
    je      _main_menu_

    ;; DivBCD  a,k1,len_num,len_a  ; /5
   	;; MulBCD	a,k2,len_num,len_a  ; *9
    AddBCD   a,sign_a, b,sign_b, len_num,len_a  ; +32
        
    OutStr  cf_answer
    OutBCD  a,len_num,len_a,pos_a,sign_a
        
    OutStr  newline
    jmp     _main_menu_
        
_fc_:                            ; Farengheit to Celsius
    OutStr  fc_prpmt

    InBCD   a,len_num,len_a,pos_a,sign_a
        
    cmp     len_a, 0            ; length of input is 0
    je      _main_menu_

    SubBCD  a,b,len_num,len_a   ; -32 
    MulBCD  a,k1,len_num,len_a  ; *5
    DivBCD	a,k2,len_num,len_a  ; /9
        
    OutStr  fc_answer
    OutBCD  a,len_num,len_a,pos_a,sign_a
        
    OutStr  newline
    jmp     _main_menu_

_end_:  
	mov	    ax,4c00h
	int	    21h
    main	endp
code	ends
end	main
