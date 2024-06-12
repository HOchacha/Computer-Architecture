    .text
    .globl main:
main:
    addiu $sp, $sp, -24
    sw $fp, 20($sp)
    move $fp, $sp
    sw $zero, 8($fp)
    sw $zero, 12($fp)
    sw $zero, 8($fp)
    j  foo + 44
    nop
    lw $v1, 12($fp)
    lw $v0, 8($fp)
    nop
    addiu $v0, $v0, 1
    sw $v0, 8($fp)
    lw $v0, 8($fp)
    nop
    slti $v0, $v0, 101
    bnez $v0, 20
    nop
    lw
