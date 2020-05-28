section .data
    const1 dq 2.0
    const2 dq 3.0
    const3 dq 0.0
    const4 dq -24.0
    
section .text
global f1
f1:
    push ebp
    mov ebp, esp
    
    finit
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    frndint
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    fsubp
    f2xm1
    fld1
    faddp
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    fxch
    fscale
    fxch
    fstp st0
    fld    qword[const1]
    faddp
    
    mov esp, ebp
    pop ebp
    ret
    
global f2
f2:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld1
    fchs
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
    
global f3
f3:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld1
    faddp
    fld qword[const1]
    fchs 
    fmulp
    fld qword[const2]
    fdivrp
    
    mov esp, ebp
    pop ebp
    ret
    
global f1p
f1p:
    push ebp
    mov ebp, esp
    
    finit
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    frndint
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    fsubp
    f2xm1
    fld1
    faddp
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    fxch
    fscale
    fxch
    fstp st0
    
    mov esp, ebp
    pop ebp
    ret
    
    global f2p
f2p:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld1
    fdiv
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
    
    global f3p
f3p:
    push ebp
    mov ebp, esp
    
    finit
    
    fld qword[const2]
    fld qword[const1]
    fdivp
    fchs
    
    mov esp, ebp
    pop ebp
    ret
    
global f1pp
f1pp:
    push ebp
    mov ebp, esp
    
    finit
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    frndint
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    fsubp
    f2xm1
    fld1
    faddp
    fld    qword[ebp + 8]
    fldl2e
    fmulp
    fxch
    fscale
    fxch
    fstp st0
    
    mov esp, ebp
    pop ebp
    ret
    
global f2pp
f2pp:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld qword[const1]
    fdiv
    fdiv
    fdivp
    fchs
    
    mov esp, ebp
    pop ebp
    ret
    
global f3pp
f3pp:
    push ebp 
    mov ebp, esp
    
    finit
    fld qword[const3]
    
    mov esp, ebp
    pop ebp
    ret
    
global f2p4
f2p4:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld qword[const4]
    fdiv
    fdiv
    fdiv
    fdiv
    fdivp
    fchs
    
    mov esp, ebp
    pop ebp
    ret