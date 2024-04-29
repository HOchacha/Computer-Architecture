.text
.global main
main:
    li $t0, 0x1234
    li $t1, 0x1151
    add $v0, $t0, $t1
    addu $v0, $t0, $t1
    addiu $v0, $t0, -0x34
    addi $v0, $t0, -0x34
    sub $v0, $t0, $t1
    subu $v0, $t0, $t1
    and $v0, $t0, $t1
    andi $v0, $t0, 0xff
    or  $v0, $t0, $t1
    ori $v0, $t0, 0xFF
    nor $v0, $t0, $t1
    lui $v0, 0x0001
    lw  $v0, 0($sp)
    sw  $v0, 0($sp)
    slt $v0, $t0, $t1
    slti $v0, $t0, 0xff
    sltiu $v0, $t0,0xff
    sll $v0, $t0, 2
    srl $v0, $t0, 2
    nop
    jr  $ra