#include <sys/regdef.h>
.eqv FRAME_SIZE, 32
.eqv O_a, 32
.eqv O_i, 36
.eqv O_j, 40
.eqv O_regla, 44 
.eqv O_N, 48
.eqv GP, 28
.eqv FP, 24
.eqv CELL, 20
.eqv C, 16
.eqv L, 12
.eqv R, 8
.eqv TO_SHIFT, 4
.eqv MASK, 0

.text
.align 2
/*
unsigned char proximo(unsigned char* a,
                      unsigned int i, unsigned int j
                      unsigned char regla, unsigned int N);
*/
                          
.ent    proximo
.globl  proximo

proximo:
    subu    $sp, $sp, FRAME_SIZE
    sw      $gp, GP($sp)
    sw      $fp, FP($sp)

    move    $fp, $sp

    sw      $a0, O_a($fp) # matriz a
    sw      $a1, O_i($fp) # fila i
    sw      $a2, O_j($fp) # col j
    sb      $a3, O_regla($fp) # regla -> 1 byte
    lw      $t0, O_N($fp) # N esta guardado en el aba del caller

    multu   $zero, $zero  # nukeamos lo y hi
    multu   $a1, $t0      # i * N
    mflo    $t1           # low en t1 
    mfhi    $t2           # hi en t2 

    bne     $t2, $zero, overflow  # checkeamos qeu la multiplicacion no haya dado of

    addu    $t1, $t1, $a2 # j + i * N -> lo guardamos en CELL 
    sw      $t1, CELL($fp) # nos guardamos la variable -> indexa en el array en c

    addu    $t2, $a0, $t1 # &a[j + i * N]
    lbu     $t3, 0($t2)   # t3 = a[j + i * N] loadeo un byte sin signo (unsigned char)
    sb      $t3, C($fp)   # c = a[j + i * N]  guardo un byte

    subu    $t3, $t0, 1   # t3 = N-1

    beq     $a2, $zero, first_cell  # if(!j) 
    nop

    beq     $a2, $t3, last_cell
    nop

    b       no_border


# if(!j)
first_cell:
    addu    $t3, $t1, $t3  # t3 = j + i * N + N - 1
    addu    $t3, $t3, $t0  # t3 = &a[j + i * N + N - 1]
    lbu     $t4, 0($t3)    # t4 = a[j + i * N + N - 1]
    sb      $t4, L($fp)    # l = a[j + i * N + N - 1]

    addiu   $t3, $t1, 1    # t3 = j + i * N + 1
    addu    $t3, $t3, $t0   # t3 = &a[j + i * N + 1]
    lbu     $t4, 0($t3)
    sb      $t4, R($fp)

    b       shift_seg

# else if(j == N - 1)
last_cell:
    subu    $t2, $t1, 1   # t2 = j + i * N - 1
    
    addu    $t4, $a0, $t2 # t4 = &a[j + i * N - 1]
    lbu     $t5, 0($t4)   # t5 = a[j + i * N - 1]
    sb      $t5, L($fp)   # l = a[j + i * N - 1]

    negu    $t3           # t3 = -N + 1
    addu    $t1, $t1, $t3 # t1 = j + i * N - N + 1
    addu    $t1, $t1, $t0 # t1 = &a[j + i * N - N + 1]
    lbu     $t4, 0($t1)   # t4 = a[j + i * N - N + 1]
    sb      $t4, R($fp)

    b       shift_seg

# else 
no_border:
    subu    $t1, $t1, 1   # t1 = j + i * N - 1
    
    addu    $t3, $a0, $t1 # t3 = &a[j + i * N - 1]
    lbu     $t4, 0($t3)   # t4 = a[j + i * N - 1]
    sb      $t4, L($fp)   # l = a[j + i * N - 1]

    addiu   $t1, $t1, 2   # t1 = j + i * N + 1
    addu    $t3, $a0, $t1 # t3 = &a[j + i * N + 1]
    lbu     $t4, 0($t3)   # t4 = a[j + i * N + 1]
    sb      $t4, R($fp)   # r = a[j + i * N - 1]

    b       shift_seg


shift_seg:
    lbu     $t0, L($fp)
    lbu     $t1, C($fp)
    lbu     $t2, R($fp)
    sll     $t0, $t0, 2   # t0 = l << 2
    sll     $t1, $t1, 1   # t1 = c << 1
    or      $t3, $t0, $t1 # t3 = l | c
    or      $t3, $t3, $t2 # t3 = l | c | r
    sb      $t3, TO_SHIFT($fp) # to_shift = l | c | r
    li      $t4, 1
    sllv    $t4, $t4, $t3 # t4 = 0x1 << to_shift
    sb      $t4, MASK($fp) # mask = 0x1 << to_shift
    b       and_seg


and_seg:
    lbu     $t0, O_regla($fp)   # t0 = regla
    lbu     $t1, MASK($fp)      # t1 = mask
    and     $t2, $t0, $t1
    sltu    $v0, $zero, $t2     # v0 == 1 si 0 < regla & mask sino 0
    b       proximo_end 

proximo_end:
    lw      $fp, FP($sp)
    lw      $gp, GP($gp)
    addiu   $sp, $sp, FRAME_SIZE 
    jr      $ra


overflow:
    # handle

.end proximo