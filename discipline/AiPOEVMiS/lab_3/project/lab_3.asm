;; Copy memory contents from buffer_from
;; to buffer_to with length len
CpMem   macro buffer_to,buffer_from, len
    lea     si, buffer_from
    lea     di, buffer_to
    mov     cx, len
    call    CpMemp
    endm
        
;; Create new file
;; if already exists, truncate it
;; Put in f_handle new file handler
NewFile macro f_name,f_handle
    mov     ah, 3ch
    mov     cx, 0
    lea     dx, f_name     
    int     21h
    mov     f_handle, ax    
    endm

;; Open file in read/write mode
;; Put in f_handle new file handler
OpenFile macro f_name,f_handle
    mov     ah, 3dh
    mov     al, 2
    lea     dx, f_name
    int     21h
    mov     f_handle, ax    
    endm
        
;; Close file with file_handle       
CloseFile macro f_handle
    push    bx
    mov     ah, 3eh
    mov     bx, f_handle
    int     21h
    pop     bx
    endm

ReadFile  macro f_handle,len_read, buffer,len_buffer
    local   _err_,_end_
        
    mov     ah, 3fh
    mov     bx, f_handle
    lea     dx, buffer
    mov     cx, len_buffer
    int     21h

    jc      _err_               ; read error
    mov     len_read, ax
    jmp     _end_
        
_err_:  
    mov     len_read, 0

_end_:  
    endm
        
;; Write string to file using f_handle
OutFStr macro   f_handle, str,len_str
    mov     ah, 40h
    mov     bx, f_handle
    mov     cx, len_str
    mov     dx, offset str
    int     21h
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

;; Write result header to file
OutFResMsg macro f_res_handle, f_1,len_f_1, f_2,len_f_2, f_3,len_f_3
    OutFStr  f_res_handle, f_1, len_f_1
    OutFStr  f_res_handle, msg_and, len_msg_and
    
    OutFStr  f_res_handle, f_2, len_f_2
    OutFStr  f_res_handle, msg_and, len_msg_and

    OutFStr  f_res_handle, f_3, len_f_3
    OutFStr  f_res_handle, colon, len_colon
    OutFStr  f_res_handle, newline, len_newline

    endm
    
;; Put in buffer_res common part of buffer_1 and buffer_2
;; buffer_1 --- memory (first operand)
;; len_buffer_1 --- length of essential part in buffer_1
;; 
;; buffer_2 --- memory (second operand)
;; len_buffer_2 --- length of essential part in buffer_2
;; 
;; buffer_res --- memory used to store result
;; len_res --- length of result
;; max_size --- size of buffers        
BufAND   macro buffer_1,len_buffer_1, buffer_2,len_buffer_2, buffer_res,len_buffer_res, max_size
    local   _loop_,_next_,_store_,_end_       

    lea     bx, buffer_1

    mov     dx, 0               ; length of result
    cld
_loop_:
    mov     al,[bx]
    lea     di, buffer_2
    mov     cx, len_buffer_2
    
    repne   scasb
    cmp     cx, 0    
    je      _next_

    ;; check, if buffer_tmp is empty
    cmp     dx, 0
    je      _store_
    ;; else check,
    ;; if this value already exists in buffer_tmp 
    lea     di, buffer_res
    mov     cx, dx              ; cx = dx + 1
    inc     cx
    repne   scasb
    cmp     cx, 0
    jg      _next_

_store_:
    ;; if not, then store result        
    lea     di, buffer_res
    add     di, dx
    stosb
    inc     dx

_next_: 
    inc     bx        

    ;; check if it's end of buffer_1
    mov     cx, bx
    sub     cx, offset buffer_1
    cmp     cx, len_buffer_1
    jl      _loop_
        
_end_:
    mov     len_buffer_res, dx
    endm

;; Stores common part of buffer_1, buffer_2 and buffer_3 to buffer_1
Buf3AND macro buffer_1,len_buffer_1, buffer_2,len_buffer_2, buffer_3,len_buffer_3, buffer_res,len_buffer_res, max_size
    push    dx

    mov     dx, len_buffer_1
    mov     len_buffer_tmp, dx
    CpMem   buffer_tmp, buffer_1, max_size
    BufAND  buffer_tmp,len_buffer_tmp, buffer_2,len_buffer_2, buffer_res,len_buffer_res, max_size

    mov     dx, len_buffer_res
    mov     len_buffer_tmp, dx
    CpMem   buffer_tmp, buffer_res, max_size
    BufAND  buffer_tmp,len_buffer_res, buffer_3,len_buffer_3, buffer_res,len_buffer_res, max_size

    pop     dx
    endm
    
stk     segment stack
stk     ends

data    segment
CR      equ     0Dh
LF      equ     0Ah
EOS     equ     '$'
len_buffer  equ     512
        
f_a         db      'C:\input\a.txt',00
len_f_a     dw      $-f_a-1
f_a_handle  dw      0
        
f_b         db      'C:\input\b.txt',00
len_f_b     dw      $-f_b-1
f_b_handle  dw      0
        
f_c         db      'C:\input\c.txt',00
len_f_c     dw      $-f_c-1
f_c_handle  dw      0
       
f_d         db      'C:\input\d.txt',00
len_f_d     dw      $-f_d-1   
f_d_handle  dw      0        

f_res       db      'C:\output\res.txt',00        
f_res_handle  dw    0        
    
buffer_1    db      len_buffer dup(?)        
read_1      dw      0

buffer_2    db      len_buffer dup(?)        
read_2      dw      0

buffer_3    db      len_buffer dup(?)        
read_3      dw      0

buffer_4    db      len_buffer dup(?)        
read_4      dw      0

buffer_res          db      len_buffer dup(?)
len_buffer_res      dw      0

buffer_tmp          db      len_buffer dup(?)    
len_buffer_tmp      dw      0
    
msg_and             db      ' && '
len_msg_and         dw      $-msg_and    

colon           db      ':'
len_colon       dw      $-colon
    
len_newline equ      2        
newline     db       CR,LF,EOS
data    ends

code    segment
.386
assume	    cs:code,ds:data,es:data

;; Send bytes from si to di cx times
CpMemp proc
    cld
rep movsb
    ret
    endp
    
main    proc
        
mov     ax, data
mov     ds, ax
mov     es, ax
        
OpenFile f_a,f_a_handle        
ReadFile f_a_handle,read_1, buffer_1,len_buffer

OpenFile f_b,f_b_handle        
ReadFile f_b_handle,read_2, buffer_2,len_buffer

OpenFile f_c,f_c_handle
ReadFile f_c_handle,read_3, buffer_3,len_buffer    

OpenFile f_d,f_d_handle
ReadFile f_d_handle,read_4, buffer_4,len_buffer    

NewFile  f_res,f_res_handle

;; a & b & c
Buf3AND     buffer_1,read_1, buffer_2,read_2, buffer_3,read_3, buffer_res,len_buffer_res, len_buffer    
OutFResMsg  f_res_handle, f_a,len_f_a, f_b, len_f_b, f_c,len_f_c
OutFStr     f_res_handle, buffer_res, len_buffer_res
OutFStr     f_res_handle, newline, len_newline
OutFStr     f_res_handle, newline, len_newline
    
;; b & c & d
Buf3AND     buffer_2,read_2, buffer_3,read_3, buffer_4,read_4, buffer_res,len_buffer_res, len_buffer    
OutFResMsg  f_res_handle, f_b,len_f_b, f_c, len_f_c, f_d,len_f_d
OutFStr     f_res_handle, buffer_res, len_buffer_res
OutFStr     f_res_handle, newline, len_newline    
OutFStr     f_res_handle, newline, len_newline

;; a & c & d
Buf3AND     buffer_1,read_1, buffer_3,read_3, buffer_4,read_4, buffer_res,len_buffer_res, len_buffer    
OutFResMsg  f_res_handle, f_a,len_f_a, f_c, len_f_c, f_d,len_f_d
OutFStr     f_res_handle, buffer_res, len_buffer_res
OutFStr     f_res_handle, newline, len_newline    
OutFStr     f_res_handle, newline, len_newline

;; a & b & d
Buf3AND     buffer_1,read_1, buffer_2,read_2, buffer_4,read_4, buffer_res,len_buffer_res, len_buffer    
OutFResMsg  f_res_handle, f_a,len_f_a, f_b, len_f_b, f_d,len_f_d
OutFStr     f_res_handle, buffer_res, len_buffer_res
OutFStr     f_res_handle, newline, len_newline    
OutFStr     f_res_handle, newline, len_newline
    
mov	    ah,4ch
int	    21h
main	endp
        
code    ends
end     main
