.MODEL small

.STACK

.DATA
CR equ 0Dh
LF equ 0Ah
EOS equ '$'

DayOrNightMsg   db 'Is it a day or a night? (d/n) ', EOS
PartOfDayMsg    db CR, LF, 'Now later than 15:00? (y/n) ', EOS

ItIsNightMsg    db CR, LF, 'It is a night!', CR, LF, EOS

BeforeNoonMsg   db CR, LF, 'Now later than 12:00? (y/n) ', EOS
AfterNoonMsg    db CR, LF, 'Now later than 19:00? (y/n) ', EOS

BreakfastMsg    db CR, LF, 'The breakfast is ready!', CR, LF, EOS
LunchMsg        db CR, LF, 'The lunch is ready!', CR, LF, EOS
SupperMsg       db CR, LF, 'The supper is ready!', CR, LF, EOS
DinnerMsg       db CR, LF, 'The dinner is ready!', CR, LF, EOS

y_symbol        db 'y', CR, LF, EOS
n_symbol        db 'n', CR, LF, EOS
d_symbol        db 'd', CR, LF, EOS
q_symbol        db 'q', CR, LF, EOS

.CODE
start:
    mov ax, @data
    mov ds, ax
    mov dx, offset DayOrNightMsg
    call WriteMessage

day_or_night_char_input:
    mov ah, 07h
    int 21h

    cmp al, 'd'
    jz is_day

    cmp al, 'n'
    jz is_night

    cmp al, 'q'
    jz force_quit

    jnz day_or_night_char_input

force_quit:
    mov dx, offset q_symbol
    call WriteMessage
    call ExitProgram

; night branch
is_night:
    mov dx, offset n_symbol
    call WriteMessage

    mov dx, offset ItIsNightMsg
    call WriteMessage

    call ExitProgram

; day branch
is_day:
    mov dx, offset d_symbol
    call WriteMessage

    mov dx, offset PartOfDayMsg
    call WriteMessage

part_of_day_char_input:
    mov ah, 07h
    int 21h

    cmp al, 'n'
    jz before_noon_display_msg

    cmp al, 'y'
    jz after_noon_display_msg

    cmp al, 'q'
    jz force_quit

    jnz part_of_day_char_input

before_noon_display_msg:
    mov dx, offset n_symbol
    call WriteMessage

    mov dx, offset BeforeNoonMsg
    call WriteMessage

before_noon_char_input:
    mov ah, 07h
    int 21h

    cmp al, 'y'
    jz lunch

    cmp al, 'n'
    jz breakfast

    cmp al, 'q'
    jz force_quit

    jnz before_noon_char_input

after_noon_display_msg:
    mov dx, offset y_symbol
    call WriteMessage

    mov dx, offset AfterNoonMsg
    call WriteMessage

after_noon_char_input:
    mov ah, 07h
    int 21h

    cmp al, 'y'
    jz dinner

    cmp al, 'n'
    jz supper

    cmp al, 'q'
    jz force_quit

    jnz after_noon_char_input

breakfast:
    mov dx, offset n_symbol
    call WriteMessage

    mov dx, offset BreakfastMsg
    call WriteMessage
    call ExitProgram

lunch:
    mov dx, offset y_symbol
    call WriteMessage

    mov dx, offset LunchMsg
    call WriteMessage
    call ExitProgram

supper:
    mov dx, offset n_symbol
    call WriteMessage

    mov dx, offset SupperMsg
    call WriteMessage
    call ExitProgram

dinner:
    mov dx, offset y_symbol
    call WriteMessage

    mov dx, offset DinnerMsg
    call WriteMessage
    call ExitProgram

WriteMessage proc
    mov ah, 09h
    int 21h
    ret
WriteMessage endp

ExitProgram proc
    mov ah, 4Ch
    int 21h
    ret
ExitProgram endp

end start
