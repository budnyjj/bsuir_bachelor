.model small
.stack
.data
CR equ 0Dh
LF equ 0Ah
EOS equ '$'
Message db 'Hello world!', CR, LF, EOS

.code
begin:
        mov ax, @data
        mov ds, ax
        mov ah, 9
        mov dx, 00h ; offset Message
        int 21h
        mov ah, 4ch
        int 21h
end begin
