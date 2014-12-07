global  merge_raw_pixels:function
global  end_MMX:function
    
segment .text
merge_raw_pixels:
    
.process:    
    movq        mm0, [rdi]
    movq        mm1, [rsi]
    pmaxub      mm0, mm1
    movq        [rdx], mm0

    add         rdi, 8
    add         rsi, 8
    add         rdx, 8
    
    sub         rcx, 2
    jrcxz       .end
    jmp         .process
    
.end:    
    ret

end_MMX:
    emms
    ret
