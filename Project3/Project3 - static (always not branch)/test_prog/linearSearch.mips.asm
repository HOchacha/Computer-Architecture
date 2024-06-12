linearSearch.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <main>:
   0:   27bdffa8        addiu   sp,sp,-88
   4:   afbf0054        sw      ra,84(sp)
   8:   afbe0050        sw      s8,80(sp)
   c:   03a0f025        move    s8,sp
  10:   3c1c0000        lui     gp,0x0
  14:   279c0000        addiu   gp,gp,0
  18:   afbc0010        sw      gp,16(sp)           // gp의 메모리 저장 주소는 16(sp)
  1c:   8f820000        lw      v0,0(gp)            // gp의 값 불러옴
  20:   8c420000        lw      v0,0(v0)            // v0 위치에 있는
  24:   afc2004c        sw      v0,76(s8)
  28:   3c020000        lui     v0,0x0
  2c:   27c40024        addiu   a0,s8,36
  30:   24420000        addiu   v0,v0,0
  34:   24030028        li      v1,40
  38:   00603025        move    a2,v1
  3c:   00402825        move    a1,v0
  40:   8f820000        lw      v0,0(gp)
  44:   0040c825        move    t9,v0
  48:   0320f809        jalr    t9
  4c:   00000000        nop
  50:   8fdc0010        lw      gp,16(s8)
  54:   24020003        li      v0,3
  58:   afc20020        sw      v0,32(s8)
  5c:   afc00018        sw      zero,24(s8)
  60:   afc0001c        sw      zero,28(s8)
  64:   1000000e        b       a0 <main+0xa0>
  68:   00000000        nop
  6c:   8fc2001c        lw      v0,28(s8)
  70:   00021080        sll     v0,v0,0x2
  74:   27c30050        addiu   v1,s8,80
  78:   00621021        addu    v0,v1,v0
  7c:   8c42ffd4        lw      v0,-44(v0)
  80:   8fc30020        lw      v1,32(s8)
  84:   14620003        bne     v1,v0,94 <main+0x94>
  88:   00000000        nop
  8c:   8fc20020        lw      v0,32(s8)
  90:   afc20018        sw      v0,24(s8)
  94:   8fc2001c        lw      v0,28(s8)
  98:   24420001        addiu   v0,v0,1
  9c:   afc2001c        sw      v0,28(s8)
  a0:   8fc2001c        lw      v0,28(s8)
  a4:   2842000a        slti    v0,v0,10
  a8:   1440fff0        bnez    v0,6c <main+0x6c>
  ac:   00000000        nop
  b0:   8fc20018        lw      v0,24(s8)
  b4:   00402025        move    a0,v0
  b8:   8f820000        lw      v0,0(gp)
  bc:   8fc3004c        lw      v1,76(s8)
  c0:   8c420000        lw      v0,0(v0)
  c4:   10620005        beq     v1,v0,dc <main+0xdc>
  c8:   00000000        nop
  cc:   8f820000        lw      v0,0(gp)
  d0:   0040c825        move    t9,v0
  d4:   0320f809        jalr    t9
  d8:   00000000        nop
  dc:   00801025        move    v0,a0
  e0:   03c0e825        move    sp,s8
  e4:   8fbf0054        lw      ra,84(sp)
  e8:   8fbe0050        lw      s8,80(sp)
  ec:   27bd0058        addiu   sp,sp,88
  f0:   03e00008        jr      ra
  f4:   00000000        nop
        ...